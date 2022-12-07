---
marp: true
theme: default
paginate: true
_paginate: false
header: ''
footer: ''
backgroundColor: white
---

<!-- theme: gaia -->
<!-- _class: lead -->

# 第三讲 基于特权级的隔离与批处理
## 第三节 实践：批处理操作系统

<br>
<br>

向勇 陈渝 李国良 

<br>
<br>

2022年秋季

---
**提纲**

### 1. 实验目标
2. 实践步骤
3. 软件架构
4. 相关硬件
5. 应用程序设计
6. 内核程序设计

---

#### 批处理操作系统的结构
![w:750](figs/batch-os-detail.png)

  <!-- - 构造&加载 OS&APP
  - 基于RV特权级机制保护OS
  - 系统调用支持
  - 特权级切换  -->


---
#### 批处理OS目标
- 让APP与OS隔离
- 自动加载并运行多个程序
  - **批处理（batch）**

LibOS目标
- 让应用与硬件隔离
- 简化应用访问硬件的难度和复杂性
  
![bg right:54% 95%](figs/batch-os.png)

---
#### 实验要求
- 理解运行其他软件的软件
- 理解特权级和特权级切换
- 理解系统调用
- 会写``邓式鱼``批处理操作系统

邓式鱼：Dunkleosteus 在泥盆纪有坚固盾甲的海洋霸主  
![bg right:52% 90%](figs/dunkleosteus.png)

---
#### 总体思路
- 编译：应用程序和内核**独立编译**，合并为一个镜像
- 构造：系统调用服务请求接口，应用的**管理与初始化**
- 运行：OS一个一个地**执行应用**
- 运行：应用发出**系统调用**请求，OS完成系统调用
- 运行：应用与OS基于硬件特权级机制进行**特权级切换**



---
#### 历史背景
- GM-NAA I/O System(1956)
  - 启发：汽车生产线 
- MULTICS OS(1969,MIT/GE/AT&T)
  - GE 645 具有 8 级硬件支持的保护环
 GM-NAA: General Motors and North American Aviation;
 GE： General Electric
![bg right:38% 95%](figs/deng-fish.png)



---
**提纲**

1. 实验目标
### 2. 实践步骤
3. 软件架构
4. 相关硬件
5. 应用程序设计
6. 内核程序设计

---

#### 步骤
- 构造包含OS和多个APP的**单一执行镜像**
- 通过批处理支持多个**APP的自动加载和运行**
- 利用硬件特权级机制实现对操作系统自身的**保护**
- 支持跨特权级的**系统调用** 
- 实现特权级的**穿越**

![bg right:54% 100%](figs/batch-os.png)




---
#### 编译步骤
```
git clone https://github.com/rcore-os/rCore-Tutorial-v3.git
cd rCore-Tutorial-v3
git checkout ch2

cd os
make run
```

---
#### 参考运行结果
```
...
[kernel] num_app = 5
[kernel] app_0 [0x8020a038, 0x8020af90)
...
[kernel] Loading app_0
Hello, world!
[kernel] Application exited with code 0
[kernel] Loading app_1
...
[kernel] Panicked at src/batch.rs:58 All applications completed!
```


---
**提纲**

1. 实验目标
2. 实践步骤
### 3. 软件架构
4. 相关硬件
5. 应用程序设计
6. 内核程序设计

---

#### 构建应用
把多个应用合在一起与OS形成一个二进制镜像
```
├── os
│   ├── build.rs(新增：生成 link_app.S 将应用作为一个数据段链接到内核)
│   ├── Cargo.toml
│   ├── Makefile(修改：构建内核之前先构建应用)
│   └── src
│       ├── link_app.S(构建产物，由 os/build.rs 输出)
```


---
#### 改进OS
加载和执行程序、特权级上下文切换
```
├── os
│   └── src
│       ├── batch.rs(新增：实现了一个简单的批处理系统)
│       ├── main.rs(修改：主函数中需要初始化 Trap 处理并加载和执行应用)

│       └── trap(新增：Trap 相关子模块 trap)
│           ├── context.rs(包含 Trap 上下文 TrapContext)
│           ├── mod.rs(包含 Trap 处理入口 trap_handler)
│           └── trap.S(包含 Trap 上下文保存与恢复的汇编代码)
```

---
#### 系统调用

```
├── os
│   └── src
│       ├── syscall(新增：系统调用子模块 syscall)
│       │   ├── fs.rs(包含文件 I/O 相关的 syscall)
│       │   ├── mod.rs(提供 syscall 方法根据 syscall ID 进行分发处理)
│       │   └── process.rs(包含任务处理相关的 syscall)
```

---
#### 添加应用
批处理OS会按照文件名开头的数字顺序依次加载并运行它们
```
└── user(新增：应用测例保存在 user 目录下)
   └── src
      ├── bin(基于用户库 user_lib 开发的应用，每个应用放在一个源文件中)
      │   ├── 00hello_world.rs # 显示字符串的应用
      │   ├── 01store_fault.rs # 非法写操作的应用
      │   ├── 02power.rs       # 计算/IO频繁交替的应用 
      │   ├── 03priv_inst.rs   # 执行特权指令的应用
      │   └── 04priv_csr.rs    # 执行CSR操作指令的应用
```            
---
#### 应用库和编译应用支持
应用库和编译应用支持
```
└── user(新增：应用测例保存在 user 目录下)
   └── src
      ├── console.rs              # 支持println!的相关函数与宏
      ├── lang_items.rs           # 实现panic_handler函数
      ├── lib.rs(用户库 user_lib)  # 应用调用函数的底层支撑库 
      ├── linker.ld               # 应用的链接脚本
      └── syscall.rs(包含 syscall 方法生成实际用于系统调用的汇编指令，
                     各个具体的 syscall 都是通过 syscall 来实现的)
```


---
**提纲**

1. 实验目标
2. 实践步骤
3. 软件架构
### 4. 相关硬件
5. 应用程序设计
6. 内核程序设计

---

#### RISC-V陷入(trap)类指令

- ecall： 随着 CPU 当前特权级而触发不同的陷入异常
- ebreak：触发断点陷入异常

**RISC-V特权指令**

- sret： 随着 CPU 当前特权级而触发不同的陷入异常
  
![bg right:51% 120%](figs/EnvironmentCallFlow.png)


---

#### RISC-V异常向量

| Interrupt | Exception Code | Description                    |
| --------- | -------------- | ------------------------------ |
| 0         | 0              | Instruction address misaligned |
| 0         | 1              | Instruction access fault       |
| 0         | 2              | Illegal instruction            |
| 0         | 3              | **Breakpoint**                     |
| 0         | 4              | Load address misaligned        |
| 0         | 5              | Load access fault              |


            
---
#### RISC-V异常向量

| Interrupt | Exception Code | Description                    |
| --------- | -------------- | ------------------------------ |
| 0         | 6              | Store/AMO address misaligned   |
| 0         | 7              | Store/AMO access fault         |
| 0         | 8              | **Environment call from U-mode**   |
| 0         | 9              | Environment call from S-mode   |
| 0         | 11             | Environment call from M-mode   |

            
---
#### RISC-V异常向量

| Interrupt | Exception Code | Description                    |
| --------- | -------------- | ------------------------------ |
| 0         | 12             | Instruction page fault         |
| 0         | 13             | Load page fault                |
| 0         | 15             | Store/AMO page fault           |


- AMO: atomic memory operation 

---
**提纲**

1. 实验目标
2. 实践步骤
... ...
### 5. 应用程序设计
- 项目结构
- 内存布局
- 系统调用  
6. 内核程序设计

---

#### 应用与底层支撑库分离

```
└── user(应用程序和底层支撑库)
   └── src
      ├── bin(该目录放置基于用户库 user_lib 开发的应用)   
      ├── lib.rs(用户库 user_lib)  # 库函数的底层支撑库 
      ├── ......                  # 支撑库相关文件
      └── linker.ld               # 应用的链接脚本
```

---
#### 引入外部库
``` rust
  #[macro_use]
  extern crate user_lib;
```

---
#### 设计支撑库

在 lib.rs 中我们定义了用户库的入口点 _start ：
``` rust
#[no_mangle]
#[link_section = ".text.entry"]
pub extern "C" fn _start() -> ! {
    clear_bss();
    exit(main());
    panic!("unreachable after sys_exit!");
}
```


---
**提纲**

1. 实验目标

... ...

5. 应用程序设计
- 项目结构
### 内存布局
- 系统调用  
6. 内核程序设计

---

#### 应用程序的内存布局

![bg 70%](figs/memlayout.png)

---

#### 设计支撑库
`user/src/linker.ld`

- 将程序的起始物理地址调整为 0x80400000 ，应用程序都会被加载到这个物理地址上运行；
- 将 _start 所在的 .text.entry 放在整个程序的开头，也就是说批处理系统只要在加载之后跳转到 0x80400000 就已经进入了 用户库的入口点，并会在初始化之后跳转到应用程序主逻辑；
- 提供了最终生成可执行文件的 .bss 段的起始和终止地址，方便 clear_bss 函数使用。

其余的部分与之前相同


---
**提纲**

1. 实验目标

... ...

5. 应用程序设计
- 项目结构
- 内存布局
### 系统调用  
6. 内核程序设计

---

#### 应用程序的系统调用执行流

![w:1050](figs/EnvironmentCallFlow.png)

---

#### 应用程序的系统调用执行流

- 在子模块 syscall 中，应用程序通过 ecall 调用批处理系统提供的接口
- ``ecall`` 指令会触发 名为 Environment call from U-mode 的异常
- Trap 进入 S 模式执行批处理系统针对这个异常特别提供的服务代码
- a0~a6 保存系统调用的参数， a0 保存返回值, a7 用来传递 syscall ID
---
#### 系统调用支撑库
``` rust --
/// 功能：将内存中缓冲区中的数据写入文件。
/// 参数：`fd` 表示待写入文件的文件描述符；
///      `buf` 表示内存中缓冲区的起始地址；
///      `len` 表示内存中缓冲区的长度。
/// 返回值：返回成功写入的长度。
/// syscall ID：64
fn sys_write(fd: usize, buf: *const u8, len: usize) -> isize;

/// 功能：退出应用程序并将返回值告知批处理系统。
/// 参数：`xstate` 表示应用程序的返回值。
/// 返回值：该系统调用不应该返回。
/// syscall ID：93
fn sys_exit(xstate: usize) -> !;
```


---
#### 系统调用参数传递

``` rust
fn syscall(id: usize, args: [usize; 3]) -> isize {
    let mut ret: isize;
    unsafe {
        asm!(
            "ecall",
            inlateout("x10") args[0] => ret, //第一个参数&返回值
            in("x11") args[1],               //第二个参数
            in("x12") args[2],               //第三个参数
            in("x17") id                     //syscall编号
        );
    }
    ret //返回值
}
```


---
#### 系统调用封装
```rust
const SYSCALL_WRITE: usize = 64; 
const SYSCALL_EXIT: usize = 93;
//对系统调用的封装
pub fn sys_write(fd: usize, buffer: &[u8]) -> isize {
    syscall(SYSCALL_WRITE, [fd, buffer.as_ptr() as usize, buffer.len()])
}
pub fn sys_exit(xstate: i32) -> isize {
    syscall(SYSCALL_EXIT, [xstate as usize, 0, 0])
}
```

---
#### 系统调用封装
``` rust
pub fn write(fd: usize, buf: &[u8]) -> isize { sys_write(fd, buf) }

const STDOUT: usize = 1;

impl Write for Stdout {
    fn write_str(&mut self, s: &str) -> fmt::Result {
        write(STDOUT, s.as_bytes());
        Ok(())
    }
}
```


---
**提纲**

... ...

5. 应用程序设计
### 6. 内核程序设计
- 应用管理和加载
- 特权级切换
- Trap上下文
- Trap处理流程
- 执行应用程序

---

#### 将应用程序映像链接到内核
```
# os/src/link_app.S 由脚本 os/build.rs 生成
    .section .data
    .global _num_app
_num_app:
    .quad 5
    .quad app_0_start
    ...
    .quad app_4_end
    .section .data
    .global app_0_start
    .global app_0_end
app_0_start:
    .incbin "../user/target/riscv64gc-unknown-none-elf/release/00hello_world.bin"
app_0_end:
```


---
#### 应用程序管理数据结构

```rust
// os/src/batch.rs

struct AppManager {
    num_app: usize,
    current_app: usize,
    app_start: [usize; MAX_APP_NUM + 1],
}
```


---
#### 找到应用程序二进制码
- 找到 link_app.S 中提供的符号 _num_app
``` rust
lazy_static! {
    static ref APP_MANAGER: UPSafeCell<AppManager> = unsafe { UPSafeCell::new({
        extern "C" { fn _num_app(); }
        let num_app_ptr = _num_app as usize as *const usize;
        ...
        app_start[..=num_app].copy_from_slice(app_start_raw);
        AppManager {
            num_app,
            current_app: 0,
            app_start,
        }        
```

---

#### 加载应用程序二进制码
```rust
unsafe fn load_app(&self, app_id: usize) {
    // clear icache
    asm!("fence.i");
    // clear app area
    ...
    let app_src = core::slice::from_raw_parts(
        self.app_start[app_id] as *const u8,
        self.app_start[app_id + 1] - self.app_start[app_id] );
    let app_dst = core::slice::from_raw_parts_mut(
        APP_BASE_ADDRESS as *mut u8,
        app_src.len() );
    app_dst.copy_from_slice(app_src);
}
```


---
#### 加载应用程序二进制码

- fence.i ：用来清理 i-cache

注:``fence.i``是i-cache屏障(barrier)指令，非特权指令，属于 “Zifencei”扩展规范

**WHY？**

---
#### 加载应用程序二进制码

- fence.i ：用来清理 i-cache

- CPU 对物理内存所做的缓存又分成d-cache和i-cache
- OS将修改会被 CPU 取指的内存区域，这会使得 i-cache 中含有与内存中不一致的内容
- OS在这里必须使用 fence.i 指令手动清空 i-cache ，让里面所有的内容全部失效，才能够保证CPU访问内存数据和代码的正确性。



---
**提纲**

... ...

5. 应用程序设计
6. 内核程序设计
- 应用管理和加载
### 特权级切换
- Trap上下文
- Trap处理流程
- 执行应用程序

---

#### 特权级切换相关CSR
| CSR 名  | 该 CSR 与 Trap 相关的功能                                    |
| ------- | ------------------------------------------------------------ |
| sstatus | `SPP` 等字段给出 Trap 发生之前 CPU 的特权级（S/U）等 |
| sepc    | 记录 Trap 发生之前执行的最后一条指令的地址 |
| scause  | 描述 Trap 的原因      |
| stval   | 给出 Trap 附加信息      |
| stvec   | 控制 Trap 处理代码的入口地址     |

---
#### 特权级切换后的硬件逻辑

1. sstatus 的 SPP 字段会被修改为 CPU 当前的特权级（U/S）；
2. sepc 会被修改为 Trap 处理完成后默认会执行的下一条指令的地址；
3. scause/stval 分别会被修改成这次 Trap 的原因以及相关的附加信息；
4. CPU 将当前特权级设为 S，跳到 stvec 所设置的 Trap 处理入口地址。



---
#### 特权级切换与用户栈和内核栈
Why 使用两个不同的栈？

安全 安全 安全

``` rust
const USER_STACK_SIZE: usize = 4096 * 2;
const KERNEL_STACK_SIZE: usize = 4096 * 2;

static KERNEL_STACK: KernelStack = KernelStack { data: [0; KERNEL_STACK_SIZE] };
static USER_STACK: UserStack = UserStack { data: [0; USER_STACK_SIZE] };
```

---
#### 特权级切换中的换栈
``` rust
impl UserStack {
    fn get_sp(&self) -> usize {
        self.data.as_ptr() as usize + USER_STACK_SIZE
    }
}
RegSP = USER_STACK.get_sp();
RegSP = KERNEL_STACK.get_sp();
```


---
**提纲**

... ...

5. 应用程序设计
6. 内核程序设计
- 应用管理和加载
- 特权级切换
### Trap上下文
- Trap处理流程
- 执行应用程序

---

#### Trap上下文数据结构
``` rust
#[repr(C)]
pub struct TrapContext {
    pub x: [usize; 32],
    pub sstatus: Sstatus,
    pub sepc: usize,
}
```
- 对于通用寄存器而言，应用程序/内核控制流运行在不同的特权级
- 进入 Trap 的时候，硬件会立即覆盖掉 scause/stval/sstatus/sepc


---
#### 特权级切换后的Trap入口点
```rust
pub fn init() {
    extern "C" { fn __alltraps(); }
    unsafe {
        stvec::write(__alltraps as usize, TrapMode::Direct);
    }
}
```


---
#### 系统调用过程中的Trap上下文处理
1. 应用程序通过 ecall 进入到内核状态时，操作系统保存被打断的应用程序的 Trap 上下文；

![bg right:40% 100%](figs/kernel-stack.png)


---
#### 系统调用过程中的Trap上下文处理

2. 操作系统根据Trap相关的CSR寄存器内容，完成系统调用服务的分发与处理；

![bg right:40% 100%](figs/kernel-stack.png)


---
#### 系统调用过程中的Trap上下文处理

3. 操作系统完成系统调用服务后，需要恢复被打断的应用程序的Trap 上下文，并通 ``sret``指令让应用程序继续执行。
![bg right:40% 100%](figs/kernel-stack.png)
---

#### 用户栈到内核栈的切换
**sscratch CSR** 重要的中转寄存器

在特权级切换的时候，我们需要将 Trap 上下文保存在内核栈上，因此需要一个寄存器暂存内核栈地址，并以它作为基地址指针来依次保存 Trap 上下文的内容。

但是所有的通用寄存器都不能够用作基地址指针，因为它们都需要被保存，如果覆盖掉它们，就会影响后续应用控制流的执行。

---
#### 用户栈到内核栈的切换

**sscratch CSR** 重要的中转寄存器

- 暂时保存内核栈的地址
- 作为一个中转站让 sp （目前指向的用户栈的地址）的值可以暂时保存在 sscratch
- 仅需一条 `csrrw  sp, sscratch, sp // 交换对 sp 和 sscratch 两个寄存器内容`
- 完成用户栈-->内核栈的切换

---

#### 保存Trap上下文中的通用寄存器

保存通用寄存器的宏
```
# os/src/trap/trap.S
.macro SAVE_GP n
    sd x\n, \n*8(sp)
.endm
```

---
**提纲**

... ...

5. 应用程序设计
6. 内核程序设计
- 应用管理和加载
- 特权级切换
- Trap上下文
### Trap处理流程
- 执行应用程序

---

#### Trap处理流程


Trap 处理的总体流程如下：
1. 首先通过 __alltraps 将 Trap 上下文保存在内核栈上;
2. 然后跳转到 trap_handler 函数完成 Trap 分发及处理。
```
__alltraps:
    csrrw sp, sscratch, sp
    # now sp->kernel stack, sscratch->user stack

    # allocate a TrapContext on kernel stack
    addi sp, sp, -34*8    
```



---
#### 保存Trap上下文
保存通用寄存器
```
    # save general-purpose registers
    sd x1, 1*8(sp)
    # skip sp(x2), we will save it later
    sd x3, 3*8(sp)
    # skip tp(x4), application does not use it
    # save x5~x31
    .set n, 5
    .rept 27
        SAVE_GP %n
        .set n, n+1
    .endr
```


---
#### 保存Trap上下文
保存 sstatus 和 sepc 
```
    # we can use t0/t1/t2 freely, because they were saved on kernel stack
    csrr t0, sstatus
    csrr t1, sepc
    sd t0, 32*8(sp)
    sd t1, 33*8(sp)
```

---
#### 保存Trap上下文
保存 user SP
```
    # read user stack from sscratch and save it on the kernel stack
    csrr t2, sscratch
    sd t2, 2*8(sp)
```
``` rust
pub struct TrapContext {
    pub x: [usize; 32],
    pub sstatus: Sstatus,
    pub sepc: usize,
}
```
---
#### 调用trap_handler
```
    # set input argument of trap_handler(cx: &mut TrapContext)
    mv a0, sp
    call trap_handler
```
让寄存器 a0 指向内核栈的栈指针也就是我们刚刚保存的 Trap 上下文的地址，这是由于我们接下来要调用 trap_handler 进行 Trap 处理，它的第一个参数 cx 由调用规范要从 a0 中获取。


---
#### 恢复Trap上下文
1. 大部分是保存寄存器的反向操作；
2. 最后一步是 ``sret``指令 //从内核态返回到用户态

注：后面讲解“执行程序”时会比较详细的讲解"恢复Trap上下文"


---
#### trap_handler处理syscall

```rust
#[no_mangle]
pub fn trap_handler(cx: &mut TrapContext) -> &mut TrapContext {
    let scause = scause::read();
    let stval = stval::read();
    match scause.cause() {
        Trap::Exception(Exception::UserEnvCall) => {
            cx.sepc += 4;
            cx.x[10] = syscall(cx.x[17], [cx.x[10], cx.x[11], cx.x[12]]) as usize;
        }
    ...
    }
    cx
}
```


---
#### trap_handler处理syscall

``` rust
pub fn sys_exit(xstate: i32) -> ! {
    println!("[kernel] Application exited with code {}", xstate);
    run_next_app()
}
```


---
**提纲**

... ...

5. 应用程序设计
6. 内核程序设计
- 应用管理和加载
- 特权级切换
- Trap上下文
- Trap处理流程
### 执行应用程序

---

#### 应用程序的执行时机
- 当批处理操作系统初始化完成
- 某个应用程序运行结束或出错

---

#### 让应用程序执行
从内核态切换到用户态
- 准备好应用的上下文``Trap上下文``
- 恢复应用的相关寄存器
- 特别是应用用户栈指针和执行地址
- **返回用户态让应用执行** 

![bg right:35% 100%](figs/kernel-stack.png)

---

#### 返回用户态让应用执行

- 从内核态切换到用户态
  -  ``sret``指令的**硬件逻辑**：
     - 恢复响应中断/异常
     - CPU Mode从S-Mode 回到U-Mode
     - ``pc`` <-- ``spec`` CSR
     - 继续运行
---
#### 切换到下一个应用程序

调用 run_next_app 函数切换到下一个应用程序：
- 构造应用程序开始执行所需的 Trap 上下文；
- 通过 `__restore` 函数，从刚构造的 Trap 上下文中，恢复应用程序执行的部分寄存器；
- 设置 `sepc` CSR的内容为应用程序入口点 `0x80400000`；
- 切换 `scratch` 和 `sp` 寄存器，设置 `sp` 指向应用程序用户栈；
- 执行 `sret` 从 S 特权级切换到 U 特权级。


---
#### 构造Trap上下文
``` rust
impl TrapContext {
    pub fn set_sp(&mut self, sp: usize) { self.x[2] = sp; }
    pub fn app_init_context(entry: usize, sp: usize) -> Self {
        let mut sstatus = sstatus::read();
        sstatus.set_spp(SPP::User);
        let mut cx = Self {
            x: [0; 32],
            sstatus,
            sepc: entry,
        };
        cx.set_sp(sp);
        cx
```


---
#### 运行下一程序
``` rust
ub fn run_next_app() -> ! {
    ...
    unsafe {
        app_manager.load_app(current_app);
    }
    ...
    unsafe {
        __restore(KERNEL_STACK.push_context(
            TrapContext::app_init_context(APP_BASE_ADDRESS, USER_STACK.get_sp())
        ) as *const _ as usize);
    }
    panic!("Unreachable in batch::run_current_app!");
}
```

---
#### 运行下一程序
```
__restore:
    # case1: start running app by __restore
    # case2: back to U after handling trap
    mv sp, a0
    # now sp->kernel stack(after allocated), sscratch->user stack
    # restore sstatus/sepc
    ld t0, 32*8(sp)
    ld t1, 33*8(sp)
    ld t2, 2*8(sp)
    csrw sstatus, t0
    csrw sepc, t1
    csrw sscratch, t2
```


---
#### 运行下一程序

```
# restore general-purpuse registers except sp/tp
    ld x1, 1*8(sp)
    ld x3, 3*8(sp)
    .set n, 5
    .rept 27
        LOAD_GP %n
        .set n, n+1
    .endr
    # release TrapContext on kernel stack
    addi sp, sp, 34*8
    # now sp->kernel stack, sscratch->user stack
    csrrw sp, sscratch, sp
    sret
```

---
#### 提问

 sscratch 是何时被设置为内核栈顶的？

---
### 小结
- OS与硬件的关系
- OS与应用程序的关系
- 隔离（isolation）机制
- 批处理创建并执行程序
- 特权级切换
- 系统调用
- 能写邓氏鱼OS

![bg right:57% 95%](figs/batch-os-detail.png)