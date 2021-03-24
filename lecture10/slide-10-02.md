## rCore进程管理

* [v1](https://github.com/LearningOS/os-lectures/blob/d3a86df7dd85020cc35dacebd4f438619d25355b/lecture10/slide-10-02.md)
* v2

### [rCore中的进程管理系统调用](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter5/1process.html#id4)

#### `fork`

* 内核会创建一个子进程
* 子进程和调用 `fork` 父的进程在返回用户态时的状态几乎完全相同：为子进程创建一个和父进程几乎完全相同的应用地址空间。
* 父子进程的系统调用返回值`a0` 寄存器内容不同

```rust
/// 功能：当前进程 fork 出来一个子进程。
/// 返回值：对于子进程返回 0，对于当前进程则返回子进程的 PID 。
/// syscall ID：220
pub fn sys_fork() -> isize;
```

#### `waitpid`

* 进程通过 `exit` 系统调用退出后，无法立即全部地回收所占用资源
  * 内核栈
* 父进程通过 `waitpid` 系统调来获取子进程的返回状态并回收所占据的全部资源，从而彻底销毁子进程
  * 回收子进程的资源并收集它的一些信息

```rust
/// 功能：当前进程等待一个子进程变为僵尸进程，回收其全部资源并收集其返回值。
/// 参数：pid 表示要等待的子进程的进程 ID，如果为 -1 的话表示等待任意一个子进程；
/// exit_code 表示保存子进程返回值的地址，如果这个地址为 0 的话表示不必保存。
/// 返回值：如果要等待的子进程不存在则返回 -1；否则如果要等待的子进程均未结束则返回 -2；
/// 否则返回结束的子进程的进程 ID。
/// syscall ID：260
pub fn sys_waitpid(pid: isize, exit_code: *mut i32) -> isize;
```

#### `exec`

* 执行不同的可执行文件：加载一个新的 ELF 可执行文件替换原有的应用地址空间并开始执行。
* `path` 作为 `&str` 类型是一个胖指针

```rust
/// 功能：将当前进程的地址空间清空并加载一个特定的可执行文件，返回用户态后开始它的执行。
/// 参数：path 给出了要加载的可执行文件的名字；
/// 返回值：如果出错的话（如找不到名字相符的可执行文件）则返回 -1，否则不应该返回。
/// syscall ID：221
pub fn sys_exec(path: &str) -> isize;
```

调用方法

```rust
// user/src/exec.rs
pub fn sys_exec(path: &str) -> isize {
    syscall(SYSCALL_EXEC, [path.as_ptr() as usize, 0, 0])
}
```



#### `exit`

* 进程退出：当应用调用 `sys_exit` 系统调用主动退出或者出错由内核终止之后，会在内核中调用 `exit_current_and_run_next` 函数退出当前任务并切换到下一个。

用户初始程序-initproc

外壳程序-user_shell

### 进程管理的核心数据结构

#### 进程标识符

```rust
// os/src/task/pid.rs
pub struct PidHandle(pub usize);

// os/src/task/pid.rs
struct PidAllocator {
    current: usize,
    recycled: Vec<usize>,
}
```

#### 内核栈

```rust
// os/src/task/pid.rs

pub struct KernelStack {
    pid: usize,
}
```

#### 进程控制块

```rust
// os/src/task/task.rs
pub struct TaskControlBlock {
    // immutable
    pub pid: PidHandle,
    pub kernel_stack: KernelStack,
    // mutable
    inner: Mutex<TaskControlBlockInner>,
}

pub struct TaskControlBlockInner {
    pub trap_cx_ppn: PhysPageNum,
    pub base_size: usize,
    pub task_cx_ptr: usize,
    pub task_status: TaskStatus,
    pub memory_set: MemorySet,
    pub parent: Option<Weak<TaskControlBlock>>,
    pub children: Vec<Arc<TaskControlBlock>>,
    pub exit_code: i32,
}
```

#### 任务管理器

```rust
// os/src/task/manager.rs
pub struct TaskManager {
    ready_queue: VecDeque<Arc<TaskControlBlock>>,
}
```

#### 处理器监视器

```rust
// os/src/task/processor.rs
pub struct Processor {
    inner: RefCell<ProcessorInner>,
}

unsafe impl Sync for Processor {}
struct ProcessorInner {
    current: Option<Arc<TaskControlBlock>>,
    idle_task_cx_ptr: usize,
}
```

### 任务切换

```rust
// os/src/task/processor.rs
pub fn schedule(switched_task_cx_ptr2: *const usize) {
    let idle_task_cx_ptr2 = PROCESSOR.get_idle_task_cx_ptr2();
    unsafe {
        __switch(
            switched_task_cx_ptr2,
            idle_task_cx_ptr2,
        );
    }
}
```
