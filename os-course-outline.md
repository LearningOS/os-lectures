# 第1讲 操作系统概述

## 1.1 课程概述 

## 1.2 教学安排 

## 1.3 什么是操作系统

## 1.4 为什么学习操作系统，如何学习操作系统 

## 1.5 操作系统实例 

## 1.6 操作系统的演变 

## 1.7 操作系统结构

## 2.1 操作系统实验介绍：前言和国内外现状

## 2.2  OS实验目标 

## 2.3 8个OS实验概述 

## 2.4 实验环境搭建 

## 2.5 x86-32硬件介绍 

## 2.6 ucore部分编程技巧 

## 2.7  演示实验操作过程

# 第2讲 系统启动、中断、异常和系统调用

## 3.1 BIOS

## 3.2 系统启动流程

## 3.3 中断、异常和系统调用比较

## 3.4 系统调用

## 3.5 系统调用示例

## 3.6 ucore+系统调用代码

## 4.1 bootloader启动顺序

## 4.2 C函数调用的实现

## 4.3 GCC内联汇编

## 4.4 x86中断处理过程

## 4.5 练习一 ucore编译过程

## 4.6 练习二 qemu和gdb的使用

## 4.7 练习三 加载程序

## 4.8 练习四和五 ucore内核映像加载和函数调用栈分析

## 4.9 练习六 完善中断初始化和处理

# 第3讲 物理内存管理

## 计算机体系结构和内存层次

## 5.2 地址空间和地址生成

## 5.3 连续内存分配

## 5.4 碎片整理

## 5.5 伙伴系统

# 第4讲 物理内存管理: 非连续内存分配

## 6.1 非连续内存分配的需求背景

## 6.2 段式存储管理

## 6.3 页式存储管理

## 6.4 页表概述

## 6.5 快表和多级页表

## 6.6 反置页表

## 6.7 段页式存储管理

## 7.1 了解x86保护模式中的特权级

## 7.2 了解特权级切换过程

## 7.3 了解段/页表

## 7.4 了解ucore建立段/页表

## 7.5 演示lab2实验环节

# 第5讲 虚拟存储概念
Virtual Memory: page fault + lab3: page fault

## 8.1 虚拟存储的需求背景

## 8.2 覆盖和交换

## 8.3 局部性原理

## 8.4 虚拟存储概念

## 8.5 虚拟页式存储

## 8.6 缺页异常

# 第6讲 虚拟存储：页面置换算法

## 9.1 页面置换算法的概念

## 9.2 最优算法、先进先出算法和最近最久未使用算法

## 9.3 时钟置换算法和最不常用算法

## 9.4 Belady现象和局部置换算法比较

## 9.5 工作集置换算法

## 9.6 缺页率置换算法

## 9.7 抖动和负载控制

## 10.1 虚拟内存管理实验目标：虚存管理

## 10.2 回顾历史和了解当下

## 10.3 处理流程、关键数据结构和功能

## 10.4 页访问异常

## 10.5 页换入换出机制

# *第7讲 Memory virtualization

# 第8讲 进程与线程

## 11.1 进程的概念

## 11.2 进程控制块

## 11.3 进程状态

## 11.4 三状态进程模型

## 11.5 挂起进程模型

## 11.6 线程的概念

## 11.7 用户线程

## 11.8 内核线程

# 第9讲 进程和线程控制

## 12.1 进程切换

## 12.2 进程创建

## 12.3 进程加载

## 12.4 进程等待与退出

## 用户态线程库实例

## 13.1 内核线程管理实验总体介绍

## 13.2 关键数据结构

## 13.3 执行流程

## 13.4 实际操作

## 14.1 用户进程管理实验总体介绍

## 14.2 进程的内存布局

## 14.3 执行ELF格式的二进制代码-do_execve的实现

## 14.4 执行ELF格式的二进制代码-load_icode的实现

## 14.5 进程复制

## 14.6 内存管理的copy-on-write机制

# 第10讲 处理机调度

## 15.1 处理机调度概念

## 15.2 调度准则

## 15.3 先来先服务、短进程优先和最高响应比优先调度算法

## 15.4 时间片轮转、多级反馈队列、公平共享调度算法和ucore调度框架

## 15.5 实时调度和多处理器调度

## 15.6 优先级反置

# *第11讲 调度器实例

## 16.1 总体介绍和调度过程

## 16.2 调度算法支撑框架

## 16.3 时间片轮转调度算法

## 16.4 Stride调度算法

# 第12讲 CPU virtualization
## CPU Virtualization Overview
### CPU Virtualization Goal
### What is CPU: Software’s View
### CPU Virtualization Approach
## CPU Virtualization Hardware Support (VT-x)
### VT-x: Key Features
### VMX Transitions
## CPU Virtualization Software Implementation
### VCPU Concept
### VCPU Operation
### VCPU Optimization
## Mode of Operation Virtualization


# 第13讲 同步互斥

## 17.1 背景

## 17.2 现实生活中的同步问题

## 17.3 临界区和禁用硬件中断同步方法

## 17.4 基于软件的同步方法

## 17.5 高级抽象的同步方法

# 第14讲 信号量与管程

## 18.1 信号量

## 18.2 信号量使用

## 18.3 管程

## 18.4 哲学家就餐问题

## 18.5 读者-写者问题

## 19.1 同步互斥实验总体介绍

## 19.2 底层支撑

## 19.3 信号量设计实现

## 19.4 管程和条件变量设计实现

## 19.5 哲学家就餐问题

# 第15讲 死锁和进程通信

## 20.1 死锁概念

## 20.2 死锁处理方法

## 20.3 银行家算法

## 20.4 死锁检测

## 20.5 进程通信概念

## 20.6 信号和管道

## 20.7 消息队列和共享内存

# 第16讲 文件系统

## 21.1 文件系统和文件 

## 21.2 文件描述符 

## 21.3 目录、文件别名和文件系统种类

## 21.4  虚拟文件系统 

## 21.5 文件缓存和打开文件 

## 21.6 文件分配 

## 21.7 空闲空间管理和冗余磁盘阵列RAID

# *第17讲 文件系统实例

## 22.1 文件系统实验总体介绍

## 22.2 ucore 文件系统架构 

## 22.3 Simple File System分析

## 22.4 Virtual File System分析

## 22.5 I/O设备接口分析 

## 22.6 执行流程分析

# 第18讲 I/O子系统

## 23.1 I/O特点

## 23.2 I/O结构 

## 23.3 I/O数据传输

## 23.4 磁盘调度 

## 23.5 磁盘缓存

# 第19讲 I/O Subsystem: usb & I/O instances

## USB
### USB 2.0
### On-The-Go Supplement to USB 2.0
### I/O in ucore
## Linux I/O Architecture

## Windows I/O System
### Driver and Device Objects
### I/O Manager
### Deferred Procedure Calls
### Asynchronous Procedure Calls


# *第20讲 I/O virtualization（eBPF）

## General strategies for I/O virtualization
## Virtual I/O Virtualization
### Virtual Device Framework
### VMBus
## Passthrough I/O Virtualization
### Single Root I/O Virtualization
### Multi-Root I/O Virtualization

# 第21讲 Kernel Security: stack overflow

## 内核安全和缓冲区溢出
## 整数溢出
## 整数溢出分析
## 整数溢出自动检测
## Kint设计与实现
## Kint应用
## Kint改进

# 第22讲 Kernel Security: symbol execution
## Background
## EXE - EXecution generated Executions
### Overview
### Example
### Optimizations
### Results
## KLEE
### Overview
### Architecture
### Results

