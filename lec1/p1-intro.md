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

2025年春季

[课程幻灯片列表](https://www.yuque.com/xyong-9fuoz/qczol5/oqo14u60786offgg)

---

## 课程信息

### 主讲教师：
  - 向勇 陈渝 李国良 任炬 

### 助教
  - 饶淙元、胡柯洋、闭浩扬、王拓为、苏明贤、黄旺、郝子胥

---

## 上课信息

### 上课时间地点
- 时间
  - 周一上午第2节(09:50-12:15) 
- 地点
   - 李国良课堂：舜德/经管西楼302
   - 任  炬课堂：舜德/经管西楼301
   - 陈  渝课堂：三教1103

----

## 预备知识

### 程序设计语言（汇编、C 和 Rust）
 - :confounded: 不是开发应用程序
 - :smile: 而是开发系统程序

### 数据结构
 - :smile: 理解基本数据结构即可

---

## 预备知识
### 计算机组成原理
 - :smile: :smile: :smile: 刘总/康总/陆总的 RISC-V 原理 
 - :smile: Patterson 的 RISC-V 原理

### 编译原理
 - :smile: 没学过影响不大 
 - :smile: 但还是要了解高级语言 <–>RISC-V 汇编语言


---

#### 课程参考
- [课程幻灯片](https://www.yuque.com/xyong-9fuoz/qczol5/oqo14u60786offgg)
- 参考书
  - [Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)
  - [深入了解计算机系统](https://hansimov.gitbook.io/csapp/)
  - [RISC-V Reader中文版](http://riscvbook.com/chinese/RISC-V-Reader-Chinese-v2p1.pdf)
#### 课程实践：rCore Tutorial Book v3
-  [课程实践参考书](https://learningos.github.io/rCore-Tutorial-Book-v3/)
-  [课程实践代码仓库](https://github.com/rcore-os/rCore-Tutorial-v3)
-  [课程实践代码的API文档](https://github.com/rcore-os/rCore-Tutorial-v3#os-api-docs)

---

### 实验指导


#### uCore Tutorial

- [实验代码](https://github.com/LearningOS/uCore-Tutorial-Code-2025S/)
- [实验文档](https://learningos.github.io/uCore-Tutorial-Guide-2025S/)
- [测试用例](https://github.com/LearningOS/uCore-Tutorial-Test-2025S/)

---

### 实验指导

* rCore Tutorial
  - [实验文档](https://learningos.github.io/rCore-Tutorial-Guide-2025S/)
  - [API文档](https://github.com/LearningOS/rCore-Tutorial-Guide-2025S/#os-api-docs-of-rcore-tutorial-code-2022a) 
  - [实验代码](https://github.com/LearningOS/rCore-Tutorial-Code-2025S)
  - [测试用例](https://github.com/LearningOS/rCore-Tutorial-Test-2025S)
* [uCore和rCore实验帮助](https://www.yuque.com/xyong-9fuoz/qczol5/ztzg6v1h3v2g4zcx)
  - 讲解视频
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

## 作业与实验

* **平时作业**
  - 课后练习：包括问答题和编程题目，要求在deadline前提交

* **基础实验**
  - （必做）：面向 RISC-V CPU 用 Rust/C 设计实现操作系统的功能
  - （选做）：难度和工作量比必做题目大的其它题目

* **课程设计（大实验）**
  - 用组件来组合操作系统内核 
  - 参加全国大学生OS比赛


---
## 基础实验
* 实验一：操作系统的基本支持
* 实验二：地址空间
* 实验三：进程管理与调度
* 实验四：文件系统与进程间通信
* 实验五：同步互斥

**注意：每次实验的必做题和选做题的提交截止时间相同。**


---

## 课程设计（大实验）

* **用组件来组合操作系统内核**

  - 组件化操作系统[ArceOS](http://arceos.org/overview.html)
* **操作系统功能和扩展**
  - 内核模块的完善和改进
  - 内核可加载模块、微内核、在内核中引入异步编程
  - RISC-V、x86-64、MIPS、ARM支持
  - RaspBerry PI、U740、D1等
  - GUI、驱动、文件系统、网络
* 往届同学的[课程设计成果](https://shimo.im/docs/QTPRT8h8jyGQCqkJ)

---

## 成绩评定

### 选择1：（总分不超过100） 
  - 实验一~五必做题目： 40% ；期中考试 20% ； 期末考试 40%
  - 平时作业加分：每做一次平时作业加0.5分，最高加5分，且课程总评成绩总分不超过100分

---

### 选择2： 
  - 四周内完成实验一~五(2025春实验)：40% 
  - 课程设计（即大实验）：60%

**注：选择大实验的同学如果后续退出课程设计，需参加考试。**

---

## 调查问卷

[2025年春学期操作系统课选课问卷](http://oscourse2019.mikecrm.com/kwIY4Ti)
访问密码：D7t1y5w4r
请大家在第一节课后尽快填写问卷，以便我们更好地上好课。