## 第十二讲 多处理机调度内容准备

### ref

https://blog.csdn.net/nisxiya/article/details/45534069
多处理机调度问题(NP)

https://wenku.baidu.com/view/5ce576da4a7302768e9939ec.html
多处理机的任务分配和进程调度

#### Multiprocessor Scheduling (Advanced)
cpu-sched-multi.pdf
cpu-sched-multi.pdf 是ostep的一章，可以作为基础

##### cache coherence
Page 4

##### 10.2 Synchronization
Page 4

Without locks, adding or removing elements from the queue concurrently will not work

##### 10.3 Cache Affinity
The next time the process runs, it is often advantageous to run it on the same CPU

##### 10.4 Single-Queue Scheduling
single- queue multiprocessor scheduling, SQMS

try to make it more likely that process will continue to run on the same CPU if possible.

##### 10.5 Multi-Queue Scheduling
multi-queue multiprocessor scheduling (MQMS)

By migrating a job from one CPU to another, true load balance can be achieved.
##### 10.6 Linux Multiprocessor Schedulers
O(1) scheduler
Completely Fair Scheduler (CFS)
BF Scheduler (BFS)

#### Introduction to Multicore Programming
1.pdf

Multi-core architecture部分可以参考。
P6: Dual CPU Core Chip
P9-15: CPU Cache

P16-22: Cache Coherence

P44-53: work-stealing scheduler

####  Multi-core architectures
27-multicore.pdf

P18-23:  Simultaneous multithreading (SMT)

P28: Comparison: multi-core vs SMT

P35: cache coherence problem

P52: Thread safety

P56: affinity

#### Task Scheduling for Multicore Embedded Devices
Elc2013_Na.pdf

P13: CFS

P19:  DWRR(Distributed Weighted Round-Robun)

#### Multi-core computing & Multi-processor Scheduling
Operating_Systems_Issues.PDF

没有注意到可以参考的内容，或它的内容太多了，但与多核调度关系不大。

#### A Comparison of Scheduling Algorithms for Multiprocessors
smp_scheduling.pdf

##### global EDF
##### optimal P-fair algorithm PF
##### optimal algorithm LLREF

#### A complete guide to Linux process scheduling
GRADU-1428493916.pdf

3.4 CFS
3.5 REAL-TIME SCHEDULER
3.6 BFS: Brain Fuck Scheduler

#### Contention-Aware Scheduling on Multicore Systems
a8-blagodurov.pdf
we identified factors other than cache space contention that cause performance degradation in multicore systems when threads share the memory hierarchy.

### 多核CPU调度

#### 多核结构
27-multicore.pdf - P18-23:  Simultaneous multithreading (SMT) - P28: Comparison: multi-core vs SMT

##### 多核（multi-core）
1.pdf - P6: Dual CPU Core Chip

cpu-sched-multi.pdf - P3: Figure 10.2 & Figure 10.1

27-multicore.pdf - P28: Comparison: multi-core vs SMT
直观描述多核的工作原理的插图。可以直接引用。

##### 超线程（Hyper-Threading, Simultaneous multithreading(同步多线程)）
https://www.intel.com/content/www/us/en/architecture-and-technology/hyper-threading/hyper-threading-technology.html
Intel: Hyper-Threading, HT

https://www.ibm.com/support/knowledgecenter/en/ssw_aix_72/generalprogramming/smt.html
IBM: Simultaneous multithreading, SMT

http://cseweb.ucsd.edu/~tullsen/thesis.pdf
Simultaneous Multithreading
1996年研究超线程的博士论文；

https://software.intel.com/en-us/articles/introduction-to-hyper-threading-technology/
Introduction to Hyper-Threading Technology
这里也有几个比较好的来自Intel的图可以引用；

27-multicore.pdf - P18-23:  Simultaneous multithreading (SMT)

http://meseec.ce.rit.edu/eecc722-fall2012/722-9-3-2012.pdf
Simultaneous Multithreading (SMT)
这是一个完整讲解超线程的幻灯片，其中的插图很好。可以直接引用。

https://blog.csdn.net/shuiliusheng/article/details/84255514
Simultaneous Multithreading
这里有几个很直观的插图可以用。

##### 多核与超线程的结合
27-multicore.pdf - P26-29: Comparison: multi-core vs SMT

#### 多核与高速缓存
27-multicore.pdf - P31-32: “Fish” machines
1.pdf - P13: write policy
1.pdf - P11: replacement policy
1.pdf - P14: CPU缓存类型
1.pdf - P15: Cache Performance
#### 缓存一致性

cpu-sched-multi.pdf - Page 4

27-multicore.pdf - P35-47: cache coherence problem
1.pdf - P16-21: Cache Coherence
1.pdf - P16-22: MSI Protocol

#### 单队列调度算法
cpu-sched-multi.pdf - 10.4 Single-Queue Scheduling

affinity mechanism

#### 多队列调度算法
cpu-sched-multi.pdf - 10.5 Multi-Queue Scheduling
MQMS has a distinct advantage of SQMS
load imbalance
migration
#### O(1)算法
cpu-sched-multi.pdf - 10.6 Linux Multiprocessor Schedulers - O(1) scheduler

https://algorithmsandme.com/scheduling-o1-and-completely-fair-scheduler-cfs/
Scheduling : O(1) and Completely Fair Scheduler (CFS)
O(1)的插图很好。
O(1) Scheduler

https://zhuanlan.zhihu.com/p/33461281
谈谈调度 - Linux O(1)
有张图很好。

https://wikimili.com/en/O(1)_scheduler


http://people.cs.ksu.edu/~gud/docs/ppt/scheduler.pdf
Linux O(1) CPU Scheduler
P6-16: O(1) CPU Scheduler

http://www.wowotech.net/process_management/scheduler-history.html
O(n)、O(1)和CFS调度器

关于O(1)的几个插图不错。

#### work-stealing scheduler
1.pdf - P44-53: work-stealing scheduler
work stealing [FLR98]: [FLR98] “The Implementation of the Cilk-5 Multithreaded Language” by Matteo Frigo, Charles E. Leiserson, Keith Randall. PLDI ’98, Montreal, Canada, June 1998.
http://web.eecs.umich.edu/~weimerw/2015-6610/reading/p212-frigo.pdf

https://github.com/rkuchumov/staccato
C++11 Work-Stealing Task Scheduler 

https://rakyll.org/scheduler/
Go's work-stealing scheduler
这里有几个很好的图可以直接引用。

https://courses.cs.washington.edu/courses/csep506/11sp/slides/Lecture-3-Work-Stealing.pdf
WORK    STEALING    SCHEDULER
P28-31: Work    Stealing    Queue    Datastructure

https://www.cs.cmu.edu/%7Eguyb/papers/IBM08.pdf
Parallel SchedulingTheory and Practice
P23: Work Stealing

#### CFS算法

https://www.linux-magazine.com/Online/News/Completely-Fair-Scheduler-Analyzed
Completely Fair Scheduler Analyzed

https://developer.ibm.com/tutorials/l-completely-fair-scheduler/
Inside the Linux 2.6 Completely Fair Scheduler

https://www.linux-magazine.com/Online/News/Ingo-Molnar-Tests-New-BF-Scheduler
Ingo Molnar Tests New BF Scheduler

https://www.ics.uci.edu/~aburtsev/cs5460/lectures/lecture15-scheduling/lecture15-scheduling.pdf
CS5460/6460: Operating Systems
Lecture 15: Process scheduling
P28： CFS
可参考的幻灯片；

https://developer.ibm.com/technologies/linux/tutorials/l-completely-fair-scheduler
Inside the Linux 2.6 Completely Fair Scheduler

关于CFS的两个插图很好。

http://www.eecs.harvard.edu/~cs161/notes/scheduling-case-studies.pdf
Scheduling: Case Studies
P28-35：Linux’s “Completely Fair Scheduler” (CFS)

cpu-sched-multi.pdf - 10.6 Linux Multiprocessor Schedulers - Completely Fair Scheduler (CFS)
这里对CFS的介绍十分简单，就是按比例分配CPU时间；

Elc2013_Na.pdf - P13: CFS

https://algorithmsandme.com/scheduling-o1-and-completely-fair-scheduler-cfs/
Scheduling : O(1) and Completely Fair Scheduler (CFS)
Internal implementation （插图）
Red-Black Tree

https://trepo.tuni.fi/bitstream/handle/10024/96864/GRADU-1428493916.pdf

https://www.eit.lth.se/fileadmin/eit/courses/eitf60/Rapporter/Ludwig_Hellgren_Winblad_4547_assignsubmission_file_ludwig.hellgren.winblad.pdf
CFS (Completely Fair Scheduler) in the Linux kernel

Figure 2：CFS的红黑树表示
Figure 3 (load-balancing operation in Linux)

https://opensource.com/article/19/2/fair-scheduling-linux
CFS: Completely fair process scheduling in Linux

https://blog.csdn.net/yetaibing1990/article/details/82716593
CFS（完全公平调度算法）

https://blog.csdn.net/weixin_42092278/article/details/83959440?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task
浅析Linux中完全公平调度——CFS

CFS算法设计核心：CFS的三个公式

https://blog.csdn.net/haidao2009/article/details/8970422
Linux 内核 Completely Fair Scheduler （cfs）调度算法

这里有两个图很好。可以直接引用。

https://www.ibm.com/developerworks/cn/linux/l-cfs/index.html
使用完全公平调度程序（CFS）进行多任务处理


#####  Load Balancing of CFS
Elc2013_Na.pdf - P14

插图可以引用；

Start Load Balancing in CFS
 1. Task Fok, Exec, Wakeup
 2. Idle Runqueue
 3. Periodic Checking Algorithm (check and find busiest runqueue)

##### Multicore and CFS
Elc2013_Na.pdf - P17

Load Balancing
 - The most effective distribution is to have equal amounts of each core
 - Global fairness is most important

Caches of Processors
 - CPU-affinity should be considered
 - Cache effectiveness vs. Global fairness

#### BFS算法

https://www.cs.unm.edu/~eschulte/classes/cs587/data/bfs-v-cfs_groves-knockel-schulte.pdf
BFS vs. CFS - SchedulerComparison

cpu-sched-multi.pdf - 10.6 Linux Multiprocessor Schedulers - BF Scheduler (BFS)

https://wikimili.com/en/Brain_Fuck_Scheduler
Brain Fuck Scheduler

https://www.cs.mcgill.ca/~mxia3/pdfs/Case_study__formal_verification_of_the_brain_fuck_scheduler.pdf
Formal verification of the Brain Fuck Scheduler


https://www.linux-magazine.com/Online/News/Con-Kolivas-Introduces-New-BFS-Scheduler
Con Kolivas Introduces New BFS Scheduler

http://ck.kolivas.org/patches/bfs/bfs-faq.txt
FAQS about BFS

http://ck.kolivas.org/
The BFS patch along with benchmark diagrams and other details are on ck.kolivas.org.

https://wikimili.com/en/Brain_Fuck_Scheduler
Brain Fuck Scheduler

##### BFS vs.CFS Scheduler Comparison
https://www.cs.unm.edu/~eschulte/classes/cs587/data/bfs-v-cfs_groves-knockel-schulte.pdf
BFS vs.CFS Scheduler Comparison

P7: Figure4: BFS data structure

BFS has only one system-wide runqueue containing all non-running tasks.
BFS removes the need for these complicated heuristics and algorithms by using a single system-wide queue to determine the next scheduled task.
BFS implements an earliest effective virtual deadline first policy and keeps track of the  virtual deadline of each task.
P7：这一段文字大致描述了BFS的思路：只使用一个队列；所有线程按优先级排队；相同优先级的每个线程有一个时间片长度和虚拟最长等待时间；线程时间片用完时，重新计算时间片长度；线程进入等待状态时，等待时间保持；为了让线程在上次运行的CPU上运行，不同CPU对线程的虚拟截止时间加一个权重；

##### BFS的算法描述

##### wikimili

https://wikimili.com/en/Brain_Fuck_Scheduler
Brain Fuck Scheduler

BFS uses a doubly linked list data structure.
The execution behavior is still a weighted variation of the Round-Robin Scheduler

virtual deadline formula

##### 新加坡的项目报告

http://vellvisher.github.io/papers_reports/doc/BFS_FreeBSD.pdf
Analysis of the BFS Scheduler in FreeBSD

###### Single Runqueue

single run-queue which is a double linked list shared by all the CPU’s

###### Interactivity

I/O Bound tasks or interactive tasks are decided basis on thefact that the tasks which wake uphave not used their quota of CPU time and have earlier effectivedeadlines making them likelyto preempt CPU bound tasks of same priority.

###### Round Robin Interval

This is the only tunable value and it is set to 6ms by default with a range from 1ms to 1000ms.

###### Task Insertion

The task is inserted as an O(1) insertion to the double link list run-queue.
Thelookup is O(n) in the worst casewhere n is the number of CPUs on the system.

###### Task Lookup

BFS has 103 priority queues with 100 dedicated to the static priority of realtime tasks, and theremaining 3 are, in order of best to worst priority, SCHEDISO (isochronous), SCHEDNORMAL,and SCHEDIDLEPRIO (idle priority scheduling).

a bitmap of running priorities
the lookup is O(n) in the worst case, where n is the totalnumber of CPUs.

###### Task Switching

Time Slice:  its time slicereplenished and the virtual deadline reset
Sleep: virtual deadline remain the same and the same values will be used again
Preemption: higher priority than a currently running task on any CPUs.

###### Virtual Deadline

no guarantee
a quota (time slice)equal to the rr_interval and a virtual deadline.

The virtual deadline is offset from the current time in jiffies.
jiffies + (prior_atio ∗ rr_interval)
prioratio increases by 10% for every nice level

##### BFS的性能分析
http://repo-ck.com/bench/cpu_schedulers_compared.pdf
CPU SCHEDULERS COMPARED

### Linux 和对称多处理
https://www.ibm.com/developerworks/cn/linux/l-linux-smp/index.html
