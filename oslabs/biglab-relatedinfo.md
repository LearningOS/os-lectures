# 2024春季OS课大实验（课程设计）相关信息

**参加课程设计的同学，需要每周（一般是周六上午）交流一次，主要交流内容是同学和老师/助教在本周的进展情况介绍，问题，解决方案、计划和建议等方面讨论，帮助各位同学顺利完成基本实验和大实验。**

## 自学操作系统基础知识（前四周完成）
**在第四周末检查5个实验的完成情况和对操作系统的掌握情况**

### 自学Rust
- 推荐: [带在线练习的The Rust Programming Language书籍](https://rust-book.cs.brown.edu/)
- [Rust 程序设计语言中文版书籍](https://kaisery.github.io/trpl-zh-cn/)

### 自学操作系统原理
- 推荐：[OS教材:OSTEP](https://pages.cs.wisc.edu/~remzi/OSTEP/)
- [OS教材OSTEP中文版](https://github.com/remzi-arpacidusseau/ostep-translations/tree/master/chinese)

### 自学OS基本实验
- OS实验指导(代码/指导/测试/测例等)：https://github.com/learningos/ 中的 u/rCore-Tutorial-*-2024S

## 开展大实验（后十二周完成）
**一人一队，鼓励各队之间多合作，形成共赢。每周交流一次，在交流前，需要完成周进展纪要文档。在第十六周末检查大实验的最终完成情况，并鼓励参加全国大学生操作系统比赛（可以是暑期课程内容，以最终系里公布情况为准）**
**对大实验最终完成情况的检查内容包括：每周进展纪要，代码仓库的更新情况，代码展示，总结报告，总结slide等**

### 大实验题目列表
- 支持Linux App(如healer, syzkaller, ConfFuzz, DDS等，不用都支持)的组件化宏内核框架和kernel直接相关内核模块改进和优化
- 支持Linux App(如healer, syzkaller, ConfFuzz, DDS等，不用都支持)的基于异步协程的组件化宏内核框架和kernel直接相关内核模块改进和优化 
- 兼容redox/seL4/zircon等的组件化微内核框架和kernel直接相关内核模块改进和优化
- 支持ARM or x64的组件化hypervisor框架和hypervisor直接相关内核模块改进和优化
- 支持Rust STD库的组件化unikernel框架和kernel直接相关内核模块改进和优化
- 扩展Verus安全验证的Rust-based seL4组件化微内核
- 扩展Prusti安全验证的Rust-based seL4组件化微内核
- 扩展Verus安全验证的Rust-based hypervisor的信息不干扰（参考asplos24-dai.pdf）
- 扩展Prusti安全验证的Rust-based hypervisor的信息不干扰（参考asplos24-dai.pdf）
- 基于OS无关内核组件设计，实现对[AI加速单元：如Intel NPU](https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/drivers/accel/ivpu)、瑞芯微RK3588 NPU，k230 NPU等)的内核驱动支持
- 基于OS无关内核组件设计，实现并扩展 x64/arm/rv64/loongarch的HAL（硬件抽象层）
- 基于OS无关内核组件设计，实现并扩展对starfive星光二代开发板的多种外设驱动支持
- 基于OS无关内核组件设计，实现并扩展对树莓派4开发板的多种外设驱动支持
- 基于OS无关内核组件设计，实现并扩展对通用PC计算机的多种外设驱动支持
- 基于OS无关内核组件设计，实现并扩展对[virtio spec](https://docs.oasis-open.org/virtio/virtio/v1.2/csd01/virtio-v1.2-csd01.html)的多种[virtio外设驱动支持](https://github.com/rcore-os/virtio-drivers)
- 基于OS相关/无关内核组件设计，实现并协程/线程/进程/扩展调度（linux支持的各种调度算法等）/内存分配(minmalloc等)/虚存管理/文件系统（ext4等）/网络协议栈/同步互斥/中断处理/驱动 的内核组件设计/优化/完善
- 扩展Verus（或Prusti/Kani等）安全验证的OS无关的内核组件（如上所示的各种内核组件）
- 支持用户态中断的新型操作系统内核设计（在研的学术科研项目）
 
注：上述内容绝大部分都有前期工作可以借鉴，也有同学/工程师在做，在下面的参考资源中大部分有提及，并可在前期的基础上进一步改进完善，可进一步联系助教和老师了解相关题目的细节。同学们也可提出自己的题目，并与老师交流，得到老师同意后可开展。

### 可作为大实验项目的参考和可选项

#### 2023年春季OS课大实验完成项目（代码，文档，slide等）和往年OS相关开源毕设等
- https://shimo.im/docs/QTPRT8h8jyGQCqkJ/read

上面有2023春季学期操作系统课程大实验的参加者和做的题目。
每位同学做的是某个操作系统的某个组成部分或一个比较完整的系统软件，如操作系统/hypervisor等。题目来于自科研项目，开源项目或自己的想法（需要与老师交流并得到老师的认可）等。

#### 开源实验小项目（也可作为本科或研究生毕设课题）
- https://github.com/orgs/rcore-os/discussions/categories/ideas

#### ArceOS相关
- https://github.com/rcore-os/arceos 源代码仓库
- https://oslearning365.github.io/arceos-tutorial-book/ 还未完成，仅供参考
- http://record-1257797626.cos.ap-beijing.myqcloud.com/cicvedu/100476113/1708953075907.mp4 该视频在第27分钟开始讲解了arceos的基本概念和编译运行等。


### 参考资源
####  系统工具
##### 面向Rust软件的安全验证工具
- [Rust 代码的形式化验证工具简要综述](https://zhuanlan.zhihu.com/p/637360324)
- [Verus:一个用于验证用 Rust 编写的代码(包括Rust操作系统)正确性的工具，验证语言也用的Rust](https://github.com/verus-lang/verus)
   - [Verus Guide&Tutorial](https://verus-lang.github.io/verus/guide/)
   - [用Verus验证OS的论文：Atmosphere: Towards Practical Verified Kernels in Rust](https://arkivm.github.io/publications/2023-kisv-atmo.pdf)
- [Prusti:基于 Viper 验证基础设施的Rust程序（包括Rust操作系统）的静态验证器](https://www.pm.inf.ethz.ch/research/prusti.html)
   - [用Prusti验证OS的论文：Leveraging Rust for Lightweight OS Correctness](https://dl.acm.org/doi/10.1145/3625275.3625398)
- [验证Rust hypervisor论文（清华OS课题组）：Verifying Rust Implementation of Page Tables in a Software Enclave Hypervisor](https://www.cs.columbia.edu/~rgu/publications/asplos24-dai.pdf)
- [kani:a bit-precise model checker for Rust](https://github.com/model-checking/kani)
##### 面向操作系统内核的Fuzzing工具
- [healer：基于Rust编写的fuzzer](https://github.com/SunHao-0/healer)
- [syzkaller](https://github.com/google/syzkaller)
  - [syzkaller相关信息](https://github.com/orgs/rcore-os/discussions/38) 
- [ConfFuzz - Fuzzing for Interface Vulnerabilities](https://github.com/conffuzz/conffuzz)
  - [ConfFuzz paper- NDSS23](https://arxiv.org/abs/2212.12904)
#### 中间件
- 基于Rust的DDS(用于机器人/工业控制/自动驾驶领域的中间件)
   - [RustDDS](https://github.com/jhelovuo/RustDDS)
   - [LixDDS](https://gitee.com/mrunix/lix-dds)
  
#### kernel&hypervisor
这是部分可供参考的OS&Hypervisor
- [unikernel形态的组件化内核ArceOS](https://github.com/rcore-os/arceos)
   - [可运行在RISC-V星光二代开发板上的ArceOS](https://github.com/yuoo655/arceos_net/tree/starfive2)
- [基于ArceOS的宏内核形态的组件化内核Starry kernel（支持RISC-V/x64/ARM/LoongArch）](https://github.com/Arceos-monolithic/Starry)
- [宏内核形态的组件化内核Byeos kernel（支持RISC-V/x64) 2023OS比赛一等奖]( https://www.github.com/yfblock/Byteos) 
- [宏内核形态的组件化内核Alien（支持RISC-V星光二代开发板） 2023OS比赛一等奖](https://github.com/Godones/Alien)
- [宏内核形态的组件化内核UMI (支持RISC-V华山派开发板) 2023OS比赛特等奖](https://github.com/js2xxx/umi)
- [基于ArceOS的微内核形态的组件化内核os kernel](https://github.com/jhdjames37/arceos)
- [基于ArceOS的Hypervisor形态的组件化hypervisor](https://github.com/arceos-hypervisor/hypercraft)
- [Rust-base seL4微内核操作系统](https://github.com/rel4team/rel4_kernel)

#### 参考：与OS无关的kernel components
这是部分与OS无关的kernel components，有一些不一定特别完善，供参考

- [基于C的ext4 crate](https://github.com/rcore-os/lwext4_rust)
- [基于Rust的ext4 crate](https://github.com/yuoo655/ext4_rs)
- [Rust-based tcpip stack: smoltcp](https://github.com/rcore-os/smoltcp)
- [C-based tcpip stack:lwip](https://github.com/Centaurus99/arceos-lwip)
- [virtio drivers](https://github.com/rcore-os/virtio-drivers)
- [e1000 NIC driver](https://github.com/rcore-os/e1000-driver)
- [Cadence Macb ethernet driver on Sifive fu740 board](https://github.com/rcore-os/cadence-macb-driver)
- [RISC-V星光二代开发板的网卡驱动](https://github.com/yuoo655/visionfive2_net_driver)
- [RISC-V星光二代开发板的SD卡驱动](https://github.com/os-module/visionfive2-sd) 
- [nvme driver](https://github.com/rcore-os/nvme_driver)
- [isomorphic_drivers](https://github.com/rcore-os/isomorphic_drivers)
- [os scheduler](https://github.com/131131yhx/arceos)
- [os memory malloc subsystem](https://github.com/rcore-os/mem_malloc_subsystem)

其他一些与还未归类的OS无关的kernel components，OS等所在网址
- [os-modules社区](https://github.com/os-module)
- [rcore-os社区](https://github.com/rcore-os)
- [基于Rust的操作系统列表](https://github.com/chyyuu/aos_course_info/blob/master/rustoslist.md)
