## 20200410-第十六讲 进程通信
[v1](https://github.com/LearningOS/os-lectures/blob/2f1d9c5b9494e0d2c25afa3102884380991840c4/lecture16/ref.md)
### 目录
第十六讲 进程通信
16.1 进程通信概念
16.2 信号和管道
16.3 Linux信号机制
16.4 消息队列和共享内存
16.5 dbus
16.6 binder

### 16.3 Linux信号机制

20200410-09-ipc.pdf
20200410-understanding.linux.kernel.pdf
### Signal Model
#### Signal Model
Ref: 20200410-09-ipc.pdf-Page:6

 * Application registers handlers with signal() or sigaction()
 * Send signals with kill() and friends
     * Or raised by hardware exception handlers in kernel
 * Signal delivery jumps to signal handler
     * Irregular control flow, similar to an interrupt

#### Language Exceptions
Ref: 20200410-09-ipc.pdf-Page:8

 * Signals are the underlying mechanism for Exceptions and catch blocks
 * JVM or other runtime system sets signal handlers
 * Signal handler causes execution to jump to the catch block
### Signal Handler Control Flow
#### Signal Handler Control Flow
Ref: 20200410-09-ipc.pdf-Page:9

![signal-control-flow](/Users/xyong/Desktop/figs/signal-control-flow.png)

#### Alternate Stacks
Ref: 20200410-09-ipc.pdf-Page:10

 * Signal handlers can execute on a different stack than program execution.
   * Set with sigaltstack() system call
 * Like an interrupt handler, kernel pushes register state on interrupt stack
   * Return to kernel with sigreturn() system call
   * App can change its own on-stack register state!

#### Frame on the User Mode stack
Ref: https://www.halolinux.us/kernel-reference/figure-103-frame-on-the-user-mode-stack.html

![signal-stack-frame](/Users/xyong/Desktop/figs/signal-stack-frame.png)

 * pretcode: Return address of the signal handler function;
 * sig: The signal number; 
 * sc: hardware context of the User Mode process
 * fpstate: floating point registers of the User Mode process
 * extramask: blocked real-time signals
 * retcode: Eight-byte code issuing a sigreturn( ) system call;

#### Signal trampoline & sigreturn() syscall
Ref: https://www.netbsd.org/docs/internals/en/chap-processes.html#signal

a small piece of assembly code to perform cleanup after handling the signal.

The signal trampoline code in turn calls sigreturn().
This sigreturn() call undoes everything that was done in order to invoke the signal handler.
Changing the process's signal mask, switching signal stacks (see sigaltstack(2))
switches stacks, and restores the process's context
sigreturn() never returns
the signal trampoline code lives either in the vDSO or in the C library.
vDSO (virtual dynamic shared object): a small shared library that the kernel automatically maps into the address space of all user-space applications.

#### Dealing With Asynchronous Signals In Multi Threaded Program
https://stackoverflow.com/questions/6949025/how-are-asynchronous-signal-handlers-executed-on-linux

The first available thread gets the signal
Most handlers run on the thread's stack.
A handler can run on an alternate stack
the thread is running in the kernel does not run the handler until it goes to userspace.

### Signal handlers
#### Default handlers

Ref: 20200410-09-ipc.pdf-Page:11

 * Signals have default handlers:
    * Ignore, kill, suspend, continue, dump core
    * These execute inside the kernel
 * Installing a handler with signal()/sigaction() overrides the default
 * A few (SIGKILL, SIGSTOP) cannot be overridden

#### Signal Delivery
Ref: 20200410-09-ipc.pdf-Page:12
 * Kernel is lazy!
    * Send a signal == mark a pending signal in the task
       * And make runnable if blocked with TASK_INTERRUPTIBLE flag
    * Check pending signals on return from interrupt or syscall
       * Deliver if pending

#### Nested Signals
Ref: 20200410-09-ipc.pdf-Page: 17

 * sigaction() API lets you specify this in detail
    * What signals are blocked (and delivered on sigreturn)
    * Similar to disabling hardware interrupts
 * Blocking system calls inside of a signal handler are only safe with careful use of sigaction()

### ref

https://github.com/LearningOS/os-lectures/blob/master/os-course-outline.md#%E7%AC%AC16%E8%AE%B2-%E8%BF%9B%E7%A8%8B%E9%80%9A%E4%BF%A1-14%E5%B9%B4ppt
大纲

http://os.cs.tsinghua.edu.cn/oscourse/OS2019spring/lecture20
去年的相关讲义

http://os.cs.tsinghua.edu.cn/oscourse/OS2014/lecture15
2014年的相关讲义

#### Understanding the Linux Kernel
Understanding the Linux Kernel
http://ermak.cs.nstu.ru/understanding.linux.kernel.pdf
20200410-understanding.linux.kernel.pdf

P252: Figure 9-1. Catching a signal

Figure 9-2. Frame on the User Mode stack 

#### signal trampoline
https://www.systutorials.com/docs/linux/man/2-sigreturn/
sigreturn(2)

signal trampoline

https://blog.netbsd.org/tnf/entry/towards_backtracing_through_signal_trampolines
Towards backtracing through signal trampolines and fresh libc++

Signal trampolines on NetBSD

https://www.netbsd.org/docs/internals/en/chap-processes.html#signal
3.5. Signal delivery

a small piece of assembly code (called a "signal trampoline") to perform cleanup after handling the signal.

native signal trampoline for i386 is called sigcode
src/sys/arch/i386/i386/locore.S

signal trampoline provided by libc
The trampoline is now stored in the code segment of libc. For instance, for i386, the signal trampoline is named __sigtramp_siginfo_2
src/lib/libc/arch/i386/sys/__sigtramp2.S

#### Nima Honarmand: Fall 2014:: CSE 506
https://compas.cs.stonybrook.edu/~nhonarmand/courses/fa14/cse506.2/slides/ipc.pdf
20200410-09-ipc.pdf
Signals andInter-Process Communication (IPC)

这个幻灯片对信号的机制做了介绍，有很好的一个图，并有实现原理介绍；

Signal Handler Control Flow
第9页：很好的一个图；

Alternate Stacks

Nested Signals

P16: Interrupted System Calls

https://www.cs.drexel.edu/~jjohnson/wi03/cs370/lectures/lec9.html
Lecture 9: Unix Signals and IPC

https://www.win.tue.nl/~aeb/linux/lk/lk-5.html
5. Signals

https://stackoverflow.com/questions/6949025/how-are-asynchronous-signal-handlers-executed-on-linux
How are asynchronous signal handlers executed on Linux?

https://csprojectedu.com/2017/04/09/CS416-AddingSignalsToXV6/
CS416 Adding Signals to XV6