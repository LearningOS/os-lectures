## 第十八讲 文件系统实例

[v1](https://github.com/LearningOS/os-lectures/blob/355c18947ee357239ca441d69dd26c83896abb9b/lecture18/ref.md)
[v2]
### 	18.1  File Allocation Table (FAT)

#### FAT Volume

##### File Allocation Table (FAT)

- A simple file system originally **designed for small disks and simple folder structures**. 
- The FAT file system is named for its method of organization, the **file allocation table**, which resides at the beginning of the volume.
- To protect the volume, two copies of the table are kept, in case one becomes damaged.
- **The file allocation tables and the root folder must be stored in a fixed location** so that the files needed to start the system can be correctly located.

##### Structure of a FAT Volume

- Boot sector
- FAT1
- FAT2
- Root directory
- Other directories and all files

![FAT-volume](figs/FAT-volume.png)

##### Differences Between FAT Systems

![FAT-version](figs/FAT-version.png)

- FAT32 is a derivative of the File Allocation Table (FAT) file system that supports drives with over 2GB of storage.
- FAT32 drives can contain more than 65,526 clusters and results in more efficient space allocation on the FAT32 drive.

#### File Allocation System

##### File Allocation System

The file allocation table contains the following **types** of information about each cluster on the volume (see example below for FAT16):
 * Unused (0x0000)
 * Cluster in use by a file
 * Bad cluster (0xFFF7)
 * Last cluster in a file (0xFFF8-0xFFFF)

##### Example of File Allocation Table

![FAT-example](figs/FAT-example.png)

##### FAT Root Folder

The root folder contains an entry for each file and folder on the root. The only difference between the root folder and other folders is that **the root folder is on a specified location on the disk and has a fixed size** (512 entries for a hard disk, number of entries on a floppy disk depends on the size of the disk).

##### Folder Entry

The Folder Entry includes the following information:
 * Name (eight-plus-three characters)
 * Attribute byte (8 bits worth of information, described later in this section)
 * Create time (24 bits)
 * Create date (16 bits)
 * Last access date (16 bits)
 * Last modified time (16 bits)
 * Last modified date (16 bits.)
 * Starting cluster number in the file allocation table (16 bits)
 * File size (32 bits)

#### Filenames on FAT Volumes

##### Filenames on FAT Volumes

- FAT creates an **eight-plus-three name** for the file. In addition to this conventional entry. 
- FAT creates **one or more secondary folder entries** for the file, one for each 13 characters in the **long filename**. Each of these secondary folder entries stores a corresponding part of the long filename in Unicode.
- FAT sets the volume, read-only, system, and hidden **file attribute bits** of the secondary folder entry to mark it as part of a long filename. 

##### Folder Entries for the long filename

Below shows all of the folder entries for the file **Thequi~1.fox**, which has a long name of **The quick brown.fox**. The long name is in Unicode, so each character in the name uses two bytes in the folder entry. The **attribute field** for the long name entries has the value **0x0F**. The attribute field for the short name is **0x20**

##### Filenames on FAT Volumes

![FAT-filename](figs/FAT-filename.png)

### 18.2 ext4 fs
- Log-structured File System介绍 https://zhuanlan.zhihu.com/p/41358013
- http://pages.cs.wisc.edu/~remzi/OSTEP/file-journaling.pdf
- http://pages.cs.wisc.edu/~remzi/OSTEP/file-lfs.pdf
- https://pdos.csail.mit.edu/6.828/2018/lec/l-crash.txt
- https://pdos.csail.mit.edu/6.828/2018/lec/l-journal.txt
- https://pdos.csail.mit.edu/6.828/2018/homework/xv6-new-log.html
- https://pdos.csail.mit.edu/6.828/2018/readings/journal-design.pdf
- The design and Implementation of a Log-Structured File System https://people.eecs.berkeley.edu/~brewer/cs262/LFS.pdf CN  https://blog.csdn.net/flymu0808/article/details/40892675 https://blog.csdn.net/dongkun152/article/details/77994811
- 深入理解 ext4 等 Linux 文件系统 https://zhuanlan.zhihu.com/p/44267768
- ext4 slide https://compas.cs.stonybrook.edu/~nhonarmand/courses/fa14/cse506.2/slides/ext4.pdf
- ext2/ext3/ext4简介（PPT）http://itindex.net/detail/8288-ext2-ext3-ext4
- 【转】深入理解 ext4 等 Linux 文件系统（ Understanding Linux filesystems : ext4 and beyond ）https://ccie.lol/knowledge-base/linux-file-system-ext4/
- An introduction to Linux's EXT4 filesystem https://opensource.com/article/17/5/introduction-ext4-filesystem
- 干货！大话EXT4文件系统完整版 https://cloud.tencent.com/developer/article/1551286
- https://compas.cs.stonybrook.edu/~nhonarmand/courses/fa14/cse506.2/slides/ext4.pdf
- http://www.linux-kongress.org/2009/slides/ext4+btrfs_jan_kara.pdf
- https://ext4.wiki.kernel.org/index.php/Publications
- https://www.usenix.org/sites/default/files/conference/protected-files/fast17_slides_aghayev_0.pdf

### 18.3 Zettabyte File System (ZFS)

#### Ref

Richard McDougall, Jim Mauro, Solaris Internals:Solaris 10 and OpenSolaris Kernel Architecture, 2nd Edition, Prentice Hall, July 10, 2006, ISBN 0-13-148209-2

http://pages.cs.wisc.edu/~remzi/OSTEP/Citations/zfs_last.pdf
ZFS: The Last WordIn File Systems

https://nasa.cs.nctu.edu.tw/sa/2019/slides/14_ZFS.pdf
ZFS -The Last Word in Filesystem

#### ZFS overview

##### What is ZFS？

Zettabyte File System
ZFS is a new kind of filesystem that provides simple administration, transactional semantics, end-to-end data integrity, and immense scalability .

 * SPA (Storage Pool Allocator)
 * DSL (Dataset and Snapshot Layer)
 * DMU (Data Management Layer)
 * ZAP (ZFS Attribute Processor)
 * ZPL (ZFS Posix layer)
 * ZIL (ZFS Intent Log)
 * ZVOL (ZFS Volume)

##### ZFS overview

 * Pooled storage
    * Completely eliminates the antique notion of volumes
    * Does for storage what VM did for memory
 * Transactional object system
    * Always consistent on disk – no fsck, ever
    * Universal – file, block, iSCSI, swap ...
 * Provable end-to-end data integrity
    * Detects and corrects silent data corruption
    * Historically considered “too expensive” – no longer true
 * Simple administration
    * Concisely express your intent

##### ZFS Features

 * Immense capacity
    * 128bit
 * Provable data integrity
    * Detects and corrects silent data corruption
 * Simple administration
    * a pleasure to use. 

##### Pooled storage

 * No volume
 * Pooled storage
 * Many file system share pool。
 * And share all I/O channel in the pool.

##### FS/Volume Model vs. ZFS

![ZFS-pooled-storage](figs/ZFS-pooled-storage.png)



#### ZFS I/O Stack

##### FS/Volume Interfaces vs. ZFS

![ZFS-io-stack](figs/ZFS-io-stack.png)

##### ZFS I/O Stack

![ZFS-stack](figs/ZFS-stack.png)

##### ZFL (ZFS POSIX Layer)

![ZFS-zpl](figs/ZFS-zpl.png)

##### DMU (Data Management Unit)

![ZFS-dmu](figs/ZFS-dmu.png)

##### ARC (Adaptive Replacement Cache)

![ZFS-arc](figs/ZFS-arc.png)

##### ZIO (ZFS I/O Pipeline)

![ZFS-zio](figs/ZFS-zio.png)

##### VDEV (Virtual Devices)

![ZFS-vdev](figs/ZFS-vdev.png)

#### ZFS Data Integrity Model



##### ZFS Data Integrity Model

 * Everything is copy-on-write
    * Never overwrite live data
    * On-disk state always valid – no “windows of vulnerability”
    * No need for fsck(1M)
 * Everything is transactional
    * Related changes succeed or fail as a whole
    * No need for journaling
 * Everything is checksummed
    * No silent data corruption

##### Copy-On-Write Transactions

![ZFS-cow](figs/ZFS-cow.png)

##### Constant-Time Snapshots
Ref: http://pages.cs.wisc.edu/~remzi/OSTEP/Citations/zfs_last.pdf - Page 11
http://pages.cs.wisc.edu/~remzi/OSTEP/Citations/zfs_last.pdf P10

![ZFS-snapshot](figs/ZFS-snapshot2.png)

At end of TX group, don't free COWed blocks

Actually cheaper to take a snapshot than not!

The tricky part:  how do you know when a block is free?



##### End-to-End Checksums

![ZFS-checksum](figs/ZFS-checksum.png)

##### Self-Healing Data in ZFS

![ZFS-self-healing](figs/ZFS-self-healing.png)

##### RAID-Z

Ref: http://pages.cs.wisc.edu/~remzi/OSTEP/Citations/zfs_last.pdf Page 18

![ZFS-raidz](figs/ZFS-raidz.png)

 * Dynamic stripe width
    * Variable block size: 512 – 128K
    * Each logical block is its own stripe
 * All writes are full-stripe writes
    * Eliminates read-modify-write (it's fast)
    * Eliminates the RAID-5 write hole(no need for NVRAM)
 * Both single- and double-parity
 * Detects and corrects silent data corruption
    * Checksum-driven combinatorial reconstruction
 * **No special hardware** – ZFS loves cheap disks

##### Dynamic Striping

Automatically distributes load across all devices

![ZFS-striping](figs/ZFS-striping.png)

##### Object-Based Storage

![ZFS-storage](figs/ZFS-storage.png)



##### Variable Block Size

Ref: http://pages.cs.wisc.edu/~remzi/OSTEP/Citations/zfs_last.pdf Page 28

 * No single block size is optimal for everything
    * Large blocks: less metadata, higher bandwidth
    * Small blocks: more space-efficient for small objects
    * Record-structured files (e.g. databases) have natural granularity; filesystem must match it to avoid read/modify/write
 * Per-object granularity
    * A 37k file consumes 37k – no wasted space
 * Enables transparent block-based compression

##### Built-in Compression

Ref: http://pages.cs.wisc.edu/~remzi/OSTEP/Citations/zfs_last.pdf Page 29

![ZFS-compression](figs/ZFS-compression.png)

 * Block-level compression in SPA
 * Transparent to all other layers
 * Each block compressed independently
 * All-zero blocks converted into file holes
 * LZJB and GZIP available today; more on the way


### 18.4 Distributed File Systems

#### ref

http://www.cs.ucf.edu/~eurip/papers/sandbergnfs.pdf
The Sun Network Filesystem: Design, Implementation and Experience

https://searchenterprisedesktop.techtarget.com/definition/Network-File-System
Network File System (NFS) 

http://pages.cs.wisc.edu/~remzi/OSTEP/dist-nfs.pdf
Sun’s Network File System (NFS)

http://pages.cs.wisc.edu/~remzi/OSTEP/dist-afs.pdf
The Andrew File System (AFS)

https://www.openafs.org/
OpenAFS

https://web.cs.wpi.edu/~cs3013/c07/lectures/Section10-File_Systems.pdf
OPERATING SYSTEMS FILE SYSTEMS

https://web.cs.wpi.edu/~rek/DCS/D04/DFS.pdf
Distributed File Systems

http://cse.iitkgp.ac.in/~pallab/dist_sys/Lec-12-DFS.pdf
Distributed File Systems

https://www.cs.helsinki.fi/u/jakangas/Teaching/DistSys/DistSys-08f-1.pdf
Distributed Systems

http://www.cs.cmu.edu/~410-s05/lectures/L30_NFSAFS.pdf
NFS & AFS

#### What is DFS?

##### Distributed file system (DFS)

Ref: https://web.cs.wpi.edu/~rek/DCS/D04/DFS.pdf Page 3
https://www.cs.helsinki.fi/u/jakangas/Teaching/DistSys/DistSys-08f-1.pdf Page 11

A distributed implementation of the classical time-sharing model of a file system, where multiple users share files and storage resources.

 * A DFS manages set of dispersed storage devices.
 * Overall storage space managed by a DFS is composed of different, remotely located, smaller storage spaces.

![DFS-example](figs/DFS-example.png)

##### DFS Structure

Ref: https://web.cs.wpi.edu/~rek/DCS/D04/DFS.pdf Page 4

 * **Service**: software entity providing a particular type of function to a priori unknown clients.
 * **Server**: service software running on a single machine.
 * **Client**: process that can **invoke a service** using a set of operations that forms its client interface.
 * Client interface for a file service: a set of primitive file operations(create, delete, read, write).
 * Client interface of a DFS should be transparent, i.e., not distinguish between local and remote files.

#### DFS Issues

##### DFS Issues

Ref: https://web.cs.wpi.edu/~rek/DCS/D04/DFS.pdf Page 5

 * Naming and Transparency
 * Remote File Access
 * Stateful versus Stateless Service
 * File Replication

##### Naming and Transparency

Ref: https://web.cs.wpi.edu/~rek/DCS/D04/DFS.pdf Page 6

 * **Naming**: mapping between logical and physical objects.
 * **Multilevel mapping**: abstraction of a file that hides the details of how and where on the disk the file is actually stored.
 * **File replication**: the mapping returns a set of the locations of this file’s replicas; both the existence of multiple copies and their location are hidden.

##### Files Access in DFS
Ref: https://web.cs.wpi.edu/~rek/DCS/D04/DFS.pdf Page 9
 * Computation Migration
    * Remote Service Oriented
    * Caching (Blocks) for Performance
    * Server Centric Data Management → Simple and Reliable
    * Ex) NFS
 * Data Migration
    * File Caching Oriented
    * Cooperative Data Management → Complex but Scalable
    * Ex) Andrew File System (AFS)

##### Cache of Remote File

Ref: https://web.cs.wpi.edu/~rek/DCS/D04/DFS.pdf Page 10

Reduce network traffic by retaining recently accessed disk blocks in a cache, so that repeated accesses to the same information can be handled locally.
 * If needed data not already cached, a copy of data is brought from the server to the user.
 * Accesses are performed on the cached copy.
 * Files identified with one master copy residing at the server machine, but copies of (parts of) the file are scattered in different caches.
 * Cache-consistency problem – keeping the cached copies consistent with the master file.

##### Stateful File Service

 * Mechanism.
    * Client opens a file
    * Server fetches information about the file, stores it in its memory, and gives a connection identifier
    * Identifier is used for subsequent accesses until the session ends
    * Server must reclaim the main-memory space used by clients
 * Feature: Increased performance
    * Fewer disk accesses
    * If a file was opened for sequential access and can thus read ahead the next blocks

##### Stateless File Service

 * Avoids state information by making each request self-contained
 * Each request identifies the file and position in the file
 * No need to establish and terminate a connection by open and close operations
 * Feature
    * Server failure sand recovery are almost unnoticeable
    * Longer request messages
    * Slower request processing

##### File Replication

 * Replicas of the same file reside on failure-independent machines.
 * Improves availability and can shorten access time.
 * Naming scheme maps a replicated file name to a particular replica.
    * Existence of replicas should be invisible to higher levels. 
    * Replicas must be distinguished from one another by different lower-level names.
 * Updates – an update to any replica must be reflected on all other replicas
 * Demand replication – reading a nonlocal replica causes it to be cached locally, thereby generating a new nonprimary replica.

#### Andrew File System (AFS)

##### Andrew File System (AFS)

A distributed computing environment under development since 1983 at Carnegie-Mellon University

 * Design objectives
    * Highly scalable: targeted to span over 5000 workstations.
    * Secure

##### AFS architecture

![AFS-arch](figs/AFS-arch.png)

##### AFS feature

 * Dedicated servers, called Vice, present the shared name space to the clients as an homogeneous, identical, and location transparent file hierarchy.
 * Clients are presented with a partitioned space of file names:  a local name space and a shared name space.
 * Workstations run the Virtue protocol to communicate with Vice, and are required to have local disks where they store their local name space.

##### AFS Implementation

 * **Whole file caching**: Opening a remote file causes it to be cached, in its entirety, on the local disk.
 * A fid identifies a Vice file or directory.  A fid is 96 bits long and has three equal-length components

![AFS-fid](figs/AFS-fid.png)

#### SUN Network File System (NFS)

##### SUN Network File System (NFS)

Ref: http://cse.iitkgp.ac.in/~pallab/dist_sys/Lec-12-DFS.pdf Page 23

NFS is an **open protocol** developed in 1984, which simply specified the exact message formats that clients and servers would use to communicate.

 * NFS has become **de facto standard** for distributed UNIX file access.
 * Any system may be both a client and server.
 * Basic idea:
    * Remote directory is mounted onto local directory
    * Remote directory may contain mounted directories within

##### SUN Network File System Architecture

Ref: https://web.cs.wpi.edu/~cs3013/c07/lectures/Section10-File_Systems.pdf Page 39

![NFS-architecure](figs/NFS-architecure.png)

Ref: https://web.cs.wpi.edu/~cs3013/c07/lectures/Section10-File_Systems.pdf Page 40

1. UNIX filesystem layer - does normal open / read / etc. commands.
2. Virtual file system ( VFS ) layer
   a. Gives clean layer between user and filesystem.
   b. Acts as deflection point by using global vnodes.
   c. Understands the difference between local and remote names.
   d. Keeps in memory information about mounted local directories and remote directories.
3. System call interface layer
   * Presents sanitized validated requests in a uniform way to the VFS.

##### NFS: v-nodes
Ref: http://cse.iitkgp.ac.in/~pallab/dist_sys/Lec-12-DFS.pdf Page 25

![NFS-inode](figs/NFS-inode.png)

 * v-node contains a reference to a file handle if the file is remote or an i-node if the file is local
 * File system identifier
    * Unique number generated for each file system (in UNIX stored in super block
 * i-node and i-node generation number

##### Pathname Translation in NFS

Ref: https://web.cs.wpi.edu/~cs3013/c07/lectures/Section10-File_Systems.pdf Page 41

 * Break the complete pathname into components.
 * For each component, do an NFS lookup using the **component name + directory** vnode.
 * After  a  mount  point  is  reached,  each  component  piece  will  cause  a  server access.
 * Can't  hand  the  whole  operation  to  server  since  the  client  may  have  a  second mount on a subsidiary directory (a mount on a mount ).
 * A directory name cache on the client speeds up lookups.

##### Caches of Remote Data in NFS

Ref: https://web.cs.wpi.edu/~cs3013/c07/lectures/Section10-File_Systems.pdf Page 42

 * The client keeps:
    * File block cache - ( the contents of a file )
    * File attribute cache - ( file header info (inode in UNIX) ).
 * The local kernel hangs on to the data after getting it the first time.
 * On an open, local kernel, it checks with server that cached data is still OK.
 * Cached attributes are thrown away after a few seconds.
 * Data blocks use read ahead and delayed write.
 * Mechanism has:
    * Server consistency problems.
    * Good performance.

#### Google File System (GFS)

##### documents

https://pdos.csail.mit.edu/6.824/papers/gfs.pdf
The Google File System
SOSP’03

https://zhuanlan.zhihu.com/p/28155582
Google File System

https://zhuanlan.zhihu.com/p/50825652
小白带你学习google三篇论文————Google File System

https://zhuanlan.zhihu.com/p/20673524
硅谷之路9：深入浅出理解GFS

https://zhuanlan.zhihu.com/p/33944479
Google File System 论文详析

https://zhuanlan.zhihu.com/p/104427782
[Paper Reading]2003-The Google File System

##### slides

https://www.cs.brandeis.edu/~dilant/WebPage_TA160/The%20Google%20File%20System.pdf
The Google File System

http://courses.cs.vt.edu/cs5204/fall09-kafura/Presentations/Google-Filesystem.pdf
Google File System

#### ASF vs. NFS

https://web.cs.wpi.edu/~rek/DCS/D04/DFS.pdf Page 31

![NFS-AFS-comparison](figs/NFS-AFS-comparison.png)





