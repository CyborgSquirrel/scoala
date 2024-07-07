.PHONY: all pre-gen clean

all: src/gen/coechipier_main.py src/gen/impostor_main.py src/gen/log_in.py

clean:
	rm -rf src/gen

pre-gen:
	mkdir -p src/gen
 
src/gen/coechipier_main.py: pre-gen ui/coechipier-main.ui
	pyside2-uic -o src/gen/coechipier_main.py ui/coechipier-main.ui

src/gen/impostor_main.py: pre-gen ui/impostor-main.ui
	pyside2-uic -o src/gen/impostor_main.py ui/impostor-main.ui

src/gen/log_in.py: pre-gen ui/log-in.ui
	pyside2-uic -o src/gen/log_in.py ui/log-in.ui

