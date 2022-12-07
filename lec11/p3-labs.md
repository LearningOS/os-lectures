---
marp: true
theme: default
paginate: true
_paginate: false
header: ''
footer: ''
backgroundColor: white
---

<!-- theme: gaia -->
<!-- _class: lead -->

# 第十一讲 线程与协程
## 第三节 支持线程/协程的OS(TCOS)

<br>
<br>

向勇 陈渝 李国良 

2022年秋季
<!-- https://blog.aloni.org/posts/a-stack-less-rust-coroutine-100-loc/

https://stanford-cs242.github.io/f17/assets/projects/2017/kedero.pdf


https://cfsamson.gitbook.io/green-threads-explained-in-200-lines-of-rust/


https://tian-deng.github.io/posts/translation/rust/green_threads_explained_in_200_lines_of_rust/ -->
---
### 实践：TCOS
- **进化目标**
- 总体思路
- 历史背景
- 实践步骤
- 软件架构
- 相关硬件
- 程序设计

![bg right:65% 100%](figs/thread-coroutine-os-detail.png)


---
### 实践：TCOS -- 以往目标
提高性能、简化开发、加强安全、支持数据持久保存、支持应用的灵活性，支持进程间交互
- IPC OS：进程间交互
- Filesystem OS：支持数据持久保存
- Process OS: 增强进程管理和资源管理
- Address Space OS: 隔离APP访问的内存地址空间
- multiprog & time-sharing OS: 让APP共享CPU资源
- BatchOS: 让APP与OS隔离，加强系统安全，提高执行效率
- LibOS: 让APP与HW隔离，简化应用访问硬件的难度和复杂性

---
### 实践：TCOS -- 进化目标
提高执行效率，支持线程和协程
- 在进程内实现多个控制流（线程/协程）的执行
- 在用户态或内核态管理多个控制流（线程/协程）


---
### 实践：TCOS 
### 同学的进化目标
- 理解基于任务（Task）的进程/线程/协程抽象
- 理解进程/线程/协程的实现与运行机制
- 会写支持线程/协程的OS


<!-- 达科塔盗龙Dakotaraptor是一种生存于距今6700万-6500万年前白垩纪晚期的兽脚类驰龙科恐龙，它主打的并不是霸王龙的力量路线，而是利用自己修 长的后肢来提高敏捷度和奔跑速度。它全身几乎都长满了羽毛，可能会滑翔或者其他接近飞行行为的行动模式。 -->

![bg right 80%](figs/dakotaraptor.png)

---
### 实践：TCOS
- 进化目标
- **总体思路**
    - **用户态管理的用户线程**
- 历史背景
- 实践步骤
- 软件架构
- 程序设计

![bg right:70% 100%](figs/task-abstracts.png)



---

### 总体思路 
- 如何管理协程/线程/进程？
   - 任务上下文
   - **用户态管理**
   - 内核态管理 
![bg right:65% 100%](figs/task-abstracts.png)


---
### 总体思路 
- 如何管理协程/线程/进程？
   - 任务上下文
   - **用户态管理**
   - 内核态管理 
![bg right:65% 100%](figs/thread-coroutine-os-detail.png)


---
### 总体思路 
**用户态管理的用户线程**
   - 用户态管理线程的任务控制块
      - 与 Lec4中的任务控制块类似
      - 由用户态的Runtime管理
  - 任务控制块
```
struct Task {
    id: usize,
    stack: Vec<u8>,
    ctx: TaskContext,
    state: State,
}
```  
![bg right:40% 100%](figs/task-abstracts.png)

---
### 实践步骤
```
git clone https://github.com/rcore-os/rCore-Tutorial-v3.git
cd rCore-Tutorial-v3
git checkout ch8
```
包含一个应用程序
```
user/src/bin/
├──  stackful_coroutine.rs
```
---
### 实践步骤
执行这个应用程序
```
Rust user shell
>> stackful_coroutine
stackful_coroutine begin...
TASK  0(Runtime) STARTING
TASK  1 STARTING
task: 1 counter: 0
TASK 2 STARTING
task: 2 counter: 0
TASK 3 STARTING
task: 3 counter: 0
TASK 4 STARTING
task: 4 counter: 0
...
```

---
### 程序设计
简单的用户态管理多线程应用 `stackful_coroutine.rs`
```rust
pub fn main()  {
    let mut runtime = Runtime::new(); //创建线程管理子系统
    runtime.init();  // 初始化线程管理子系统
    runtime.spawn(|| {  //创建一个用户态线程
        println!("TASK  1 STARTING");
        let id = 1;
        for i in 0..4 {
            println!("task: {} counter: {}", id, i);
            yield_task();  //主动让出处理器
        }
        println!("TASK 1 FINISHED");
    }); //... 继续创建第2~4个用户态线程
    runtime.run(); //调度执行各个线程
}
```


---
### 程序设计
用户态管理的线程结构与执行状态
```rust
struct Task { //线程控制块
    id: usize,
    stack: Vec<u8>,
    ctx: TaskContext,
    state: State,
}
```
```rust
pub struct TaskContext { //线程上下文
    x1: u64,  //ra: return addres 
    x2: u64,  //sp
    ...,  //s[0..11] 寄存器
    nx1: u64, //new return addres
}
```


---
### 程序设计
用户态管理的线程结构与执行状态
```rust
struct Task { //线程控制块
    id: usize,
    stack: Vec<u8>,
    ctx: TaskContext,
    state: State,
}
```
```rust
enum State { //线程状态
    Available,
    Running,
    Ready,
}
```


---
### 程序设计
**用户态线程管理运行时初始化**
Runtime::new() 主要有三个步骤：
- 1. 设置主线程：初始化应用主线程控制块（TID为 0 ），并设置其状态为 Running；
- 2. 设置调度队列：初始化线程控制块向量(线程调度队列)，加入应用主线程控制块和空闲线程控制块，为后续的线程运行做好准备；
- 3. 设置当前运行线程id：设置Runtime 结构变量中的 current 值为0， 表示当前正在运行的线程是应用主线程。

---
### 程序设计
**用户态线程管理运行时初始化**
Runtime::init() 的主要工作是把Rutime结构变量的地址赋值给全局可变变量`RUNTIME`。这样在多线程应用在后续执行中会根据`RUNTIME`找到Runtime结构变量。

在应用的 main() 函数中，首先会依次调用上述两个函数（new和init），完成线程管理运行时的初始化过程。这样正在运行的TID为 0 的主线程就可代表线程运行时进行后续创建线程等一系列工作。


---
### 程序设计
**用户态管理的线程创建** 
```rust
    pub fn spawn(&mut self, f: fn()) { // f函数是线程入口
        let available = self  
            .tasks.iter_mut()  //遍历队列中的任务
            .find(|t| t.state == State::Available) //查找可用的任务
            .expect("no available task.");
        let size = available.stack.len();
        unsafe {
            let s_ptr = available.stack.as_mut_ptr().offset(size as isize);
            let s_ptr = (s_ptr as usize & !7) as *mut u8; // 栈按8字节对齐
            available.ctx.x1 = guard as u64;  //ctx.x1  is old return address
            available.ctx.nx1 = f as u64;     //ctx.nx2 is new return address
            available.ctx.x2 = s_ptr.offset(-32) as u64; //cxt.x2 is sp
        }
        available.state = State::Ready; //设置任务为就绪态
    }
}
```

---
### 程序设计
**用户态管理的线程创建** 

- 在线程向量中查找一个状态为 Available 的空闲线程控制块
- 初始化该空闲线程的线程控制块的线程上下文
    -  `x1`寄存器：老的返回地址 -- `guard`函数地址
    -  `nx1`寄存器：新的返回地址 -- 输入参数 `f` 函数地址
    -  `x2` 寄存器：新的栈地址 --  available.stack+size
---
```rust
fn guard() {
    unsafe {
        let rt_ptr = RUNTIME as *mut Runtime;
        (*rt_ptr).t_return();
    };
}
fn t_return(&mut self) {
    if self.current != 0 {
        self.tasks[self.current].state = State::Available;
        self.t_yield();
    }
}
```
`guard`函数意味着我们传入的`f`函数（线程的主体）已经返回，这意味着我们的线程已完成运行其任务，因此我们取消引用我们的运行时并调用t_return()。

---
### 程序设计
**用户态管理的线程切换** 
当应用要切换线程时，会调用 yield_task 函数，通过 runtime.t_yield 函数来完成具体的切换过程。runtime.t_yield 这个函数主要完成的功能：
- 在线程向量中查找一个状态为 Ready 的线程控制块
- 把当前运行的线程的状态改为`Ready`，把新就绪线程的状态改为`Running`，把 runtime 的 current 设置为新就绪线程控制块的id
- 调用函数 switch ，完成两个线程的栈和上下文的切换；


---
### 程序设计
**用户态管理的线程切换** 
```rust
fn t_yield(&mut self) -> bool {
        ...
    self.tasks[pos].state = State::Running;
    let old_pos = self.current;
    self.current = pos;

    unsafe {
        switch(&mut self.tasks[old_pos].ctx, &self.tasks[pos].ctx);
    }
    ...
```



---
### 程序设计
**用户态管理的线程切换** 
 switch 主要完成的工作：
- 完成当前指令指针(PC)的切换；
- 完成栈指针的切换；
- 完成通用寄存器集合的切换；
---
### 程序设计
**用户态管理的线程切换** 
 switch 主要完成的工作：
```
unsafe fn switch(old: *mut TaskContext, new: *const TaskContext)  {
    // a0: _old, a1: _new
    asm!("
        sd x1, 0x00(a0)
        ...
        sd x1, 0x70(a0)
        ld x1, 0x00(a1)
        ...
        ld t0, 0x70(a1)
        jr t0
    ...
```


---
### 程序设计
**用户态管理的线程执行&调度** 
```rust
    pub fn run(&mut self){
        while self.t_yield() {} 
       println!("All tasks finished!");
    }
```



---
### 实践：TCOS
- 进化目标
- **总体思路**
    - **内核态管理的用户线程**
- 历史背景
- 实践步骤
- 软件架构
- 程序设计


![bg right:70% 100%](figs/task-abstracts.png)



---

### 总体思路 
- 如何管理协程/线程/进程？
   - 任务上下文
   - 用户态管理
   - **内核态管理**

![bg right:65% 100%](figs/task-abstracts.png)


---
### 总体思路 
- 如何管理协程/线程/进程？
   - 任务上下文
   - 用户态管理
   - **内核态管理** 
![bg right:65% 100%](figs/thread-coroutine-os-detail.png)


---
### 总体思路 
**内核态管理的用户线程**
   - 内核态管理的用户线程的任务控制块
      - 与 Lec7中的任务控制块类似
      - 重构：进程中有多个代表线程的任务控制块
```
pub struct ProcessControlBlockInner {
    pub tasks: Vec<Option<Arc<TaskControlBlock>>>,
    ...
}  
```  
![bg right:40% 100%](figs/task-abstracts.png)



---
### 实践步骤
```
git clone https://github.com/rcore-os/rCore-Tutorial-v3.git
cd rCore-Tutorial-v3
git checkout ch8
```
包含几个与内核态管理的用户线程相关的应用程序
```
user/src/bin/
├──  threads.rs
├──  threads_arg.rs
```
---
### 实践步骤
执行threads_arg这个应用程序
```
Rust user shell
>> threads_arg
aaa...bbb...ccc...aaa...bbb...ccc...
thread#1 exited with code 1
thread#2 exited with code 2
ccc...thread#3 exited with code 3
main thread exited.
...
```

---
### 程序设计
简单的内核态管理多线程应用 `threads_arg.rs`
```rust
fn thread_print(arg: *const Argument) -> ! { //线程的函数主体
    ...
    exit(arg.rc)
}
pub fn main() -> i32 {
    let mut v = Vec::new();
    for arg in args.iter() {
        v.push(thread_create( thread_print, arg ));  //创建线程
    ...
    for tid in v.iter() {
        let exit_code = waittid(*tid as usize); //等待线程结束
    ...
}
```


---
### 程序设计 -- 系统调用
在一个进程的运行过程中，进程可以创建多个属于这个进程的线程，每个线程有自己的线程标识符（TID，Thread Identifier）。系统调用 thread_create 的原型如下：
```rust
/// 功能：当前进程创建一个新的线程
/// 参数：entry 表示线程的入口函数地址
/// 参数：arg：表示线程的一个参数
pub fn sys_thread_create(entry: usize, arg: usize) -> isize
```
- 创建线程不需要建立新的地址空间
- 属于同一进程中的线程之间没有父子关系


---
### 程序设计 -- 系统调用
当一个线程执行完代表它的功能后，会通过 exit 系统调用退出。需要通过该线程需要进程/主线程调用 waittid 来回收其资源，这样整个线程才能被彻底销毁。系统调用 waittid 的原型如下：
```rust
/// 参数：tid表示线程id
/// 返回值：如果线程不存在，返回-1；如果线程还没退出，返回-2；其他情况下，返回结束线程的退出码
pub fn sys_waittid(tid: usize) -> i32
```
- 进程/主线程要负责通过 waittid 来等待它创建出来的线程（不是主线程）结束并回收它们在内核中的资源
- 如果进程/主线程先调用了 exit 系统调用来退出，那么整个进程（包括所属的所有线程）都会退出


---
### 程序设计 -- 系统调用
在引入了线程机制后，进程相关的重要系统调用：fork 、 exec 、 waitpid 虽然在接口上没有变化，但在它要完成的功能上需要有一定的扩展。
- 把以前进程中与处理器执行相关的部分拆分到线程中
- 通过 fork 创建进程其实也意味着要单独建立一个主线程来使用处理器，并为以后创建新的线程建立相应的线程控制块向量
- 相对而言， exec 和 waitpid 这两个系统调用要做的改动比较小，还是按照与之前进程的处理方式来进行
- 总体上看，进程相关的这三个系统调用还是保持了已有的进程操作的语义，并没有由于引入了线程，而带来大的变化


---
### 程序设计 -- 系统调用

问题：“被fork的子进程是否要复制父进程的多个线程？”

选择A：要复制多个线程；选择B：不复制，只复制当前执行fork的这个线程；选择C：不支持多线程进程执行fork这种情况

目前的rcore tutorial ，选择了C，简化了应用的使用场景，即在使用fork和create_thread（以及基于线程的信号量，条件变量等）是不会同时出现的。所以如果有fork，假定是这个应用是单线程的进程，所以只拷贝了这个单线程的结构。这种简化设计虽然是一种鸵鸟做法，但也避免了一些允许fork和create_thread共存而导致的比较复杂的情况：...

---
### 程序设计 -- 系统调用

问题：“被fork的子进程是否要复制父进程的多个线程？”

比如：

在fork前，有三个线程Main thread， thread A, thread B, 且Thread A拿到一个lock，在临界区中执行；Thread B正在写一个文件。如果Main thread执行fork，如采用A选择，会出现子进程的Thread B和 父进程的Thread B都在写一个文件的情况。如采用B选择，则子进程中只有Main Thread，当它想得到ThreadA的那个lock时，这个lock是得不到的（因为ThreadA 在子进程中不存在，没法释放锁），会陷入到持续忙等中。

---
### 程序设计 -- 核心数据结构
为了在现有进程管理的基础上实现线程管理，需要改进一些数据结构包含的内容及接口。基本思路就是把进程中与处理器相关的部分分拆出来，形成线程相关的部分：
- 任务控制块 TaskControlBlock ：表示线程的核心数据结构
- 任务管理器 TaskManager ：管理线程集合的核心数据结构
- 处理器管理结构 Processor ：用于线程调度，维护线程的处理器状态


---
### 程序设计 -- 核心数据结构
线程控制块
```rust
pub struct TaskControlBlock {
    pub process: Weak<ProcessControlBlock>, //线程所属的进程控制块
    pub kstack: KernelStack,//任务（线程）的内核栈
    inner: UPSafeCell<TaskControlBlockInner>,
}
pub struct TaskControlBlockInner {
    pub res: Option<TaskUserRes>,  //任务（线程）用户态资源
    pub trap_cx_ppn: PhysPageNum,//trap上下文地址
    pub task_cx: TaskContext,//任务（线程）上下文
    pub task_status: TaskStatus,//任务（线程）状态
    pub exit_code: Option<i32>,//任务（线程）退出码
}
```


---
### 程序设计 -- 核心数据结构
进程控制块
```rust
pub struct ProcessControlBlock {
    pub pid: PidHandle,
    inner: UPSafeCell<ProcessControlBlockInner>,
}
pub struct ProcessControlBlockInner {
    pub tasks: Vec<Option<Arc<TaskControlBlock>>>,
    pub task_res_allocator: RecycleAllocator,
    ...
}
```
 RecycleAllocator是PidAllocator的升级版，即一个相对通用的资源分配器，可用于分配进程标识符（PID）和线程的内核栈（KernelStack）。

 
---
### 程序设计 -- 管理机制
线程创建
当一个进程执行中发出系统调用 sys_thread_create 后，操作系统就需要在当前进程的基础上创建一个线程，即在线程控制块中初始化各个成员变量，建立好进程和线程的关系等，关键要素包括：
- 线程的用户态栈：确保在用户态的线程能正常执行函数调用
- 线程的内核态栈：确保线程陷入内核后能正常执行函数调用
- 线程的跳板页：确保线程能正确的进行用户态<–>内核态切换
- 线程上下文：即线程用到的寄存器信息，用于线程切换


---
### 程序设计 -- 管理机制
线程创建
```rust
pub fn sys_thread_create(entry: usize, arg: usize) -> isize {
    // create a new thread
    let new_task = Arc::new(TaskControlBlock::new(...
    // add new task to scheduler
    add_task(Arc::clone(&new_task));
    // add new thread to current process
    let tasks = &mut process_inner.tasks;
    tasks[new_task_tid] = Some(Arc::clone(&new_task));
    *new_task_trap_cx = TrapContext::app_init_context( //建立trap/task上下文
        entry,
        new_task_res.ustack_top(),
        kernel_token(),
    ... 
```

---
### 程序设计 -- 管理机制
线程退出
- 当一个非主线程的其他线程发出 sys_exit 系统调用时，内核会调用 exit_current_and_run_next 函数退出当前线程并切换到下一个线程，但不会导致其所属进程的退出。
- 当主线程 即进程发出这个系统调用，当内核收到这个系统调用后，会回收整个进程（这包括了其管理的所有线程）资源，并退出。


---
### 程序设计 -- 管理机制
线程退出
```rust
pub fn sys_exit(exit_code: i32) -> ! {
    exit_current_and_run_next(exit_code); ...
pub fn exit_current_and_run_next(exit_code: i32) { 
    let task = take_current_task().unwrap();
    let mut task_inner = task.inner_exclusive_access();   
    drop(task_inner); //释放线程资源
    drop(task);  //释放线程控制块
     if tid == 0 {
        // 释放当前进程的所有线程资源
        // 释放当前进程的资源
...
```




---
### 程序设计 -- 管理机制
等待线程结束
- 如果找到 tid 对应的线程，则尝试收集该线程的退出码 exit_tid ，否则返回错误（退出线程不存在）。
- 如果退出码存在(意味该线程确实退出了)，则清空进程中对应此线程的线程控制块（至此，线程所占资源算是全部清空了），否则返回错误（线程还没退出）。

---
### 程序设计 -- 管理机制
```rust
pub fn sys_waittid(tid: usize) -> i32 {
    ...
    if let Some(waited_task) = waited_task {
        if let Some(waited_exit_code) = waited_task.....exit_code {
            exit_code = Some(waited_exit_code);
        }
    } else {
        return -1; // waited thread does not exist
    }
    if let Some(exit_code) = exit_code {
        process_inner.tasks[tid] = None; //dealloc the exited thread
        exit_code
    } else {
        -2 // waited thread has not exited
    }
```

---
### 程序设计 -- 管理机制
线程执行中的特权级切换和调度切换

- 线程执行中的特权级切换与第四讲中介绍的任务切换的设计与实现是一致的
- 线程执行中的调度切换过程与第七讲中介绍的进程调度机制是一致的


---
### 小结
- 用户态管理的用户线程
- 内核态管理的用户线程
- 能写达科塔盗龙OS

![bg right 70%](figs/dakotaraptor.png)