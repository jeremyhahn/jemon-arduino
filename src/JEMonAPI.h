#ifndef JEMONAPI_H
#define JEMONAPI_H

#include "Arduino.h"
#include "Ethernet.h"

class JEMonAPI {

    private:
       EthernetClient _client;
       int _ethernetPin;
       int _sdcardPin;
       uint8_t *_ip;
       uint16_t _port;
       char _param[50];
       char _params[500];
       boolean connect();

    public:
        JEMonAPI();
        JEMonAPI(int ethernetPin, int sdcardPin, uint8_t *ip, uint16_t port);
        ~JEMonAPI();
        boolean connected();
        String get(char *resource);
        String post(char *resource, char *params);
        void close();
};

#endif
