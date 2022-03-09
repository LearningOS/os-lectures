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

## 第五讲 地址空间-物理内存管理
### 第三节 实践：地址空间抽象的OS


---
## 实践：地址空间抽象的OS
- **进化目标**
- 总体思路
- 历史背景
- 实践步骤
- 软件架构
- 相关硬件
- 程序设计

![bg right 100%](figs/multiprog-os-detail.png)

---
## 实践：地址空间抽象的OS
### 进化目标
**地址空间隔离**

- multiprog & time-sharing OS目标
  - 进一步提高系统中多个应用的总体性能和效率
- BatchOS目标
  - 让APP与OS隔离，提高系统的安全性和效率
- LibOS目标
  - 让应用与硬件隔离，简化应用访问硬件的难度和复杂性


---
## 实践：地址空间抽象的OS
### 同学的进化目标
- 理解地址空间
- 掌握页机制
- 会处理页访问异常
- 会写支持页机制的操作系统

<!-- 头甲龙 -->

![bg right 80%](figs/ch4-os.png)



---
## 小结
- 地址空间
- 连续内存分配
- 段机制
- 页表机制
- 页访问异常
- 能写头甲龙OS
