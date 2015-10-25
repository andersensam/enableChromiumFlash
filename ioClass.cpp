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