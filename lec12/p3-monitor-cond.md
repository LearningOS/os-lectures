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

## 第三节 管程与条件变量

 管程（Moniter）  条件变量（CoCondVar）
 

---
### 管程 
- 动机：为什么有管程？ 传统PV和锁机制有如下问题：
  - 程序易读性差：要了解对于一组共享变量及信号量的操作是否正确，则必须通读整个系统或者并发程序。
  - 程序不利于修改和维护：程序局部性很差，所以任一组变量或一段代码的修 改都可能影响全局。
  - 正确性难以保证：操作系统或并发程序通常很大，要保证这样一个复杂的系统没有逻辑错误很难。
  - 容易发生死锁：如果不使用好P、V操作时，逻辑上发生错误，很有可能会导致死锁。

---
### 管程
- 管程是一种用于多线程互斥访问共享资源的程序结构
- 采用面向对象方法，简化了线程间的同步控制
- 任一时刻最多只有一个线程执行管程代码
- 正在管程中的线程可临时放弃管程的互斥访问，等待事件出现时恢复
![w:600](figs/basic-monitor.png)

---
### 管程 -- 条件变量
- 管程的组成：一个由过程（函数）、变量及数据结构等组成的一个集合
   - 一个锁：控制管程代码的互斥访问
   - 0或者多个条件变量: 管理共享数据的并发访问，每个条件变量有个等待（紧急）队列
   - 入口：入口等待队列
![bg right:40% 100%](figs/moniter.jpg)

---
### 管程 -- 条件变量
- 管程中的共享变量在管程外部是不可见的，外部只能通过调用管程中所说明的外部过程 (函数）来间接地访问管程中的共享变量
  - 规定管程互斥进入；
  - 管程中设有进程等待队以及相应的等待及唤醒操作。
![bg right:40% 100%](figs/basic-monitor-2.png)


---
### 管程 -- 条件变量
- 互斥：任一时刻管程中只能有一个活跃进程
   - 进入管程的线程因资源被占用而进入等待状态
   - 每个条件变量表示一种等待原因，对应一个等待队列
   - 入口队列管理未进入管程的线程/进程
![bg right:40% 100%](figs/basic-monitor-2.png)

---
### 管程 -- 条件变量
- 同步：条件变量（Condition Variables)以及相关的两个操作：wait和signal，处理等待机制。
- Wait()操作
   - 将自己阻塞在等待队列中
   - 释放管程的互斥访问
   - 将一个等在管程之外的进程调入
- Signal()操作
   - 将等待队列中的一个线程唤醒
   - 如果等待队列为空，则等同空操作

![bg right:40% 100%](figs/basic-monitor-2.png)


---
### 管程 -- 条件变量
- 入口等待队列：在管程入口处的等待队列
- 条件等待队列：某个条件变量的等待队列（为资源占用而等待）
- 紧急等待队列：唤醒使用的紧急队列。因为进程会执行唤醒操做，所以可能有多个等待使用管程的队列，这样的队列称为紧急队列，它的优先级高于等待队列；（为互斥而等待的队列）

![bg right:40% 100%](figs/moniter.jpg)

---
### 管程 -- 条件变量
- enter过程：进程在进入管程之前要获得互斥访问权
- leave过程：当进程离开管程时，如果紧急队列不为空，那么它就必须负责唤醒紧急队列中的进程。
- 条件型变量c：指向一个等待该条件的队列。
- wait(c)：释放管程权力，进入c的条件等待队列；唤醒紧急等待队列的第一个线程<!--// 为进入管程的进程分配某种类型的资源，如果此时这种资源可用，那么进程使用，否则进程被阻塞，进入条件等待队列-->
- signal(c)：唤醒由于等待这种资源而进入条件等待队列的(c的条件等待队列)第一个线程<!--进入管程的进程某种资源释放，此时进程会唤醒由于等待这种资源而进入条件等待队列的第一个进程-->

---
### 管程 -- 条件变量
- 模块化，一个管程是一个基本程序单位，可以单独编译。

- 抽象数据类型，管程是一种特殊的数据类型，其中不仅有数据，而且有对数据进行操作的代码。

- 信息隐蔽，管程是半透明的，管程中的过程（函数）实现了某些功能，在其外部则是不可见的。

![bg right:40% 100%](figs/moniter.jpg)

---
### 管程 -- 实现条件变量
![w:1000](figs/cond-1.png)

---
### 管程 -- 实现条件变量
![w:1000](figs/cond-2.png)

---
### 管程 -- 实现条件变量
![w:1000](figs/cond-3.png)

---
### 管程 -- 实现条件变量
![w:1000](figs/cond-4.png)

---
### 管程 -- 实现条件变量
![w:1000](figs/cond-5.png)

---
### 管程 -- 实现条件变量
![w:1000](figs/cond-6.png)

---
### 管程 -- 实现条件变量
![w:1000](figs/cond-7.png)

---
### 管程 -- 实现条件变量
![w:1000](figs/cond-8.png)


---
### 管程 -- 实现条件变量
![w:1000](figs/cond-9.png)

---
### 管程 
<!-- https://blog.csdn.net/qq_34666857/article/details/103189107 Java并发编程模拟管程（霍尔Hoare管程、汉森Hansan管程、MESA管程) -->
管程中条件变量的释放处理方式

如果进程P1因条件A未满足处于阻塞状态，那么当进程P2让条件A满足并执行signal操作唤醒P1后，不被许进程P1和P2同时处于管程中，那么如何确定哪个执行哪个等待？
可采用下面的两种方式之一进行处理：

- 1：P2等待，直至P1离开管程或者等待另一个条件  （ Hoare）
- 2：P1等待，直至P2离开管程或者等待另一个条件(MESA/Hansen)



---
### 管程 
<!-- https://blog.csdn.net/qq_34666857/article/details/103189107 Java并发编程模拟管程（霍尔Hoare管程、汉森Hansan管程、MESA管程) -->
管程中条件变量的释放处理方式
- 线程 T2 的signal，使线程 T1 等待的条件满足时
  - Hoare：T2 通知完 T1后，T2 阻塞，T1 马上执行；等 T1 执行完，再唤醒 T2 执行
  - Hansen： T2 通知完 T1 后，T2 还会接着执行，T2 执行结束后（规定：最后操作是signal），然后 T1 再执行
  - MESA：T2 通知完 T1 后，T2 还会接着执行，T1 并不会立即执行，而是从条件变量的等待队列进到入口等待队列里面（重新竞争）


---
### 管程 - Hoare 
<!-- https://www.cnblogs.com/upnote/p/13030741.html   Java synchronized的理论基础-管程(Monitor) -->
  - 1.ThreadA 进入 管程monitor
  - 2.ThreadA 等待资源 (进入wait queue)
  - 3.ThreadB 进入monitor
  - 4.ThreadB 资源可用 ，通知ThreadA恢复执行，并把自己转移到signal queue。
  - 5.ThreadA 重新进入 monitor
  - 6.ThreadA 离开monitor
  - 7.ThreadB 重新进入 monitor
  - 8.ThreadB 离开monitor
  - 9.其他在entry queue中的线程通过竞争进入monitor


---
### 管程 - Mesa 
<!-- https://www.cnblogs.com/upnote/p/13030741.html   Java synchronized的理论基础-管程(Monitor) -->
  - 1.ThreadA 进入 monitor
  - 2.ThreadA 等待资源 (进入wait queue，并释放monitor)
  - 3.ThreadB 进入monitor
  - 4.ThreadB 资源可用，通知ThreadA。(ThreadA被转移到entey queue，重新平等竞争)
  - 5.ThreadB 继续执行
  - 6.ThreadB 离开monitor
  - 7.ThreadA 获得执行机会，从entry queue出队列，恢复执行
  - 8.ThreadA 离开monitor
  - 9.其他在entry queue中的线程通过**竞争**进入monitor


---
### 管程 - Hansen： 
<!-- https://www.cnblogs.com/upnote/p/13030741.html   Java synchronized的理论基础-管程(Monitor) -->
  - 1.ThreadA 进入 monitor
  - 2.ThreadA 等待资源r
  - 3.ThreadB 进入monitor
  - 4.ThreadB 离开Monitor,并给通知等待资源r的线程，资源可用
  - 5.ThreadA 重新进入 monitor
  - 6.ThreadA 离开monitor
  - 7.其他线程从entry queue中竞争进入monitor


---
### 管程 
管程中条件变量的释放处理方式
<!-- https://cseweb.ucsd.edu/classes/sp17/cse120-a/applications/ln/lecture8.html --> 
<!-- https://juejin.cn/post/6925331537365843981 synchronized原理剖析 -->
![w:1100](figs/cond-releases.png)


---
### 管程 
<!-- 管程中条件变量的释放处理方式 -->
![w:900](figs/cond-releases-2.png)




---
### 管程 
<!-- 管程中条件变量的释放处理方式 -->
![w:900](figs/cond-releases-3.png)

---
### 管程 -- 生产者-消费者问题
![w:1000](figs/monitor-pc-1.png)


---
### 管程 -- 生产者-消费者问题
![w:1000](figs/monitor-pc-2.png)


---
### 管程 -- 生产者-消费者问题
![w:1000](figs/monitor-pc-3.png)


---
### 管程 -- 生产者-消费者问题
![w:1000](figs/monitor-pc-4.png)

