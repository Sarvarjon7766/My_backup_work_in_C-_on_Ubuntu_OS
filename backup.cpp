#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>

// Function to log messages to a file
void logMessage(const std::string& message, const std::string& logFilePath) {
    std::ofstream logFile;
    logFile.open(logFilePath, std::ios_base::app);
    if (logFile.is_open()) {
        std::time_t result = std::time(nullptr);
        logFile << std::asctime(std::localtime(&result)) << " " << message << "\n";
        logFile.close();
    } else {
        std::cerr << "Error opening log file." << std::endl;
    }
}

// Function to toggle automatic backup
void toggleBackup(bool& isBackupEnabled, const std::string& logFilePath) {
    isBackupEnabled = !isBackupEnabled;
    if (isBackupEnabled) {
        logMessage("Backupni yoqish", logFilePath);
    } else {
        logMessage("Backupni o'chirish", logFilePath);
    }
}

int main() {
    bool isBackupEnabled = false;
    std::string logFilePath = "/home/sarvar/SARVAR/backup.log";

    while (true) {
        if (isBackupEnabled) {
            // Execute backup logic here
            // For example, execute rsync command
            std::string sourceFolder = "/home/sarvar/Test/Baza";
            std::string destinationFolder = "/home/sarvar/Test/Backup";
            std::string rsyncCommand = "rsync -avz " + sourceFolder + " " + destinationFolder;
            int result = std::system(rsyncCommand.c_str());

            // Log the result
            if (result == 0) {
                logMessage("Backup successful", logFilePath);
            } else {
                logMessage("Backup failed", logFilePath);
            }

            // Wait for some time before the next backup
            std::this_thread::sleep_for(std::chrono::minutes(10)); // Wait for 10 minutes
        }
    }

    return 0;
}

