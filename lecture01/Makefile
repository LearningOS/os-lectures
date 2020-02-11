SOURCE = $(wildcard *.tex)
PDF = $(patsubst %.tex,%.pdf,$(SOURCE))

%.pdf:%.tex
	xelatex $<

.PHONY:all clean
all:$(PDF)

clean:
	rm -f *.pdf *.out *.toc *.aux *.log *.nav *.gz *.snm *.vrb


