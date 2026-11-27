SHELL := /bin/sh
PDFLATEX ?= pdflatex
CXX ?= c++
export SOURCE_DATE_EPOCH := 1795737600
export FORCE_SOURCE_DATE := 1
export TZ := UTC
DATA_URL := https://www.math.uniri.hr/~mmaksimovic/46_descendants6.txt
DATA_SHA256 := 56feb86ad4a71c5e89b6b8ffb1e3e7b7f1271cf37d85e878d9b4a3ac3ddc7dba
.PHONY: verify source paper

verify:
	@sh verify.sh build

# Optional: download Maksimovic's published descendants of the regular two-graphs on 46
# vertices, check the pinned digest, and re-derive evidence/wt23.txt from two-graph 114.
source:
	@mkdir -p build/source
	@curl -sSfL -o build/source/46_descendants6.txt $(DATA_URL)
	@test "$$(shasum -a 256 build/source/46_descendants6.txt | cut -d' ' -f1)" = "$(DATA_SHA256)" \
		&& echo "MATCH upstream data $(DATA_SHA256)"
	@$(CXX) -O2 -std=c++17 evidence/derive.cpp -o build/source/derive
	@build/source/derive build/source/46_descendants6.txt evidence/phi114-involution.txt evidence/wt23.txt

paper:
	@mkdir -p build/tex
	@$(PDFLATEX) -halt-on-error -interaction=batchmode -output-directory=build/tex paper/main.tex
	@$(PDFLATEX) -halt-on-error -interaction=batchmode -output-directory=build/tex paper/main.tex
	@$(PDFLATEX) -halt-on-error -interaction=batchmode -output-directory=build/tex paper/main.tex
	@! grep -E 'Overfull|undefined references|undefined citations|Warning:' build/tex/main.log
	@cp build/tex/main.pdf paper/main.pdf
