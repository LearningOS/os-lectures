## 第十讲 进程、线程和协程的实现

 * [v1](https://github.com/LearningOS/os-lectures/blob/819ca469608126937276764cf6be6c8bdb35e96c/lecture10/ref.md)
 * v2

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

汇编语言

#### 2. 线程上下文和线程栈

[两百行Rust代码解析绿色线程原理（二）一个能跑通的例子](https://zhuanlan.zhihu.com/p/100846626)

线程上下文[数据结构](https://github.com/cfsamson/example-greenthreads/blob/master/src/main.rs#L28)`ThreadContext`

用户线程栈

[两百行Rust代码解析绿色线程原理（三）栈](https://zhuanlan.zhihu.com/p/100964432)

栈空间大小和可增长的栈

栈布局

用户线程栈打印

#### 3. 线程控制块和运行时支持

[两百行Rust代码解析绿色线程原理（四）一个绿色线程的实现](https://zhuanlan.zhihu.com/p/101061389)

[裸函数](https://docs.microsoft.com/zh-cn/cpp/c-language/naked-functions?view=msvc-160)naked_functions：为了与编译器协调处理函数调用和中断处理中栈的使用，而定义的一个约定。它仅影响函数的 prolog 和 epilog 序列的编译器代码生成的性质。

线程控制块[数据结构]()`Thread`

线程[运行时](https://github.com/cfsamson/example-greenthreads/blob/master/src/main.rs#L49)支持`Runtime`
new
run
t_return
t_yield

#### 4. 用户线程API和线程切换

[线程API](https://github.com/cfsamson/example-greenthreads/blob/master/src/main.rs#L119)
spawn
yield_thread

[线程切换](https://github.com/cfsamson/example-greenthreads/blob/master/src/main.rs#L158)`switch`

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