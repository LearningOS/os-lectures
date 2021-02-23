# 已有教学素材收集

* [v1](https://github.com/LearningOS/os-lectures/blob/57187673ab9e28379108a50808c53d26ea88f2b2/lecture03/ref.md)

## 第3讲 进程与调度
### 参考

实验文档-[第二章实现批处理系统](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter2/3batch-system.html#id1)

[第三章多道程序与分时多任务](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter3/index.html)

### 3.1 进程概念

进程的概念（9.1 进程的概念[wiki](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture09)、[幻灯片]()）
进程控制块（9.2 进程控制块：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2018spring/lecture11?action=AttachFile&do=get&target=20180402-11-2-进程控制块.pptx)）
进程状态（9.3 进程状态：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture11?action=AttachFile&do=get&target=11-3-进程状态.pptx)）
三状态进程模型（9.4 三状态进程模型：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture11?action=AttachFile&do=get&target=11-4-三状态进程模型.pptx)）

### 3.2 进程调度

处理机调度概念（11.1 处理机调度概念[wiki](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture11)、[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture15?action=AttachFile&do=get&target=15-1.pptx)）

协作式调度与抢占式调度
 * 协作式调度：主动释放处理器
 * 抢占式调度：通过时钟中断来强制打断一个程序的执行

先来先服务调度算法（11.3 先来先服务：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture15?action=AttachFile&do=get&target=15-3.pptx)）
时间片轮转调度算法（11.4 时间片轮转：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture15?action=AttachFile&do=get&target=15-4.pptx)）

### 3.3 进程切换与管理（switch/fork/exec/wait/exit）

进程切换（12.1 进程切换：[wiki](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture10)、[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture12?action=AttachFile&do=get&target=12-1.pptx)）：

* 不同类型的上下文与切换：函数调用与返回；系统调用和返回；进程切换；
* 切换位置的要求：调用方；用户进程的可选位置；用户态的任意位置，内核的指定位置；

进程创建（12.2 进程创建：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture12?action=AttachFile&do=get&target=12-2.pptx)）
进程退出（12.4 进程等待与退出：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture12?action=AttachFile&do=get&target=12-4.pptx)）

### 3.4 同步互斥与进程间通信

进程同步（13.1 背景[wiki](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture13)、[幻灯片](os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture17?action=AttachFile&do=get&target=17-1%E8%83%8C%E6%99%AF.pptx)）

信号量的基本概念（14.1 信号量[wiki](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture14)、[幻灯片](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture14?action=AttachFile&do=view&target=20200402-18-1.pptx)）

进程通信（16.1 进程通信概念[wiki](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture16)、[幻灯片](os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture20?action=AttachFile&do=get&target=20-5.pptx)）
管道（16.2 信号和管道[幻灯片](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture20?action=AttachFile&do=get&target=20-6.pptx)）

### 3.5 multi-process OS

代码介绍

[用户栈与内核栈](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter2/4trap-handling.html#id7)：假定在批处理中只有一个进程，系统调用和异常触发的进入和退出内核时，会在内核栈和用户栈间进行切换；

[Trap 上下文的保存与恢复](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter2/4trap-handling.html#id8)：软件进行的上下文切换；

[Trap 分发与处理](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter2/4trap-handling.html#id9)

[执行应用程序](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter2/4trap-handling.html#ch2-app-execution)：进入用户态第一次执行应用程序；

[多道程序加载](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter3/1multi-loader.html#id5)

[任务切换的设计与实现](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter3/2task-switching.html#id5)：[不同类型的上下文与切换](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter3/2task-switching.html#id4)

[任务控制块与任务运行状态](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter3/3multiprogramming.html#id3)：简单的进程控制块和进程模型；

协作式和抢占式切换：

主动调用`sys_yield` 来交出 CPU 使用权。

* [多道程序背景与 yield 系统调用](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter3/3multiprogramming.html#yield)：这里的插图比较好；

[sys_yield 和 sys_exit](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter3/3multiprogramming.html#id3)：切换的实现；

进程状态图：

[第一次进入用户态](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter3/3multiprogramming.html#id5)：多进程下的第一次进入用户态；

[时钟中断与计时器](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter3/4time-sharing-system.html#id5)

[抢占式调度](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter3/4time-sharing-system.html#id6)

[时间片轮转调度实验文档](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter3/4time-sharing-system.html#id4)


