## 第十讲 进程、线程和协程的实现

 * v1

### 参考文献

2020年操作系统课第21讲[异步编程](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture21)

第十讲[进程和线程控制](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture10)

Evernote：20200115-陈渝找到的一个操作系统课的线程调度的作业或实验

### 1. 进程的实现

12.1 进程切换 [PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture12?action=AttachFile&do=get&target=12-1.pptx)
12.2 进程创建 [PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture12?action=AttachFile&do=get&target=12-2.pptx)
12.3 进程加载 [PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture12?action=AttachFile&do=get&target=12-3.pptx)
12.4 进程等待与退出 [PPT讲义](http://os.cs.tsinghua.edu.cn/oscourse/OS2015/lecture12?action=AttachFile&do=get&target=12-4.pptx)

### 2. 线程的实现

12.5 rCore进程和线程控制 [PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture10?action=AttachFile&do=view&target=slide-10-05.pdf)

[Green Threads Explained in 200 Lines of Rust...](https://cfsamson.gitbook.io/green-threads-explained-in-200-lines-of-rust/)

[两百行Rust代码解析绿色线程原理](https://zhuanlan.zhihu.com/p/100058478)

[两百行Rust代码解析绿色线程原理（五）附录：支持 Windows](https://zhuanlan.zhihu.com/p/101168659)


### 3. 协程的实现

协程的实现([200行代码讲透RUST FUTURES](https://stevenbai.top/rust/futures_explained_in_200_lines_of_rust/))

### 4. Rust语言中的Future

### 5. Generator机制和async/await语言机制

### 6. Self-Referential Structs & Pin机制

### 7. Waker 和 Reactor 机制

21.1 Background [PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture21?action=AttachFile&do=view&target=slide-21-01.pdf)
21.2 Futures in Rust [PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture21?action=AttachFile&do=view&target=slide-21-02.pdf)
21.3 Generators and async/await [PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture21?action=AttachFile&do=view&target=slide-21-03.pdf)
21.4 Self-Referential Structs & Pin [PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture21?action=AttachFile&do=view&target=slide-21-04.pdf)
21.5 Waker and Reactor [PDF讲义](https://os.cs.tsinghua.edu.cn/oscourse/OS2020spring/lecture21?action=AttachFile&do=view&target=slide-21-05.pdf)

