## 20200331-第十四讲内容准备

[v1]()

https://doc.rust-lang.org/std/sync/struct.RwLock.html
Struct std::sync::RwLock
A reader-writer lock

https://zh.cppreference.com/w/cpp/language/raii
RAII：资源获取即初始化（Resource Acquisition Is Initialization）
Resource Acquisition Is Initialization or RAII, is a C++ programming technique which binds the life cycle of a resource that must be acquired before use (allocated heap memory, thread of execution, open socket, open file, locked mutex, disk space, database connection—anything that exists in limited supply) to the lifetime of an object. 

https://github.com/tafia/quick-xml
Rust high performance xml reader and writer 

https://rfc1149.net/blog/2011/01/07/the-third-readers-writers-problem/
The third readers-writers problem

### Rc：单线程的引用计数

https://doc.rust-lang.org/rust-by-example/std/rc.html
Rc(Reference Counting)

A single-threaded reference-counting pointer. 'Rc' stands for 'Reference Counted'.

https://doc.rust-lang.org/1.37.0/src/alloc/rc.rs.html#273-276

```rust
pub struct Rc<T: ?Sized> {
    ptr: NonNull<RcBox<T>>,
    phantom: PhantomData<T>,
}
```

可以直接在页面上运行的小例子；

### Sync

https://zhuanlan.zhihu.com/p/64699643
如何理解 rust 中的 Sync、Send？

https://doc.rust-lang.org/std/sync/index.html
Module std::sync

https://doc.rust-lang.org/std/sync/index.html#higher-level-synchronization-objects
Higher-level synchronization objects

Arc: Atomically Reference-Counted pointer, which can be used in multithreaded environments to prolong the lifetime of some data until all the threads have finished using it.

Barrier: Ensures multiple threads will wait for each other to reach a point in the program, before continuing execution all together.

Condvar: Condition Variable, providing the ability to block a thread while waiting for an event to occur.

mpsc: Multi-producer, single-consumer queues, used for message-based communication. Can provide a lightweight inter-thread synchronisation mechanism, at the cost of some extra memory.

Mutex: Mutual Exclusion mechanism, which ensures that at most one thread at a time is able to access some data.

Once: Used for thread-safe, one-time initialization of a global variable.

RwLock: Provides a mutual exclusion mechanism which allows multiple readers at the same time, while allowing only one writer at a time. In some cases, this can be more efficient than a mutex.

#### Arc: Atomically Reference-Counted pointer

https://doc.rust-lang.org/std/sync/struct.Arc.html
Struct std::sync::Arc

A thread-safe reference-counting pointer. 'Arc' stands for 'Atomically Reference Counted'.

https://doc.rust-lang.org/src/alloc/sync.rs.html#196-199
```rust
pub struct Arc<T: ?Sized> {
    ptr: NonNull<ArcInner<T>>,
    phantom: PhantomData<ArcInner<T>>,
}
```

impl<T> Arc<T>
pub fn new(data: T) -> Arc<T>
pub fn new_uninit() -> Arc<MaybeUninit<T>>
pub fn new_zeroed() -> Arc<MaybeUninit<T>>
pub fn pin(data: T) -> Pin<Arc<T>>
pub fn try_unwrap(this: Arc<T>) -> Result<T, Arc<T>>
pub fn new_uninit_slice(len: usize) -> Arc<[MaybeUninit<T>]>
pub unsafe fn assume_init(self) -> Arc<[T]>
pub fn into_raw(this: Arc<T>) -> *const T
pub unsafe fn from_raw(ptr: *const T) -> Arc<T>
pub fn into_raw_non_null(this: Arc<T>) -> NonNull<T>
pub fn downgrade(this: &Arc<T>) -> Weak<T>
pub fn weak_count(this: &Arc<T>) -> usize
pub fn strong_count(this: &Arc<T>) -> usize
pub fn ptr_eq(this: &Arc<T>, other: &Arc<T>) -> bool
pub fn make_mut(this: &mut Arc<T>) -> &mut T
pub fn get_mut(this: &mut Arc<T>) -> Option<&mut T>
pub unsafe fn get_mut_unchecked(this: &mut Arc<T>) -> &mut T
pub fn downcast<T>(self) -> Result<Arc<T>, Arc<dyn Any + 'static + Send + Sync>> 

https://doc.rust-lang.org/src/alloc/sync.rs.html#943
fn clone(&self)

#### atomic
https://doc.rust-lang.org/core/sync/atomic/index.html
Module core::sync::atomic

Atomic types provide primitive shared-memory communication between threads, and are the building blocks of other concurrent types.

```rust
pub struct AtomicBool {
    v: UnsafeCell<u8>,
}
```

atomic_load

https://doc.rust-lang.org/src/core/intrinsics.rs.html#310
pub fn atomic_xchg<T>(dst: *mut T, src: T) -> T;

https://doc.rust-lang.org/core/sync/atomic/struct.AtomicUsize.html
Struct core::sync::atomic::AtomicUsize

https://doc.rust-lang.org/src/core/sync/atomic.rs.html#1229-1231
```rust
pub struct $atomic_type {
            v: UnsafeCell<$int_type>,
        }
```


```rust
impl AtomicUsize
pub const fn new(v: usize) -> Self
pub fn get_mut(&mut self) -> &mut usize
pub fn into_inner(self) -> usize
pub fn load(&self, order: Ordering) -> usize
pub fn store(&self, val: usize, order: Ordering)
pub fn swap(&self, val: usize, order: Ordering) -> usize
pub fn compare_and_swap
pub fn compare_exchange
pub fn compare_exchange_weak
pub fn fetch_add(&self, val: usize, order: Ordering) -> usize
pub fn fetch_sub(&self, val: usize, order: Ordering) -> usize
pub fn fetch_and(&self, val: usize, order: Ordering) -> usize
pub fn fetch_nand(&self, val: usize, order: Ordering) -> usize
pub fn fetch_or(&self, val: usize, order: Ordering) -> usize
pub fn fetch_xor(&self, val: usize, order: Ordering) -> usize
pub fn fetch_update<F>
pub fn fetch_max(&self, val: usize, order: Ordering) -> usize
pub fn fetch_min(&self, val: usize, order: Ordering) -> usize
pub fn as_mut_ptr(&self) -> *mut usize
```

https://doc.rust-lang.org/src/core/sync/atomic.rs.html#1428-1431

```rust
pub fn swap(&self, val: $int_type, order: Ordering) -> $int_type {
                    // SAFETY: data races are prevented by atomic intrinsics.
                    unsafe { atomic_swap(self.v.get(), val, order) }
}
```

https://doc.rust-lang.org/src/core/sync/atomic.rs.html#148-150
pub fn spin_loop_hint()

#### Barrier

https://doc.rust-lang.org/std/sync/struct.Barrier.html
Struct std::sync::Barrier

```rust
pub struct Barrier {
    lock: Mutex<BarrierState>,
    cvar: Condvar,
    num_threads: usize,
}
```

```rust
impl Barrier
pub fn new(n: usize) -> Barrier
pub fn wait(&self) -> BarrierWaitResult
```

##### 演示

https://doc.rust-lang.org/std/sync/struct.Barrier.html

有一个例子可演示；

https://doc.rust-lang.org/src/std/sync/barrier.rs.html#128-145
pub fn wait(&self) -> BarrierWaitResult

lock = self.cvar.wait(lock).unwrap();

#### Condvar

https://doc.rust-lang.org/std/sync/struct.Condvar.html
Struct std::sync::Condvar

Condition variables represent the ability to block a thread such that it consumes no CPU time while waiting for an event to occur. Condition variables are typically associated with a boolean predicate (a condition) and a mutex. The predicate is always verified inside of the mutex before determining that a thread must block.

```rust
pub struct Condvar {
    inner: Box<sys::Condvar>,
    mutex: AtomicUsize,
}
```
```rust
impl Condvar
pub fn new() -> Condvar
pub fn wait<'a, T>
pub fn wait_while<'a, T, F>
pub fn wait_timeout_ms<'a, T>
pub fn wait_timeout<'a, T>
pub fn wait_timeout_while<'a, T, F>
pub fn notify_one(&self)
pub fn notify_all(&self)
```

##### 演示

https://play.rust-lang.org/

```rust 
#![allow(unused)]
fn main() {
use std::sync::{Arc, Mutex, Condvar};
use std::thread;

let pair = Arc::new((Mutex::new(false), Condvar::new()));
let pair2 = pair.clone();

// Inside of our lock, spawn a new thread, and then wait for it to start.
thread::spawn(move|| {
    let (lock, cvar) = &*pair2;
    let mut started = lock.lock().unwrap();
    *started = true;
    // We notify the condvar that the value has changed.
    println!("notify_one");
    cvar.notify_one();
});

// Wait for the thread to start up.
let (lock, cvar) = &*pair;
let mut started = lock.lock().unwrap();
while !*started {
    println!("before wait");
    started = cvar.wait(started).unwrap();
    println!("after wait");
}
}
```
##### 演示：notify_all

```rust
#![allow(unused)]
fn main() {
use std::sync::{Arc, Mutex, Condvar};
use std::thread;

let pair = Arc::new((Mutex::new(false), Condvar::new()));
let pair2 = pair.clone();

thread::spawn(move|| {
    let (lock, cvar) = &*pair2;
    let mut started = lock.lock().unwrap();
    *started = true;
    // We notify the condvar that the value has changed.
    println!("notify_all");
    cvar.notify_all();
});

// Wait for the thread to start up.
let (lock, cvar) = &*pair;
let mut started = lock.lock().unwrap();
// As long as the value inside the `Mutex<bool>` is `false`, we wait.
while !*started {
    println!("before wait");
    started = cvar.wait(started).unwrap();
    println!("after wait");
}
}
```
##### wait()函数的实验
https://doc.rust-lang.org/src/std/sync/condvar.rs.html#196-204
pub fn wait<'a, T>(&self, guard: MutexGuard<'a, T>) -> LockResult<MutexGuard<'a, T>>

self.inner.wait(lock);

#### mpsc::channel

https://doc.rust-lang.org/std/sync/mpsc/index.html
Module std::sync::mpsc

https://doc.rust-lang.org/std/sync/mpsc/fn.channel.html
std::sync::mpsc::channel

Creates a new asynchronous channel, returning the sender/receiver halves.

https://doc.rust-lang.org/src/std/sync/mpsc/mod.rs.html#711-714
```rust
pub fn channel<T>() -> (Sender<T>, Receiver<T>) {
    let a = Arc::new(oneshot::Packet::new());
    (Sender::new(Flavor::Oneshot(a.clone())), Receiver::new(Flavor::Oneshot(a)))
}
```
#### mpsc::sync_channel

https://doc.rust-lang.org/std/sync/mpsc/fn.sync_channel.html
std::sync::mpsc::sync_channel

Creates a new synchronous, bounded channel. 

https://doc.rust-lang.org/src/std/sync/mpsc/mod.rs.html#764-767

```rust
pub fn sync_channel<T>(bound: usize) -> (SyncSender<T>, Receiver<T>) {
    let a = Arc::new(sync::Packet::new(bound));
    (SyncSender::new(a.clone()), Receiver::new(Flavor::Sync(a)))
}
```

#### Once

https://doc.rust-lang.org/std/sync/struct.Once.html
Struct std::sync::Once

Performs an initialization routine once and only once. The given closure will be executed if this is the first time call_once has been called, and otherwise the routine will not be invoked.

This method will block the calling thread if another initialization routine is currently running.

https://doc.rust-lang.org/rust-by-example/std_misc/ffi.html?highlight=ffi#foreign-function-interface
Foreign Function Interface

#### RwLock

https://doc.rust-lang.org/std/sync/struct.RwLock.html
Struct std::sync::RwLock

This type of lock allows a number of readers or at most one writer at any point in time. The write portion of this lock typically allows modification of the underlying data (exclusive access) and the read portion of this lock typically allows for read-only access (shared access).

```rust
pub struct RwLock<T: ?Sized> {
    inner: Box<sys::RWLock>,
    poison: poison::Flag,
    data: UnsafeCell<T>,
}
```
impl<T: ?Sized> RwLock<T>
pub fn read(&self) -> LockResult<RwLockReadGuard<T>>
pub fn try_read(&self) -> TryLockResult<RwLockReadGuard<T>>
pub fn write(&self) -> LockResult<RwLockWriteGuard<T>>
pub fn try_write(&self) -> TryLockResult<RwLockWriteGuard<T>>
pub fn is_poisoned(&self) -> bool
pub fn into_inner(self) -> LockResult<T>
pub fn get_mut(&mut self) -> LockResult<&mut T>

### Mutex

https://doc.rust-lang.org/std/sync/struct.Mutex.html
Struct std::sync::Mutex
A mutual exclusion primitive useful for protecting shared data

impl<T> Mutex<T>
pub fn new(t: T) -> Mutex<T>
pub fn lock(&self) -> LockResult<MutexGuard<T>>
pub fn try_lock(&self) -> TryLockResult<MutexGuard<T>>
pub fn is_poisoned(&self) -> bool
pub fn into_inner(self) -> LockResult<T>
pub fn get_mut(&mut self) -> LockResult<&mut T>

这里有mutex的例子和实现描述；

https://doc.rust-lang.org/src/std/sync/mutex.rs.html#111
struct Mutex的实现

```rust
pub struct Mutex<T: ?Sized> {
    // Note that this mutex is in a *box*, not inlined into the struct itself.
    // Once a native mutex has been used once, its address can never change (it
    // can't be moved). This mutex type can be safely moved at any time, so to
    // ensure that the native mutex is used correctly we box the inner mutex to
    // give it a constant address.
    inner: Box<sys::Mutex>,
    poison: poison::Flag,
    data: UnsafeCell<T>,
}
```

https://zhuanlan.zhihu.com/p/52401660
Rust学习（37）：线程通讯 - mutex

#### MutexGuard

inner.raw_lock

https://stackoverflow.com/questions/51335679/where-is-a-mutexguard-if-i-never-assign-it-to-a-variable
Where is a MutexGuard if I never assign it to a variable?

Place expressions and value expressions
place contexts and value contexts

#### &mut

https://stackoverflow.com/questions/31298802/let-mut-syntax
Let &mut syntax

#### pointers

https://doc.rust-lang.org/std/primitive.pointer.html
Common ways to create raw pointers

值引用
reference (&T)
在生命期内的变量引用
mutable reference (&mut T).

#### box

boxed value

https://doc.rust-lang.org/std/boxed/struct.Box.html
Struct std::boxed::Box

https://doc.rust-lang.org/rust-by-example/std/box.html
Box, stack and heap

Box: A pointer type for heap allocation.

https://stackoverflow.com/questions/30352802/what-does-the-box-keyword-do
What does the box keyword do?

#### lock

https://doc.rust-lang.org/std/sync/struct.RwLock.html
Struct std::sync::RwLock

https://doc.rust-lang.org/src/std/sync/rwlock.rs.html#222
pub fn try_read(&self)

https://doc.rust-lang.org/src/std/sync/rwlock.rs.html#183
pub fn read(&self)

#### Poisoning

https://doc.rust-lang.org/nomicon/poisoning.html
Poisoning

Mutex poisons not for true safety in the sense that Rust normally cares about. It poisons as a safety-guard against blindly using the data that comes out of a Mutex that has witnessed a panic while locked.

#### InnerAttribute & OuterAttribute

https://doc.rust-lang.org/reference/attributes.html
Attributes

*InnerAttribute* :
  `#` `!` `[` *Attr* `]`

*OuterAttribute* :
  `#` `[` *Attr* `]`

#### Unwrap and Expect
这是rust语言的错误信息输出机制，用于函数执行出错时的信息输出。

https://learning-rust.github.io/docs/e4.unwrap_and_expect.html
Unwrap and Expect

unwrap()
The functionality is bit similar to the following codes, which are using match instead unwrap().

expect()
Similar to unwrap() but can set a custom message for the panics.

https://stackoverflow.com/questions/36362020/what-is-unwrap-in-rust-and-what-is-it-used-for
What is unwrap in Rust, and what is it used for?