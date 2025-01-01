#include "types.h"
#include <string>

using namespace std;

// PS: I know using a class would make this not vomit inducing, but dunno how to use those and
//      can't be bothered to explain it to my team if I learn how
namespace Logs {
    vector<string> logs(8);

    void addLog(const string& log){

        size_t separator = log.find('\\');
        if (separator == log.npos) {
            // Slide all elem back
            for (size_t i = 0; i < logs.size()-1; ++i)
                logs[i] = logs[i+1];
            // Add log at the end
            logs[logs.size()-1] = log;
        }
        else {
            // weird ass recursive shit?
            addLog(log.substr(0, separator));
            addLog(log.substr(separator+1));
        }

        // This avoids push_back and erase, which fuck up the memory I think? lmao idk
    }

    void setLog(const size_t& pos, const string& log) {
        logs[pos] = log;
    }

    const vector<string>& getLogs() {
        return logs;
    }
}
