all: enableChromiumFlash.cpp
	clang++ -Wall -Wextra -Wpedantic -std=c++14 -o enableChromiumFlash enableChromiumFlash.cpp
clean:
	$(RM) enableChromiumFlash
