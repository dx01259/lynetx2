//
// Created by DengXu on 27/10/2016.
//

#ifndef LYNETX_TCPSERVICE_H
#define LYNETX_TCPSERVICE_H

#include "EpollService.h"

namespace lynetx {

    class TcpService :
            public EpollService
    {
    public:
        TcpService();
        virtual ~TcpService();

    protected:
        void *HandleEvent(void *parameter);
    };
}
#endif //LYNETX_TCPSERVICE_H
