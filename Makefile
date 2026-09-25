all: compile

compile:
	mkdir -p builds
	gcc -g -O0 -Wextra  -Iinclude main.c src/*.c -o builds/vc
	ls src/*.c
	ls include/*.h
	echo "compilation compeleted"

debug:
	gdb builds/vc

debug-tui:
	gdb -tui builds/vc

build_final:
	mkdir -p version
	gcc -Wextra -Iinclude main.c src/*.c -o builds/vartc
	ls src/*.c
	ls include/*.h
	echo "compilation compeleted"


