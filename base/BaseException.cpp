//
// Created by DengXu on 2016/10/3.
//

#include "BaseException.h"
#include <sstream>
#include <cxxabi.h>

using namespace std;

namespace lynetx {

    BaseException::BaseException(const string &msg) throw()
            :m_buf(msg),
             m_FileName("<unknown file>"),
             m_FuncName("<unknown func>"),
             m_Line(-1),
             m_StackTraceSize(0)
    {}

    BaseException::~BaseException() throw()
    {

    }

    void BaseException::Init(const char *file, const char *func, int line)
    {
        this->m_FileName = file;
        this->m_FuncName = func;
        this->m_Line     = line;
        this->m_StackTraceSize = backtrace(m_StackTrace, MAX_STACK_TRACE_SIZE);
    }

    string BaseException::GetClassName() const
    {
        return std::string("BaseException");
    }

    string BaseException::GetMessage() const
    {
        return this->m_buf;
    }

    const char *BaseException::what() const throw()
    {
        return ToString().c_str();
    }

    const string &BaseException::ToString() const
    {
        if (this->m_What.empty())
        {
            stringstream sstr("");
            if (m_Line > 0)
            {
                sstr << m_FileName<<"("<<m_Line<<")";
            }
            sstr<<":"<<GetClassName();
            if (!GetMessage().empty())
            {
                sstr<<":"<<GetMessage();
            }
            sstr<<"\nStack Trace:\n";
            sstr<<GetStackTrace();
            m_What = sstr.str();
        }
        return this->m_What;
    }

    string BaseException::GetStackTrace() const
    {
        if (m_StackTraceSize == 0)
            return "<No stack trace>\n";

        char  **pString = backtrace_symbols(m_StackTrace, 10);
        if (NULL == pString)
            return "<Unkown error: backtrace_symbols returned NULL>\n";
        string result;
        for (size_t i = 0; i < m_StackTraceSize; ++i)
        {
            string mName = pString[i];
            string::size_type begin = mName.find('(');
            string::size_type end   = mName.rfind('+', begin);
            if (begin == string::npos || end == string::npos)
            {
                result += mName;
                result += '\n';
                continue;
            }
            ++begin;
            int status;
            char *s = abi::__cxa_demangle(mName.substr(begin, end-begin).c_str(), NULL, 0, &status);

            if (0 != status)
            {
                result += mName;
                result += '\n';
                continue;
            }

            string dName(s);
            free(s);

            result += mName.substr(0, begin);
            result += dName;
            result += mName.substr(end);
            result += '\n';
        }
        free(pString);
        return std::string(result);
    }
}

