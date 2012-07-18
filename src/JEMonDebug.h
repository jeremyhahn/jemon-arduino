#ifndef JEMONDEBUG_H
#define JEMONDEBUG_H

#include "Arduino.h"

class JEMonDebug {

    private:

    public:
        JEMonDebug();
        ~JEMonDebug();
        int free_memory();
};

extern int  __bss_end;
extern int  *__brkval;

#endif
