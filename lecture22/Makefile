SOURCE = $(wildcard *.tex)
PDF = $(patsubst %.tex,%.pdf,$(SOURCE))

%.pdf:%.tex
	xelatex $<

.PHONY:all clean cleanall
all:$(PDF)

cleanall:
	rm -f *.pdf *.out *.toc *.aux *.log *.nav *.gz *.snm *.vrb *.bak *.org ~*

clean:
	rm -f *.out *.toc *.aux *.log *.nav *.gz *.snm *.vrb
