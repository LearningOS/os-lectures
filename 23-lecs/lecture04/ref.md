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

[地址格式与组成](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/3sv39-implementation-1.html#id3)：

* 在 64 位架构上虚拟地址长度应该是 64 位
* SV39 分页模式规定 64 位虚拟地址的 [63:39]这 25 位必须和第 38 位相同
* MMU 取出后 39 位，再尝试将其转化为 56 位的物理地址

![sv39-va-pa](/Users/xyong/github/os-lectures/lecture04/figs/sv39-va-pa.png)

[地址类型定义](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/address.rs#L5)：`struct PhysAddr`、`struct VirtAddr`、`struct PhysPageNum`、`struct VirtPageNum`

![address-5](/Users/xyong/github/os-lectures/lecture04/figs/address-5.png)

[地址和页号的相互转换](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/address.rs#L88)：

![address-88](/Users/xyong/github/os-lectures/lecture04/figs/address-88.png)

##### 页表项

![sv39-pte](/Users/xyong/github/os-lectures/lecture04/figs/sv39-pte.png)

[页表项的数据结构抽象与类型定义](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/3sv39-implementation-1.html#id5)

[PageTableEntry](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/page_table.rs#L21)

 `PageTableEntry` 的工具[函数](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/page_table.rs#L45)

![page_table-45](/Users/xyong/github/os-lectures/lecture04/figs/page_table-45.png)

##### 页表

[多级页表实现](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/4sv39-implementation-2.html#id5)

`PageTable`[数据结构](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/page_table.rs#L56)

![page_table-56](/Users/xyong/github/os-lectures/lecture04/figs/page_table-56.png)

[PageTable](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/page_table.rs#L114)



##### 地址转换过程

[多级页表原理](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/3sv39-implementation-1.html#id6)

SV39 地址转换的全过程

![sv39-full](/Users/xyong/github/os-lectures/lecture04/figs/sv39-full.png)

SV39 中的 R/W/X 组合的含义

![pte-rwx](/Users/xyong/github/os-lectures/lecture04/figs/pte-rwx.png)



##### 地址映射建立和撤消

[建立和拆除虚实地址映射关系](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/4sv39-implementation-2.html#id8)：

* 在多级页表中找到一个虚拟地址对应的页表项
* 修改页表项的内容以建立虚实地址映射关系
* 页表中间的页表项可能未创建：手动分配物理页存放该页表项

[map](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/page_table.rs#L114)、[unmap](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/page_table.rs#L120)：

![page_table-114](/Users/xyong/github/os-lectures/lecture04/figs/page_table-114.png)



##### 物理页管理

[实现 SV39 多级页表机制（下）](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/4sv39-implementation-2.html#sv39)：物理内存管理、多级页表、地址转换；

[物理页帧管理](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/4sv39-implementation-2.html#id2)：

* 声明一个 `FrameAllocator` Trait 描述物理页帧管理器的功能
* 实现一种简单的栈式物理页帧管理策略 `StackFrameAllocator` 

[FrameAllocator](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/frame_allocator.rs#L35)

![frame_allocator-L35](/Users/xyong/github/os-lectures/lecture04/figs/frame_allocator-L35.png)

栈式物理页帧管理策略

* 分配 `alloc` 时，检查栈 `recycled` 内有没有之前回收的物理页号；
  * 如果有的话直接弹出栈顶并返回；
  * 否则，从之前从未分配过的物理页号区间的左端点 `current`分配。
* 回收 `dealloc` 时，检查回收页面的合法性，然后将其压入 `recycled` 栈中。



##### 地址空间

[逻辑段](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/5kernel-app-spaces.html#id4)：指地址区间中的一段属性相同的连续虚拟地址区间，以相同方式映射到物理页帧。

[MapArea](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/memory_set.rs#L193)

![memory_set-L193](/Users/xyong/github/os-lectures/lecture04/figs/memory_set-L193.png)

[地址空间](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/5kernel-app-spaces.html#id5)：包含一个多级页表 `page_table` 和一个逻辑段 `MapArea` 的向量 `areas` 。

[struct MemorySet](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/memory_set.rs#L38)

![memory_set-L38](/Users/xyong/github/os-lectures/lecture04/figs/memory_set-L38.png)

注：[Resource Acquisition is Initialisation (RAII) Explained](https://www.tomdalling.com/blog/software-design/resource-acquisition-is-initialisation-raii-explained/)

##### 内核地址空间

[内核地址空间](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/5kernel-app-spaces.html#id6)

[内核地址空间高256GiB布局](https://rcore-os.github.io/rCore-Tutorial-Book-v3/_images/kernel-as-high.png)

![kernel-as-high](/Users/xyong/github/os-lectures/lecture04/figs/kernel-as-high.png)

[内核地址空间低256GiB布局](https://rcore-os.github.io/rCore-Tutorial-Book-v3/_images/kernel-as-low.png)：四个逻辑段 `.text/.rodata/.data/.bss` 被恒等映射到物理内存；

![kernel-as-low](/Users/xyong/github/os-lectures/lecture04/figs/kernel-as-low.png)





[new_kernel](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/memory_set.rs#L78)

保护页面 (Guard Page)

##### 用户地址空间 

[应用地址空间](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/5kernel-app-spaces.html#id7)：借助地址空间的抽象，可以让所有应用程序都使用同样的起始地址；

[应用地址空间的布局](https://rcore-os.github.io/rCore-Tutorial-Book-v3/_images/app-as-full.png)

![app-as-full](/Users/xyong/github/os-lectures/lecture04/figs/app-as-full.png)

[from_elf](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/memory_set.rs#L126)

##### 内核地址空间初始化

[建立并开启基于分页模式的虚拟地址空间](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/6multitasking-based-on-as.html#id1)

* CPU 将跳转到内核入口点并在 S 特权级上执行，此时并没有开启分页模式；

[内核地址空间初始化](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch4/os/src/mm/mod.rs#L15)

![mod-L15](/Users/xyong/github/os-lectures/lecture04/figs/mod-L15.png)

##### 使能分页机制

[SV39 分页模式启用]()：S特权级的MMU使能；

* 切换 satp CSR 必须是平滑，即切换 satp 的指令及其下一条指令的虚拟地址是相邻的；
* 内核内存布局的代码段在切换之后采用恒等映射，切换前的物理地址直接访问可视为恒等映射。

##### 用户态与内核态间的地址空间切换

[跳板的实现](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/6multitasking-based-on-as.html#id6)

需求：

1. 使能了分页机制后，必须用户态与内核态切换中同时完成地址空间的切换。
2. 通过修改 satp 在应用地址空间和内核地址空间间切换。
3. 应用和内核地址空间在切换地址空间指令附近是平滑的。

实现：

* 内核与用户进程各有自己的地址空间，共享同一个Trampoline（ `__alltraps` 的代码）和TrapContext（ `__alltraps` 的数据）；Trampoline可在用户地址空间和内核态时访问。
* 当应用 Trap 进入内核时，硬件会设置一些 CSR 并在 S 特权级下跳转到 `__alltraps` 保存 Trap 上下文。

map_trampoline建立跳板区域的虚实映射关系：

1. 用户态是不能访问的；
2. 中断时，中断进入时硬件保存现场并不直接访问这个区域的内存，而是放在寄存器中；
3. 这个区域只在内核态且是用户地址空间时访问；
4. 这两个页表的设置是一样的，可以保证它只在内核态可以访问；
5. 中断服务例程的地址在链接时得到；



#### 7. File-System 操作系统

##### 文件接口

[文件](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter6/1file-descriptor.html#id3)：所有输入输出都被视为文件操作(Everything is a file)
统一的 `File`抽象[接口](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch6/os/src/fs/mod.rs#L5)

![mod-L5](/Users/xyong/github/os-lectures/lecture04/figs/mod-L5.png)

用户缓冲区的抽象 `UserBuffer`：[struct UserBuffer](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch6/os/src/mm/page_table.rs#L199)

![page_table-L199](/Users/xyong/github/os-lectures/lecture04/figs/page_table-L199.png)

##### 标准输入和输出文件实现

[标准输入和标准输出](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter6/1file-descriptor.html#id3)

标准输入：[stdin](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch6/os/src/fs/stdio.rs#L10)

![stdio-L10](/Users/xyong/github/os-lectures/lecture04/figs/stdio-L10.png)

标准输出：[stdout](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch6/os/src/fs/stdio.rs#L33)

![stdio-L33](/Users/xyong/github/os-lectures/lecture04/figs/stdio-L33.png)

##### 文件描述符

[文件描述符与文件描述符表](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter6/1file-descriptor.html#id5) ：进程控制块中的文件描述符表、进程的标准输入输出

![task-L20](/Users/xyong/github/os-lectures/lecture04/figs/task-L20.png)

[进程控制块中的文件描述符表](https://github.com/rcore-os/rCore-Tutorial-v3/blob/ch6/os/src/task/task.rs#L20)：在进程创建时，缺省打开标准输入和输出；

##### 文件相关的系统调用

[文件读写系统调用](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter6/1file-descriptor.html#id6)：基于文件抽象接口和文件描述符表，可以让文件读写系统调用 `sys_read/write` 变得更加通用；

![fs-L5](/Users/xyong/github/os-lectures/lecture04/figs/fs-L5.png)

