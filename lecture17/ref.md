
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


