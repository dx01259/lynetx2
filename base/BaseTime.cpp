//
// Created by DengXu on 2016/10/10.
//

#include "BaseTime.h"

namespace lynetx {

    BaseTime::BaseTime(time_t utc)
    {
        gmtime_r(&utc, &this->m_time);
    }

    BaseTime::BaseTime(const int year, const int month, const int day, const int hour, const int minute,
                       const int second)
    {
        if (year > 1900)
        {
            this->m_time.tm_year = year - 1900;
            this->m_time.tm_mon  = month-1;
            this->m_time.tm_mday = day;
            this->m_time.tm_hour = hour;
            this->m_time.tm_min  = minute;
            this->m_time.tm_sec  = second;
        }
    }

    BaseTime::~BaseTime() {

    }

    bool BaseTime::operator==(const BaseTime &other)
    {
        time_t theTime = mktime(&this->m_time);
        time_t othTime = mktime((struct tm *)&(other.m_time));

        return theTime == othTime ? true : false;
    }

    bool BaseTime::operator!=(const BaseTime &other)
    {
        time_t theTime = mktime(&m_time);
        time_t othTime = mktime((struct tm *)&(other.m_time));

        return theTime != othTime ? true:false;
    }

    bool BaseTime::operator>=(const BaseTime &other)
    {
        time_t theTime = mktime(&m_time);
        time_t othTime = mktime((struct tm *)&(other.m_time));

        return theTime >= othTime ? true:false;
    }

    bool BaseTime::operator<=(const BaseTime &other)
    {
        time_t theTime = mktime(&m_time);
        time_t othTime = mktime((struct tm *)&(other.m_time));

        return theTime <= othTime ? true:false;
    }

    bool BaseTime::operator>(const BaseTime &other)
    {
        time_t theTime = mktime(&m_time);
        time_t othTime = mktime((struct tm *)&(other.m_time));

        return theTime > othTime ? true:false;
    }

    bool BaseTime::operator<(const BaseTime &other)
    {
        time_t theTime = mktime(&m_time);
        time_t othTime = mktime((struct tm *)&(other.m_time));

        return theTime < othTime ? true:false;
    }

    time_t BaseTime::GetUtcTime()
    {
        return mktime(&this->m_time);
    }

    struct tm BaseTime::GetTime() const
    {
        return this->m_time;
    }

    void BaseTime::SetCurrentTime()
    {
        time_t now;
        time(&now);
        localtime_r(&now, &m_time);
    }

    string BaseTime::ToString()
    {
        string szResult(20, 0);
        snprintf(&szResult[0], 20,
                 "%04u-%02u-%02u %02u:%02u:%02u",
                 m_time.tm_year+1900, m_time.tm_mon+1, m_time.tm_mday,
                 m_time.tm_hour, m_time.tm_min, m_time.tm_sec
        );
        szResult.resize(19);
        return szResult;
    }

    string BaseTime::ToDayString()
    {
        string szResult(11, 0);
        snprintf(&szResult[0], 11,
                 "%04u-%02u-%02u",
                 m_time.tm_year+1900, m_time.tm_mon+1, m_time.tm_mday
        );
        szResult.resize(10);
        return szResult;
    }
}
