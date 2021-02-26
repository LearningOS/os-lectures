## 20210226-第四讲内容准备

### 第四讲 存储管理

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

SV39 多级页表机制：
[实现 SV39 多级页表机制（上）](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/3sv39-implementation-1.html#sv39)：在RV64架构下的虚拟地址与物理地址的访问属性（可读，可写，可执行等），组成结构（页号，帧好，偏移量等），访问的空间范围等；
[实现 SV39 多级页表机制（下）](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/4sv39-implementation-2.html#sv39)：物理内存管理、多级页表、地址转换；
[内核地址空间](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/5kernel-app-spaces.html#id6)、[应用地址空间](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/5kernel-app-spaces.html#id7)

[建立并开启基于分页模式的虚拟地址空间](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/6multitasking-based-on-as.html#id1)

从用户态到内核态的地址空间切换：[跳板的实现](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter4/6multitasking-based-on-as.html#id6)

#### 7. File-System 操作系统

[文件](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter6/1file-descriptor.html#id3)：
统一的抽象接口 `File` 
用户缓冲区的抽象 `UserBuffer`

[标准输入和标准输出](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter6/1file-descriptor.html#id3)

[文件描述符与文件描述符表](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter6/1file-descriptor.html#id5) ：进程控制块中的文件描述符表、进程的标准输入输出

[文件读写系统调用](https://rcore-os.github.io/rCore-Tutorial-Book-v3/chapter6/1file-descriptor.html#id6)

