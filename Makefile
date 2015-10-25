MKDIR_P = mkdir -p
RM_RF = rm -rf

all: enableChromiumFlash.cpp
	$(MKDIR_P) x86_64
	clang++ -Wall -Wextra -Wpedantic -std=c++14 -o x86_64/enableChromiumFlash enableChromiumFlash.cpp
clean:
	$(RM_RF) x86_64
	$(RM) chromium.cpp
