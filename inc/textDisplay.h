#ifndef __textDisplay__
#define __textDisplay__

#include <ostream>

#include "grid.h"

class TextDisplay final: public Observer {
    std::vector<std::vector<char>> theDisplay;
    public:
    TextDisplay(const Grid &grid);
    virtual void notify(Subject&) override;
    void notify(Grid&);
    virtual ~TextDisplay() = default;
    friend std::ostream &operator<<(std::ostream&,const TextDisplay&);
};

std::ostream &operator<<(std::ostream&,const TextDisplay&);

#endif
