/**
 * Jeremy's Energy Monitor debug class
 * 
 * @author Jeremy Hahn
 * @copyright Make A Byte, inc
 */
#include "Arduino.h"
#include "JEMonDebug.h"

/**
 * Constructor
 */
JEMonDebug::JEMonDebug() {
}

/**
 * Destructor
 */
JEMonDebug::~JEMonDebug() {
}

int free_memory() {

 int free_memory;

 if((int)__brkval == 0)
   free_memory = ((int)&free_memory) - ((int)&__bss_end);
 else
   free_memory = ((int)&free_memory) - ((int)__brkval);

 return free_memory;
}
