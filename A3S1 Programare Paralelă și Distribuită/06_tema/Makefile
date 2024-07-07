.PHONY: test run prepare

test: test.py prepare
	python test.py

prepare: \
	data \
	competitors-correct.txt

competitors-correct.txt: FORCE
	( cd ~/scoala/ppd/05_tema && make ./target/sequential )
	~/scoala/ppd/05_tema/target/sequential ./data/ ./competitors-correct.txt /dev/null

# data

data: gen.py
	python gen.py data

FORCE:
