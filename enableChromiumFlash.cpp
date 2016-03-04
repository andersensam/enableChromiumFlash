#include <iostream>
#include <fstream>
#include "ioclass.cpp"
#include "systemClass.cpp"

class io {
public:
    void requestVersion(std::string* versionNumber) {
        std::cout << "Enter a Flash version number: ";
        std::cin >> *versionNumber;
    }
    void createFile(const std::string* executionString) {
        std::ofstream sourceFile;
        sourceFile.open("chromium.cpp");
        sourceFile << "#include <iostream>\n";
        sourceFile << "int main() {\n";
        sourceFile << *executionString;
        sourceFile << "return 0;\n";
        sourceFile << "}\n";
        sourceFile.close();
        
    }
    bool verifyInstallation() {
        std::cout << "This version of Chromium has not yet been patched for Flash. Do you want to continue? [Y/N]: ";
        std::cin >> vInstall;
        if (vInstall == 'Y' || vInstall == 'y') {
            return true;
        }
        else {
            return false;
        }
    }
private:
    char vInstall;
} io;

class systemFunctions {
public:
    bool existingInstallation(std::string* chromeName) {
        std::ifstream infile(*chromeName);
        return infile.good();
    }
    void createInstallation() {
        system("mv /Applications/Chromium.app/Contents/MacOS/Chromium /Applications/Chromium.app/Contents/MacOS/Chromium_");
    }
    void enableFlash() {
        system("clang++ -Wall -Wextra -Wpedantic -std=c++14 chromium.cpp -o /Applications/Chromium.app/Contents/MacOS/Chromium");
    }
} sysF;

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
