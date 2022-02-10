### 进程地址空间与熔断(meltdown)漏洞

#### 历史版本

[v1](https://github.com/LearningOS/os-lectures/blob/eeab82b9b9682d079b2ad7e63e522e48079d1098/lecture09/ref.md)

[v2](https://github.com/LearningOS/os-lectures/blob/9019d3ae3a8b18c6a0ec1a230652bf0f24714066/lecture09/ref.md)

#### ref

https://mp.weixin.qq.com/s/zlspXeDGlAEzVsq2h6gg8w
首发：Meltdown漏洞分析与实践 （nice）

https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=694d99d40972f12e59a3696effee8a376b79d7c8
x86/cpu, x86/pti: Do not enable PTI on AMD processors

https://github.com/xyongcn/exploit/tree/master/meltdown
meltdown和spectre比较

https://github.com/21cnbao/meltdown-example
宋宝华： 用代码切身实践体会meltdown漏洞

[CPU Meltdown和Spectre漏洞分析](https://www.cnblogs.com/Shepherdzhao/p/8253421.html)

https://mp.weixin.qq.com/s/2FvvFUT8taRPv6GOHzNW-g
处理器A级漏洞Meltdown(熔毁)和Spectre(幽灵)分析报告 （nice：有几个很好的图示）

https://meltdownattack.com/meltdown.pdf
Meltdown: Reading Kernel Memory from User Space

https://spectreattack.com/spectre.pdf
Spectre Attacks: Exploiting Speculative Execution

Kernelpage-table isolation (KPTI)

https://lwn.net/Articles/741878/
The current state of kernel page-table isolation

https://gruss.cc/files/kaiser.pdf
KASLR is Dead: Long Live KASLR

https://www.zhihu.com/question/265012502?utm_medium=social&utm_source=wechat_session&from=groupmessage&isappinstalled=0
有几个很好的图。

Kernel page-tableisolation

http://voltjockey.com/

http://voltjockey.com/flies/paper/2.pdf
VoltJockey: Breaking SGX by Software-ControlledVoltage-Induced Hardware Faults

#### 背景

假设有abc三个地址，其中a地址没有访问的权限，但是b和c可以访问，此时执行下面这个条件表达式：

x= a？b:c

表面看来，由于a地址无法访问，所以系统会直接报错！
但实际上，CPU为了加快执行速度，会采用多流水线作业方式。它会在检查a是否可访问的同时，预先就往下执行了。
等到权限检查结果回来，已经根据a的结果完成了b或者c的加载，只是还没有赋给x而已。经过加载的b或者c会在缓存里。虽然报错了，但如果再次访问就会比较快。
于是再次访问b和c，根据返回的时间快慢，就可以猜到a的内容！

#### CPU高速缓存结构(Intel Skylake)

[How Does CPU Cache Work?](https://www.makeuseof.com/tag/what-is-cpu-cache/)

![cache-in-skylake](figs/cache-in-skylake.png)

https://mp.weixin.qq.com/s/zlspXeDGlAEzVsq2h6gg8w

各级存储结构的访问延迟

| 访问类型            | 延迟           |
| ------------------- | -------------- |
| L1 cache命中        | 约4个时钟周期  |
| L2 cache 命中       | 约10个时钟周期 |
| L3 cache命中        | 约40个时钟周期 |
| 访问本地DDR         | 约60 纳秒      |
| 访问远端内存节点DDR | 约100纳秒      |

#### 指令执行的乱序优化(Intel Skylake)
https://meltdownattack.com/meltdown.pdf
Meltdown: Reading Kernel Memory from User Space
Figure 1: Simplified illustration of a single core of the Intel’s Skylake microarchitecture

![skylake-out-of-order](figs/skylake-out-of-order.png)

https://www.zhihu.com/question/265012502?utm_medium=social&utm_source=wechat_session&from=groupmessage&isappinstalled=0

乱序执行可以简单的分为三个阶段

1. 获取指令，解码后存放到执行缓冲区Reservations Stations
2. 乱序执行指令，结果保存在一个结果序列中
3. 退休期Retired Circle，重新排列结果序列及安全检查（如地址访问的权限检查），提交结果到寄存器

#### CPU异常指令执行

https://www.freebuf.com/vuls/159269.html
CPU异常指令执行

![exception](figs/exception.png)

#### CPU数据访问权限和地址合法性检查

https://www.freebuf.com/vuls/159269.html
图3 CPU数据访问权限和地址合法性检查

![right-check](figs/right-check.png)

#### 熔断漏洞(CVE-2017-5754)：利用过程

https://meltdownattack.com/meltdown.pdf
Meltdown: Reading Kernel Memory from User Space

![meltdown-poc](figs/meltdown-poc.jpg)

 1. 接收者开辟一段2^8=256个page大小的内存(256*4096)作为probe array，并保证这部分内存未被缓存。
 2. 假设要访问的非法内存的地址存在rcx, 通过mov指令读取位于rcx地址的内存中的一个字节，存在rax中，这条指令将来会产生异常，然而在异常产生前，就可以通过transient instructions把读取的内容发送出去：
 3. 假设读取的值是i，那么就在transient instructions里面访问probe array的第i*4096个元素，这会导致第i*4096个元素被缓存。
 4. 接收者通过测量所有的256个page的内存的访问时间，就可以知道i的值了。

#### 熔断漏洞：原理
https://mp.weixin.qq.com/s/2FvvFUT8taRPv6GOHzNW-g
图4 漏洞原理图

![meltdown-method](figs/meltdown-method.jpg)

#### 熔断漏洞：在用户态读取内核数据

https://meltdownattack.com/meltdown.pdf
Meltdown: Reading Kernel Memory from User Space
Figure 4

![access-duration](figs/access-duration.png)

#### KPTI: Kernel page-table isolation
https://gruss.cc/files/kaiser.pdf
KASLR is Dead: Long Live KASLR
Fig. 2

![kaiser](figs/kaiser.png)

(a) The kernel is mapped into the address space of every user process.
(b) Theoretical concept of stronger kernel isolation. It splits the address spacesand  only  interrupt  handling  code  is  mapped  in  both  address  spaces. 
(c)  Forcompatibility with x86 Linux, KAISER relies on SMAP to prevent invalid usermemory references and SMEP to prevent execution of user code in kernel mode.

supervisor-mode access prevention (SMAP) and supervisor-mode execution prevention (SMEP)

#### Shadow address space in KAISER
https://gruss.cc/files/kaiser.pdf
KASLR is Dead: Long Live KASLR
Fig. 3: Shadow address space

Kernel Address Isolation to have Side channels Efficiently Removed, KAISER

![kaiser-shadow-AS](figs/kaiser-shadow-AS.png)

PML4 of user address space and kernel addressspace are placed next to each other in physical memory.

https://en.wikipedia.org/wiki/Kernel_page-table_isolation


#### “骑士” 漏洞（CVE-2019-11157）

http://voltjockey.com/flies/paper/2.pdf
VoltJockey: Breaking SGX by Software-ControlledVoltage-Induced Hardware Faults
Fig. 1.   Overview of our voltage-induced fault attack

![VoltJockey](figs/VoltJockey.png)

动态电源管理模块DVFS（Dynamic Voltage and Frequency Scaling）允许多核处理器根据负载信息采用相应的频率和电压运行，以降低处理器的功耗。
当一个核出现电压和频率不太匹配（如电压偏低无法满足较高频率运行需求）时，系统就会出现短暂“故障”。
故障对系统行为结果的干扰会泄露出的系统行为信息。

