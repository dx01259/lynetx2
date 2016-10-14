//
// Created by DengXu on 2016/10/10.
//

#ifndef LYNETX_EPOLLSERVICE_H
#define LYNETX_EPOLLSERVICE_H


#include "AsyncSocket.h"

namespace lynetx {

    class EpollService
    {
    public:
        EpollService();

        EpollService(const AsyncSocket sock);


    };
}


#endif //LYNETX_EPOLLSERVICE_H
