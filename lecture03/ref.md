# 已有教学素材收集

* [v1](https://github.com/LearningOS/os-lectures/blob/57187673ab9e28379108a50808c53d26ea88f2b2/lecture03/ref.md)
* [v2](https://github.com/LearningOS/os-lectures/blob/8dc5af59fb5f79fef2d9ee26915863648a3da9af/lecture03/ref.md)
* v3

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

### 3.5 教学实验：分时多任务系统

#### 系统调用：中断上下文保存与恢复

`TrapContext` [结构体](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3-coop/os/src/trap/context.rs#L4)

`__alltraps` 的[实现](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3-coop/os/src/trap/trap.S#L12)

上下文恢复的 `__restore` 的[实现](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3-coop/os/src/trap/trap.S#L40)

#### 任务切换：任务上下文(Task Context)

![task_context](/Users/xyong/github/os-lectures/lecture03/figs/task_context.png)

 `TaskContext` [数据结构](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3-coop/os/src/task/context.rs#L2)

#### 进程切换过程

![switch](/Users/xyong/github/os-lectures/lecture03/figs/switch.png)

`__switch` 的[实现](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3-coop/os/src/task/switch.S#L10)

#### 进程切换的实现

如何进入用户态第一次执行应用程序？

 `run_next_app` [函数](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch2/os/src/batch.rs#L116)

 `app_init_context` [函数](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch2/os/src/trap/context.rs#L12)

#### 多道批处理系统中的程序加载

 `load_apps` [函数](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3-coop/os/src/loader.rs#L55)

#### 进程管理：任务运行状态

简单的进程控制块数据结构和三状态进程模型

![fsm-coop](/Users/xyong/github/os-lectures/lecture03/figs/fsm-coop.png)

```TaskStatus```[数据结构](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3-coop/os/src/task/task.rs#L13)

#### 进程管理：任务控制块

**任务控制块** (Task Control Block)：```TaskControlBlock``` [数据结构](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3-coop/os/src/task/task.rs#L1)

#### 协作式调度：主动让出CPU

主动调用`sys_yield` 来交出 CPU 使用权。

![multiprogramming](/Users/xyong/github/os-lectures/lecture03/figs/multiprogramming.png)

#### sys_yield 和 sys_exit

 `sys_yield` [系统调用](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3/user/src/syscall.rs#L27)

```sys_yield```的[实现](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3/os/src/syscall/process.rs#L13)

```sys_exit```的[实现](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3/os/src/syscall/process.rs#L7)

#### 第一次进入用户态

多进程下的第一次进入用户态；

 `init_app_cx` 的[实现](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3/os/src/loader.rs#L82)

 `task::run_first_task` 的[实现](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3/os/src/task/mod.rs#L48)

```task::run_next_task```的[实现](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3/os/src/task/mod.rs#L82)

#### 抢占式调度

`timer` [模块](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3/os/src/timer.rs#L12)

`suspend_current_and_run_next` 的[引用](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3/os/src/trap/mod.rs#L53)和[实现](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch3/os/src/task/mod.rs#L119)


