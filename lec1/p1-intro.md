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
### 第一节 课程概述 & 教学安排

<br>
<br>

向勇 陈渝 李国良 

<br>
<br>

2022年秋季

---

## 课程信息

### 主讲教师：
  - 向勇
  - 陈渝

### 助教
  - 闭浩扬、田凯夫、赵方亮、贺鲲鹏

---

## 上课信息

### 上课时间地点
- 星期三 上午第二大节 09:50-12:15 (1-16周) 
- 地点
   - 五教 5101

----

## 预备知识

### 程序设计语言（汇编、C 和 Rust）
 - :( 不是开发应用程序
 - :) 而是开发系统程序

### 数据结构
 - :) 理解基本数据结构即可

---

## 预备知识
### 计算机组成原理
 - :( 刘总/康总的 RISC-V 原理
 - :) Patterson 的 RISC-V 原理

### 编译原理
 - :) 没学过影响不大 
 - :( 但还是要了解高级语言 <–>RISC-V 汇编语言


---

#### 课程参考
- [课程幻灯片](https://www.yuque.com/docs/share/4c39608f-3051-4445-96ca-f3c018cb96c7)
- 参考书
  * [Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)
  - [深入了解计算机系统](https://hansimov.gitbook.io/csapp/)
  - [RISC-V Reader中文版](http://riscvbook.com/chinese/RISC-V-Reader-Chinese-v2p1.pdf)
#### 课程实践：rCore Tutorial Book v3
-  [课程实践参考书](https://learningos.github.io/rCore-Tutorial-Book-v3/)
-  [课程实践代码仓库](https://github.com/rcore-os/rCore-Tutorial-v3)
-  [课程实践代码的API文档](https://github.com/rcore-os/rCore-Tutorial-v3#os-api-docs)

---

### 实验指导


#### uCore-RV-64

* 基准代码仓库（[lab](https://github.com/uCore-RV-64/uCore-RV-64-lab)）
* 文档仓库（[doc](https://github.com/uCore-RV-64/uCore-RV-64-doc)）
* 在线文档[入口](https://ucore-rv-64.github.io/uCore-RV-64-doc/index.html)
* 实验参考答案仓库（[answer](https://github.com/uCore-RV-64/uCore-RV-64-answer)）
* 自动测试脚本仓库（[test](https://github.com/uCore-RV-64/uCore-RV-64-test)）
* codespace开发环境配置脚本仓库（[config](https://github.com/uCore-RV-64/uCore-RV-64-conf)）

---

### 实验指导

#### rCore
- [实验文档](https://github.com/LearningOS/rCore-Tutorial-Guide-2022S/)
- [API文档](https://github.com/LearningOS/rCore-Tutorial-Guide-2022S/#os-api-docs-of-rcore-tutorial-code-2022s) , [实验代码](https://github.com/LearningOS/rCore-Tutorial-Code-2022S)
- [测试用例](https://github.com/LearningOS/rCore-Tutorial-Test-2022S)

#### uCore和rCore实验[讲解视频](https://www.yuque.com/docs/share/1b5b9260-8a80-4427-a612-78ec72b37e5f)

---


![bg right 100%](figs/ucorearch.png)


### OS 原理与设计思想

* 操作系统结构
* 中断及系统调用
* 内存管理
* 进程管理
* 处理机调度
* 同步互斥
* 文件系统
* I/O 子系统


---

## 作业与实验

### 平时作业
  - 课后练习

### 基础实验
  - 面向 RISC-V CPU 用 Rust/C 设计实现操作系统的功能
 
### 课程设计  
  - 大实验

---
## 基础实验
### 实验一：操作系统的基本支持
### 实验二：地址空间
### 实验三：进程管理与调度
### 实验四：文件系统与进程间通信
### 实验五：同步互斥


---

## 课程设计（大实验）

### 各种操作系统相关的功能和扩展

- 多种CPU平台上的操作系统移植
  * RISC-V、x86-64、MIPS、ARM
- 多种开发板的驱动开发
  * RaspBerry PI、U740、D1等
  * GUI、驱动、文件系统、网络
- 操作系统内核模块的完善和改进
  * 内核可加载模块、微内核
  * 在内核中引入异步编程

--- 

## 成绩评定

### 选择1： 
  - 按时完成实验一至实验五：30% 
  - 期中考试 30% + 期末考试 40% ：70%
### 选择2： 
  - 四周内完成实验一至实验五(2022春季实验)：30% 
  - 课程设计（即大实验）：70%
    - 注：选择大实验的同学如果后续退出课程设计，需参加考试。

--- 

## 调查问卷

[2022年秋季学期操作系统课选课问卷](http://oscourse2019.mikecrm.com/fPozIRL)（访问密码：XxW21Ur1CF）

- 为什么要学这门课？ 
- 你打算如何来学这门课？
- 对自己的课程学习要求是什么？
- 你愿意如实报告是否独立完成实验任务？
- 你希望在操作系统课上学到什么知识和什么能力？
- 以前的学习情况？
