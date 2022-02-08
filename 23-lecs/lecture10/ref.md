## 第十讲 进程、线程和协程的实现

 * [v1](https://github.com/LearningOS/os-lectures/blob/819ca469608126937276764cf6be6c8bdb35e96c/lecture10/ref.md)
 * [v2](https://github.com/LearningOS/os-lectures/blob/be99e6e30b6210810d0dc310fedc9f743bf4ecab/lecture10/ref.md)
 * [v3](https://github.com/LearningOS/os-lectures/blob/faf60c62ccdd5260797c0ca9ad222dd218c4e13e/lecture10/ref.md)
 * v4

### 10.1 进程的实现

#### 1. 进程切换

[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture12?action=AttachFile&do=get&target=12-1.pptx)
#### 2. 进程创建

[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture12?action=AttachFile&do=get&target=12-2.pptx)

#### 3. 进程加载

[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture12?action=AttachFile&do=get&target=12-3.pptx)
#### 4. 进程等待与退出

[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture12?action=AttachFile&do=get&target=12-4.pptx)

#### 5. rCore进程和线程控制

[PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture10?action=AttachFile&do=view&target=slide-10-05.pdf)

### 10.2 线程的实现

[Green Threads Explained in 200 Lines of Rust...](https://cfsamson.gitbook.io/green-threads-explained-in-200-lines-of-rust/)

[完整源代码](https://github.com/cfsamson/example-greenthreads)

#### 1. 与CPU架构相关信息

[两百行Rust代码解析绿色线程原理（一）绪论及基本概念](https://zhuanlan.zhihu.com/p/100058478)

用户线程调度是非抢占式的；

CPU体系结构：寄存器

[Combined Volume Set of Intel® 64 and IA-32 Architectures Software Developer’s Manuals](https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html#combined)

System-Level Registers and Data Structures in IA-32e Mode

出处：[325462-sdm-vol-1-2abcd-3abcd.pdf](https://software.intel.com/content/dam/develop/external/us/en/documents-tps/325462-sdm-vol-1-2abcd-3abcd.pdf) P2859

![IA-32e-registers](figs/IA-32e-registers.png)

出处：[325462-sdm-vol-1-2abcd-3abcd.pdf](https://software.intel.com/content/dam/develop/external/us/en/documents-tps/325462-sdm-vol-1-2abcd-3abcd.pdf) P76 Figure 3-4. General System and Application Programming Registers

![x86-32-registers](figs/x86-32-registers.png)

出处：[325462-sdm-vol-1-2abcd-3abcd.pdf](https://software.intel.com/content/dam/develop/external/us/en/documents-tps/325462-sdm-vol-1-2abcd-3abcd.pdf) P77 Table 3-2. Addressable General Purpose Registers

![8-16-32-64-registers](figs/8-16-32-64-registers.png)

汇编语言

![green-thread-switch](figs/green-thread-switch.png)

#### 2. 线程上下文和线程栈

[两百行Rust代码解析绿色线程原理（二）一个能跑通的例子](https://zhuanlan.zhihu.com/p/100846626)

线程上下文[数据结构](https://github.com/cfsamson/example-greenthreads/blob/master/src/main.rs#L28)`ThreadContext`

![green-thread-ThreadContext](figs/green-thread-ThreadContext.png)

[两百行Rust代码解析绿色线程原理（三）栈](https://zhuanlan.zhihu.com/p/100964432)

栈空间大小

1. 现代操作系统中启动进程时，标准栈大小通常为8MB；
2. 可能出现“栈溢出”；
3. 当我们自己控制栈时，我们可以选择我们想要的大小；
4. 可增长栈：当栈空间用完时，会分配一个更大的栈并将栈内容移到更大的栈上，并恢复程序继续执行，不会导致栈溢出；（Go 语言）



栈布局

出处：[325462-sdm-vol-1-2abcd-3abcd.pdf](https://software.intel.com/content/dam/develop/external/us/en/documents-tps/325462-sdm-vol-1-2abcd-3abcd.pdf) P152 Figure 6-1. Stack Structure

![stack-structure](figs/stack-structure.png)



#### 3. 线程控制块和运行时支持

[两百行Rust代码解析绿色线程原理（四）一个绿色线程的实现](https://zhuanlan.zhihu.com/p/101061389)

[裸函数](https://docs.microsoft.com/zh-cn/cpp/c-language/naked-functions?view=msvc-160)naked_functions：为了与编译器协调处理函数调用和中断处理中栈的使用，而定义的一个约定。它仅影响函数的 prolog 和 epilog 序列的编译器代码生成的性质。

线程控制块[数据结构](https://github.com/cfsamson/example-greenthreads/blob/master/src/main.rs#L19)`Thread`

![thread](figs/thread.png)

线程[运行时](https://github.com/cfsamson/example-greenthreads/blob/master/src/main.rs#L49)支持`Runtime`
new
run
t_return
t_yield

#### 4. 用户线程API和线程切换

[线程API](https://github.com/cfsamson/example-greenthreads/blob/master/src/main.rs#L119)
spawn

![spawn](figs/spawn.png)

yield_thread

![yield_thread](figs/yield_thread.png)

[线程切换](https://github.com/cfsamson/example-greenthreads/blob/master/src/main.rs#L158)`switch`

![t_yield](figs/t_yield.png)

#### 5. 用户线程的操作系统依赖

[两百行Rust代码解析绿色线程原理（五）附录：支持 Windows](https://zhuanlan.zhihu.com/p/101168659)

示例适用于 OSX、Linux 和 Windows

Windows栈




### 10.3 协程的实现

协程的实现([200行代码讲透RUST FUTURES](https://stevenbai.top/rust/futures_explained_in_200_lines_of_rust/))

#### 1. Rust语言中的Future

21.1 Background [PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture21?action=AttachFile&do=view&target=slide-21-01.pdf)
21.2 Futures in Rust [PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture21?action=AttachFile&do=view&target=slide-21-02.pdf)

#### 2. Generator机制和async/await语言机制

21.3 Generators and async/await [PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture21?action=AttachFile&do=view&target=slide-21-03.pdf)

#### 3. Self-Referential Structs & Pin机制

21.4 Self-Referential Structs & Pin [PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture21?action=AttachFile&do=view&target=slide-21-04.pdf)

#### 4. Waker 和 Reactor 机制21.5 Waker and Reactor [PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture21?action=AttachFile&do=view&target=slide-21-05.pdf)

### 课后思考题

1. 在RISC-V上用C或Rust语言实现用户线程支持库；
2. 在Window、Linux和Mac OS上利用可用的语言和已有的操作系统支持，写一个测例程序，比较各系统下创建进程、线程和协程的最大值和上下文切换开销。