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

## 第一讲 操作系统概述
- [第一节 课程概述 & 教学安排](./lec1/p1-intro.html)
- [第二节 什么是操作系统](./lec1/p2-whatisos.html)
- [第三节 操作系统历史演化](./lec1/p3-oshistory.html)
- [第四节 操作系统结构](./lec1/p4-osarchitecture.html)
- [第五节 实践：试试UNIX/Linux](./lec1/p5-tryunix.html)

---
## 第二讲 实践与实验介绍

- [第一节 实践与实验简要分析](./lec2/p1-labintro.html)
- [第二节 Compiler与OS](./lec2/p2-compiling.html)
- [第三节 硬件启动与软件启动](./lec2/p3-boot.html)
- [第四节 实践：裸机程序 -- LibOS](./lec2/p4-lab1.html)

---

## 第三讲 基于特权级的隔离与批处理
- [第一节 从 OS 角度看计算机系统](./lec3/p1-osviewarch.html)
- [第二节 从 OS 角度看RISC-V](./lec3/p2-osviewrv.html)
- [第三节 实践：批处理操作系统](./lec3/p3-batchos.html)

---

## 第四讲 多道程序与分时多任务
- [第一节 相关背景与基本概念](./lec4/p1-multiprog.html)
- [第二节 实践：多道程序与分时多任务操作系统](./lec4/p2-labs.html)

---

## 第五讲 地址空间-物理内存管理
- [第一节 地址空间](./lec5/p1-memintro.html)
- [第二节 内存分配](./lec5/p2-memalloc.html)
- [第三节 实践：建立地址空间的操作系统](./lec5/p3-labs.html)

---
## 第六讲  地址空间-虚拟存储管理
- [第一节  虚拟存储的基本概念](./lec6/p1-vmoverview.html)
- [第二节 页面置换算法 -- 局部页面置换算法](./lec6/p2-pagereplace-1.html)
- [第三节 页面置换算法 -- 全局页面置换算法](./lec6/p2-pagereplace-2.html)

---
## 第七讲  进程管理与单处理器调度
- [第一节 进程管理](./lec7/p1-process-overview.html)
- [第二节 单处理器调度](./lec7/p2-sched.html)
- [第三节 实时管理与调度](./lec7/p3-realtime.html)
- [第四节 实践：支持进程的操作系统](./lec7/p4-labs.html)

---
## 第八讲  多处理器调度
- [第一节 对称多处理与多核架构](./lec8/p1-multiprocessor-overview.html)
- [第二节 多处理器调度概述](./lec8/p2-multiprocessor-sched-overview.html)
- [第三节 Linux O(1) 调度](./lec8/p3-linux-O1-sched.html)
- [第四节 Linux CFS（Completely Fair Schduler） 调度](./lec8/p4-linux-cfs-sched.html)
- [第五节 Linux/FreeBSD BFS 调度](./lec8/p5-linux-bfs-sched.html)

---
## 第九讲  文件系统
- [第一节 文件系统概述](./lec9/p1-fsoverview.html)
- [第二节 文件系统的设计与实现](./lec9/p2-fsimplement.html)
- [第三节 支持崩溃一致性的文件系统](./lec9/p3-fsjournal.html)
- [第四节 支持文件的操作系统](./lec9/p4-fs-lab.html)

---
## 第十讲  进程间通信
- [第一节 进程间通信(IPC)概述](./lec10/p1-ipcoverview.html)
- [第二节 支持IPC的OS](./lec10/p2-ipclabs.html)


---
## 第十一讲  线程与协程
- [第一节 线程](./lec11/p1-thread.html)
- [第二节 协程](./lec11/p2-coroutine.html)
- [第三节 支持线程/协程的OS(TCOS)](./lec11/p3-labs.html)

---
## 第十二讲 同步互斥
- [第一节 概述](./lec12/p1-syncmutex.html)
- [第二节 信号量](./lec12/p2-semaphore.html)
- [第三节 管程与条件变量](./lec12/p3-monitor-cond.html)
- [第四节 同步互斥实例问题](./lec12/p4-instances.html)
- [第五节 死锁](./lec12/p5-deadlock.html)
- [第六节 支持同步互斥的OS(SMOS)](./lec12/p6-labs.html)

---
## 第十三讲 设备管理
- [第一节 设备接口](./lec13/p1-devinterface.html)
- [第二节 磁盘子系统](./lec13/p2-disk.html)
- [第三节 支持device的OS（DOS）](./lec13/p3-labs.html)

---
### OS课程介绍
- [清华计算机系2022春季OS课程](./course-intro.md)