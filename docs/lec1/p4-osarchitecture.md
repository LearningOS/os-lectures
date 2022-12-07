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
<!-- page_number: true -->
<!-- _class: lead -->

## 第一讲 操作系统概述

### 第四节 操作系统结构

<br>
<br>

向勇 陈渝 李国良 

<br>
<br>

2022年秋季

---
## 简单结构
MS-DOS：应用和OS混在一起 (1981–1994)
- **没有拆分为模块**
- 主要用汇编编写
- 没有安全保护

![bg right 100%](./figs/msdos.png)


---
## 单体分层结构
将单体操作系统 (Monolithic OS) 划分为**多层** (levels)
- 每层建立在低层之上
- 最底层 (layer 0), 是硬件驱动
- 最高层 (layer N) 是用户界面
- 每一层仅使用更低一层的功能和服务

![bg right 100%](./figs/multi-level-os-arch.png)


---
## 微内核结构(Micro Kernel)
- **尽可能把内核功能移到用户空间**
- 用户模块间的通信使用消息传递
- 好处: 灵活/安全...
- 缺点: 性能
- LPC: 本地过程调用(Local Procedure Call)
- HAL: 硬件抽象层（Hardware Abstraction Layer）

![bg right:45% 100%](./figs/microkernel-arch.png)

---
## 外核结构(Exokernel)
- 让内核分配物理资源给多个应用程序, 并让每个程序决定如何处理这些资源
- 程序能链接到操作系统库 (libOS) 实现了操作系统抽象
- **保护与控制分离**
- Distributed Shared Memory(DSM)

![bg right:45% 100%](./figs/exokernel-arch.png)


---
## 虚拟机结构
虚拟机管理器将单独的机器接口转换成很多的虚拟机, 每个虚拟机都是一个原始计算机系统的有效副本, 并能完成所有的处理器指令

![bg right:45% 100%](./figs/vmm-arch.png)

---
## 虚拟机结构


![bg 70%](./figs/vmm-arch-view2.png)

---
## 应用程序运行与 OS 抽象 + 架构的关系

![bg 90%](./figs/os-env.png)