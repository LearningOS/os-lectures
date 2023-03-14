# 2020-12-20 更新

* 说明了子进程机制；
* 在基础系统调用中，补充了 open/close/pipe 的相关说明；
* 将 kill 移动到拓展系统调用；
# 实现细节约定

* 以下 int/i32 均指有符号 32 位整数。（然而出于实现方便可以进行一些调整，比如将所有的返回值都调整为 64 位有符号整数 long long/i64）
# 子进程机制

当一个进程通过 exit 系统调用或者由于出错退出之后，它应当被标记为处于僵尸（Zombie）状态，此时可以尽可能多的回收资源，但不是全部。需要等待它的父进程在 waitpid 系统调用中 wait 到这个子进程的时候，该子进程的资源（包括进程控制块 PCB）才被全部回收。

一个进程 fork 出来的进程会成为它的子进程，一般来说它需要负责通过 waitpid 系统调用来回收子进程的资源。然而，如果一个进程在子进程还在运行的时候退出，它的所有子进程需要被转移到进程 initproc 下面。

在内核初始化之后，需要加载唯一的用户进程 initproc，参考实现如下：

```rust
#[no_mangle]
fn main() -> i32 {
    if fork() == 0 {
        exec("user_shell\0");
    } else {
        loop {
            let mut exit_code: i32 = 0;
            let pid = wait(&mut exit_code);
            if pid == -1 {
                yield_();
                continue;
            }
            println!(
                "[initproc] Released a zombie process, pid={}, exit_code={}",
                pid,
                exit_code,
            );
        }
    }
    0
}
```
可以看到它 fork 了一个子进程并运行用户终端 user_shell。它自身则是不断循环 wait，来回收那些被转移到它下面的子进程的资源。
# 基础系统调用接口

## open

syscall ID：56

功能：打开一个文件，并返回可以访问它的文件描述符。

C 接口：int open(char* path, unsigned int flags);

Rust 接口：fn open(path: *const u8, flags: u32);

参数：**fd**描述要打开的文件的文件名（简单起见，文件系统不需要支持目录，所有的文件都放在根目录 / 下），**flags**描述打开文件的标志，具体含义见备注。

返回值：如果出现了错误则返回 -1，否则返回可以访问给定文件的文件描述符。

可能的错误：文件不存在。

备注：在分配文件描述符的时候，总是会选取所有可能的文件描述符中编号最小的一个。参考 xv6，打开文件的 flags 支持以下几种：

* 如果 flags 为 0，则表示以只读模式*RDONLY*打开；
* 如果 flags 第 0 位被设置（0x001），表示以只写模式*WRONLY*打开；
* 如果 flags 第 1 位被设置（0x002），表示既可读又可写*RDWR*；
* 如果 flags 第 9 位被设置（0x200），表示允许创建文件*CREATE*，在找不到该文件的时候应创建文件；如果该文件已经存在则应该将该文件的大小归零；
* 如果 flags 第 10 位被设置（0x400），则在打开文件的时候应该将该文件的大小归零，也即*TRUNC*。
## close

syscall ID：57

功能：关闭一个文件。

C 接口：int close(int fd);

Rust 接口：fn close(fd: i32) -> i32;

参数：**fd**描述一个文件，可能是索引节点/管道/串口。

返回值：如果出现了错误则返回 -1，否则返回 0。

可能的错误：传入的文件描述符 fd 并未被打开。

## pipe

syscall ID：59

功能：建立一个管道，用于当前进程及其子进程之间的通信。

C 接口：int pipe(int pipefd[2]);

Rust 接口：fn pipe(pipefd: &mut [i32]) -> i32;

参数：**pipefd**描述一个大小为 2 的 fd 数组，前一项为管道输入端的 fd，后一项为管道输出端的 fd。

返回值：如果出现了错误则返回 -1，否则返回 0。

可能的错误：传入的地址 pipefd 不合法；

备注：在分配文件描述符的时候，总是会选取所有可能的文件描述符中编号最小的一个。

## read

syscall ID：63

功能：从文件中读取一段内容到内存中的缓冲区。

C 接口：int read(int fd, char *buf, int len);

Rust 接口： fn read(fd: i32, buf: *mut u8, len: i32) -> i32;

参数：**fd**描述当前进程需要访问的文件，**buf**表示保存文件中读到的数据的缓冲区的地址，**len**表示最大的读取字节数。

返回值：如果出现了错误则返回 -1，否则返回实际读到的字节数。

可能的错误：传入的**fd**不合法；

备注：该 syscall 的实现可能是阻塞的。

## write

syscall ID：64

功能：从内存中的缓冲区写入一段内容到文件。

C 接口：int write(int fd, char *buf, int len);

Rust 接口：fn write(fd: i32, buf: *mut u8, len: i32) -> i32;

参数：**fd**描述当前进程需要访问的文件，**buf**表示保存即将写入文件的数据的缓冲区的地址，**len**表示最大的写入字节数。

返回值：如果出现了错误则返回 -1，否则返回实际写入的字节数。

可能的错误：传入的**fd**不合法；

备注：该 syscall 的实现可能是阻塞的。

## exit

syscall ID：93

功能：退出当前进程。

C 接口：int exit(int status);

Rust 接口：fn exit(status: i32) -> i32;

参数：**status**描述当前进程的返回值，并应当由其父进程捕获到。

返回值：正常情况下应不会返回。请在调用 exit 之后加入 panic 语句来确保这一点。

可能的错误：触发了调用 exit 之后的 panic；

## sleep

syscall ID：101

功能：将当前进程休眠一段时间。

C 接口：int sleep(int n);

Rust 接口：fn sleep(n: i32) -> i32;

参数：**n**描述将当前进程休眠多少个时间单位，采用哪种时间单位待定，可选项：时间片个数/毫秒数/ CPU 时钟周期数，请帮忙确定。暂定为毫秒数。

返回值：总是返回 0。

可能的错误：无。

备注：该 syscall 的实现可能是阻塞的。

## yield

syscall ID：124

功能：主动交出当前进程的 CPU 使用权，从而使得 CPU 可以执行其他进程。

C 接口：int yield();

Rust 接口：fn yield() -> i32;

参数：无参数。

返回值：总是返回 0。

可能的错误：无。

## gettime

syscall ID：169

功能：获取当前时间。

C 接口：int gettime(unsigned long long* time);

Rust 接口：fn gettime(time: *mut u64) -> i32;

参数：将当前时间保存在地址**time**处。时间的单位待定，可选为毫秒数/ CPU 时钟周期数，请帮忙确定。暂定为毫秒数。

返回值：总是返回 0。

可能的错误：无。

## getpid

syscall ID：172

功能：获取当前进程的进程 ID。

C 接口：int getpid();

Rust 接口：fn getpid() -> i32;

参数：无参数。

返回值：返回当前进程的进程 ID。

可能的错误：无。

## fork

syscall ID：220

功能：生成一个子进程，其地址空间与当前进程（也称父进程）完全相同，且和父进程一样，回到用户态之后都是从系统调用的下一条指令开始执行。

C 接口：int fork();

Rust 接口：fn fork() -> i32;

参数：无参数。

返回值：如果出现了错误则返回 -1；否则对于父进程，返回子进程的进程 ID；对于子进程则返回 0。

可能的错误：生成子进程的过程中会分配新的物理页框，如果物理页框不足则应该撤销所有操作，放弃生成子进程并返回错误；

## exec

syscall ID：221

功能：替换当前进程的地址空间为一个程序，且返回用户态之后从该程序的入口点开始执行。还需要初始化当前进程的运行栈支持带有参数。

C 接口：int exec(char *file, char *argv[]);

Rust 接口：fn exec(file: *const u8, argv: *const *const u8);

参数：**file**表示将要替换到的程序的文件名，**argv**表示新程序的执行参数。

返回值：如果出现了错误则返回 -1；否则不应该返回。

可能的错误：**file**不存在；需要分配物理页框而物理页框不足，此时应该撤销所有操作并返回错误。

## waitpid

syscall ID：260

功能：当前进程等待一个子进程结束，并获取其返回值。

C 接口：int waitpid(int pid, int *status);

Rust 接口： fn waitpid(pid: i32, status: *mut i32) -> i32;

参数：**pid**表示要等待结束的子进程的进程 ID，如果为 0 的话表示等待任意一个子进程结束；**status**表示保存子进程返回值的地址，如果这个地址为 0 的话表示不必保存。

返回值：如果出现了错误则返回 -1；否则返回结束的子进程的进程 ID。

可能的错误：如果在调用时找不到符合要求的子进程（当前进程没有子进程或者 pid!= 0 而当前进程没有 pid 相符的子进程）则返回错误；传入的地址 status 不为 0 但是不合法；

备注：该 syscall 的实现可能是阻塞的。

# 拓展系统调用接口

## kill

syscall ID：129

功能：杀死一个进程。

C 接口：int kill(int pid);

Rust 接口：fn kill(pid: i32) -> i32;

参数：**pid**表示要杀死的进程的进程 ID。

返回值：如果杀死当前进程的话则不返回。如果出现了错误则返回 -1，否则返回 0。

可能的错误：尝试杀死初始用户进程 initproc；不存在对应 pid 的进程；

备注：在 kill 一个目前正处于阻塞状态的进程的时候情况比较复杂，随着其处于的阻塞状态的不同，需要讨论更加明确的语义，请帮忙一同确定。

# 参考内容

[xv6 实验指导书]([https://pdos.csail.mit.edu/6.828/2020/xv6/book-riscv-rev1.pdf](https://pdos.csail.mit.edu/6.828/2020/xv6/book-riscv-rev1.pdf))

[之前总结的用户程序支持文档]([https://github.com/wyfcyx/osnotes/blob/master/book/v3/%E7%94%A8%E6%88%B7%E7%A8%8B%E5%BA%8F%E6%94%AF%E6%8C%81.md](https://github.com/wyfcyx/osnotes/blob/master/book/v3/%E7%94%A8%E6%88%B7%E7%A8%8B%E5%BA%8F%E6%94%AF%E6%8C%81.md))


