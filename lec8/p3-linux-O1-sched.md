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

## 第八讲 多处理器调度

### 第三节 Linux O(1) 调度

---
### SMP 和 Linux 内核
- 在 Linux 2.0 的早期，SMP 支持由一个“大锁”组成，这个“大锁”对操作系统内部的访问进行串行化
- 在 2.2 前的内核中，SMP 实现在用户级，Linux 内核本身并不能因为有多个处理器而得到加速
![w:700](figs/sqms.png) 

---
### Linux 2.4 内核：SMP 实现在核心级
- 使用多处理器可以加快内核的处理速度，调度器是复杂度为 O(n)
  - 内核调度器维护两个 queue：runqueue 和 expired queue
  - 两个 queue 都永远保持有序
  - 一个 process 用完时间片，就会被插入 expired queue
  - 当 runqueue 为空时，把 runqueue 和 expired queue 交换一下
![w:800](figs/linux-2.4-sched.png) 


---
### Linux 2.4 内核：SMP 实现在核心级
- 使用多处理器可以加快内核的处理速度，调度器是复杂度为 O(n)
  - 全局共享的就绪队列
  - 寻找下一个可执行的 process，这个操作一般都是 O(1)
  - 每次进程用完时间片，找合适的位置执行插入操作，会遍历所有任务，复杂度为O(n)
![w:800](figs/linux-2.4-sched.png) 


---
### Linux 2.4 内核：SMP 实现在核心级
- 使用多处理器可以加快内核的处理速度，调度器是复杂度为 O(n)
  - 现代操作系统都能运行成千上万个进程
  - O(n) 算法意味着每次调度时，对于当前执行完的process，需要把所有在 expired queue 中的 process 过一遍，找到合适的位置插入
  - 这不仅仅会带来性能上的巨大损失，还使得系统的调度时间非常不确定 -- 根据系统的负载，可能有数倍甚至数百倍的差异
  ![w:800](figs/linux-2.4-sched.png) 

  
---
### Linux O(1) 调度器
Linux 2.6 版本的调度器是由 Ingo Molnar 设计并实现的。Ingo 从 1995 年开始就一直参与 Linux 内核的开发。他编写这个新调度器的动机是为唤醒、上下文切换和定时器中断开销建立一个完全 O(1) 的调度器

![bg right 100%](figs/O1.jpeg) 


  
---
### Linux O(1) 调度器
- 满足 O(1) 的数据结构？
- 回顾一下数据结构的四种基本操作和时间复杂度
  - access：随机访问
    - array: 平均情况和最坏情况均能达到 O(1)
    - linked list 是 O(N)
    - tree 一般是 O(log N)
![bg right 100%](figs/O1.jpeg) 

  
---
### Linux O(1) 调度器
- 满足 O(1) 的数据结构？
- 回顾一下数据结构的四种基本操作和时间复杂度
  - search：搜索
    - hash table 时间复杂度是 O(1)，但它最坏情况下是 O(N)
    - 大部分 tree（b-tree / red-black tree）平均和最坏情况都是 O(log N)
![bg right 100%](figs/O1.jpeg) 

  
---
### Linux O(1) 调度器
- 满足 O(1) 的数据结构？
- 回顾一下数据结构的四种基本操作和时间复杂度
  - insert/deletion：插入和删除
    - hash table 时间复杂度是 O(1)，但它最坏情况下是 O(N)
    - linked list，stack，queue 在平均和最坏情况下都是 O(1)

![bg right:40% 100%](figs/O1.jpeg) 

    
---
### Linux O(1) 调度器

- 进程有 140 种优先级，可用长度为 140 的 array 去记录优先级。access 是 O(1)
- 每个优先级下面用一个FIFO queue 管理这个优先级
下的 process。新来的插到队尾，先进先出，insert/deletion 都是 O(1)

![bg right:40% 100%](figs/O1.jpeg) 

    
---
### Linux O(1) 调度器

- 进程有 140 种优先级，可用长度为 140 的 array 去记录优先级。access 是 O(1)
- bitarray，它为每种优先级分配一个 bit，如果这个优先级队列下面有 process，那么就对相应的 bit 染色，置为 1，否则置为 0。
- 问题就简化成寻找一个 bitarray 里面最高位是 1 的 bit（left-most bit），这基本上是一条CPU 指令的事。

![bg right:40% 100%](figs/O1.jpeg) 


    
---
### Linux O(1) 调度器

步骤
- 在 active bitarray(APA) 中寻找 left-most bit 的位置 x。
- 在 APA 中找到对应队列 APA[x]。
- 从 APA[x] 中 dequeue 一个 process。


![bg right:40% 100%](figs/O1.jpeg) 

    
---
### Linux O(1) 调度器

步骤
- 对于当前执行完的 process，重新计算其priority，然后 enqueue 到 expired priority array(EPA) 相应的队里 EPA[priority]。
- 如果 priority 在 expired bitarray 里对应的 bit 为 0，将其置 1。
- 如果 active bitarray 全为零，将 active bitarray 和 expired bitarray 交换一下。

![bg right:40% 100%](figs/O1.jpeg)   

    
---
### Linux O(1) 调度器
多核/SMP 支持
- 在一定时间间隔后，进行 load balance 分析
- rq > cpu_load : represents load on the CPU
- 在每个时钟中断后进行计算
- current_load = rq >nr_running *
SCHED_LOAD_SCALE;
- 由负载轻的 CPU pulling 进程而不是 pushing进程
![bg right:40% 100%](figs/O1.jpeg)   