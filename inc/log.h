#ifndef __log__
#define __log__

#include <string>
#include <fstream>

namespace Log {
    void initLogs();
    std::ofstream &getLogFile(std::string fileName);
};

#endif
