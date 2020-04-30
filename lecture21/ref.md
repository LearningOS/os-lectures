## 20200430-第二十一讲内容准备

[v1]()

2020春,操作系统课,课堂内容,准备

### 结论

讲课内容基本按两个参考文献的内容来组织。
https://stevenbai.top/rust/futures_explained_in_200_lines_of_rust/
https://github.com/cfsamson/books-futures-explained
关于异步的思路很清楚；

https://os.phil-opp.com/async-await/#futures-in-rust
有两个插图很好；

### 调研

deadlock async rust

multithreaded `Future` executor

https://github.com/fede1024/rust-scheduled-executor
Single and multi-threaded task scheduler

https://zhuanlan.zhihu.com/p/66028983
Rust Async: 标准库futures api解析

### 讨论

#### 函数指针的安全使用
https://cfsamson.github.io/books-futures-explained/2_waker_context.html
基于这里的描述，我可以认为“在rust中可以安全地使用函数指针”吗？

函数指针一直可以是safe的
核心是所有extern fn都是 unsafe 的

然后 fn(A)->B 和 unsafe fn(A)->B 是两个不一样的类型
所以传递函数指针一直都很safe，但是只要出现调用就得unsafe
前面说的这段代码用了函数指针的调用，只是不是外部定义的。所以是安全的。

#### 外部函数的安全问题

一个问题，在假定rCore的内核是安全的。然后用可加载内核模块写了个rust的FS，在rCore中引用它。能保证它是安全的吗？

Rust 链接 Rust 模块，不过 FFI 的话，现在方法应该只有静态链接
如果要做动态链接的内核模块，估计还得写成 FFI 那种，这样跨 FFI 边界就是 C ABI 了
这个时候可能还得 unsafe

两边都是rust安全的模块，可以不用FFI而实现动态链接吗？直观感觉，应该是可能的。
假定在rCore中对FS使用固定的ABI，这时动态加载内核模块，应该能rust安全。能确认吗？
这是写可加载内核模块必须的，应该也是rust安全关心的。如果可能，找找解决方案。

#### 没有FFI的动态链接

主要问题是Rust lang team故意没有固定 ABI
他们的理由好象是为了方便以后语言功能的改动
一方面，有没有办法指挥编译器暴露特定的符号
另一方面，因为 Rust 里面没有“声明”这么回事儿，所以不知道有没有办法用某个接口，但是不把接口的实现包含在输出的object里？

暴露函数可以用no_mangle
不过由于abi不固定可能还是需要暴露C接口
我觉得可能比较靠谱的，能做成的
是模块分发的时候同时包含源码和 rlib
然后 OS 内核内嵌一个编译器，小一点的，只做 typecheck
好像 rlib 里面就包含接口信息了
但是这个链接就比.so 之类的的链接复杂多了
虽然abi可能会变但是同一天的toolchain不会变，这样就不需要暴露c接口了
直接提供rlib
缺点是如果toolchain升级，所有程序都要重新编译

### 背景

#### 抢先式和非抢先式调度

参考： https://cfsamson.github.io/book-exploring-async-basics/2_async_history.html#non-preemptive-multitasking Non-Preemptive multitasking

非抢先式： yielded

抢先式：时钟中断

#### 进程、内核线程和用户线程

参考： https://stevenbai.top/rust/futures_explained_in_200_lines_of_rust/ 线程

线程的概念（待补充）

内核线程的特征

 * 优点:
    * 简单
    * 易用
    * 线程切换快
    * 支持多处理机上并行
 * 缺点:
    * 线程堆栈开销：大量线程并发执行时，可能导致内存耗尽
    * 内核线程的用户态与内核态的切换开销：大量线程并发执行时，切换操作占用CPU时间多
    * 响应时间问题：内核其他功能执行影响线程快速切换回来
 * 结论：使用线程并发执行大量小任务时，开销很大；

#### 用户线程（绿色线程，green thread）

参考： https://stackoverflow.com/questions/15983872/difference-between-user-level-and-kernel-supported-threads
https://stevenbai.top/rust/futures_explained_in_200_lines_of_rust/  绿色线程(Green threads)

OS-level threads
native threads
Kernel-level threads

a green thread that is managed by your language
coroutines in C, goroutines in Go, fibers in Ruby, etc
the language translates it into async calls to the OS.
The language then allows other green threads to run while waiting for the result.

The best of both worlds is to have one OS thread per CPU, and many green threads that are magically moved around onto OS threads. Languages like Go and Erlang can do this.

Rust曾经支持绿色线程，但他们它达到1.0之前被删除了

用户线程的特征
 * 堆栈开销：解决这个问题不容易,并且有成本
 * 跨平台实验困难：支持许多不同的平台，就很难正确实现

https://cfsamson.gitbook.io/green-threads-explained-in-200-lines-of-rust/
Green Threads Explained in 200 Lines of Rust...

#### 从回调到承诺 (promises)

参考： https://stevenbai.top/rust/futures_explained_in_200_lines_of_rust/ 从回调到承诺 (promises)

承诺是解决回调带来的复杂性的一种方法，承诺被重写为状态机。

从语法上讲，Rusts Futures 0.1很像上面的承诺示例，Rusts Futures 0.3很像我们上一个示例中的 async / await。

#### Readiness-based event queues

参考： https://cfsamson.github.io/book-exploring-async-basics/6_epoll_kqueue_iocp.html#readiness-based-event-queues

**Basically this happens when we want to read data from a socket using epoll/kqueue:**

1. We create an event queue by calling the syscall `epoll_create` or `kqueue`.
2. We ask the OS for a file descriptor representing a network socket.
3. Through another syscall, we register an interest in `Read` events on this socket. It's important that we also inform the OS that we'll be expecting to receive a notification when the event is ready in the event queue we created in (1).
4. Next, we call `epoll_wait` or `kevent` to wait for an event. This will block (suspend) the thread it's called on.
5. When the event is ready, our thread is unblocked (resumed), and we return from our "wait" call with data about the event that occurred.
6. We call `read` on the socket we created in 2.

#### Completion-based event queues

参考： https://cfsamson.github.io/book-exploring-async-basics/6_epoll_kqueue_iocp.html#completion-based-event-queues

IOCP stands for I/O Completion Ports and is a completion-based event queue. This type of queue notifies you when events are completed. 

basic breakdown of what happens in this type of event queue:

1. We create an event queue by calling the syscall `CreateIoCompletionPort`.
2. We create a buffer and ask the OS to give us a handle to a socket.
3. We register an interest in `Read` events on this socket with another syscall, but this time we also pass in the buffer we created in (2) to which the data will be read.
4. Next, we call `GetQueuedCompletionStatusEx`, which will block until an event has completed.
5. Our thread is unblocked, and our buffer is now filled with the data we're interested in.

#### Epol, Kqueue and IOCP

参考： https://cfsamson.github.io/book-exploring-async-basics/6_epoll_kqueue_iocp.html#epoll
https://zhuanlan.zhihu.com/p/39970630 select poll epoll的区别

Epoll

Epoll is the Linux way of implementing an event queue. In terms of functionality, it has a lot in common with Kqueue. The advantage of using epoll over other similar methods on Linux like select or poll is that epoll was designed to work very efficiently with a large number of events.

Kqueue

Kqueue is the MacOS way of implementing an event queue, which originated from BSD, in operating systems such as FreeBSD, OpenBSD, etc. In terms of high level functionality, it's similar to Epoll in concept but different in actual use.

Some argue it's a bit more complex to use and a bit more abstract and "general".

IOCP

IOCP or Input Output Completion Ports is the way Windows handles this type of event queue.

#### Epoll

参考： https://zhuanlan.zhihu.com/p/39970630

在调用epoll_create时，内核在epoll文件系统里建了个file结点，在内核cache里建了个红黑树用于存储以后epoll_ctl传来的socket；

再建立一个list链表，用于存储准备就绪的事件，当epoll_wait调用时，仅仅观察这个list链表里有没有数据即可。有数据就返回，没有数据就sleep，等到timeout时间到后即使链表没数据也返回。

epoll用kmem_cache_create（slab分配器）分配内存用来存放struct epitem和struct eppoll_entry。

当调用epoll_wait检查是否有事件发生时，只需要检查eventpoll对象中的rdlist双链表中是否有epitem元素即可。如果rdlist不为空，则把发生的事件复制到用户态，同时将事件数量返回给用户。

参考： https://zhuanlan.zhihu.com/p/39970630

![epoll](/Users/xyong/Desktop/os-lectures/lecture21/figs/epoll.jpg)

### rust future

参考： https://stevenbai.top/rust/futures_explained_in_200_lines_of_rust/
参考： https://github.com/cfsamson/books-futures-explained
参考： https://cfsamson.github.io/books-futures-explained/conclusion.html
参考： Evernote： 20200402-异步消息调研

#### 什么是`Future`?

`Future`是一些将在未来完成的操作。
 Rust中的异步实现基于轮询,每个异步任务分成三个阶段:

1. 轮询阶段(The Poll phase). 一个`Future`被轮询后,会开始执行,直到被阻塞. 我们经常把轮询一个Future这部分称之为执行器(executor)
2. 等待阶段.  事件源(通常称为reactor)注册等待一个事件发生，并确保当该事件准备好时唤醒相应的`Future`
3. 唤醒阶段.  事件发生,相应的`Future`被唤醒。 现在轮到执行器(executor),就是第一步中的那个执行器，调度`Future`再次被轮询，并向前走一步，直到它完成或达到一个阻塞点，不能再向前走, 如此往复,直到最终完成.

#### Leaf futures & Non-leaf-futures

 * Leaf future
    * 由运行时创建`leaf futures`, 代表资源。
    * 对这些资源的操作，比如套接字上的 Read 操作，将是非阻塞的，并返回一个我们称之为`leaf-future`的Future.
 * Non-leaf-future
    * Non-leaf-futures指的是那些我们用`async`关键字创建的Future.
    * 异步程序的大部分是Non-leaf-futures，这是一种可暂停的计算。
    * 通常由`await` 一系列`leaf-future`组成.能够将控制权交给运行时的调度程序，然后在稍后停止的地方继续执行。

#### 运行时（runtime）与rust

一些高级语言提供“运行时”，用于处理并发；

rust的并发处理运行时由函数库实现，分为两部分：

执行器(The Executor)：实际要执行的未来操作；

分析器 (The Reactor)：通知机制

#### Rust future使用

1. 一个公共接口，`Future trait`
2. 通过async和await关键字进行暂停和恢复`Future`
3. `Waker`接口, 可以唤醒暂停的`Future`

#### concept of futures
https://os.phil-opp.com/async-await/#example

#### Futures in Rust
https://os.phil-opp.com/async-await/#futures-in-rust

#### Zero-cost futures in Rust
https://aturon.github.io/blog/2016/08/11/futures/

#### The Async/Await Pattern
https://os.phil-opp.com/async-await/#the-async-await-pattern

### 生成器（状态机）

#### State Machine Transformation

https://os.phil-opp.com/async-await/#state-machine-transformation
异步机制的工作流程图；

#### Self-Referential Structs
https://os.phil-opp.com/async-await/#self-referential-structs

#### The Problem with Self-Referential Structs
https://os.phil-opp.com/async-await/#the-problem-with-self-referential-structs
自引用数据结构的插图；

### *Rust future的实现

参考： https://stevenbai.top/rust/futures_explained_in_200_lines_of_rust/#四-唤醒器和上下文waker-and-context

#### 唤醒器

注：waker相当于是一个动态函数指针的定义和引用方法；其中有一处代码是不安全的。

`Waker`类型允许在运行时的reactor 部分和执行器部分之间进行松散耦合。

通过使用不与`Future`执行绑定的唤醒机制，我们将得到一个松散耦合，其中很容易使用新的`leaf-future`来扩展生态系统。

创建一个 Waker 需要创建一个 vtable，这个vtable允许我们使用动态方式调用我们真实的Waker实现.

引用的大小是不同的。 许多是8字节(在64位系统中是指针大小) ，但有些是16字节。

##### 胖指针

16字节大小的指针被称为“胖指针” ，因为它们携带额外的信息。

- 前8个字节是指向数组中第一个元素的实际指针(或 slice 引用的数组的一部分)
- 第二个8字节是切片的长度

##### trait对象

指向 trait 对象的指针布局如下:

- 前8个字节指向trait 对象的data
- 后八个字节指向trait对象的 vtable

使用动态分发，引用一个trait对象，除了它实现了 trait 定义的方法之外，我们对这个对象一无所知。

#### 生成器 coroutines, generators

参考： https://stevenbai.top/rust/futures_explained_in_200_lines_of_rust/#五 生成器和async/await

https://github.com/rust-lang/rfcs/blob/master/text/2033-experimental-coroutines.md coroutine

### Pin

参考： https://stevenbai.top/rust/futures_explained_in_200_lines_of_rust/#六 Pin

#### pinning API

https://github.com/rust-lang/rfcs/blob/master/text/2349-pin.md
the pinning API was proposed in RFC 2349

#### Pin

https://os.phil-opp.com/async-await/#pin-box-t-and-unpin
Pin<Box<T>> and Unpin

#### Pinning和自引用结构

参考： https://stevenbai.top/rust/futures_explained_in_200_lines_of_rust/#六-pin

### Reactor

参考： https://stevenbai.top/rust/futures_explained_in_200_lines_of_rust/#reactor