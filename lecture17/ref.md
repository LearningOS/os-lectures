### 第十七讲 文件系统扩展

* [v1](https://github.com/LearningOS/os-lectures/blob/ded5de1d168c7ed7bbf6845129a1455ccdaac432/lecture17/ref.md)：2020年的第十七讲大纲
* [v2](https://github.com/LearningOS/os-lectures/blob/ab62be1d45ca15ee6aeab1ec049e99b1ec6ae1ae/lecture17/ref.md)：2021年第十七讲大纲第一稿
* [v3]:test

#### 参考文献

2020年[第十七讲 文件系统概念](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture17)：去年的内容全新地讲；

2021年[第四讲 存储管理](https://os.cs.tsinghua.edu.cn/oscourse/OS2021spring/lecture04)：这里的第4.5节讲了文件系统的基本概念和文件的组织结构；

#### 17.1 目录与文件别名

回顾：文件、文件组织、rCore的文件系统

  [PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture21?action=AttachFile&do=get&target=21-1.pptx)   

#### 17.2 空闲空间管理

  [空闲空间管理](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture21?action=AttachFile&do=get&target=21-5.pptx)

#### 17.3 VFS

VFS（共享，缓存）：文件缓存和打开文件： [PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture21?action=AttachFile&do=get&target=21-3.pptx)   

[The virtual file system (VFS)](www.cs.uni.edu/~diesburg/courses/dd/notes/VFS.pptx)：这里是一个55页的幻灯片，主要介绍VFS的接口；

[Virtual File System](https://www.cs.unc.edu/~porter/courses/cse506/s16/slides/vfs.pdf)：这也是一个关于VFS的课程幻灯片；



#### 17.4 procfs

##### procfs文档

[procfs](https://tldp.org/LDP/Linux-Filesystem-Hierarchy/html/proc.html)：这里是对procfs的技术描述；

/proc is very special in that it is also a virtual filesystem.

it can be regarded as a control and information centre for the  kernel.a lot of system utilities are simply calls to files  in this directory.

all of them have a file size of 0, with the exception of kcore, mtrr  and self.

it as a window into the kernel. it just acts as a pointer to where the actual  process information resides.



一些常见的proc目录和文件：

/proc/PID/fd

Directory,  which contains all file descriptors.

/proc/PID/maps

Memory  maps to executables and library files.

/proc/PID/status

Process  status in human readable form.

/proc/mtrr

 Information regarding  mtrrs. the Memory Type Range Registers (MTRRs) may be used to control processor  access to memory ranges. This is most useful when you have a video (VGA)  card on a PCI or AGP bus. Enabling write-combining allows bus write  transfers to be combined into a larger transfer before bursting over the  PCI/AGP bus. This can increase performance of image write operations 2.5  times or more.

##### wikipedia-procfs

[wikipedia-procfs](https://en.wikipedia.org/wiki/Procfs)

The proc filesystem (procfs) is a special filesystem in Unix-like operating systems that presents information about processes and other system information in a hierarchical file-like structure, providing a more convenient and standardized method for dynamically accessing process data held in the kernel than traditional tracing methods or direct access to kernel memory.

Typically, it is mapped to a mount point named /proc at boot time.

The proc file system acts as an interface to internal data structures in the kernel. It can be used to obtain information about the system and to change certain kernel parameters at runtime (sysctl).

The proc filesystem provides a method of communication between kernel space and user space.

/proc/PID/cmdline, the command that originally started the process.
/proc/PID/cwd, a symlink to the current working directory of the process.
/proc/PID/environ contains the names and values of the environment variables that affect the process.
/proc/PID/exe, a symlink to the original executable file, if it still exists (a process may continue running after its original executable has been deleted or replaced).
/proc/PID/fd, a directory containing a symbolic link for each open file descriptor.
/proc/PID/fdinfo, a directory containing entries which describe the position and flags for each open file descriptor.
/proc/PID/maps, a text file containing information about mapped files and blocks (like heap and stack).
/proc/PID/mem, a binary image representing the process's virtual memory, can only be accessed by a ptrace'ing process.
/proc/PID/root, a symlink to the root path as seen by the process. For most processes this will be a link to / unless the process is running in a chroot jail.
/proc/PID/status contains basic information about a process including its run state and memory usage.
/proc/PID/task, a directory containing hard links to any tasks that have been started by this (i.e.: the parent) process.

##### A brief history of /proc

[](http://dtrace.org/blogs/eschrock/2004/06/25/a-brief-history-of-proc/)
Tom Killian wrote the first implementation of /proc, explained in his paper published in 1984. It was designed to replace the venerable ptrace system call, which until then was used for primitive process tracing.

##### procfs intro from IBM （非常好的参考）

[Archived | Access the Linux kernel using the /proc filesystem](https://developer.ibm.com/technologies/linux/articles/l-proc/)

介绍了procfs的机理；

procfs类似的文件系统还有sysfs和debugfs.

与内核的交互：
Interactive tour of /proc: `ls /proc`
Reading from and writing to /proc (configuring the kernel): 

```
cat /proc/sys/net/ipv4/ip_forward
0
echo "1" > /proc/sys/net/ipv4/ip_forward
cat /proc/sys/net/ipv4/ip_forward

1
```

可通过可加载内核模块在procfs中加信息交互文件；它通过回调函数完成信息交互。

[Linux Kernel Procfs Guide](https://kernelnewbies.org/Documents/Kernel-Docbooks?action=AttachFile&do=get&target=procfs-guide_2.6.29.pdf)：这里介绍了procfs的编程和接口；

[Linux 文件系统：procfs, sysfs, debugfs 用法简介](https://www.cnblogs.com/qiuheng/p/5761877.html)

 * procfs 历史最早，最初就是用来跟内核交互的唯一方式，用来获取处理器、内存、设备驱动、进程等各种信息。
 * sysfs 跟 kobject 框架紧密联系，而 kobject 是为设备驱动模型而存在的，所以 sysfs 是为设备驱动服务的。
 * debugfs 从名字来看就是为debug而生，所以更加灵活。

[DebugFS, SecurityFS, PipeFS, and SockFS](http://dcjtech.info/topic/debugfs-securityfs-pipefs-and-sockfs/)：这里简单介绍了几种VFS的特点和适用场景；

#### 17.5 内核动态分析

[Using the Linux Tracing Infrastructure](https://events.static.linuxfound.org/sites/events/files/slides/praesentation_0.pdf)：这里描述了内核跟踪的一些基础设施；


