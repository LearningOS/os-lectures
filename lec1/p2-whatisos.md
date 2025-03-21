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

## 第一讲 操作系统概述
### 第二节 什么是操作系统

<br>
<br>

向勇 陈渝 李国良 任炬 

<br>
<br>

2025年春季

---

## 操作系统定义

没有公认的精确定义

  操作系统是**管理硬件资源**、控制程序运行、改善人机界面和**为应用软件提供支持**的一种系统**软件**。[计算机百科全书]
 
![bg right 100%](./figs/os-position.png)

承上启下的操作系统

---

## 操作系统是一个资源管理程序
- 应用与硬件之间的**中间层**
- **管理**各种软硬件资源
- 访问软硬件资源的**服务**
- **解决访问冲突**, 确保公平使用

![bg right 100%](./figs/os-position.png)

---

## 操作系统是一个控制程序
- 一个系统软件
- 执行程序, 给程序**提供服务**
- 控制程序执行过程, **防止错误**
- **方便用户使用**计算机系统

![bg right 100%](./figs/os-position.png)

---

## 操作系统中的软件分类

- Shell – 命令行接口
- GUI – 图形用户接口
- Kernel – 操作系统的内部

![bg right 100%](./figs/sort-of-os.png)

---
## uCore/rCore 教学操作系统内核

![w:800](./figs/ucorearch.png)


---
## 操作系统内核的抽象

![w:800](./figs/os-abstract.png)


---
## 操作系统内核的抽象

![w:700](./figs/run-app.png)

---
## 操作系统内核的特征

- **并发**：计算机系统中同时存在多个运行程序
- **共享**：程序间“同时”访问互斥共享各种资源
- **虚拟**：每个程序” 独占” 一台完整的计算机
- **异步**：服务的完成时间不确定，也可能失败 

---
## 你对操作系统内核的理解

###  用户/应用对操作系统的需求？

---
## 你对操作系统内核的理解

###  用户/应用对操作系统的需求？
- 高效 -- 易用 ?
- 强大的操作系统服务 -- 简单的接口 ?
- 灵活性 -- 安全性 ?


---
## 为什么要学习这门课程

- 可以了解计算机机壳后面的软硬件运行原理
- 可以学习软硬件基础架构和原理
- 深入了解程序运行的机理
- 可以发现和修复难对付的bug


---
## 操作系统设计理念

- 抽象：屏蔽硬件复杂性，提供统一接口。
- 资源管理：高效分配和调度有限资源。
- 隔离与保护：避免进程间干扰，保护系统安全。
- 并发与并行：支持多任务共享资源或并行运行。
- 透明性：隐藏底层复杂性，为用户提供一致体验。
- 可移植性：适应不同硬件平台，扩展应用场景。
- 简单性与模块化：降低复杂性，提高维护效率。

<!-- 如果你花费大量时间来开发，维护并调试应用程序，你最终还是要知道大量操作系统的知识 -->