# 第十讲 进程和线程控制
https://tablesgenerator.com/

[v1](https://github.com/LearningOS/os-lectures/blob/3f429b1e5c7fba1ae1dde052794698dc85024ec4/lecture10/ref.md)

[v2]()

## 10.1 进程切换 
## 10.2 进程创建 
## 10.3 进程加载 
## 10.4 进程等待与退出 
## 10.5 rCore的进程和线程控制

### rCore的进程相关代码分析

#### 进程和线程的数据结构

##### 1-rCore的进程控制块结构struct Process

https://github.com/rcore-os/rCore/blob/master/kernel/src/process/structs.rs#L61
/Users/xyong/github/rCore/kernel/src/process/structs.rs
Line 61
pub struct Process

![process](/Users/xyong/Desktop/os-lectures/lecture10/figs/process.png)

/Users/xyong/github/rCore/kernel/src/process/structs.rs
Line 42:
pub struct Pid(usize);

##### 2-rCore的内存地址空间结构MemorySet

/Users/xyong/github/rCore/crate/memory/src/memory_set/mod.rs
Line 119:
pub struct MemorySet

```rust
pub struct MemorySet<T: PageTableExt> {
    areas: Vec<MemoryArea>,
    page_table: T,
}
```



/Users/xyong/github/rCore/crate/memory/src/memory_set/mod.rs
Line 17:
pub struct MemoryArea
```rust
pub struct MemoryArea {
    start_addr: VirtAddr,
    end_addr: VirtAddr,
    attr: MemoryAttr,
    handler: Box<dyn MemoryHandler>,
    name: &'static str,
}
```

/Users/xyong/github/rCore/kernel/src/memory.rs
Line 29:
```rust
pub type MemorySet = rcore_memory::memory_set::MemorySet<PageTableImpl>;
```
/Users/xyong/github/rCore/kernel/src/arch/riscv/paging.rs
Line 20:
pub struct PageTableImpl
```rust
pub struct PageTableImpl {
    page_table: TopLevelPageTable<'static>,
    root_frame: Frame,
    entry: Option<PageEntry>,
}
```
/Users/xyong/github/riscv/src/paging/multi_level.rs
Line 8:
pub struct Rv32PageTable
```rust
pub struct Rv32PageTable<'a> {
    root_table: &'a mut PageTable,
    linear_offset: usize, // VA = PA + linear_offset
}
```
Line 16:
```rust
type TopLevelPageTable<'a> = riscv::paging::Rv32PageTable<'a>;
```
/Users/xyong/github/rCore/crate/memory/src/paging/mod.rs
Line 111:
unsafe fn activate(&self)

```rust
    /// Activate this page table
    unsafe fn activate(&self) {
        let old_token = Self::active_token();
        let new_token = self.token();
        debug!("switch table {:x?} -> {:x?}", old_token, new_token);
        if old_token != new_token {
            Self::set_token(new_token);
            Self::flush_tlb();
        }
    }
```
/Users/xyong/github/rCore/kernel/src/arch/riscv/paging.rs
Line 258:
unsafe fn set_token(token: usize)
```rust
    unsafe fn set_token(token: usize) {
        asm!("csrw satp, $0" :: "r"(token) :: "volatile");
    }
```
##### proc.exit

/Users/xyong/github/rCore/kernel/src/syscall/proc.rs
Line 211:
pub fn sys_kill(&mut self, pid: usize, sig: usize) -> SysResult
Line 256:
pub fn sys_exit(&mut self, exit_code: usize) -> ! 
Line 289:
pub fn sys_exit_group(&mut self, exit_code: usize) -> !



##### Scheduler

https://rcore-os.github.io/rCore_tutorial_doc/chapter7/part3.html
线程调度之 Round Robin 算法

https://github.com/rcore-os/rcore-thread/blob/master/src/scheduler/rr.rs#L20
impl Scheduler for RRScheduler

/Users/xyong/github/rcore-thread/src/scheduler/mod.rs
Line 19:
pub trait Scheduler: 'static

/Users/xyong/github/rCore/kernel/src/arch/riscv/context.rs
Line 9:
pub struct TrapFrame

/Users/xyong/github/rCore/kernel/src/arch/riscv/interrupt.rs
Line 56:
pub extern "C" fn rust_trap(tf: &mut TrapFrame)

pub fn set_timer(stime_value: u64)
pub fn set_next() 
pub fn timer
timer()
pub extern "C" fn rust_trap(tf: &mut TrapFrame)

###### 用Pid(0)创建新进程
/Users/xyong/github/rCore/kernel/src/process/structs.rs
Line 113:
pub fn new_kernel(entry: extern "C" fn(usize) -> !, arg: usize) -> Box<Thread>
Line 248:
pub fn new_user(
        inode: &Arc<dyn INode>,
        exec_path: &str,
        args: Vec<String>,
        envs: Vec<S/tring>,
    ) -> Box<Thread>
Line 327:
pub fn fork(&self, tf: &TrapFrame) -> Box<Thread>

##### 3-线程
/Users/xyong/github/rCore/kernel/src/process/structs.rs
Line 28
pub struct Thread

https://github.com/rcore-os/rcore-thread/blob/master/src/thread_pool.rs#L8
struct Thread
/Users/xyong/github/rcore-thread/src/thread_pool.rs
```rust
struct Thread {
    /// Current status of the thread.
    status: Status,
    /// Next status after the thread stop running.
    status_after_stop: Status,
    /// A waiter thread of this. It will be woken up on my exit.
    waiter: Option<Tid>,
    /// If detached, all resources will be released on exit.
    detached: bool,
    /// The context of the thread.
    context: Option<Box<dyn Context>>,
}
```

https://github.com/rcore-os/rcore-thread/blob/master/src/thread_pool.rs#L25
pub enum Status

https://doc.rust-lang.org/src/std/thread/mod.rs.html#1052
Line 1054:
fn new() -> ThreadId

/Users/xyong/github/rCore/kernel/src/process/mod.rs
Line 106:
pub fn thread_manager() -> &'static ThreadPool

#### 4-线程状态转换

/Users/xyong/github/rCore/docs/2_OSLab/g5/exp3.md
Line 87:
多核线程管理
每个进程有3个状态：Ready等待执行，Running正在执行，Sleep不可执行

https://rcore-os.github.io/rCore_tutorial_doc/chapter6/part1.html
线程状态与保存

https://github.com/rcore-os/rcore-thread/blob/master/src/thread_pool.rs#L151
fn set_status(&self, tid: Tid, status: Status)

Status::Ready
proc.status
set_status

/Users/xyong/github/rcore-thread/src/thread_pool.rs

```rust
pub enum Status {
    Ready,
    Running(usize),
    Sleeping,
    /// aka ZOMBIE. Its context was dropped.
    Exited(ExitCode),
}
```
/Users/xyong/github/rcore-thread/src/thread_pool.rs
```rust
fn set_status(&self, tid: Tid, status: Status)
```

![set-status](/Users/xyong/Desktop/os-lectures/lecture10/figs/set-status.png)

#### 上下文切换的数据结构和函数

##### 5-上下文切换的数据结构文档

/Users/xyong/github/rCore/docs/2_OSLab/g2/context.md
上下文切换的文档

相关数据结构


1. `TrapFrame`:

    ```rust
    pub struct TrapFrame {
        /// General registers
        pub x: [usize; 32],
        /// Supervisor Status
        pub sstatus: Sstatus,
        /// Supervisor Exception Program Counter
        pub sepc: usize,
        /// Supervisor Trap Value
        pub stval: usize,
        /// Supervisor Cause
        pub scause: Scause,
    }
    ```

    在陷入异常时向栈中压入的内容，由 [trap.S](../../../kernel/src/arch/aarch64/interrupt/trap.S#L92) 的 `__alltraps` 构建。

2. `ContextData`:

    ```rust
    struct ContextData {
        /// Return address
        ra: usize,
        /// Page table token
        satp: usize,
        /// Callee-saved registers
        s: [usize; 12],
    }
    ```

    执行上下文切换时向栈中压入的内容，由 `__switch()` 函数构建。

3. `InitStack`:

    ```rust
    pub struct InitStack {
        context: ContextData,
        tf: TrapFrame,
    }
    ```

    对于新创建的线程，不仅要向栈中压入 `ContextData` 结构，还需手动构造 `TrapFrame` 结构。为了方便管理就定义了 `InitStack` 包含这两个结构体。

4. `Context`:

    ```rust
    pub struct Context {
        /// The stack pointer of the suspended thread.
        /// A `ContextData` is stored here.
        sp: usize,
    }
	```

    每个进程控制块 `Process` ([kernel/src/process/context.rs](../../../kernel/src/process/structs.rs#L13)) 都会维护一个平台相关的 `Context` 对象。


##### 数据结构

/Users/xyong/github/rCore/kernel/src/arch/riscv/context.rs
Line 105:
struct ContextData
Line 127:
pub struct Context
Line 133:
impl Context

/Users/xyong/github/rCore/kernel/src/memory.rs
Line 103:
pub struct KernelStack(usize)

/Users/xyong/github/rCore/kernel/src/arch/riscv/context.rs
Line 84:
pub struct InitStack

##### 6-切换函数

https://rcore-os.github.io/rCore_tutorial_doc/chapter6/part2.html
线程切换

/Users/xyong/github/rCore/kernel/src/process/structs.rs
Line 89：
unsafe fn switch_to(&mut self, target: &mut dyn rcore_thread::Context)

![switch-to](/Users/xyong/Desktop/os-lectures/lecture10/figs/switch-to.png)

https://github.com/rcore-os/rcore-thread/blob/master/src/context/riscv.rs#L110
pub unsafe extern "C" fn switch(_from: &mut *mut Self, _to: &mut *mut Self)

/Users/xyong/github/rCore/kernel/src/arch/riscv/context.rs
Line 141:
pub unsafe extern "C" fn switch(&mut self, _target: &mut Self) 

![riscv-32-switch](/Users/xyong/Desktop/os-lectures/lecture10/figs/riscv-32-switch.png)

##### 7-线程切换过程

scheduler.push
need_reschedule

/Users/xyong/github/rcore-thread/src/scheduler/mod.rs
pub trait Scheduler

![scheduler](/Users/xyong/Desktop/os-lectures/lecture10/figs/scheduler.png)

#### 8-与进程管理相关的系统调用

/Users/xyong/github/rCore/kernel/src/syscall/proc.rs
与进程管理相关的系统调用

/Users/xyong/github/rCore/kernel/src/syscall/proc.rs
fn sys_

![proc-syscall](/Users/xyong/Desktop/os-lectures/lecture10/figs/proc-syscall.png)


#### 线程管理的接口
/Users/xyong/github/rCore/docs/2_OSLab/os2atc/ucore_os_in_rust.md

线程模块——接口与实现

线程模块——面向接口的上层实现

线程模块——兼容标准库的高层封装

/Users/xyong/github/rCore/kernel/src/lib.rs
Line 24:
pub use crate::process::{new_kernel_context, processor};

##### 线程模块——接口与实现

##### 9-线程模块——面向接口的上层实现
/Users/xyong/github/rCore/docs/2_OSLab/os2atc/ucore_os_in_rust.md
Line 418:

https://doc.rust-lang.org/std/thread/
Module std::thread

```rust
// thread.rs
pub fn current() -> Thread {...}
pub fn sleep(dur: Duration) {...}
pub fn spawn<F, T>(f: F) -> JoinHandle<T> {...}
pub fn yield_now() {...}
pub fn park() {...}
```
在上页基础上进一步封装。
提供和标准库`std::thread`完全一致的上层接口。
使得依赖std的多线程代码，可以方便地迁移到内核中。

/Users/xyong/github/rCore/kernel/src/lib.rs
Line 26:
pub use rcore_thread::std_thread as thread;

/Users/xyong/github/rCore/kernel/src/process/structs.rs
Line 88:
impl rcore_thread::Context for Thread

/Users/xyong/github/rcore-thread/examples/riscv/src/main.rs
thread::spawn
使用spawn的例子；

/Users/xyong/github/rcore-thread/src/std_thread.rs
pub fn

![rcore-thread](/Users/xyong/Desktop/os-lectures/lecture10/figs/rcore-thread.png)

https://doc.rust-lang.org/std/thread/#functions

![thread-function](/Users/xyong/Desktop/os-lectures/lecture10/figs/thread-function.png)

##### 线程模块——兼容标准库的高层封装