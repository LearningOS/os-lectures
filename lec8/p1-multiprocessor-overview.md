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

# 第八讲 多处理器调度
## 第一节 对称多处理与多核架构

<br>
<br>

向勇 陈渝 李国良 任炬 

2024年春季

[课程幻灯片列表](https://www.yuque.com/xyong-9fuoz/qczol5/ewvhdy3epbwbkn3n)

---

**提纲**
<style>
.container{
    display: flex;    
}
.col{
    flex: 1;
}
</style>

<div class="container">

<div class="col">

### 1. 多处理机器
2. Cache一致性(Cache Coherence)

</div>

<div class="col">

</div>

</div>

---

#### 单核处理器
![w:800](figs/single-core.png) 

---

#### 超线程(Hyperthread, Simultaneous multithreading)处理器
- 将CPU内部暂时闲置处理资源充分调动起来
  - 寄存器、程序计数器独立
  - 算术计算单元等硬件共用
  - 不适合计算密集型任务
  - 适合IO密集型任务

![bg right 80%](figs/hyperthread.png) 

---

#### 多核(multi-core)处理器
![w:1150](figs/multi-core.png) 

---

#### 众核(many-core)处理器
![w:1150](figs/many-core.png) 

---

**提纲**
<style>
.container{
    display: flex;    
}
.col{
    flex: 1;
}
</style>

<div class="container">

<div class="col">

1. 多处理机器
### 2. Cache一致性(Cache Coherence)

</div>

<div class="col">

</div>

</div>

---

#### 对称多处理器(SMP)与非一致内存访问系统(NUMA)
![w:1000](figs/smp-numa.png) 

---

#### Cache 一致性 (Cache Coherence)
![w:800](figs/cache-coherence.png) 

---

#### Cache 一致性问题
![w:900](figs/cache-coherence-problem.png)


<!-- Cache一致性问题（Cache Coherence）是多处理器计算环境中的一个关键问题，尤其是在使用共享内存系统时。在这样的系统中，多个处理器可能会同时访问相同的内存位置，而每个处理器可能有自己的缓存。如果不同处理器的缓存中存储了同一内存地址的不同副本，那么就可能出现数据不一致的情况。

Cache一致性问题的核心
多重缓存副本：
当多个处理器缓存了相同内存位置的数据时，如果一个处理器修改了该数据，其他处理器缓存的副本则会变得过时。

读写操作的可见性：
如果一个处理器修改了它的本地缓存中的数据，这种修改必须对其他处理器可见，以确保所有处理器都能看到最新的值。

操作的顺序：
在多处理器系统中，操作的执行顺序对程序的行为和输出可能有重大影响。确保所有处理器对共享内存的读取和写入操作的顺序达成一致是非常重要的。


导致Cache一致性问题的情形
并行处理更新：
如果两个或更多的处理器同时更新同一内存位置，则它们各自的缓存将包含不同的值，从而导致一致性问题。

延迟同步：
缓存更新的信息需要时间传播到所有处理器，如果在这段延迟时间内发生了对相同数据的访问，可能读取到过时的数据。 -->