FLAGS = -pdf -shell-escape -interaction=nonstopmode

all: compact

compact:
	latexmk $(FLAGS) -jobname=Referencia_ICPC -pdflatex="pdflatex %O '\let\ifextendedversion\iffalse\input{%S}'" $(MAIN)

extended:
	latexmk $(FLAGS) -jobname=Referencia_ICPC_extended -pdflatex="pdflatex %O '\let\ifextendedversion\iftrue\input{%S}'" $(MAIN)

clean:
	latexmk -c
	rm -rf _minted* *.nav *.snm *.vrb

clean-all: clean
	latexmk -C
	rm -f Referencia_ICPC.pdf Referencia_ICPC_extended.pdf

.PHONY: all compact extended clean clean-all


