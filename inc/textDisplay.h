#ifndef __textDisplay__
#define __textDisplay__

#include "subjectObserver.h"

class TextDisplay: public Observer {
public:
    TextDisplay() = default;
    virtual ~TextDisplay() = default;
    virtual void notify(Subject&) override;  
};

#endif
