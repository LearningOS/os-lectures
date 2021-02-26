### 第四讲 存储管理

 * [v1](https://github.com/LearningOS/os-lectures/blob/61f05814711b7dd6a8bfd0b7b4c3cf48025775ba/lecture04/ref.md)
 * [v2](https://github.com/LearningOS/os-lectures/blob/4578d7e2d1a2c4671e4503a611a11f07e41dbbcd/lecture04/ref.md)
 * V3

#### 1. 计算机体系结构和内存层次概述

4.1 计算机体系结构和内存层次：[幻灯片文件](http://os.cs.tsinghua.edu.cn/oscourse/OS2018spring/lecture05?action=AttachFile&do=get&target=20180424-5-1.pptx)、

#### 2. 内存分配概述

4.2 地址空间和地址生成：[幻灯片文件](http://os.cs.tsinghua.edu.cn/oscourse/OS2018spring/lecture05?action=AttachFile&do=get&target=20180424-5-2.pptx)、
4.3 连续内存分配：[幻灯片文件](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture05?action=AttachFile&do=get&target=5-3.pptx)（只用前两页）
5.1 非连续内存分配的需求背景：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture06?action=AttachFile&do=get&target=lecture06-1.pptx)

#### 3. 页式存储管理与多级页表

5.3 页式存储管理：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture06?action=AttachFile&do=get&target=lecture06-3.pptx)
5.4 页表概述：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture06?action=AttachFile&do=get&target=lecture06-4.pptx)
5.5 快表和多级页表：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture06?action=AttachFile&do=get&target=lecture06-5-6.pptx)

#### 4. 虚拟内存

6.4 虚拟存储概念：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2019spring/lecture08?action=AttachFile&do=get&target=20190320-os-08-05虚拟存储管理的概念.pptx)
6.5 虚拟页式存储管理：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2018spring/lecture08?action=AttachFile&do=get&target=20180514-os-08-06虚拟页式存储.pptx) 

#### 5. 文件系统概述

17.1 文件系统和文件：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture21?action=AttachFile&do=get&target=21-1.pptx)
17.2 文件描述符
17.6 文件分配：[PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2017spring/lecture21?action=AttachFile&do=get&target=20170508-21-4.pptx) 

#### 6. mem-isolation 操作系统

##### RISC-V页映射机制

5.6 RISC-V页映射机制：[PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture05?action=AttachFile&do=get&target=slide-05-06.pdf)中SV39的页表
5.7 使能RISC-V页表：[PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture05?action=AttachFile&do=get&target=slide-05-07.pdf)（这里的描述可能错的）

[实现 SV39 多级页表机制（上）](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/3sv39-implementation-1.html#sv39)：在RV64架构下的虚拟地址与物理地址的访问属性（可读，可写，可执行等），组成结构（页号，帧好，偏移量等），访问的空间范围等；

##### 逻辑地址和物理地址

[地址格式与组成](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/3sv39-implementation-1.html#id3)

[地址类型定义](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/address.rs#L5)

[地址和页号的相互转换](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/address.rs#L88)

##### 页表项

[页表项的数据结构抽象与类型定义](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/3sv39-implementation-1.html#id5)

[PageTableEntry](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/page_table.rs#L21)

 `PageTableEntry` 的工具[函数](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/page_table.rs#L45)

##### 地址转换过程

[多级页表原理](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/3sv39-implementation-1.html#id6)

SV39 中的 R/W/X 组合的含义

SV39 地址转换的全过程

##### 物理页管理

[实现 SV39 多级页表机制（下）](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/4sv39-implementation-2.html#sv39)：物理内存管理、多级页表、地址转换；

[物理页帧管理](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/4sv39-implementation-2.html#id2)

[FrameAllocator](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/frame_allocator.rs#L35)

##### 页表

[多级页表实现](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/4sv39-implementation-2.html#id5)

`PageTable`[数据结构](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/page_table.rs#L56)

[PageTable](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/page_table.rs#L114)

[PageTableEntry](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/page_table.rs#L21)

##### 地址映射建立和撤消

[建立和拆除虚实地址映射关系](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/4sv39-implementation-2.html#id8)

[map](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/page_table.rs#L114)

[unmap](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/page_table.rs#L120)

##### 地址空间

[逻辑段抽象](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/5kernel-app-spaces.html#id4)

[MapArea](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/memory_set.rs#L193)

[地址空间抽象](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/5kernel-app-spaces.html#id5)

[struct MemorySet](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/memory_set.rs#L38)

注：[Resource Acquisition is Initialisation (RAII) Explained](https://www.tomdalling.com/blog/software-design/resource-acquisition-is-initialisation-raii-explained/)

##### 内核地址空间

[内核地址空间](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/5kernel-app-spaces.html#id6)

[内核地址空间布局-高地址](https://rcore-os.github.io/rCore-Tutorial-Book-v3/_images/kernel-as-high.png)
[内核地址空间布局-低地址](https://rcore-os.github.io/rCore-Tutorial-Book-v3/_images/kernel-as-low.png)
[new_kernel](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/memory_set.rs#L78)

保护页面 (Guard Page)

##### 用户地址空间 

[应用地址空间](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/5kernel-app-spaces.html#id7)：借助地址空间的抽象，可以让所有应用程序都使用同样的起始地址；

[应用地址空间的布局](https://rcore-os.github.io/rCore-Tutorial-Book-v3/_images/app-as-full.png)

[from_elf](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/memory_set.rs#L126)

##### 内核地址空间初始化

[建立并开启基于分页模式的虚拟地址空间](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/6multitasking-based-on-as.html#id1)

CPU 将跳转到内核入口点并在 S 特权级上执行，此时并没有开启分页模式；

[内核地址空间初始化](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/mod.rs#L15)

##### 使能分页机制

[SV39 分页模式启用]()：S特权级的MMU使能；

切换 satp 的指令及其下一条指令这两条相邻的指令的 虚拟地址是相邻的

pc 只是简单的自增当前指令的字长

经过的地址转换流程却是不同的

切换之后是一个恒等映射

切换之前是视为物理地址直接取指，也可以将其看成一个恒等映射

##### 用户态与内核态间的地址空间切换

从用户态到内核态的地址空间切换：[跳板的实现](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/6multitasking-based-on-as.html#id6)

使能了分页机制后，必须用户态与内核态切换中同时完成地址空间的切换。即：通过修改 satp 在应用地址空间和内核地址空间间切换。应用和内核地址空间在切换地址空间指令附近是平滑的。

将 Trap 上下文保存在 应用地址空间的一个虚拟页面中，以避免切换到内核地址空间才能保存。

当应用 Trap 进入内核的时候，硬件会设置一些 CSR 并在 S 特权级下跳转到 `__alltraps` 保存 Trap 上下文。此时 sp 寄存器仍指向用户栈，但 `sscratch`则被设置为指向应用地址空间中存放 Trap 上下文的位置，实际在次高页面。

进入内核态后，先保存通用寄存器和一些 CSR；再切换到了内核地址空间；

 跳板页面：`__alltraps` 恰好位于这个物理页帧的开头，其物理地址被外部符号 `strampoline` 标记。在开启分页模式之后，内核和应用代码都只能看到地址空间



#### 7. File-System 操作系统

##### 文件接口

[文件](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter6/1file-descriptor.html#id3)：所有输入输出都被视为文件操作(Everything is a file)
统一的 `File`抽象[接口](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch6/os/src/fs/mod.rs#L5) 
用户缓冲区的抽象 `UserBuffer`：[struct UserBuffer](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch6/os/src/mm/page_table.rs#L199)

##### 标准输入和输出文件实现

[标准输入和标准输出](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter6/1file-descriptor.html#id3)

标准输入：[stdin](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch6/os/src/fs/stdio.rs#L10)

标准输出：[stdout](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch6/os/src/fs/stdio.rs#L33)

##### 文件描述符

[文件描述符与文件描述符表](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter6/1file-descriptor.html#id5) ：进程控制块中的文件描述符表、进程的标准输入输出

[进程控制块中的文件描述符表](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch6/os/src/task/task.rs#L20)：在进程创建时，缺省打开标准输入和输出；

##### 文件相关的系统调用

[文件读写系统调用](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter6/1file-descriptor.html#id6)：基于文件抽象接口和文件描述符表，可以让文件读写系统调用 `sys_read/write` 变得更加通用；