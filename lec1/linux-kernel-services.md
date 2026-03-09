---
marp: false
theme: default
paginate: true
_paginate: false
header: ''
footer: ''
backgroundColor: white
---

<!-- theme: gaia -->
<!-- page_number: true -->
<!-- _class: lead -->

## 第一讲 操作系统概述

### 第六节 Linux 内核服务总体架构

<br>
<br>

向勇 陈渝 李国良 任炬

<br>
<br>

2026年春季

---

## 问题

- `helloworld` 为什么不能直接把字符写到硬件上？
- `open`、`copy`、`fork`、`redirect`、`pipe` 为什么都要经过内核？
- Linux 内核到底提供了哪些服务？这些服务如何组合起来？

---

## 总体主线

```mermaid
flowchart TB
    subgraph userSpace["用户态"]
        shellProg["Shell / 用户程序"]
        appCode["helloworld / open / copy / forkexec"]
        libc["C 库封装\nprintf open read write fork exec"]
    end

    subgraph kernelSpace["内核态"]
        syscallEntry["系统调用入口\ntrap / syscall"]
        procSvc["进程管理"]
        memSvc["内存管理"]
        fsSvc["文件系统与 VFS"]
        ioSvc["I/O 与设备驱动"]
        ipcSvc["IPC / pipe / socket"]
    end

    hw["终端 / 磁盘 / 网卡 / 时钟 / CPU"]

    shellProg --> appCode
    appCode --> libc
    libc --> syscallEntry
    syscallEntry --> procSvc
    syscallEntry --> memSvc
    syscallEntry --> fsSvc
    syscallEntry --> ioSvc
    syscallEntry --> ipcSvc
    ioSvc --> hw
    fsSvc --> hw
    procSvc --> hw
```

- 用户程序看到的是函数和文件描述符
- 内核看到的是进程、地址空间、文件对象、设备对象和缓冲区
- 硬件访问被统一封装成受保护的内核服务

---

## `helloworld` 如何得到输出服务

```mermaid
sequenceDiagram
    participant shell as Shell
    participant app as hello
    participant libc as libc
    participant kernel as LinuxKernel
    participant tty as TTYConsole
    participant device as UARTOrDisplay

    shell->>kernel: fork + execve ./hello
    kernel-->>app: 开始执行 main
    app->>libc: printf hello_world newline
    libc->>kernel: write fd1 buf n
    kernel->>tty: 根据 fd=1 找到标准输出
    tty->>device: 输出字符流
    device-->>tty: 写入完成
    tty-->>kernel: 返回状态
    kernel-->>libc: write 返回
    libc-->>app: printf 返回
    app->>kernel: exit status 0
    kernel-->>shell: wait 返回退出状态
```

- `helloworld` 并不知道屏幕或串口的寄存器地址
- 它只知道调用 `printf` 或 `write`
- 内核负责把“标准输出”翻译成真正的终端或串口设备

---

## 一次系统调用内部发生了什么

```mermaid
flowchart TD
    userCall["用户态调用\nwrite fd buf n"] --> trap["执行 syscall 指令"]
    trap --> switchMode["硬件切换到内核态"]
    switchMode --> saveCtx["保存用户态上下文"]
    saveCtx --> dispatch["按 syscall 号分发"]
    dispatch --> sysWrite["执行 sys_write"]
    sysWrite --> kernelWork["检查参数\n查找 fd\n调用 VFS / 驱动"]
    kernelWork --> setRet["写回返回值"]
    setRet --> restoreCtx["恢复用户态上下文"]
    restoreCtx --> returnUser["返回用户态继续执行"]
```

- 看起来像函数调用，本质上是受保护的内核入口
- 应用不能直接跳进任意内核代码，只能通过规定好的系统调用接口
- 这保证了安全性，也让不同程序共享通用服务

---

## Linux 内核服务的总体分工

```mermaid
flowchart LR
    appReq["应用请求"] --> proc["进程管理\nfork exec wait exit"]
    appReq --> mem["内存管理\nmmap brk page fault"]
    appReq --> fs["文件系统\nopen read write close stat"]
    appReq --> io["设备与 I/O\nconsole disk net"]
    appReq --> ipc["进程间通信\npipe signal socket"]

    proc --> cpu["CPU / 调度"]
    mem --> ram["内存 / 页表"]
    fs --> disk["磁盘 / 目录 / inode"]
    io --> terminal["终端 / 串口 / 网卡"]
    ipc --> buffer["内核缓冲区 / 事件"]
```

- `fork/exec/wait/exit` 对应进程管理服务
- `open/read/write/close/stat` 对应文件系统与 I/O 服务
- `pipe`、`signal`、`socket` 对应通信服务
- 各类服务共用同一个系统调用边界

---

## 文件与 I/O：`open / read / write / close`

```mermaid
flowchart LR
    app["应用程序"] -->|"open out"| fdTable["进程文件描述符表"]
    fdTable --> fd3["fd 3"]
    fdTable --> fd1["fd 1 标准输出"]

    fd3 --> fileObj["内核打开文件对象"]
    fd1 --> stdoutObj["终端文件对象"]

    fileObj --> vfs["VFS / 文件系统"]
    stdoutObj --> vfs
    vfs --> inode["目录项 / inode / 页缓存"]
    vfs --> driver["终端驱动 / 块设备驱动"]
```

- `open()` 返回的是文件描述符，不是直接返回“磁盘块”
- `read()` 和 `write()` 总是先根据 `fd` 找到内核中的打开文件对象
- 这样同一套接口既能访问普通文件，也能访问终端、管道、设备

---

## 进程服务：`fork / exec / wait / exit`

```mermaid
flowchart TD
    shell["Shell"] --> forkStep["fork\n复制进程执行上下文"]
    forkStep --> parent["父进程\n得到子进程 pid"]
    forkStep --> child["子进程\nfork 返回 0"]
    child --> execStep["execve\n装入新程序映像"]
    execStep --> runProg["运行 hello 或其他程序"]
    runProg --> exitStep["exit\n返回状态"]
    parent --> waitStep["wait\n等待子进程"]
    exitStep --> waitStep
    waitStep --> prompt["Shell 打印下一个提示符"]
```

- Shell 本身并不实现“运行别的程序”的全部细节
- 它依赖内核的进程创建、程序装载和等待回收服务
- `fork + exec + wait` 是 UNIX/Linux 非常经典的组合方式

---

## 重定向：为什么改 `fd=1` 就够了

```mermaid
flowchart LR
    subgraph beforeRun["默认情况"]
        fd0a["fd 0"] --> stdinA["键盘 / 输入"]
        fd1a["fd 1"] --> stdoutA["终端 / 屏幕"]
        fd2a["fd 2"] --> stderrA["终端 / 屏幕"]
    end

    subgraph redirected["执行 close 1 加 open output.txt 之后"]
        fd0b["fd 0"] --> stdinB["键盘 / 输入"]
        fd1b["fd 1"] --> fileOut["output.txt"]
        fd2b["fd 2"] --> stderrB["终端 / 屏幕"]
    end
```

- 程序只会向 `fd=1` 写数据，不需要知道它后面连的是屏幕还是文件
- 重定向的关键不在应用本身，而在 Shell 和内核共同维护的文件描述符绑定
- 这说明内核抽象强调“统一接口、可替换后端”

---

## 管道：`pipe` 如何提供进程间通信

```mermaid
flowchart LR
    procA["进程 A\nwrite 到 p1"] --> writeEnd["管道写端 p1"]
    writeEnd --> pipeBuf["内核管道缓冲区"]
    pipeBuf --> readEnd["管道读端 p0"]
    readEnd --> procB["进程 B\nread p0"]
```

- `pipe()` 创建两个文件描述符：一个读端，一个写端
- 数据并不是直接从一个用户进程内存拷到另一个用户进程内存
- 内核提供缓冲、同步和阻塞唤醒机制，因此管道能安全工作

---

## 从 `p5-tryunix` 的例子看内核服务

```mermaid
flowchart TB
    examples["用户态小例子"] --> openEx["open.c"]
    examples --> copyEx["copy.c"]
    examples --> forkEx["fork.c"]
    examples --> execEx["exec.c"]
    examples --> forkexecEx["forkexec.c"]
    examples --> redirectEx["redirect.c"]
    examples --> pipeEx["pipe2.c"]

    openEx --> fsSvc["文件系统 / fd 分配"]
    copyEx --> ioSvc["read write / 缓冲区 I/O"]
    forkEx --> procSvc["进程复制 / 调度"]
    execEx --> loadSvc["程序装载 / 地址空间重建"]
    forkexecEx --> procSvc
    forkexecEx --> loadSvc
    redirectEx --> fdSvc["fd 重绑定 / 文件对象继承"]
    pipeEx --> ipcSvc["管道缓冲区 / 同步"]
```

- `open.c` 强调“名字 -> 文件对象 -> 文件描述符”
- `copy.c` 强调“文件访问其实统一成 `read/write`”
- `fork/exec/forkexec` 强调程序执行依赖进程管理服务
- `redirect` 和 `pipe2` 强调 UNIX 抽象具有很强的组合能力

---

## `helloworld` 到各个服务的联系

- `printf("hello world\\n")`
  - 常经过 libc，最终调用 `write`
- `write(fd=1, buf, n)`
  - 用到文件描述符、VFS、终端驱动
- Shell 启动 `./hello`
  - 用到 `fork + execve + wait`
- 程序运行本身
  - 用到调度器、地址空间、栈和代码段
- 最终看到字符输出
  - 依赖终端设备和驱动程序

---

## 为什么由内核统一提供这些服务

- 硬件访问需要保护，不能让任意应用直接操作设备和内存
- 不同程序都需要进程、文件、通信等共性能力，适合由内核统一实现
- 内核提供统一抽象后，应用只需面对少量简单接口
- 这些接口还能组合出重定向、管道、Shell 执行等强大机制

---

## 小结

- 用户程序通过 `C 库 -> 系统调用 -> 内核服务` 获得能力
- Linux 内核把硬件访问封装成进程、内存、文件、I/O、IPC 等抽象
- `helloworld`、`open`、`copy`、`forkexec`、`redirect`、`pipe2` 都只是这些抽象的不同组合
- UNIX/Linux 接口数量不多，但表达力很强，这正是其经典之处
