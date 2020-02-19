# 1. 多种语言协同构造的 OS

已有工作：

1. TypeKernel：三位六字班同学在2019年OS+编译专题训练课上的联合实验。用Haskell语言构造了一个用于编写OS的DSL，将其编译为C语言子集（C----），并实现了一个基于UEFI的Demo。

参考资料：

1. [Typekernel](http://os.cs.tsinghua.edu.cn/oscourse/OsTrain2019/g6)，[给后来者的话](https://github.com/typekernel/typekernel-doc/blob/master/TO_FOLLOWERS.md)

# 2. 为 rcore 实现更多 Linux 系统调用

主要目标：

* 在 rcore 上扩展 Linux 系统调用支持，以支持更多应用。可以考虑实现或者完善：信号机制、TTY、用户和群组权限管理、procfs和devfs。

已有工作：

1. 在 OS2019 大实验中，王润基和陈嘉杰合作在 rCore 中实现了 Linux ABI，支持运行原生的 Linux 程序（基于 musl libc，不支持 glibc）。目前 rCore 中已经实现了60多个 Linux Syscall（+20多个空实现），支持运行：Busybox, GCC, Nginx, Redis, Rustc 等实际应用。
2. [Biscuit](https://github.com/mit-pdos/biscuit) 是 MIT 用 Golang 编写的类 Unix OS，[相关论文](https://pdos.csail.mit.edu/papers/biscuit.pdf)发表在 OSDI2018 上。他们实现了58 个 Syscall（不完全兼容Linux），支持运行 Nginx 和 Redis（经过修改，基于他们自己的 libc）。性能测试与 Linux 对比，只慢了 5%-10%。我们尝试在 rCore 上重复这一工作，但最终由于真机调试过于困难而作罢。 

参考资料：

1. [rCore 对标 Biscuit OS 进行真实应用/网卡的性能测试](http://os.cs.tsinghua.edu.cn/oscourse/OS2019spring/projects/g04)
2. [rCore 毕业论文](http://os.cs.tsinghua.edu.cn/oscourse/OsTrain2019?action=AttachFile&do=view&target=Rust语言操作系统的设计与实现_王润基毕业论文.pdf)
3. [在 rCore 中实现 epoll](http://os.cs.tsinghua.edu.cn/oscourse/OsTrain2019/g4)
4. [在 rCore 中实现 SystemV 信号量和共享内存](http://os.cs.tsinghua.edu.cn/oscourse/OsTrain2019/g3)
5. [在 rCore 中实现 Framebuffer 运行 mgba](http://os.cs.tsinghua.edu.cn/oscourse/OS2019spring/projects/g02)

# 3. 用 RUST 重写 zircon（zCore）

主要目标：

* 基于 rCore 现有基础，用 Rust 重新实现 Zircon 微内核。
* 根据文档描述，实现相应的内核对象和系统调用，目标是能运行到 shell。
* 在新项目中尝试新技术、积累经验，用来重构和改进 rCore。

已有工作：

1. 潘庆霖在 OSTrain2019 大实验中对 Fuchsia 进行了完整的调研和分析。
2. 随后王润基在寒假期间尝试搭起了 zCore 项目框架，目前已实现了 8 个 syscall 和诸多内核对象，还剩 50 多个。
3. zCore 尝试的新技术包括：抽象出 HAL 以实现纯用户态开发和测试，应用 async 实现内核任务管理……

参考资料：

1. [Fuchsia 调研项目 wiki](http://os.cs.tsinghua.edu.cn/oscourse/OsTrain2019/g1)，[分析文档](https://github.com/PanQL/zircon-notes)
2. [zCore 项目仓库](https://github.com/rcore-os/zCore)
3. [Fuchsia 源码及官方文档](https://github.com/PanQL/fuchsia/tree/master/docs)
4. [Fuchsia 中文社区](https://fuchsia-china.com)

PS：

* 此项目是某位助教哥哥的毕设课题，和另一位助教哥哥本学期的个人娱乐项目：）））

# 4. 用 RUST 实现 KVM 功能

主要目标：

* 实现一个简单的 VMM（虚拟机监控程序）
* 对外提供 Linux KVM 或 [Zircon Hypervisor 接口](https://github.com/PanQL/fuchsia/tree/master/docs/reference/syscalls#hypervisor-guests)
* 尝试利用 x86 VT-x、RISCV H 扩展或 ARM 相关指令集
* 能够同时运行多个 rCore

参考资料：

1. [JailHouse：Linux-based Hypervisor](https://github.com/siemens/jailhouse)
2. [RVirt：MIT 用 Rust 写的 RISCV Hypervisor](https://github.com/siemens/jailhouse)
3. [Linux KVM](https://www.linux-kvm.org/page/Main_Page), [Apple Hypervisor Framework](https://developer.apple.com/documentation/hypervisor)

# 5. RISCV 用户态中断

主要目标：

* 利用 RISCV 用户态中断机制，改进 OS 以提升 IPC 及 IO 性能。

参考资料：

1. [RISCV 特权级手册](https://riscv.org/specifications/privileged-isa)

# 6. 重构 rcore 内核组件形成 OS-Kit

主要目标：

* 将 rCore 拆分成独立可复用的 crates，可组合成多种特定 OS

已有工作：

* 将庞大的 OS 拆分成一个个独立的模块，一直是 rCore 开发的指导思想和终极目标。不过现实中工程总是十分 dirty 的，需要不断地在优雅设计和实际产出中作出妥协。

参考资料：

* [JudgeDuckOS64](https://github.com/wangrunji0408/JudgeDuck-OS-64)：利用 rCore 现有模块重新实现的[应用程序稳态测试系统（评测鸭）](http://os.cs.tsinghua.edu.cn/oscourse/OS2018spring/projects/g04)

# 7. 为 rcore 适配树莓派4（ARM64）

主要目标：

* 让 rCore 支持树莓派4物理硬件
* 完善与改进已有的树莓派3驱动(SD卡、音频、GPU)，或添加新驱动支持(USB、网卡、蓝牙)

参考资料：

1. [rCore 的 ARM64 和树莓派3移植](http://os.cs.tsinghua.edu.cn/oscourse/OsTrain2018/g2)
2. [在 rCore 中支持树莓派3声卡](http://os.cs.tsinghua.edu.cn/oscourse/OS2019spring/projects/g08)
3. [在 rCore 中支持树莓派3 SD卡](http://os.cs.tsinghua.edu.cn/oscourse/OS2019spring/projects/g11)
4. [在 rCore 中移植 VideoCore IV 驱动](http://os.cs.tsinghua.edu.cn/oscourse/OsTrain2019/g2)

# 8. 为 rcore 适配基于 rv64 的物理硬件（如 K210、FPGA+Rocket Chip等）

# 9. 形式化验证的OS

# 10. 基于 rcore 的网络路由器

主要目标：

* 完善多网卡支持，实现系统路由表和内置的网络功能，或者给用户态提供一个类似PCAP的接口，然后编写一个软路由
* （可选）在计网联合实验的成果上继续
* （可选）优化 10G 网卡驱动（ixgbe）的稳定性和性能，并且在 PC 机上运行

参考资料：

1. [FPGA 上运行 RISC-V rCore 构建路由器](http://os.cs.tsinghua.edu.cn/oscourse/OS2019spring/projects/g05)
2. [计网联合实验](https://github.com/z4yx/Router-Lab/tree/master/Joint)

# 11. 改进rust语言的async on no-std

# 12. 内核态的rust std实现

# 13. 基于Labeled RISCV的OS kernel支持

参考资料：

1. [为 rCore 适配 PARD / Labeled RISCV](http://os.cs.tsinghua.edu.cn/oscourse/OsTrain2018/g3)

# 14. 在 rcore 中支持 container

# 1. 自由选择 OS 相关的论文、改进结果

参考资料

# 1. 为 rcore 添加 USB 驱动支持

主要目标：

* 在 rcore 中实现 USB 协议栈
* 支持简单的 USB 设备，如 USB 键盘/鼠标、U 盘读写
* 能够在至少一种真实硬件上演示(树莓派、PC)

参考资料：

1. [https://github.com/cfgbd/rustos/tree/master/usb](https://github.com/cfgbd/rustos/tree/master/usb)
1. [在 rCore 中移植 USB 驱动的尝试](http://os.cs.tsinghua.edu.cn/oscourse/OsTrain2018/g2)
