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

## 第四讲 多道程序与分时多任务
### 第二节 实践：多道程序操作系统

---
## 实践：多道程序操作系统
### 进化目标
- 进一步提高系统中多个应用的总体性能和效率
### BatchOS目标
- 让APP与OS隔离，提高系统的安全性和效率
### LibOS目标
- 让应用与硬件隔离，简化应用访问硬件的难度和复杂性

---
## 实践：多道程序操作系统
### 总体思路
- 编译：(OLD)应用程序和内核独立编译，合并为一个镜像
- 编译：应用程序需要各自的起始地址
- 构造：(OLD)系统调用服务请求接口，任务的管理与初始化
- 构造：任务控制块，任务的上下文/状态管理
- 运行：(OLD)特权级切换，任务与OS相互切换
- 运行：任务通过系统调用实现主动切换

---
## 实践：multiprogOS
### 步骤（基于BatchOS）
- 修改APP的链接脚本(定制起始地址)
- 加载&执行应用
- 切换任务

![bg right 100%](figs/multiprog-os.png)

---
## 实践：multiprogOS
### 具体步骤
```
git clone https://github.com/rcore-os/rCore-Tutorial-v3.git
cd rCore-Tutorial-v3
git checkout ch3-coop
```

---
## 实践：multiprogOS
### 具体步骤
```
[RustSBI output]
[kernel] Hello, world!
AAAAAAAAAA [1/5]
BBBBBBBBBB [1/2]
....
CCCCCCCCCC [2/3]
AAAAAAAAAA [3/5]
Test write_b OK!
[kernel] Application exited with code 0
CCCCCCCCCC [3/3]
...
[kernel] Application exited with code 0
[kernel] Panicked at src/task/mod.rs:106 All applications completed!
```
---
## 实践：批处理OS
### 代码结构
构建应用
```
└── user
    ├── build.py(新增：使用 build.py 构建应用使得它们占用的物理地址区间不相交)
    ├── Makefile(修改：使用 build.py 构建应用)
    └── src (各种应用程序)    
```


---
## 实践：批处理OS
### 代码结构
改进OS：加载和执行程序
```
├── os
│   └── src
│       ├── batch.rs(移除：功能分别拆分到 loader 和 task 两个子模块)
│       ├── config.rs(新增：保存内核的一些配置)
│       ├── loader.rs(新增：将应用加载到内存并进行管理)
│       ├── main.rs(修改：主函数进行了修改)
│       ├── syscall(修改：新增若干 syscall)
```

---
## 实践：批处理OS
### 代码结构
改进OS：管理任务，切换任务
```
├── os
│   └── src
│       ├── task(新增：task 子模块，主要负责任务管理)
│       │   ├── context.rs(引入 Task 上下文 TaskContext)
│       │   ├── mod.rs(全局任务管理器和提供给其他模块的接口)
│       │   ├── switch.rs(将任务切换的汇编代码解释为 Rust 接口 __switch)
│       │   ├── switch.S(任务切换的汇编代码)
│       │   └── task.rs(任务控制块 TaskControlBlock 和任务状态 TaskStatus 的定义)