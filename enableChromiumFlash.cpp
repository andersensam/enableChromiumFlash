#include <iostream>
#include <fstream>
#include "ioclass.cpp"
#include "systemClass.cpp"

int main() {
    
    std::string versionNumber;
    std::string executionString = "system(\"/Applications/Chromium.app/Contents/MacOS/Chromium_ --ppapi-flash-path=/Library/Internet\\\\ Plug-Ins/PepperFlashPlayer/PepperFlashPlayer.plugin/Contents/MacOS/PepperFlashPlayer --ppapi-flash-version=";
    
    io.requestVersion(&versionNumber);
    
    executionString += versionNumber;
    executionString += "\");\n";
    
    io.createFile(&executionString);
    
    std::string chromeName = "/Applications/Chromium.app/Contents/MacOS/Chromium_";
    
    if(!sysF.existingInstallation(&chromeName)) {
        if(!io.verifyInstallation()) {
            std::cout << "Installation cancelled\n";
            return 1;
        }
        sysF.createInstallation();
    }
    sysF.enableFlash();
    
    std::cout << "Installation complete.";
    
    return 0;
}
