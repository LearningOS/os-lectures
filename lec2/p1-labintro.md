---
marp: true
theme: default
paginate: true
_paginate: false
header: ''
footer: ''
---

<!-- theme: gaia -->
<!-- _class: lead -->

## 第二讲 实践与实验介绍
### 第一节 实践与实验简要分析

<br>
<br>

向勇 陈渝 李国良 

<br>
<br>

2022年春季

---

## 实践与实验介绍

* 库级支持
* 批处理支持
* 多道程序与分时多任务
* 支持地址空间
* 支持文件系统
* 支持进程间通信
* 并发支持
* 管理I/O设备

---

## 库级支持

- 远古操作系统雏形
- 现代简单嵌入式操作系统

### 相关知识点
- 函数调用
- 编译器与操作系统的配合
- 硬件启动和软件启动
- 编写/调试裸机程序


![bg right 100%](figs/os-as-lib.png)

--- 

## 批处理OS
- 支持程序执行切换

### 相关知识点

- 特权级/特权操作
- RV特权级/特权操作
- 系统调用/异常
- 加载&执行&切换应用程序
- 特权级切换

![bg right 100%](figs/batch-os.png)

--- 
## 多道程序OS
- 支持多个程序驻留内存并依次执行
### 相关知识点
- 协作式调度
- 内存空间划分与管理

![bg right 100%](figs/multiprog-os.png)

--- 
## 分时多任务OS
- 支持多个程序轮流执行

### 相关知识点
- 抢占式调度
- 中断处理
- 上下文切换

![bg right 100%](figs/timesharing-os.png)

--- 
## 地址空间抽象的OS
- 支持程序间内存空间隔离

### 相关知识点
- 地址空间抽象
- 静态内存分配
- 动态内存分配
- 页式存储管理
![bg right 100%](figs/address-space-os.png)

--- 
## 进程抽象的OS
- 支持动态创建程序执行
### 相关知识点
- 进程抽象
- 进程管理
- 调度机制
  
![bg right 100%](figs/process-os.png)


--- 
## 文件抽象的OS
- 处理数据的便捷长期存储
### 相关知识点
- 文件抽象
- 文件组织结构
- 文件系统设计与实现

![bg right 100%](figs/fs-os.png)

--- 
## 实践 -- 支持进程间通信的OS

### 相关知识点

![bg right 100%](figs/ipc-os.png)


--- 
## 实践 -- 支持并发的OS

### 相关知识点

![bg right 100%](figs/os-as-lib.png)

--- 
## 实践 -- 管理I/O设备的OS

### 相关知识点

![bg right 100%](figs/os-as-lib.png)