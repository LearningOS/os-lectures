# 操作系统课程，2025秋季，清华大学计算机系

## 老师与助教

### 主讲教师：
  - 向勇 陈渝 李国良 任炬
### 助教
  - 饶淙元、胡柯洋、闭浩扬、王拓为、苏明贤、黄旺、郝子胥
  - [AI助教](https://www.coze.com/store/agent/7466038346734387217?bot_id=true)
## 上课时间/地点

  
## 课程资源
### 课程大纲
- [课程&实验大纲](os-course-outline.md)
### 课程幻灯片
* [Github仓库](https://github.com/LearningOS/os-lectures/)
* [Gitee备份仓库](https://gitee.com/learning-os/os-lectures/)
* [课程幻灯片在线阅读](https://learningos.github.io/os-lectures/)
* pdf 版会在课前发布到网络学堂
### 课程参考书

* OS：[Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP)
* Computer System：[深入了解计算机系统](https://hansimov.gitbook.io/csapp)
* RISC-V CPU：[RISC-V Reader中文版](http://riscvbook.com/chinese/RISC-V-Reader-Chinese-v2p1.pdf)
* OS实践：[rCore Tutorial Book v3](https://rcore-os.github.io/rCore-Tutorial-Book-v3)
    * 配套代码和API文档
        * [Github仓库](https://github.com/rcore-os/rCore-Tutorial-v3)
        * [Gitee备份仓库](https://gitee.com/learning-os/rCore-Tutorial-v3)
        * [各章OS的API 在线文档](https://learningos.github.io/rCore-Tutorial-v3/)
        * [可显示内核动态执行信息的内核分支](https://github.com/rcore-os/rCore-Tutorial-v3/tree/ch9-log)
### 课程答疑
* [QA仓库](https://git.tsinghua.edu.cn/os-lab/q-and-a/)
* [助教的实验讲解视频](https://cloud.tsinghua.edu.cn/d/ce9eced17e89471c8c30/)
### 课后习题

[rCore Tutorial Book v3](https://rcore-os.github.io/rCore-Tutorial-Book-v3)中各章后面的“练习”小节中的“课后练习”和“练习参考答案”小节

###	往年考题

在网络学堂的“课程文件”中的“往年考试题”栏中。

### rCore基本实验

#### 实验指导书

包含每次实验必做的编程和问答作业，以及相对rCore Tutorial Book-v3较为精简的指导

* [rCore-Tutorial-Guide文档源码](https://github.com/LearningOS/rCore-Tutorial-Guide-2025S)
*  [rCore-Tutorial-Guide文档在线阅读](https://learningos.github.io/rCore-Tutorial-Guide-2025S/)
* [lab1(ch3) OS框架API在线文档](https://learningos.github.io/rCore-Tutorial-Code-2025S/ch3/os/index.html)
* [lab2(ch4) OS框架API在线文档](https://learningos.github.io/rCore-Tutorial-Code-2025S/ch4/os/index.html)
#### 代码框架

* [Github仓库](https://github.com/LearningOS/rCore-Tutorial-Code-2025S)
* [git.tsinghua仓库](https://git.tsinghua.edu.cn/os-lab/public/rcore-tutorial-code-2025s)
#### 用户态测例

* [Github仓库](https://github.com/LearningOS/rCore-Tutorial-Test-2025S)
* [git.tsinghua仓库](https://git.tsinghua.edu.cn/os-lab/public/rcore-tutorial-test-2025s)
### uCore基本实验

#### 实验指导书

* [Github仓库](https://github.com/LearningOS/uCore-Tutorial-Guide-2025S)
* [uCore-Tutorial-Guide文档在线阅读](https://learningos.github.io/uCore-Tutorial-Guide-2025S/)
#### 代码框架

* [Github仓库](https://github.com/LearningOS/uCore-Tutorial-Code-2025S)
* [git.tsinghua仓库](https://git.tsinghua.edu.cn/os-lab/public/ucore-tutorial-code-2025s)
#### 用户态测例

* [Github仓库](https://github.com/LearningOS/uCore-Tutorial-Test-2025S)
* [git.tsinghua仓库](https://git.tsinghua.edu.cn/os-lab/public/ucore-tutorial-test-2025s)

### 大实验
需要在规定时间内完成rCore或uCore基本实验，才能进行大实验。
欢迎所有感兴趣的同学尝试下面的大实验内容。如有问题，可联系陈渝老师等。

- [2025大实验相关信息](./oslabs/biglab-relatedinfo-2025s.md)


## 其它内容

 1. [幻灯片模板](style-marp.md)
 2. [RISC-V与X86 CPU硬件特征的对比介绍](rv-x86-hardware-info-video.md)
 3. 如何生成PDF/pptx slides
      - [ubuntu 用 markdown + vscode + marp 编写 slides 并输出为 pdf](https://www.cnblogs.com/luyi07/p/14736322.html)

        ```
        marp --pdf --html --allow-local-files lec[1-9]*/*.md # for building PDF slides
        marp --pptx --html --allow-local-files lec[1-9]*/*.md # for building pptx slides
        ```
 
 4. 如何合并pdf files
 
```
# Debian/Ubuntu 安装 poppler组件，包括 pdfunite工具
sudo apt install poppler-utils
# 合并pdf files
pdfunite input1.pdf input2.pdf input3.pdf output.pdf
```       
