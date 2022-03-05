---
marp: true
theme: default
paginate: true
_paginate: false
header: ''
footer: ''
---

<!-- theme: gaia -->
<!-- _class: lead -->

## 第二讲 实践与实验介绍
### 第四节 实践：LibOS


---
## 实践：LibOS
- **进化目标**
- 总体思路
- 历史背景
- 实践步骤
- 软件设计

---
## 实践：LibOS
### 进化目标
- 让应用与硬件隔离
- 简化应用访问硬件的难度和复杂性

![bg right 100%](figs/os-as-lib.png)


---
## 实践：LibOS
- 进化目标
- **总体思路**
- 历史背景
- 实践步骤
- 软件设计

---
## LibOS
### 总体思路
- 编译：通过设置编译器支持编译裸机程序
- 构造：建立裸机程序的栈和SBI服务请求接口
- 运行：OS的起始地址和执行环境初始化

![bg right 100%](figs/os-as-lib.png)



---
## 实践：LibOS
- 进化目标
- 总体思路
- **历史背景**
- 实践步骤
- 软件设计


---
## LibOS
### 历史
1949-1951 年，英国 J. Lyons and Co. 公司（连锁餐厅和食品制造集团公司）开创性地引入并使用剑桥大学的 EDSAC 计算机，联合设计实现了 LEO I ‘Lyons Electronic Office’ 软硬件系统


![bg right 70%](figs/LEO_III_computer_circuit_board.jpg)



---
## LibOS
### 历史
- 参与 EDSAC 项目的 David Wheeler 发明了子程序的概念 – Wheeler Jump 
- 在有了便捷有效的子程序概念和子程序调用机制后，软件开发人员在EDSAC和后续的LEO计算机上开发了大量的系统子程序库，形成了最早的操作系统原型。

![bg right 70%](figs/LEO_III_computer_circuit_board.jpg)


---
## 实践：LibOS
- 进化目标
- 总体思路
- 历史背景
- **实践步骤**
- 软件设计


---
## LibOS
### 实践步骤
- 建好开发与实验环境
- 移出标准库依赖
- **支持函数调用**
- 基于SBI服务完成输出与关机
supervisor-binary interface）

**深入理解运行程序的内存空间和栈**

![bg right 100%](figs/os-as-lib.png)

---
## LibOS
### 具体步骤
```
git clone https://github.com/rcore-os/rCore-Tutorial-v3.git
cd rCore-Tutorial-v3
git checkout ch1

cd os
make run
```

---
## LibOS
### 执行结果
```
[RustSBI output]
Hello, world!
.text [0x80200000, 0x80202000)
.rodata [0x80202000, 0x80203000)
.data [0x80203000, 0x80203000)
boot_stack [0x80203000, 0x80213000)
.bss [0x80213000, 0x80213000)
Panicked at src/main.rs:46 Shutdown machine!
```

除了显示 Hello, world! 之外还有一些额外的信息，最后关机。



---
## 实践：LibOS
- 进化目标
- 总体思路
- 历史背景
- 实践步骤
- **软件设计**



---
## 实践：LibOS
- **软件设计**
  - **代码结构**
  - App/OS内存布局
  - 定制内存布局
  - 生成内核二进制镜像
  - 基于 GDB 验证启动流程
  - 支持函数调用
  - 支持SBI调用
---
## LibOS -- 代码结构
```
./os/src
Rust        4 Files   119 Lines
Assembly    1 Files    11 Lines

├── bootloader(内核依赖的运行在 M 特权级的 SBI 实现，本项目中我们使用 RustSBI)
│   ├── rustsbi-k210.bin(可运行在 k210 真实硬件平台上的预编译二进制版本)
│   └── rustsbi-qemu.bin(可运行在 qemu 虚拟机上的预编译二进制版本)
```



---
## LibOS -- 代码结构
```
├── os(我们的内核实现放在 os 目录下)
│   ├── Cargo.toml(内核实现的一些配置文件)
│   ├── Makefile
│   └── src(所有内核的源代码放在 os/src 目录下)
│       ├── console.rs(将打印字符的 SBI 接口进一步封装实现更加强大的格式化输出)
│       ├── entry.asm(设置内核执行环境的的一段汇编代码)
│       ├── lang_items.rs(需要我们提供给 Rust 编译器的一些语义项，目前包含内核 panic 时的处理逻辑)
│       ├── linker-qemu.ld(控制内核内存布局的链接脚本以使内核运行在 qemu 虚拟机上)
│       ├── main.rs(内核主函数)
│       └── sbi.rs(调用底层 SBI 实现提供的 SBI 接口)
```


<!-- https://blog.51cto.com/onebig/2551726
(深入理解计算机系统) bss段，data段、text段、堆(heap)和栈(stack) -->


---
## 实践：LibOS
- **软件设计**
  - 代码结构
  - **App/OS内存布局**
  - 定制内存布局
  - 生成内核二进制镜像
  - 基于 GDB 验证启动流程
  - 支持函数调用
  - 支持SBI调用
---
## LibOS -- App/OS内存布局
![w:900](figs/memlayout.png)

---
## LibOS -- App/OS内存布局

bss段：
- bss段（bss segment）通常是指用来存放程序中未初始化的全局变量的一块内存区域
- bss是英文Block Started by Symbol的简称
- bss段属于静态内存分配
![bg right 100%](figs/memlayout.png)


---
## LibOS -- App/OS内存布局

data段：
- 数据段（data segment）通常是指用来存放程序中已初始化的全局变量的一块内存区域
- 数据段属于静态内存分配
![bg right 100%](figs/memlayout.png)



---
## LibOS -- App/OS内存布局

text段：
- 代码段（code segment/text segment）是指存放执行代码的内存区域
- 这部分区域的大小确定，通常属于只读
- 在代码段中，也有可能包含一些只读的常数变量
![bg right 100%](figs/memlayout.png)



---
## LibOS -- App/OS内存布局

堆（heap）：
- 堆是用于动态分配的内存段，可动态扩张或缩减
- 程序调用malloc等函数新分配的内存被动态添加到堆上
- 调用free等函数释放的内存从堆中被剔除
![bg right 100%](figs/memlayout.png)


---
## LibOS -- App/OS内存布局

栈(stack)：
- 栈又称堆栈，是用户存放程序临时创建的局部变量
- 函数被调用时，其参数和函数的返回值也会放到栈中
- 由于栈的先进先出(FIFO)特点，所以栈特别方便用来保存/恢复当前执行状态



![bg right 100%](figs/memlayout.png)


---
## LibOS -- App/OS内存布局

栈(stack)：
从这个意义上讲，我们可以把堆栈看成一个寄存、交换临时数据的内存区

OS编程与应用编程的一个显著区别是，OS编程需要理解栈上的物理内存结构和机器级内容。

![bg right 100%](figs/memlayout.png)



---
## LibOS -- App/OS内存布局

Q： C语言与Rust语言中的 static 变量位于执行程序的哪个区域？

![bg right 100%](figs/memlayout.png)


---
## LibOS -- App/OS内存布局

Q： C语言与Rust语言中的 static 变量位于执行程序的哪个区域？
A： static变量算是一种全局变量，位于data段。 

![bg right 100%](figs/memlayout.png)



---
## 实践：LibOS
- **软件设计**
  - 代码结构
  - App/OS内存布局
  - **定制内存布局**
  - 生成内核二进制镜像
  - 基于 GDB 验证启动流程
  - 支持函数调用
  - 支持SBI调用
---
## LibOS -- 定制内存布局
```
# os/src/linker-qemu.ld
OUTPUT_ARCH(riscv)
ENTRY(_start)
BASE_ADDRESS = 0x80200000;

SECTIONS
{
    . = BASE_ADDRESS;
    skernel = .;

    stext = .;
    .text : {
      *(.text.entry)
```
![bg right 100%](figs/memlayout.png)

---
## LibOS -- 定制内存布局
```
    .bss : {
        *(.bss.stack)
        sbss = .;
        *(.bss .bss.*)
        *(.sbss .sbss.*)
```

BSS：Block Started by Symbol
SBSS：small bss，近数据


![bg right 100%](figs/memlayout.png)



---
## 实践：LibOS
- **软件设计**
  - 代码结构
  - App/OS内存布局
  - 定制内存布局
  - **生成内核二进制镜像**
  - 基于 GDB 验证启动流程
  - 支持函数调用
  - 支持SBI调用
---
## LibOS -- 生成内核二进制镜像

![w:900](figs/load-into-qemu.png)

---
## LibOS -- 生成内核二进制镜像
```
rust-objcopy --strip-all \
target/riscv64gc-unknown-none-elf/release/os \
-O binary target/riscv64gc-unknown-none-elf/release/os.bin
```


---
## 实践：LibOS
- **软件设计**
  - 代码结构
  - App/OS内存布局
  - 定制内存布局
  - 生成内核二进制镜像
  - **基于 GDB 验证启动流程**
  - 支持函数调用
  - 支持SBI调用
---
## LibOS -- 基于 GDB 验证启动流程
```
qemu-system-riscv64 \
    -machine virt \
    -nographic \
    -bios ../bootloader/rustsbi-qemu.bin \
    -device loader,file=target/riscv64gc-unknown-none-elf/release/os.bin,addr=0x80200000 \
    -s -S
```

```
riscv64-unknown-elf-gdb \
    -ex 'file target/riscv64gc-unknown-none-elf/release/os' \
    -ex 'set arch riscv:rv64' \
    -ex 'target remote localhost:1234'
[GDB output]
0x0000000000001000 in ?? ()
```


---
## 实践：LibOS
- **软件设计**
  - 代码结构
  - App/OS内存布局
  - 定制内存布局
  - 生成内核二进制镜像
  - 基于 GDB 验证启动流程
  - **支持函数调用**
  - 支持SBI调用
  
---
## LibOS -- 支持函数调用
![w:800](figs/function-call.png)

---
## LibOS -- 支持函数调用
![w:1000](figs/fun-call-in-rv.png)

伪指令 ret 翻译为 jalr x0, 0(x1)，含义为跳转到寄存器 ra 保存的物理地址，由于 x0 是一个恒为 0 的寄存器，在 rd 中保存这一步被省略。


---
## LibOS -- 支持函数调用
![w:1000](figs/fun-call-in-rv.png)

在进行函数调用的时候，通过 jalr 指令保存返回地址并实现跳转；而在函数即将返回的时候，则通过 ret 伪指令回到跳转之前的下一条指令继续执行。这样，RISC-V 这两条指令就实现了函数调用流程的核心机制。

---
## LibOS -- 支持函数调用
函数调用规范

函数调用规范 (Calling Convention) 约定在某个指令集架构上，某种编程语言的函数调用如何实现。它包括了以下内容：

- 函数的输入参数和返回值如何传递；
- 函数调用上下文中调用者/被调用者保存寄存器的划分；
- 其他的在函数调用流程中对于寄存器的使用方法。

---
## LibOS -- 支持函数调用
RISC-V函数调用规范
![w:1200](figs/rv-call-regs.png)


---
## LibOS -- 支持函数调用
RISC-V函数调用规范
![w:800](figs/call-stack.png)

---
## LibOS -- 支持函数调用
RISC-V函数调用规范
![w:900](figs/stack-frame.png)


---
## LibOS -- 支持函数调用

它的开头和结尾分别在 sp(x2) 和 fp(s0) 所指向的地址。按照地址从高到低分别有以下内容，它们都是通过 sp 加上一个偏移量来访问的：
- ra 寄存器保存其返回之后的跳转地址，是一个调用者保存寄存器；
- 父亲栈帧的结束地址 fp ，是一个被调用者保存寄存器；
- 其他被调用者保存寄存器 s1 ~ s11 ；
- 函数所使用到的局部变量。

---
## LibOS -- 支持函数调用

分配并使用启动栈
```
# os/src/entry.asm
    .section .text.entry
    .globl _start
_start:
    la sp, boot_stack_top
    call rust_main

    .section .bss.stack
    .globl boot_stack
boot_stack:
    .space 4096 * 16
    .globl boot_stack_top
boot_stack_top:
```

---
## LibOS -- 支持函数调用

分配并使用启动栈
```
# os/src/linker-qemu.ld
.bss : {
    *(.bss.stack)
    sbss = .;
    *(.bss .bss.*)
    *(.sbss .sbss.*)
}
ebss = .;
```
在链接脚本 linker.ld 中 .bss.stack 段最终会被汇集到 .bss 段中
.bss 段一般放置需要被初始化为零的数据


---
## LibOS -- 支持函数调用

将控制权转交给 Rust 代码，该入口点在 main.rs 中的``rust_main``函数
```rust
// os/src/main.rs  
pub fn rust_main() -> ! {
    loop {}
}
```
- ``fn`` 关键字：函数； ``pub`` 关键字：对外可见，公共的
- ``loop`` 关键字：循环  



---
## LibOS -- 支持函数调用

清空bss段
```Rust
pub fn rust_main() -> ! {
    clear_bss(); //调用清空bss的函数clear_bss()
}
fn clear_bss() {
    extern "C" {
        fn sbss(); //bss段的起始地址
        fn ebss(); //bss段的结束地址
    }
    //对[sbss..ebss]这段内存空间清零
    (sbss as usize..ebss as usize).for_each(|a| {
        unsafe { (a as *mut u8).write_volatile(0) }
    });
}
```


---
## 实践：LibOS
- **软件设计**
  - 代码结构
  - App/OS内存布局
  - 定制内存布局
  - 生成内核二进制镜像
  - 基于 GDB 验证启动流程
  - 支持函数调用
  - **支持SBI调用**
---
## LibOS -- 支持SBI调用
在屏幕上打印 Hello world! 

### RustSBI
- 提供基本的底层服务
- 需要遵循SBI调用约定

---
## LibOS -- 支持SBI调用
RustSBI服务
```rust
// os/src/sbi.rs
const SBI_SET_TIMER: usize = 0;
const SBI_CONSOLE_PUTCHAR: usize = 1;
const SBI_CONSOLE_GETCHAR: usize = 2;
const SBI_CLEAR_IPI: usize = 3;
const SBI_SEND_IPI: usize = 4;
const SBI_REMOTE_FENCE_I: usize = 5;
const SBI_REMOTE_SFENCE_VMA: usize = 6;
const SBI_REMOTE_SFENCE_VMA_ASID: usize = 7;
const SBI_SHUTDOWN: usize = 8;
```
- ``usize`` 机器字大小的无符号整型
---
## LibOS -- 支持SBI调用

```rust
// os/src/sbi.rs
#[inline(always)] //总是把函数展开
fn sbi_call(which: usize, arg0: usize, arg1: usize, arg2: usize) -> usize {
    let mut ret; //可修改的变量ret
    unsafe {
        asm!(//内嵌汇编
            "ecall", //切换到更高特权级的机器指令
            inlateout("x10") arg0 => ret, //SBI参数0&返回值
            in("x11") arg1,  //SBI参数1
            in("x12") arg2,  //SBI参数2
            in("x17") which, //SBI编号
        );
    }
    ret //返回ret值
}
```
---
## LibOS -- 支持SBI调用
在屏幕上输出一个字符
```rust
// os/src/sbi.rs
pub fn console_putchar(c: usize) {
    sbi_call(SBI_CONSOLE_PUTCHAR, c, 0, 0);
}
```
#### 实现格式化输出
- 编写基于 console_putchar 的 println! 宏

---
## LibOS -- 支持SBI调用
关机
```rust
// os/src/sbi.rs
pub fn shutdown() -> ! {
    sbi_call(SBI_SHUTDOWN, 0, 0, 0);
    panic!("It should shutdown!");
}
```
- ``panic!``和``println!``是一个宏（类似C的宏），``!``是宏的标志
---
## LibOS -- 支持SBI调用
优雅地处理错误panic
```rust
#[panic_handler]
fn panic(info: &PanicInfo) -> ! { //PnaicInfo是结构类型
    if let Some(location) = info.location() { //出错位置存在否？
        println!(
            "Panicked at {}:{} {}",
            location.file(), //出错的文件名
            location.line(), //出错的文件中的行数
            info.message().unwrap() //出错信息
        );
    } else {
        println!("Panicked: {}", info.message().unwrap());
    }
    shutdown() //关机
}
```

---
## LibOS -- 支持SBI调用
优雅地处理错误panic
```rust
pub fn rust_main() -> ! {
    clear_bss();
    println!("Hello, world!");
    panic!("Shutdown machine!");
}
```
运行结果
```
[RustSBI output]
Hello, world!
Panicked at src/main.rs:26 Shutdown machine!
```
