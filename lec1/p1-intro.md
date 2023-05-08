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

向勇 陈渝 李国良 任炬 

<br>

2023年春季

---

## 课程信息

### 主讲教师：
  - 向勇
    * xyong@tsinghua.edu.cn

### 助教
  - 廖东海
      * ctrlz.donghai@gmail.com

---

## 预备知识

### 程序设计语言（汇编、C 和 Rust）
 - :( 不是开发应用程序
 - :) 而是开发系统程序

### 数据结构
 - :) 理解基本数据结构即可

---

## 预备知识
### 计算机组成原理
 - :) Patterson 的 RISC-V 原理

### 编译原理
 - :) 没学过影响不大 
 - :( 但还是要了解高级语言 <–>RISC-V 汇编语言

---

#### 课程参考

- 参考书
  - [Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)
  - [深入了解计算机系统](https://hansimov.gitbook.io/csapp/)
  - [RISC-V Reader中文版](http://riscvbook.com/chinese/RISC-V-Reader-Chinese-v2p1.pdf)
- 往年教学视频
  - [操作系统(RISC-V)](https://www.xuetangx.com/course/thu08091002729/12425488)
  - [操作系统](https://www.xuetangx.com/course/THU08091000267/12424484)

---

### 实验指导


#### uCore Tutorial

- [实验代码](https://github.com/LearningOS/uCore-Tutorial-Code-2023S/)
- [实验文档](https://learningos.github.io/uCore-Tutorial-Guide-2023S/)
- [测试用例](https://github.com/LearningOS/uCore-Tutorial-Test-2023S)

---

### 实验指导

#### rCore Tutorial
- [实验文档](https://learningos.github.io/rCore-Tutorial-Guide-2023S/)
- [API文档](https://github.com/LearningOS/rCore-Tutorial-Guide-2023S/#os-api-docs-of-rcore-tutorial-code-2022s) 
- [实验代码](https://github.com/LearningOS/rCore-Tutorial-Code-2023S)
- [测试用例](https://github.com/LearningOS/rCore-Tutorial-Test-2023S)

#### [uCore和rCore实验讲解视频](https://www.yuque.com/docs/share/1b5b9260-8a80-4427-a612-78ec72b37e5f)
- 部分内容将逐步更新

---


![bg right:57% 100%](figs/ucorearch.png)


### OS 原理与设计思想

- 操作系统结构
- 中断及系统调用
- 内存管理
- 进程管理
- 处理机调度
- 同步互斥
- 文件系统
- I/O 子系统

---

## 成绩评定

### 平时作业

- 课后练习：包括问答题和编程题目

### 成绩评定

  - 课堂和课后交流：10%
    - 提问和回答
    - 要求提问者在交流结束，将结论整理后放到雨课堂中
  - 课堂和课后练习：20%
  - 期末考试 70%

---

## 调查问卷

[DICT人才菁英计划培训班-2023春季操作系统课选课问卷](http://oscourse2019.mikecrm.com/SRu5Gpv)
（访问密码：Cs8x2uYk）

- 基本信息
- 知识背景
- 课程学习目标和要求
