//
// Created by DengXu on 2016/10/5.
//

#ifndef LYNETX_CONFIG_H
#define LYNETX_CONFIG_H

#include <unistd.h>

#ifdef __MAC_OS_X_VERSION_MAX_ALLOWED
#define __MAC_OS__

#elif __LINUX__
#define __LINUX_OS__

#else
#define __WINDOWS_OS__
#endif

#endif //LYNETX_CONFIG_H
