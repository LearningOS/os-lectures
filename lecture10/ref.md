# 第十讲 进程和线程控制
https://tablesgenerator.com/

[v1]()

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

/Users/xyong/github/rCore/kernel/src/process/structs.rs
Line 42:
pub struct Pid(usize);

##### 2-rCore的内存地址空间结构MemorySet

/Users/xyong/github/rCore/crate/memory/src/memory_set/mod.rs
Line 119:
pub struct MemorySet

/Users/xyong/github/rCore/crate/memory/src/memory_set/mod.rs
Line 17:
pub struct MemoryArea

/Users/xyong/github/rCore/kernel/src/memory.rs
Line 29:
pub type MemorySet = rcore_memory::memory_set::MemorySet<PageTableImpl>;

/Users/xyong/github/rCore/kernel/src/arch/riscv/paging.rs
Line 20:
pub struct PageTableImpl

/Users/xyong/github/riscv/src/paging/multi_level.rs
Line 8:
pub struct Rv32PageTable
Line 16:
type TopLevelPageTable<'a> = riscv::paging::Rv32PageTable<'a>;

/Users/xyong/github/rCore/crate/memory/src/memory_set/mod.rs
Line 241:
pub unsafe fn activate(&self)

/Users/xyong/github/rCore/kernel/src/arch/riscv/paging.rs
Line 258:
unsafe fn set_token(token: usize)
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
        envs: Vec<String>,
    ) -> Box<Thread>
Line 327:
pub fn fork(&self, tf: &TrapFrame) -> Box<Thread>

##### 3-线程
/Users/xyong/github/rCore/kernel/src/process/structs.rs
Line 28
pub struct Thread

https://github.com/rcore-os/rcore-thread/blob/master/src/thread_pool.rs#L8
struct Thread

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


#### 上下文切换的数据结构和函数

##### 文档

/Users/xyong/github/rCore/docs/2_OSLab/g2/context.md
上下文切换的文档

##### 5-数据结构

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

/Users/xyong/github/rCore/kernel/src/arch/riscv/context.rs
Line 141:
pub unsafe extern "C" fn switch(&mut self, _target: &mut Self) 

/Users/xyong/github/rCore/kernel/src/process/structs.rs
Line 89：
unsafe fn switch_to(&mut self, target: &mut dyn rcore_thread::Context)

https://github.com/rcore-os/rcore-thread/blob/master/src/context/riscv.rs#L110
pub unsafe extern "C" fn switch(_from: &mut *mut Self, _to: &mut *mut Self)

##### 7-线程切换过程

scheduler.push


#### 8-与进程管理相关的系统调用

/Users/xyong/github/rCore/kernel/src/syscall/proc.rs
与进程管理相关的系统调用

/Users/xyong/github/rCore/kernel/src/syscall/proc.rs
fn sys_


#### 线程管理的接口
/Users/xyong/github/rCore/docs/2_OSLab/os2atc/ucore_os_in_rust.md

线程模块——接口与实现

线程模块——面向接口的上层实现

线程模块——兼容标准库的高层封装

/Users/xyong/github/rCore/kernel/src/lib.rs
Line 24:
pub use crate::process::{new_kernel_context, processor};

##### 线程模块——接口与实现

##### 线程模块——面向接口的上层实现
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

##### 线程模块——兼容标准库的高层封装