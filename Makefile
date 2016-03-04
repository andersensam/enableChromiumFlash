MKDIR_P = mkdir -p
RM_RF = rm -rf

all: enableChromiumFlash.c
	$(MKDIR_P) x86_64
	clang -Wall -Wextra -Wpedantic -std=c99 -o x86_64/enableChromiumFlash enableChromiumFlash.c
clean:
	$(RM_RF) x86_64
	$(RM) chromium.c
