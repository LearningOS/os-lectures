##### 向勇使用的风格
```
---
marp: true
theme: default
paginate: true
_paginate: false
header: ''
footer: '向勇：异步编程、Rust语言和异步操作系统'
---
```

#### 分页

```

---

```

#### 页码

```
---
<!-- _paginate: true -->

# Slide 2

## Subtitle

Lorem ipsum dolor sit amet, consectetur adipiscing elit.

---
```

#### 幻灯片页眉

有了下面这一行后，后面的第一页都会页眉了。

```
<!-- header: '1. 异步编程 - 1.1 基本概念和原理'-->
```

#### Annotations in markdown

[Annotations in markdown](https://stackoverflow.com/questions/29853106/annotations-in-markdown)

下面幻灯片中的2和3行是不显示的。

```
---
# Slide 3

* Item 1
<!--
* item 2
* Item 3 -->
```

#### 插图

`![width:900px](figs/异步IO模型.png)`