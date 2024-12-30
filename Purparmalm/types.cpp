#include "types.h"
#include <string>

using namespace std;

namespace Logs {
    vector<string> logs = {"LOGS_2078-04-29_23-12-09.2408751",
                           "Initializing...",
                           "Visual sensors: OK",
                           "Motion sensors: OK",
                           "AI: ERROR",
                           "Attempting Troubleshoot... ERROR",
                           "Big boulette detected!",
                           "Attempting Shutdown... ERROR"};

    void addLog(const string& log){
        // Slide all elem back
        for (size_t i = 0; i < logs.size()-1; ++i)
            logs[i] = logs[i+1];
        // Add log at the end
        logs[logs.size()-1] = log;

        // This avoids push_back and erase, which fuck up the memory I think? lmao idk
    }

    const vector<string>& getLogs() {
        return logs;
    }
}
