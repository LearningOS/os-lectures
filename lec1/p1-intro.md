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

2022年春季

---

## 课程信息

### 主讲教师：
  - 陈渝
  - 李国良

### 助教
  - 张译仁 钮泽平 饶淙元 尤予阳 徐奥淳 王瑞康
  - 马思源 彭浩洋 田凯夫 曹隽诚 安之达 许善朴

---

## 上课信息

### 上课时间地点
- 星期一 上午第二大节 09:50-12:15 (1-16周) 
- 地点
   - 五教 5305  李国良
   - 五教 5205  陈渝


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
- [课程在线Slides](http://learningos.github.io/os-lectures/)
- [参考书: Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)
- [参考书: 深入了解计算机系统](https://hansimov.gitbook.io/csapp/)
- [RISC-V Reader中文版](http://riscvbook.com/chinese/RISC-V-Reader-Chinese-v2p1.pdf)
#### 课程实践
-  [课程实践参考书:rCore Tutorial Book v3](https://learningos.github.io/rCore-Tutorial-Book-v3/)
-  [课程实践代码:rCore Tutorial v3](https://github.com/rcore-os/rCore-Tutorial-v3)
-  [课程实践代码的API文档:rCore Tutorial v3](https://learningos.github.io/rCore-Tutorial-v3/)

---

### 实验指导

放置在[GitHub/LearningOS](https://github.com/LearningOS)和[Gitee/learning-os 备份](https://gitee.com/learning-os)上
#### uCore Tutorial Guide 2022 Spring
- [实验文档](https://github.com/LearningOS/uCore-Tutorial-Guide-2022S/) ，[实验代码](https://github.com/LearningOS/uCore-Tutorial-Code-2022S)，[测试用例](https://github.com/LearningOS/uCore-Tutorial-Test-2022S)

#### rCore Tutorial Guide 2022 Spring
- [实验文档](https://github.com/LearningOS/rCore-Tutorial-Guide-2022S/)  , [API文档](https://github.com/LearningOS/rCore-Tutorial-Guide-2022S/) , [实验代码](https://github.com/LearningOS/rCore-Tutorial-Code-2022S)，[测试用例](https://github.com/LearningOS/rCore-Tutorial-Test-2022S)

#### 视频介绍
- [uCore框架](https://cloud.tsinghua.edu.cn/f/358c6c509f0046ddbc4d/) ,  [rCore框架](https://cloud.tsinghua.edu.cn/f/7ab685e3346f4053aedf/) 
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


---
## 基础实验

### 实验四：文件系统与进程间通信
### 实验五：同步互斥


---

## 课程设计（大实验）

### 各种操作系统相关的功能和扩展

- RISC-V、x86-64、MIPS、ARM
- GUI、驱动、文件系统、网络
- 内核可加载模块、微内核

--- 

## 成绩评定

### 选择1： 
  - 按时完成实验一至实验五：40% 
  - 期中考试 20% +期末考试 40% ：60%
### 选择2： 
  - 7周内完成实验一至实验五(2021秋季实验)：40% 
  - 课程设计（即大实验）：60%
注：选择大实验的同学如果后续退出课程设计，请完成本学期的实验一至五，并参加考试。

--- 

## 调查问卷

[2022年春季学期操作系统课选课问卷](http://oscourse2019.mikecrm.com/kuIuYck)

- 为什么要学这门课？ 
- 你打算如何来学这门课？
- 对自己的课程学习要求是什么？
- 你愿意如实报告是否独立完成实验任务？
- 你希望在操作系统课上学到什么知识和什么能力？
- 以前的学习情况？

**采集仅限于清华和学堂在线的操作系统课内注册的同学信息** 

