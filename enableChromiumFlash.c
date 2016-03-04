/*
 * Project: enableChromiumFlash
 * Author: Sam Andersen
 * Email: samstext@gmail.com
 * Version: 20160304
 *
 * enableChromiumFlash: small utility for enabling the PPAPI flash plugin
 * for Chromium on OS X. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enableChromiumFlash.h"

/* Check desired Flash version for installation */
void requestVersion(char* versionNumber) {
	printf("Enter a flash version number: ");
	scanf("%s", versionNumber);
	while(getchar() != '\n');
}

/* Create the C file that will serve as the drop-in executable */
void createFile(const char* executionString) {
	FILE* sourceFile;
	sourceFile = fopen("chromium.c", "w");
	fprintf(sourceFile, "#include <stdlib.h>\n\n");
	fprintf(sourceFile, "int main(void) {\n");
	fprintf(sourceFile, "	%s", executionString);
	fprintf(sourceFile, "	return 0;\n");
	fprintf(sourceFile, "}\n");
	fclose(sourceFile);
}

/* Verify that the user does want to install */
bool verifyInstallation(bool previousInstall) {
	char vInstall;
	if (!previousInstall) {
		printf("This version of Chromium has not yet been patched for Flash. Do you want to continue? [Y/N]: ");
	}
	else {
		printf("Do you want to continue with the installation? [Y/N]: ");
	}
	scanf("%c", &vInstall);
	if (vInstall == 'Y' || vInstall == 'y') {
		return true;
	}
	else {
		return false;
	}
}

/* Check to see if the file already exists, indicating a previous installation */
bool existingInstallation(const char* chromiumName) {
	FILE* chromeExec;
	chromeExec = fopen(chromiumName, "r");
	if (chromeExec == NULL) {
		return false;
	}
	else {
		fclose(chromeExec);
		return true;
	}
}

/* Move the old executable, Chromium --> Chromium_ */
void createInstallation() {
        system("mv /Applications/Chromium.app/Contents/MacOS/Chromium /Applications/Chromium.app/Contents/MacOS/Chromium_");
}

/* Compile the replacement executable */
void enableFlash() {
	system("clang -std=c99 chromium.c -o /Applications/Chromium.app/Contents/MacOS/Chromium");
}

int main(void) {
	bool vInstall = false;
	char* versionNumber;
	char* executionString;
	char* executionBase = "system(\"/Applications/Chromium.app/Contents/MacOS/Chromium_ --ppapi-flash-path=/Library/Internet\\\\ Plug-Ins/PepperFlashPlayer/PepperFlashPlayer.plugin/Contents/MacOS/PepperFlashPlayer --ppapi-flash-version=";
	char* executionTail = "\");\n";
	char* chromiumName = "/Applications/Chromium.app/Contents/MacOS/Chromium_";
	if (!existingInstallation(chromiumName)) {
		vInstall = verifyInstallation(false);
		if (!vInstall) {
			fprintf(stderr, "Installation declined\n");
			exit(1);
		}
	}
	versionNumber = calloc(250, sizeof(char));
	requestVersion(versionNumber);
	executionString = calloc(250, sizeof(char));
	strcat(executionString, executionBase);
	strcat(executionString, versionNumber);
	strcat(executionString, executionTail);
	strcat(executionString, "\0");
	createFile(executionString);
	vInstall = verifyInstallation(true);
	if (!vInstall) {
		fprintf(stderr, "Installation cancelled\n");
		exit(1);
	}
	if (!existingInstallation(chromiumName)) {
		createInstallation();
	}
	enableFlash();
	free(versionNumber);
	free(executionString);
	return 0;
} 
