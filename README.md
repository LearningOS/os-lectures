# os-lectures
http://os.cs.tsinghua.edu.cn/oscourse/OS2020spring

## 索引

 1. [大纲](os-course-outline.md)
 2. [课堂教学组织方式](os-course-style.md)
 3. [幻灯片模板](template.tex)（[出处](https://www.latextemplates.com/template/beamer-presentation)）

## 如何生成PDF
- ubuntu 方式
```
$ sudo apt install texlive-full
$ cd lectureXX
## for all slides
$ make all
## for single slide
$ xelatex slide-XX-YY
```

- overleaf方式
把代码上传到`overleaf.com`网站上，让它帮忙生成。
