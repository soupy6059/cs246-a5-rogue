#ifndef __textDisplay__
#define __textDisplay__

#include "subjectObserver.h"

class TextDisplay: public Observer {
public:
    TextDisplay() = default;
    virtual ~TextDisplay() = default;
    
    // observing the game observing the player for printing to std::cout
    virtual void notify(Subject&) override;
};

#endif
