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