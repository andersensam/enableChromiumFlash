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

#ifndef ENABLEFLASH_H
#define ENABLEFLASH_H

typedef enum {
	false = 0, 
	true = 1
} bool;

void requestVersion(char* versionNumber);
void createFile(const char* executionString);
bool verifyInstallation();
bool existingInstallation(const char* chromiumName);
void createInstallation();
void enableFlash();

#endif
