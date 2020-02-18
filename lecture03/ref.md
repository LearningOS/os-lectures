# 已有教学素材收集

## 第3讲 中断、异常和系统调用
### 第1节 中断、异常和系统调用

ref：2018-lec3-chy.pdf

#### 背景
2018-lec3-chy.pdf：P24
为什么需要中断、异常和系统调用
	在计算机运行中，内核是被信任的第三方
	只有内核可以执行特权指令
	方便应用程序
中断和异常希望解决的问题
	当外设连接计算机时，会出现什么现象?
	当应用程序处理意想不到的行为时，会出现什么现象?
系统调用希望解决的问题
	用户应用程序是如何得到系统服务?
	系统调用和功能调用的不同之处是什么?

#### 计算机体系结构概述
2018-lec3-chy.pdf：P3、P4

#### RV板级图

需要补充（类似2018-lec3-chy.pdf：P9）

#### 中断、异常和系统调用比较
2018-lec3-chy.pdf：P25
源头
	中断:外设
	异常:应用程序意想不到的行为
	系统调用:应用程序请求操作提供服务
响应方式
	中断:异步
	异常:同步
	系统调用:异步或同步
处理机制
	中断:持续，对用户应用程序是透明的
	异常:杀死或者重新执行意想不到的应用程序指令
	系统调用:等待和持续

#### 基本的中断、异常和系统调用
ref：
rv的中断编号

#### 内核的进入与退出
2018-lec3-chy.pdf：P31
插图

#### 中断、异常和系统调用比较

插图2018-lec3-chy.pdf：P32

源头
	中断:外设
	异常:应用程序意想不到的行为
	系统调用:应用程序请求操作提供服务
响应方式
	中断:异步
	异常:同步
	系统调用:异步或同步
处理机制
	中断:持续，对用户应用程序是透明的
	异常:杀死或者重新执行意想不到的应用程序指令
	系统调用:等待和持续

#### 中断、异常和系统调用
2018-lec3-chy.pdf：P33
系统调用(system call)
	应用程序主动向操作系统发出的服务请求
异常(exception)
	非法指令或者其他原因导致当前指令执行失败 (如:内存出错)后的处理请求
中断(hardware interrupt)
	来自硬件设备的处理请求

#### 中断处理机制

插图2018-lec3-chy.pdf：P34

硬件处理
在CPU初始化时设置中断使能标志
	依据内部或外部事件设置中断标志
	依据中断向量调用相应中断服务例程

#### 中断和异常处理机制

插图2018-lec3-chy.pdf：P35

软件
现场保存(CPU+编译器)
中断服务处理(服务例程)
清除中断标记(服务例程)
现场恢复(CPU+编译器)

#### 中断嵌套
2018-lec3-chy.pdf：P36
硬件中断服务例程可被打断
	不同硬件中断源可能在硬件中断处理时出现
	硬件中断服务例程中需要临时禁止中断请求
	中断请求会保持到CPU做出响应
异常服务例程可被打断
	异常服务例程执行时可能出现硬件中断
异常服务例程可嵌套
	异常服务例程可能出现缺页

### 第2节 系统调用

#### 系统调用

2018-lec3-chy.pdf：P39

操作系统服务的编程接口
通常由高级语言编写(C、C++和rust等)
程序访问通常是通过高层次的API接口而不是直接进行系统调用
三种最常用的应用程序编程接口(API)
Win32 API 用于 Windows
POSIX API 用于 POSIX-based systems (包括UNIX，LINUX， Mac OS X的所有版本)
Java API 用于JAVA虚拟机(JVM)
ABI和API的区别

#### 使用 OpenSBI 提供的服务
https://rcore-os.github.io/rCore_tutorial_doc/chapter2/part6.html

https://stackoverflow.com/questions/3784389/difference-between-api-and-abi


API: Application Program Interface

This is the set of public types/variables/functions that you expose from your application/library.

In C/C++ this is what you expose in the header files that you ship with the application.
ABI: Application Binary Interface

This is how the compiler builds an application.
It defines things (but is not limited to):

    How parameters are passed to functions (registers/stack).
    Who cleans parameters from the stack (caller/callee).
    Where the return value is placed for return.
    How exceptions propagate.
#### 系统调用的实现
2018-lec3-chy.pdf：P40

#### 函数调用和系统调用的不同处
2018-lec3-chy.pdf：P41

#### 中断、异常和系统调用的开销
2018-lec3-chy.pdf：P42

### 第3节 RISC-V Intro (Intr/syscall )

https://riscv.org/wp-content/uploads/2016/07/Tue0900_RISCV-20160712-Interrupts.pdf

http://crva.ict.ac.cn/documents/RISC-V-Reader-Chinese-v2p1.pdf
RISC-V手册

#### RISC-V Interrupt Design Goals
Tue0900_RISCV-20160712-Interrupts.pdf：p3

#### Categorizing Sources of RISC-V Interrupts

Machine Interrupt Pending CSR (mip)
PlaCorm-Level Interrupt Controller (PLIC)
SoGware Interrupts
Timer Interrupts
Machine Interrupt Enable CSR (mie)
Interrupts in mstatus
All interrupts trap to M-mode by default
Optional Interrupt Handler Delegation
#### PLIC Conceptual Block Diagram
Tue0900_RISCV-20160712-Interrupts.pdf：p14
PLIC Interrupt Gateways
PLIC Per-Interrupt ID and Priority
#### PLIC Interrupt Flow
Tue0900_RISCV-20160712-Interrupts.pdf：p21
#### PLIC Interrupt Preemption/Nesting
PLIC Access Control
SiFive Freedom Platform PLIC Mapping

#### Interrupt/Trap Vectors
#### User-Level Interrupts “N”
#### Interrupts in Secure Embedded Systems
#### 函数调用规范(Calling convention)
RISC-V-Reader-Chinese-v2p1.pdf：p43
RISC-V 应用程序二进制接口(ABI)
	图 3.2 RISC-V 整数和浮点寄存器的汇编助记符
	标准的 RV32I 函数入口和出口
	结尾部分释放栈帧并返回调用点: RISC-V-Reader-Chinese-v2p1.pdf：p45

#### 异常和中断的原因
RISC-V-Reader-Chinese-v2p1.pdf：p102
图 10.3:RISC-V 异常和中断的原因

### 第4节 中断、异常、系统调用示例 (各种小例子)

#### 系统调用示例
2018-lec3-chy.pdf：P44
文件复制过程中的系统调用序列

#### rCore系统调用示例
类似2018-lec3-chy.pdf：P45

#### 手动触发断点中断
https://rcore-os.github.io/rCore_tutorial_doc/chapter3/part2.html

#### 访问系统调用
https://rcore-os.github.io/rCore_tutorial_doc/chapter8/part1.html

https://github.com/rcore-os/rCore_tutorial/blob/ch8-pa1/usr/rust/src/syscall.rs
访问系统调用的用户态代码

https://github.com/rcore-os/rCore_tutorial/blob/ch8-pa1/usr/rust/src/io.rs
println的用户态代码

#### 使用 OpenSBI 提供的服务
https://rcore-os.github.io/rCore_tutorial_doc/chapter2/part6.html




