# 第七讲 虚拟存储：局部页面置换算法

## 第1节 页面置换算法的概念

## 第2节 最优/最近/最坏/先进先出/最近最久未使用 算法

## 第3节 时钟置换算法和最不常用算法

## 第4节 Belady现象和局部置换算法比较

## 第5节 页表自映射

### ref
http://os.cs.tsinghua.edu.cn/oscourse/OS2019spring/lecture09
http://os.cs.tsinghua.edu.cn/oscourse/OS2013/lecture05
20130326-lecture05-mm-instance.pptx
页表自映射

http://inst.eecs.berkeley.edu/~cs61c/resources/su18_lec/Lecture7.pdf
RISC-V Instruction Formats

https://cseweb.ucsd.edu/classes/wi14/cse141/pdf/08/12_CSE141-MBT-Virtual-Memory.ppt.pdf
Virtual Memory 

#### 自映射改成线性映射
https://github.com/oscourse-tsinghua/rcore_plus/pull/50
这个PR记录了从自映射改成线性映射的过程
我感觉你的这个问题，主要来自rust写页表的事。对吗？

我感觉你的这个问题，主要来自rust写页表的不方便。对吗？是的。
是语言的原因？感觉不是，C语言写也会不方便

具体到页表操作，riscv crate同时保留了两种实现
https://github.com/rcore-os/riscv/tree/master/src/paging

multi_level.rs：线性映射
recursive.rs：自映射

在xy-plus/rcore-step-by-step里也有自映射的页表。。。
https://github.com/xy-plus/rcore_step_by_step_old
https://github.com/LearningOS/rcore_step_by_step
https://github.com/LearningOS/rcore_step_by_step/tree/master/os/crate/riscv/src/paging

似乎可以在这个commit里面找到
https://github.com/LearningOS/rcore_step_by_step_old2/tree/f6e9d1603d0949dd2187e873ec38307e7d3c1f56

#### rCore代码分析

/Users/xyong/github/rCore/crate/memory/src/paging/mock_page_table.rs
pub struct MockEntry

/Users/xyong/github/rCore/docs/2_OSLab/os2atc/ucore_os_in_rust.md
内存模块——接口的Mock实现
实现一个仿真页表，模拟地址转换的过程，从数组中存取数据。

/Users/xyong/github/rCore/kernel/src/arch/riscv/paging.rs
PageTable
impl PageTable for PageTableImpl

Line 15:
target_arch = "riscv32"
type TopLevelPageTable<'a> = riscv::paging::Rv32PageTable<'a>;

/Users/xyong/github/rCore/kernel/src/arch/riscv/paging.rs
Line 285:
impl FrameAllocator for FrameAllocatorForRiscv

Line 30:
pub struct PageEntry

/Users/xyong/github/rCore/docs/1_OS/RISCV.md
set_recursive

READONLY_SHARED
contains
RESERVED2
RESERVED1

/Users/xyong/github/rCore/kernel/src/arch/aarch64/interrupt/context.rs
pub struct TrapFrame

/Users/xyong/github/rCore/crate/memory/src/paging/mod.rs
pub trait PageTable

/Users/xyong/github/rCore/kernel/src/arch/riscv/paging.rs
impl PageTable for PageTableImpl

use riscv::paging::{
    Mapper, PageTable as RvPageTable, PageTableEntry, PageTableFlags as EF, PageTableType,
    RecursivePageTable,
};

https://github.com/equation314/aarch64/blob/master/src/paging/page_table.rs
struct PageTableFlags

#### RecursivePageTable

/Users/xyong/github/rCore/kernel/src/arch/riscv/paging.rs
Line 50:
fn get_entry(&mut self, vaddr: usize) -> Option<&mut dyn Entry>

https://github.com/rcore-os/riscv
/Users/xyong/github/riscv/src/addr.rs
Line 252:
pub fn of_ppn(ppn: usize) -> Self

/Users/xyong/github/riscv/src/addr.rs
Line 72:
pub fn from_page_table_indices(p2_index: usize, p1_index: usize, offset: usize) -> Self

/Users/xyong/github/riscv/src/addr.rs
Line 235:
pub fn from_page_table_indices(p2_index: usize, p1_index: usize) -> Self

/Users/xyong/github/riscv/src/addr.rs
Line 4:
pub struct VirtAddr(usize)

Line 111:
pub struct PhysAddr(usize)

Line 41:
pub fn p2_index(&self) -> usize

Line 46:
pub fn p1_index(&self) -> usize

/Users/xyong/github/riscv/src/paging/recursive.rs
Line 174:
pub struct RecursivePageTable

#### PageEntry
/Users/xyong/github/rCore/kernel/src/arch/riscv/paging.rs
Line 74:
impl Entry for PageEntry 
Line 107:
fn set_target(&mut self, target: usize)

#### rust的代码引用

/Users/xyong/github/rCore/kernel/src/arch/riscv/paging.rs
self.0.flags().contains(EF::DIRTY)
use crate::arch::interrupt::TrapFrame;

https://docs.rs/riscv/0.5.4/riscv/register/index.html

https://docs.rs/crate/riscv/0.5.4/source/src/register/scause.rs

/Users/xyong/github/rCore/kernel/src/arch/riscv/consts.rs
pub const KERNEL_OFFSET

https://doc.rust-lang.org/rust-by-example/mod/super.html

#### bitflags

https://docs.rs/bitflags/1.2.1/bitflags/

https://github.com/rcore-os/riscv/blob/master/src/paging/page_table.rs#L101
pub struct PageTableFlags
const RESERVED2

riscv32
dirty
sw_dirty
riscv::paging::Rv32PageTable

https://github.com/rcore-os/riscv/blob/master/src/paging/multi_level.rs
Line 8:
pub struct Rv32PageTable

#### 自映射页表的初始化
/Users/xyong/github/riscv/src/paging/recursive.rs
Line 200:
impl<'a> Mapper for RecursivePageTable<'a>
Line 210:
pub fn new(table: &'a mut PageTable) -> Result<Self, NotRecursivelyMapped>

RecursivePageTable

rec_idx

recursive_index

/Users/xyong/github/rCore/docs/1_OS/RISCV.md

```rust
fn set_recursive(self: &mut PageTable, recursive_index: usize, frame: Frame)
```

我正在RecursivePageTable的代码，没有找到set_recursive()是在什么时候执行的？recursive_index的取值是多少？ @王润基 @More than xkcd #378 谁知道？

https://github.com/LearningOS/rcore_step_by_step_old/blob/master/xy_os/riscv-pk/bbl/bbl.c#L49

static void setup_page_table_sv32

这一部分初始化的代码并没有使用set_recursive，而是用C搞的。

### 页表自映射

#### 基于4KB页面的32位CPU二级页表

https://cseweb.ucsd.edu/classes/wi14/cse141/pdf/08/12_CSE141-MBT-Virtual-Memory.ppt.pdf

Page 8:

![2-level-pagetable](figs/2-level-pagetable.png)

#### 地址转换的计算过程

20130326-lecture05-mm-instance.pptx
Page 10

计算过程图

![addr-translation](figs/addr-translation.png)

#### 页表自映射机制

![self-mapping-PTE](figs/self-mapping-PTE.png)

### X86-32页表自映射

#### 基于4KB页面的X86-32二级页表

20130326-lecture05-mm-instance.pptx
Page 9

地址转换和二级页表的

![x86-32-addr-translation](figs/x86-32-addr-translation.png)

#### X86-32页表项结构

Ref: 20130326-lecture05-mm-instance.pptx
Page 17

![x86-32-page-tabel-entry](figs/x86-32-page-tabel-entry.png)


#### 用C语言宏表示的地址转换计算过程

20130326-lecture05-mm-instance.pptx
Page 11

```c
// page directory index
#define PDX(la) ((((uintptr_t)(la)) >> PDXSHIFT) & 0x3FF)
// page table index
#define PTX(la) ((((uintptr_t)(la)) >> PTXSHIFT) & 0x3FF)
// page number field of address
#define PPN(la) (((uintptr_t)(la)) >> PTXSHIFT)
// offset in page
#define PGOFF(la) (((uintptr_t)(la)) & 0xFFF)
```



#### X86-32的第一级页表的自映射
20130326-lecture05-mm-instance.pptx
Page 23

![1-level-self-mapping-pt](figs/1-level-self-mapping-pt.png)

#### X86-32的第二级页表的自映射
20130326-lecture05-mm-instance.pptx
Page 24

![2-level-self-mapping-pt](figs/2-level-self-mapping-pt.png)

#### X86-32自映射页表项初始化
```C
// recursively insert boot_pgdir in itself
// to form a virtual pate table at virtual address VPT
boot_pgdir[PDX(VPT)] = PADDR(boot_pgdir) | PTE_P | PTE_W;
```
### riscv32页表自映射

#### RISC-V Sv32的二级页表

https://learningos.github.io/rcore_step_by_step_webdoc/docs/%E9%A1%B5%E8%A1%A8%E7%AE%80%E4%BB%8B.html
图

![riscv32-pagetable](figs/riscv32-pagetable.png)

#### RISC-V32页表项结构

Ref: https://learningos.github.io/rcore_step_by_step_webdoc/docs/页表简介.html
riscv-privileged-20190608-1.pdf
Page 80:
Figure 4.15: Sv32 page table entry

![riscv32-page-entry](figs/riscv32-page-entry.png)

riscv-privileged-20190608-1.pdf
Table 4.4: Encoding of PTE R/W/X fields.

![PTE-RWX-fields](figs/PTE-RWX-fields.png)



#### rCore中riscv32的自映射

/Users/xyong/github/rCore/docs/1_OS/RISCV.md

![riscv32-self-mapping](figs/riscv32-self-mapping.png)

RISCV页表项中的flags，明确表示它指向的是数据页（VRW），还是下层页表（V）。
在访问一级页表虚地址期间，将它所对应的二级页表项flags置为VRW。
访问二级页表本身，还需要再加一个自映射的二级页表项，其flags为VRW。
