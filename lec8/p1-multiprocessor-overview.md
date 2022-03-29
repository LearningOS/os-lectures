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

### 第一节 对称多处理与多核架构



<br>
<br>

向勇 陈渝 李国良 

<br>
<br>

2022年春季

---
### 单核处理器
![w:800](figs/single-core.png) 


---
### 超线程(Hyperthread,Simultaneous multithreading)处理器
![w:500](figs/hyperthread.png) 


---
### 多核(multi-core)处理器
![w:1000](figs/multi-core.png) 

---
### 众核(many-core)处理器
![w:1000](figs/many-core.png) 

---
### 对称多处理器(SMP)与非一致内存访问系统(NUMA)
![w:900](figs/smp-numa.png) 

---
### Cache 一致性 (Cache Coherence)
![w:800](figs/cache-coherence.png) 


---
### Cache 一致性问题
![w:900](figs/cache-coherence-problem.png) 