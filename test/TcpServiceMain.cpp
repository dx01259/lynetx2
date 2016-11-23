//
// Created by DengXu on 27/10/2016.
//

#include "TcpService.h"
#include "LoggerManager.h"

using namespace lynetx;

int main()
{
    try
    {
        int a = 10;
        {
            TcpService service;
            Timeout out = Timeout(1000);
            if(service.Start("127.0.0.1", 8000, 10, 50, out))
            {
                LoggerManager::Instance()->GetSysLogger()->Info(LOGGER_INFO, 20, "系统启动成功！");
            }else {
                LoggerManager::Instance()->GetSysLogger()->Error(LOGGER_ERR, 20, "服务启动失败！");
            }

            sleep(100);

            service.Stop();
        }

        printf("对象销毁\n");
        sleep(10);
    }
    catch (const BaseException &e)
    {
        LoggerManager::Instance()->GetSysLogger()->Error(LOGGER_ERR, strlen(e.what()), e.what());
    }

    return 0;
}