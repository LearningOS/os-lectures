## 第五讲 [物理内存管理: 非连续内存分配](http://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture06)

### 参考资料

http://crva.ict.ac.cn/documents/RISC-V-Reader-Chinese-v2p1.pdf
RISC-V手册

https://content.riscv.org/wp-content/uploads/2018/05/riscv-privileged-BCN.v7-2.pdf
RISC-V Privileged Architecture
很好的幻灯片；

http://web.cecs.pdx.edu/~harry/riscv/RISCV-Summary.pdf
RISC-V: An Overview of the Instruction Set Architecture
一本很好的RV电子书。

https://www2.eecs.berkeley.edu/Pubs/TechRpts/2016/EECS-2016-1.pdf
Design of the RISC-V Instruction Set Architecture

https://content.riscv.org/wp-content/uploads/2017/05/riscv-privileged-v1.10.pdf
RISC-V 指令集手册卷2：特权体系结构（Privileged Architecture Version 1.10）

2.2CSR地址映射约定
CSR地址约定使用CSR地址的高位来编码缺省的访问特权。这简化了硬件中的错误检测。

## 第1节 非连续内存分配的需求背景 

## 第2节 段式存储管理 

## 第3节 页式存储管理 
## 第4节 页表概述 
## 第5节 快表和多级页表 
## 第6节 反置页表 
## 第7节 段页式存储管理
## 第8节 RISC-V的内存管理机制 


#### Sv32、39、48、57和64
基于页面的虚拟存储器体系结构
Sv32、Sv39、Sv48 需要实现支持 M、S 和 U 特权级。

### Sv32
[4000264810-6362872868596917296596815.pdf]p42

Sv32 实现支持一个 32 位虚拟地址空间，分割成 4KB 页面。


V 位表明 PTE 是否是有效的;
Type 字段表明了 PTE 是一个指 向下级页表的指针，还是一个叶子 PTE(leaf PTE)。同时还编码了访 问权限。
每个叶子 PTE 维护一个被引用(referenced，R)位和脏(dirty，D)位。



### Sv39
[4000264810-6362872868596917296596815.pdf]p45


### CSR address space
[riscv-privileged-BCN.v7-2.pdf]p12

### RISC-V Page Table Entries
[riscv-privileged-BCN.v7-2.pdf]p16
### Memory Fences
[riscv-privileged-BCN.v7-2.pdf]p17

### 页表
https://rcore-os.github.io/rCore_tutorial_doc/chapter5/part1.html
页表：从虚拟内存到物理内存
#### 页表项
页表项 (PTE, Page Table Entry)
#### 多级页表

#### 页表基址


### RISC-V Virtual Memory Protections
[riscv-privileged-BCN.v7-2.pdf]p19


### Physical Memory Attributes
[riscv-privileged-BCN.v7-2.pdf]p21