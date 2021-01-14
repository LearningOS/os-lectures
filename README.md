# os-lectures

http://os.cs.tsinghua.edu.cn/oscourse/OS2020spring

## 索引

 1. [大纲](os-course-outline.md)
 1. [操作系统课知识点](os-knowledge-point.md)
 2. [课堂教学组织方式](os-course-style.md)
 3. [幻灯片模板](template.tex)（[出处](https://www.latextemplates.com/template/beamer-presentation)）
 4. [由自动脚本生成的讲义合并版本](https://github.com/dramforever/os-lectures-build/releases)（由王瑞康同学提供）
 5. [RISC-V与X86 CPU硬件特征的对比介绍](rv-x86-hardware-info-video.md)

## 如何生成PDF

- ubuntu 方式

```
## add some chinese fonts
$ sudo apt install fonts-noto-cjk  fonts-noto-cjk-extra  fonts-noto-mon
$ sudo apt install texlive-full
$ cd lectureXX
## for all slides
$ make all
## for single slide
$ xelatex slide-XX-YY
```

- fedora 方式

```
## add noto-serif-cjk-sc
$ sudo dnf install google-noto-serif-cjk-sc-fonts
## add texlive
$ sudo dnf install texlive texlive-ctex texlive-minted 
## the rest of the steps are the same as on ubuntu
```

如果遇到 `! Package minted Error: You must invoke LaTeX with the -shell-escape flag.` ，
则在 makefile 中或命令行中的 `xelatex` 后添加 `-shell-escape` ，例：`xelatex -shell-escape slide-XX-YY` 。

- overleaf 方式

把代码上传到`overleaf.com`网站上，让它帮忙生成。
