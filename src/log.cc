#include "log.h"

#include <map>
#include <memory>

using namespace std;

static map<string,unique_ptr<ofstream>> loggingFiles;

void initLogFile(string fileName) {
    loggingFiles[fileName] = make_unique<ofstream>(string{"log/"} + fileName + string{".log"});
}

void Log::initLogs() {
    initLogFile("neighbourCount");
    initLogFile("bug");
}

ofstream &Log::getLogFile(string fileName) {
    return *loggingFiles.at(fileName);
}
