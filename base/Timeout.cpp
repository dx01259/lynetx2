//
// Created by DengXu on 2016/10/12.
//

#include "Timeout.h"
#include <limits.h>

namespace lynetx{

    Timeout::Timeout(const unsigned long to)
    {
        this->m_timeout = to;
        this->Reset();
    }

    Timeout::~Timeout() {

    }

    void Timeout::Init(const unsigned long out)
    {
        this->m_timeout = out;
        this->Reset();
    }

    void Timeout::Reset()
    {
        this->m_startTime = this->TimeGetTime();
    }

    unsigned long Timeout::Start()
    {
        return (m_started= true, m_startTime=TimeGetTime());
    }

    void Timeout::SetTimeout(const unsigned long out)
    {
        this->m_timeout = out;
    }

    bool Timeout::IsTimeout() const
    {
        return (Elapse() > this->m_timeout);
    }

    unsigned long Timeout::Elapse() const
    {
        unsigned long end = TimeGetTime();
        return this->m_started ? ((m_startTime<=end) ? (end-m_startTime) : (INT_MAX-end)) : 0;
    }

    unsigned long Timeout::Timeleft()
    {
        return (m_timeout>Elapse() ? m_timeout-Elapse() : 0);
    }

    unsigned long Timeout::TimeGetTime() const
    {
        unsigned long uptime = 0;
        struct timespec spec;
        if (clock_gettime(CLOCK_MONOTONIC, &spec) == 0)
        {
            uptime = spec.tv_sec*1000+spec.tv_nsec/1000000;
        }
        return uptime;
    }

    bool Timeout::SetTimespecLeftNow(struct timespec &spec, const unsigned long &millisecond)
    {
        struct timeval val;
        int ret = gettimeofday(&val, NULL);
        spec.tv_sec = val.tv_sec+millisecond/1000;
        unsigned long minitmp = millisecond % 1000;
        unsigned long usec = val.tv_usec + minitmp*1000;
        spec.tv_sec += usec/(1000000);
        usec %= 1000000;
        spec.tv_nsec = usec*1000;
        spec.tv_sec += (spec.tv_nsec/(1000000000));
        spec.tv_nsec %=1000000000;
        return 0==ret ? true:false;
    }

    struct timespec *Timeout::GetLocalTimespec()
    {
        struct timeval val;
        gettimeofday(&val, NULL);
        m_spec.tv_sec = val.tv_sec;
        m_spec.tv_nsec = val.tv_usec*1000;
        return &m_spec;
    }
}