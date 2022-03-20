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

## 第七讲 进程管理与单处理器调度
### 第四节 实践：建立进程的OS
<br>
<br>

Process OS(POS)


---
## 实践：POS
- **进化目标**
- 总体思路
- 历史背景
- 实践步骤
- 软件架构
- 相关硬件
- 程序设计

![bg right:65% 100%](figs/process-os-detail.png)


---
## 实践：PSOS -- 以往目标
提高性能、简化开发、加强安全
- Address Space OS: APP不用考虑其运行时的起始执行地址，隔离APP访问的内存地址空间
- multiprog & time-sharing OS目标: 让APP有效共享CPU，提高系统总体性能和效率
- BatchOS目标: 让APP与OS隔离，加强系统安全，提高执行效率
- LibOS目标: 让APP与HW隔离，简化应用访问硬件的难度和复杂性
---
## 实践：PSOS -- 进化目标
增强进程管理和资源管理
提高性能、简化开发、加强安全

- 整合之前的特权级、地址空间、任务，形成进程
- 进程成为资源的拥有者
- 扩展进程动态特征，能够在应用层面发出如下系统调用请求：
   - 动态创建子进程
   - 动态构造新进程
   - 子进程退出/父进程等待子进程退出

---
## 实践：PSOS
### 同学的进化目标
- 理解进程概念
- 理解进程的动态管理机制的设计与实现
- 初步认识进程调度
- 掌握shell应用的编写与使用
- 会写支持进程的操作系统

<!-- 智商最高的白垩纪“伤齿龙” 操作系统 troodon -->

![bg right 50%](figs/troodon.png)



---
## 实践：POS
- 进化目标
- **总体思路**
- 历史背景
- 实践步骤
- 软件架构
- 相关硬件
- 程序设计

![bg right:65% 100%](figs/process-os-detail.png)

---
### 总体思路
- 编译：应用程序和内核独立编译，合并为一个镜像
- 编译：不同应用程序可采用统一的起始地址
- 构造：系统调用服务，进程的管理与初始化
- 构造：建立基于页表机制的虚存空间
- 运行：特权级切换，进程与OS相互切换
- 运行：切换地址空间，跨地址空间访问数据


---
## 实践：POS
- 进化目标
- 总体思路
- **历史背景**
- 实践步骤
- 软件架构
- 相关硬件
- 程序设计

![bg right:65% 100%](figs/process-os-detail.png)


---
### 历史
- 1965：描述未来的 MULTICS 操作系统
  - MIT 的 Fernando J. Corbató 教授牵头
  - 参与单位：MIT, GE(通用电气公司), AT&T Bell Labs
  - 提出了进程的动态管理思想，启发和造就了UNIX
- 1971：Thompson shell 
  - 由Ken Thompson写的第一个UNIX Shell
  - 按照极简主义设计，语法非常简单，是一个简单的命令行解释器
  - 它的许多特征影响了以后的操作系统命令行界面的发展
---
## 实践：POS
- 进化目标
- 总体思路
- 历史背景
- **实践步骤**
- 软件架构
- 相关硬件
- 程序设计

![bg right:65% 100%](figs/process-os-detail.png)


---
### 实践步骤 
```
git clone https://github.com/rcore-os/rCore-Tutorial-v3.git
cd rCore-Tutorial-v3
git checkout ch5
cd os
make run
```

---
### 实践步骤 
```
[RustSBI output]
...
yield
**************/
Rust user shell
>>
```
操作系统启动``shell``后，用户可以在``shell``中通过敲入应用名字来执行应用。


---
## 实践：POS
- 进化目标
- 总体思路
- 历史背景
- 实践步骤
- **软件架构**
- 相关硬件
- 程序设计

![bg right:65% 100%](figs/process-os-detail.png)


---
**软件架构**
- 简化应用
- 建立Paging
- 内核页表
- 应用页表
- 信息传递
- 跳板机制
- 扩展TCB
- 扩展异常
  
![bg right:65% 100%](figs/process-os-detail.png)

---
### 代码结构
改进OS
```
├── os
    ├── build.rs(修改：基于应用名的应用构建器)
    └── src
         ├── loader.rs(修改：基于应用名的应用加载器)
         ├── main.rs(修改)
         ├── mm(修改：为了支持本章的系统调用对此模块做若干增强)
```

---
### 代码结构
改进OS
```
├── os
    └── src
         ├── syscall
             ├──fs.rs(修改：新增 sys_read)
             ├── mod.rs(修改：新的系统调用的分发处理)
             └── process.rs（修改：新增 sys_getpid/fork/exec/waitpid）
         ├── task
             ├── manager.rs(新增：任务管理器，为上一章任务管理器功能的一部分)
             ├── mod.rs(修改：调整原来的接口实现以支持进程)
             ├── pid.rs(新增：进程标识符和内核栈的 Rust 抽象)
             ├── processor.rs(新增：处理器管理结构 ``Processor`` ，为上一章任务管理器功能的一部分)
             └── task.rs(修改：支持进程管理机制的任务控制块)
         └── trap
              ├── mod.rs(修改：对于系统调用的实现进行修改以支持进程系统调用)
```


---
## 实践：POS
- 进化目标
- 总体思路
- 历史背景
- 实践步骤
- 软件架构
- **相关硬件** 没有变化
- 程序设计

![bg right:65% 100%](figs/process-os-detail.png)

---
## 实践：POS
- 进化目标
- 总体思路
- 历史背景
- 实践步骤
- 软件架构
- 相关硬件
- **程序设计** 
  <!-- 主要的事情就是**实现地址空间** -->

![bg right:65% 100%](figs/process-os-detail.png)



---
## 实践：POS - 程序设计
<!-- **程序设计**  -->
- **理解进程**
- 应用程序设计
- 内核程序设计


![bg right:40% 100%](figs/process-os-detail.png)



---
### 实践：POS  -- 程序设计
**应用角度：理解进程**
- **进程** 是正在执行的应用
  
**OS角度：理解进程**
-  **进程** 是应用在其地址空间上的一次执行过程
   - 进程拥有资源，操作系统根据进程的执行状态管理其资源 
![bg right:40% 100%](figs/seg-addr-space.png)

---
## 实践：POS - 程序设计
<!-- **程序设计**  -->
- 理解进程
- **应用程序设计**
- 内核程序设计


![bg right:40% 100%](figs/process-os-detail.png)


---
## 实践：POS -- 应用程序设计 
  - 系统调用
```
/// 功能：当前进程 fork 出来一个子进程。
/// 返回值：对于子进程返回 0，对于当前进程则返回子进程的 PID
/// syscall ID：220
pub fn sys_fork() -> isize;
```
```
/// 功能：将当前进程的地址空间清空并加载一个特定的可执行文件，返回用户态后开始它的执行。
/// 参数：path 给出了要加载的可执行文件的名字；
/// 返回值：如果出错的话（如找不到名字相符的可执行文件）则返回 -1，否则不应该返回。
/// syscall ID：221
pub fn sys_exec(path: &str) -> isize;
```
<!-- ![bg right:50% 100%](figs/app-as-full.png) -->



---
## 实践：POS -- 应用程序设计 
  - 系统调用
```
/// 功能：当前进程等待一个子进程变为僵尸进程，回收其全部资源并收集其返回值。
/// 参数：pid 表示要等待的子进程的进程 ID，如果为 -1 的话表示等待任意一个子进程；
/// exit_code 表示保存子进程返回值的地址，如果这个地址为 0 的话表示不必保存。
/// 返回值：如果要等待的子进程不存在则返回 -1；否则如果要等待的子进程均未结束则返回 -2；
/// 否则返回结束的子进程的进程 ID。
/// syscall ID：260
pub fn sys_waitpid(pid: isize, exit_code: *mut i32) -> isize;
```


---
## 实践：POS -- 应用程序设计 
应用``shell``的执行流程
1. 通过``sys_read``获取字符串（即文件名）
2. 通过``sys_fork``创建子进程
3. 在子进程中通过``sys_exec``创建新应用的进程
4. 在父进程中通过``sys_waitpid``等待子进程结束
5. 跳转到第一步循环执行

---
## 实践：POS - 程序设计
<!-- **程序设计**  -->
- 理解进程
- 应用程序设计
- **内核程序设计**

![bg right:40% 100%](figs/process-os-detail.png)

---
### 内核程序设计
- **应用的链接与加载支持**
- 核心数据结构
    - 进程控制块
    - 进程管理器
    - 处理器管理结构
- 进程管理机制
  - 初始进程创建
  - 进程生成与回收
  - 进程调度

![bg right:50% 100%](figs/process-os-detail.png)


---
### 内核程序设计 --  应用的链接与加载支持
在编译操作系统的过程中，会生成如下的 link_app.S 文件
```
 3 _num_app:
 4     .quad 15            #应用程序个数
 7 ......
 9 _app_names:             #app0的名字
10     .string "exit"          
12 ......
17 app_0_start:            #app0的开始位置
18     .incbin "../user/target/riscv64gc-unknown-none-elf/release/exit"
19 app_0_end:              #app0的结束位置
```


---
### 内核程序设计 --  应用的链接与加载支持
- 基于应用名的应用加载
在加载器 loader.rs 中，我们会分析 link_app.S 中的内容，并用一个全局可见的 只读 向量 ``APP_NAMES`` 来按照顺序将所有应用的名字保存在内存中，为通过 exec 系统调用创建新进程做好了前期准备。


---
### 内核程序设计 -- 核心数据结构
进程抽象的对应实现是进程控制块 -- ``TaskControlBlock``






---
## 小结
- 进程概念与进程实现的关系
- 进程管理机制
- 基本调度机制
- 能写伤齿龙OS
![bg right:50% 100%](figs/process-os-detail.png)