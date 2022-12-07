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

# 第十二讲 同步与互斥

## 第六节 支持同步互斥的OS(SMOS)


---
### 实践：SMOS
- **进化目标**
- 总体思路
- 历史背景
- 实践步骤
- 程序设计

![bg right:65% 100%](figs/thread-coroutine-os-detail.png)


---
### 实践：SMOS -- 以往目标
提高性能、简化开发、加强安全、支持数据持久保存、支持应用的灵活性，支持进程间交互，支持线程和协程
- TCOS：支持线程和协程  ； IPC OS：进程间交互
- Filesystem OS：支持数据持久保存
- Process OS: 增强进程管理和资源管理
- Address Space OS: 隔离APP访问的内存地址空间
- multiprog & time-sharing OS: 让APP共享CPU资源
- BatchOS： 让APP与OS隔离，加强系统安全，提高执行效率
- LibOS: 让APP与HW隔离，简化应用访问硬件的难度和复杂性

---
### 实践：SMOS -- 进化目标
在多线程中支持对共享资源的同步互斥访问
- 互斥锁机制
- 信号量机制
- 管程与条件变量机制


---
### 实践：SMOS 
### 同学的进化目标
- 理解同步互斥的各种机制
- 理解用同步互斥机制解决同步互斥问题
- 会写支持线程间同步互斥的OS


<!-- 慈母龙英文名(maiasaura)的含义是“好妈妈蜥蜴”。1979年在美国蒙大拿，科学家们发现了一些恐龙窝，其中有小恐龙的骨架。于是他们把这种恐龙命名为慈母龙。。 -->

![bg right 80%](figs/maiasaura.png)

---
### 实践：SMOS
- 进化目标
- **总体思路**
    - **同步互斥**
- 历史背景
- 实践步骤
- 程序设计

![bg right:70% 100%](figs/syncmutex-os-key-structures.png)

---
### 实践：SMOS
- 进化目标
- **总体思路**
    - **同步互斥**
- 历史背景
- 实践步骤
- 程序设计

![bg right:70% 100%](figs/syncmutex-os-detail.png)


---
### 实践：SMOS
历史背景
- 1963年前后，当时的数学家 Edsger Dijkstra和他的团队正在为Electrologica X8计算机开发一个操作系统（THE多道程序系统）的过程中，提出了信号（Semaphore）是一种变量或抽象数据类型，用于控制多个线程对共同资源的访问。
- Brinch Hansen(1973)和Hoare(1974)结合操作系统和Concurrent Pascal编程语言，提出了一种高级同步原语，称为管程(monitor)。一个管程是一个由过程（procedures，Pascal语言的术语，即函数）、共享变量等组成的集合。线程可调用管程中的过程。

---
### 实践步骤
```
git clone https://github.com/rcore-os/rCore-Tutorial-v3.git
cd rCore-Tutorial-v3
git checkout ch8
```
包含了多个同步互斥相关的多线程应用程序
```
user/src/bin/
├──  mpsc_sem.rs          # 基于信号量的生产者消费者问题
├──  phil_din_mutex.rs    # 基于互斥锁的哲学家问题
├──  race_adder_*.rs      # 各种方式的全局变量累加问题
├──  sync_sem.rs          # 基于信号量的同步操作
├──  test_condvar.rs      # 基于条件变量的同步操作
```

---
### 实践步骤
内核代码的主要改进部分
```
os/src/
├── sync
│   ├── condvar.rs        //条件变量
│   ├── mod.rs 
│   ├── mutex.rs          //互斥锁
│   ├── semaphore.rs      //信号量
│   └── up.rs
├── syscall
│   ├── sync.rs //增加了互斥锁、信号量和条件变量相关系统调用
├── task
│   ├── process.rs //进程控制块增加了互斥锁、信号量和条件变量
├── timer.rs     // 添加与定时相关的TimerCondVar类条件变量
```

---
### 实践步骤
比如执行哲学家问题的应用程序，展示了5个哲学家用5把叉子进行思考/进餐/休息的过程。
```
Rust user shell
>> phil_din_mutex
time cost = 7271
'-' -> THINKING; 'x' -> EATING; ' ' -> WAITING
#0: -------                 xxxxxxxx----------       xxxx-----  xxxxxx--xxx
#1: ---xxxxxx--      xxxxxxx----------    x---xxxxxx
#2: -----          xx---------xx----xxxxxx------------        xxxx
#3: -----xxxxxxxxxx------xxxxx--------    xxxxxx--   xxxxxxxxx
#4: ------         x------          xxxxxx--    xxxxx------   xx
#0: -------                 xxxxxxxx----------       xxxx-----  xxxxxx--xxx
>>
```

---
### 实践步骤
全局变量累加问题的多线程应用 `race_adder.rs`
```
A           //全局变量 
A=A+1       //多个线程对A进行累加 
```
多个线程执行上述代码，真的会出现Race Condition（竞争条件）吗？

- 并发、无序的线程在使用有限、独占、不可抢占的资源而产生矛盾称为竞争（Race）
- 多个线程无序竞争不能被同时访问的资源而出现执行出错的问题，称为竞争条件（Race Condition）

---
### 实践步骤
全局变量累加问题的多线程应用 `race_adder.rs`
```rust
pub fn main() -> i32 {
    let start = get_time();
    let mut v = Vec::new();
    for _ in 0..THREAD_COUNT {
        v.push(thread_create(f as usize, 0) as usize);  // f函数是线程主体
    }
    let mut time_cost = Vec::new();
    for tid in v.iter() {
        time_cost.push(waittid(*tid));
    }
    println!("time cost is {}ms", get_time() - start);
    assert_eq!(unsafe { A }, PER_THREAD * THREAD_COUNT); //比较累计值A
    0
}
```


---
### 实践步骤
全局变量累加问题的多线程应用 `race_adder.rs`
```rust
unsafe fn f() -> ! {
    let mut t = 2usize;
    for _ in 0..PER_THREAD {    
        let a = &mut A as *mut usize;    // “缓慢执行”A=A+1 
        let cur = a.read_volatile();     // “缓慢执行”A=A+1
        for _ in 0..500 {  t = t * t % 10007; } // 增加切换概率
        a.write_volatile(cur + 1);      // “缓慢执行”A=A+1
    }
    exit(t as i32)
}
```
---
### 实践步骤
全局变量累加问题的多线程应用 `race_adder.rs`
```
>> race_adder
time cost is 31ms
Panicked at src/bin/race_adder.rs:40, assertion failed: `(left == right)`
  left: `15788`,
 right: `16000`
[kernel] Aborted, SIGABRT=6
```
每次都会执行都会出现Race Condition（竞争条件）！


---
### 实践步骤
基于原子操作的全局变量累加问题的多线程应用 `race_adder_atomic.rs`
```rust
unsafe fn f() -> ! {
    for _ in 0..PER_THREAD {
        while OCCUPIED
            .compare_exchange(false, true, Ordering::Relaxed, Ordering::Relaxed)
            .is_err()  {  yield_(); }           // 基于CAS操作的近似spin lock操作
        let a = &mut A as *mut usize;           // “缓慢执行”A=A+1 
        let cur = a.read_volatile();            // “缓慢执行”A=A+1 
        for _ in 0..500 { t = t * t % 10007; }  // 增加切换概率
        a.write_volatile(cur + 1);              // “缓慢执行”A=A+1 
        OCCUPIED.store(false, Ordering::Relaxed);  // unlock操作
    }
    ...
```
---
### 实践步骤
基于原子操作的全局变量累加问题的多线程应用 `race_adder_atomic.rs`

```
>> race_adder_atomic
time cost is 29ms
>> race_adder_loop
```
可以看到，执行速度快，且正确。

---
### 实践步骤
基于互斥锁的多线程应用 `race_adder_mutex_[spin|block]`
```rust
unsafe fn f() -> ! {
    let mut t = 2usize;
    for _ in 0..PER_THREAD {
        mutex_lock(0); //lock(id)
        let a = &mut A as *mut usize;   // “缓慢执行”A=A+1 
        let cur = a.read_volatile();    // “缓慢执行”A=A+1 
        for _ in 0..500 {  t = t * t % 10007; } // 增加切换概率
        a.write_volatile(cur + 1);      // “缓慢执行”A=A+1 
        mutex_unlock(0); //unlock(id)
    }
    exit(t as i32)
}
```
---
### 实践步骤
基于互斥锁的全局变量累加问题的多线程应用 `race_adder_mutex_spin`
```
>> race_adder_mutex_spin  
time cost is 249ms
# 执行系统调用，且进行在就绪队列上的取出/插入/等待操作
```

基于互斥锁的全局变量累加问题的多线程应用 `race_adder_mutex_block`
```
>> race_adder_mutex_blocking
time cost is 919ms  
# 执行系统调用，且进行在就绪队列+等待队列上的取出/插入/等待操作
```

---
###  程序设计
spin mutex和 block mutex 的核心数据结构： `UPSafeCell`
```rust
pub struct UPSafeCell<T> { //允许在单核上安全使用可变全局变量
    inner: RefCell<T>,  //提供内部可变性和运行时借用检查
}
unsafe impl<T> Sync for UPSafeCell<T> {} //声明支持全局变量安全地在线程间共享
impl<T> UPSafeCell<T> {
    pub unsafe fn new(value: T) -> Self {
        Self { inner: RefCell::new(value) }
    }
    pub fn exclusive_access(&self) -> RefMut<'_, T> {
        self.inner.borrow_mut()  //得到它包裹的数据的独占访问权
    }
}
```

---
###  程序设计
spin mutex和 block mutex 的核心数据结构
```rust
pub struct MutexSpin {
    locked: UPSafeCell<bool>,  //locked是被UPSafeCell包裹的布尔全局变量
}
pub struct MutexBlocking {
    inner: UPSafeCell<MutexBlockingInner>,
}
pub struct MutexBlockingInner {
    locked: bool,
    wait_queue: VecDeque<Arc<TaskControlBlock>>, //等待获取锁的线程等待队列
}
```


 ---
###  程序设计
spin mutex的相关函数
```rust
pub trait Mutex: Sync + Send { //Send表示跨线程 move，Sync表示跨线程share data
    fn lock(&self);
    fn unlock(&self);
}

    fn unlock(&self) {
        let mut locked = self.locked.exclusive_access(); //独占访问locked
        *locked = false; //
    }
```

---
###  程序设计
spin mutex的相关函数
```rust
impl Mutex for MutexSpin {
    fn lock(&self) {
        loop {
            let mut locked = self.locked.exclusive_access(); //独占访问locked
            if *locked {
                drop(locked);
                suspend_current_and_run_next(); //把当前线程放到就绪队列末尾
                continue;
            } else {
                *locked = true; //得到锁了，可以继续进入临界区执行
                return;
        ...
 ```   


---
###  程序设计
block mutex的相关函数
```rust
impl Mutex for MutexBlocking {
    fn lock(&self) {
        let mut mutex_inner = self.inner.exclusive_access(); //独占访问mutex_inner
        if mutex_inner.locked {
            //把当前线程挂到此lock相关的等待队列中
            mutex_inner.wait_queue.push_back(current_task().unwrap());
            drop(mutex_inner);
            //把当前线程从就绪队列中取出，设置为阻塞态，切换到另一就绪线程执行
            block_current_and_run_next();
        } else {
            mutex_inner.locked = true; //得到锁了，可以继续进入临界区执行
        }
    }
```


---
###  程序设计
block mutex的相关函数
```rust
    fn unlock(&self) {
        let mut mutex_inner = self.inner.exclusive_access();
        assert!(mutex_inner.locked);
        //从等待队列中取出线程，并放入到就绪队列中
        if let Some(waking_task) = mutex_inner.wait_queue.pop_front() {
            add_task(waking_task); 
        } else {
            mutex_inner.locked = false; //释放锁
        }
    }
```
---
### 实践步骤
基于信号量的多线程应用 `sync_sem`
```rust
pub fn main() -> i32 {
    // create semaphores
    assert_eq!(semaphore_create(0) as usize, SEM_SYNC);
    // create threads
    let threads = vec![
        thread_create(first as usize, 0),
        thread_create(second as usize, 0),
    ];
    // wait for all threads to complete
    for thread in threads.iter() {
        waittid(*thread as usize);
    }
...
```

---
### 实践步骤
基于信号量的多线程应用 `sync_sem`
```rust
unsafe fn first() -> ! {
    sleep(10);
    println!("First work and wakeup Second");
    semaphore_up(SEM_SYNC);
    exit(0)
}
unsafe fn second() -> ! {
    println!("Second want to continue,but need to wait first");
    semaphore_down(SEM_SYNC);
    println!("Second can work now");
    exit(0)
}
```

---
### 实践步骤
基于信号量的多线程应用 `sync_sem`
```
>> sync_sem
Second want to continue,but need to wait first
First work and wakeup Second
Second can work now
sync_sem passed!
```
- 信号量初值设为0
- semaphore_down() ：线程会挂起/阻塞（suspend/block）
- semaphore_up()：会唤醒挂起的线程

---
###  程序设计
semaphore的核心数据结构
```rust
pub struct Semaphore {
    pub inner: UPSafeCell<SemaphoreInner>, //UPSafeCell包裹的内部可变结构
}

pub struct SemaphoreInner {
    pub count: isize, //信号量的计数值
    pub wait_queue: VecDeque<Arc<TaskControlBlock>>, //信号量的等待队列
}
```

---
###  程序设计
semaphore的相关函数
```rust
    pub fn down(&self) {
        let mut inner = self.inner.exclusive_access();
        inner.count -= 1; //信号量的计数值减一
        if inner.count < 0 {
            inner.wait_queue.push_back(current_task().unwrap()); //放入等待队列
            drop(inner);
            //把当前线程从就绪队列中取出，设置为阻塞态，切换到另一就绪线程执行
            block_current_and_run_next();
        }
    }
```


---
###  程序设计
semaphore的相关函数
```rust
    pub fn up(&self) {
        let mut inner = self.inner.exclusive_access();
        inner.count += 1;//信号量的计数值加一
        if inner.count <= 0 {
            //从等待队列中取出线程，并放入到就绪队列中
            if let Some(task) = inner.wait_queue.pop_front() {
                add_task(task);
            }
        }
    }
```



---
### 实践步骤
基于互斥锁和条件变量的多线程应用 `test_condvar`
```rust
pub fn main() -> i32 {
    // create condvar & mutex
    assert_eq!(condvar_create() as usize, CONDVAR_ID);
    assert_eq!(mutex_blocking_create() as usize, MUTEX_ID);
    // create threads
    let threads = vec![ thread_create(first as usize, 0),
                        thread_create(second as usize, 0),];
    // wait for all threads to complete
    for thread in threads.iter() {
        waittid(*thread as usize);
    }
    ...
```

---
### 实践步骤
基于互斥锁和条件变量的多线程应用 `test_condvar`
```rust
unsafe fn second() -> ! {
    println!("Second want to continue,but need to wait A=1");
    mutex_lock(MUTEX_ID);
    while A == 0 {
        println!("Second: A is {}", A);
        condvar_wait(CONDVAR_ID, MUTEX_ID);
    }
    mutex_unlock(MUTEX_ID);
    println!("A is {}, Second can work now", A);
    exit(0)
}
```

---
### 实践步骤
基于互斥锁和条件变量的多线程应用 `test_condvar`
```rust
unsafe fn first() -> ! {
    sleep(10);
    println!("First work, Change A --> 1 and wakeup Second");
    mutex_lock(MUTEX_ID);
    A = 1;
    condvar_signal(CONDVAR_ID);
    mutex_unlock(MUTEX_ID);
    exit(0)
}
```

---
### 实践步骤
基于互斥锁和条件变量的多线程应用 `test_condvar`
```
>> test_condvar
Second: A is 0
First work, Change A --> 1 and wakeup Second
A is 1, Second can work now
```
- `second`先执行，但由于`A==0`，使得等在条件变量上
- `first`后执行，但会先于`second`，并通过条件变量唤醒`second`

---
###  程序设计
condvar的核心数据结构
```rust
pub struct Condvar {
    pub inner: UPSafeCell<CondvarInner>, //UPSafeCell包裹的内部可变结构
}

pub struct CondvarInner {
    pub wait_queue: VecDeque<Arc<TaskControlBlock>>,//等待队列
}
```

---
###  程序设计
condvar的相关函数
```rust
    pub fn wait(&self, mutex: Arc<dyn Mutex>) {
        mutex.unlock(); //释放锁
        let mut inner = self.inner.exclusive_access();
        inner.wait_queue.push_back(current_task().unwrap()); //放入等待队列
        drop(inner);
        //把当前线程从就绪队列中取出，设置为阻塞态，切换到另一就绪线程执行
        block_current_and_run_next();
        mutex.lock();
    }
```

---
###  程序设计
condvar的相关函数
```rust
    pub fn signal(&self) {
        let mut inner = self.inner.exclusive_access();
        //从等待队列中取出线程，并放入到就绪队列中
        if let Some(task) = inner.wait_queue.pop_front() {
            add_task(task);
        }
    }
```

---
###  程序设计
sleep的设计实现
```rust
pub fn sys_sleep(ms: usize) -> isize {
    let expire_ms = get_time_ms() + ms;
    let task = current_task().unwrap();
    add_timer(expire_ms, task);
    block_current_and_run_next();
    0
}
```
---
### 小结
- 学习掌握面向多线程应用的同步互斥机制
   - 互斥锁
   - 信号量
   - 条件变量
   - 原子操作
- 能写慈母龙OS

![bg right 70%](figs/maiasaura.png)