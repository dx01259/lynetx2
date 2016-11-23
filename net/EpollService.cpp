//
// Created by DengXu on 2016/10/10.
//

#include "EpollService.h"
#include "LoggerManager.h"

namespace lynetx {

    EpollService::EpollService():
            m_isStarted(false)
    {
        check_zero(EpollCreate());
    }

    EpollService::EpollService(const AsyncSocket sock):
            m_isStarted(false)
    {
        this->m_AsyncSocket = sock;
        check_zero(EpollCreate());
    }

    EpollService::~EpollService()
    {

    }

    bool EpollService::Start(const char *ip, const short port, const int corePoolSize,
                             const int maxmunPoolSize,const Timeout keepAliveTime)
    {
        if (NULL != ip)
        {
            try {
                this->m_AsyncSocket.InitAsyncSocket(ip, true, port);
                this->m_AsyncSocket.Listen(SOCK_MAX_CONN);
                this->m_pThreadPoolHandle = boost::make_shared<ThreadPool>(corePoolSize, maxmunPoolSize,
                                                                           keepAliveTime, this, CallFunc);

                return true;
            }
            catch (BaseException baseException)
            {
                string sMeesage = baseException.what();
                LoggerManager::Instance()->GetSysLogger()->Error(LOGGER_ERR, sMeesage.size(), sMeesage.c_str());
            }
            catch (exception e)
            {

            }
        }

        return false;
    }

    bool EpollService::Stop()
    {
        this->m_pThreadPoolHandle->DestroyThreadPool();
        return false;
    }

    void *EpollService::CallFunc(void *parameter)
    {
        EpollService *service = (EpollService *)parameter;
        if (service)
        {
            printf("CallFunc begin %u\n", pthread_self());
            service->EpollWait();
            printf("CallFunc end %u\n", pthread_self());
        }
        return NULL;
    }

    void *EpollService::HandleEvent(void *parameter)
    {

        return NULL;
    }

    size_t EpollService::Receive(unsigned char *data, size_t length)
    {
        return 0;
    }

    size_t EpollService::Send(const unsigned char *data, const size_t length)
    {
        return 0;
    }
}