//
// Created by DengXu on 2016/10/3.
//

#ifndef LYNETX_BASEEXCEPTION_H
#define LYNETX_BASEEXCEPTION_H

#include <execinfo.h>
#include <exception>
#include <string>

using namespace std;

namespace lynetx {

    class BaseException : public exception{

    public:
        BaseException(const string &msg="") throw();

        virtual ~BaseException() throw();

        void Init(const char *file, const char *func, int line);

        virtual string GetClassName() const ;

        virtual string GetMessage() const ;

        const char *what() const throw() ;

        const string & ToString() const ;

        string GetStackTrace() const ;

    protected:
        string m_buf;
        const char *m_FileName;
        const char *m_FuncName;
        long m_Line;
    private:
        enum {MAX_STACK_TRACE_SIZE = 50};
        void *m_StackTrace[MAX_STACK_TRACE_SIZE];
        size_t  m_StackTraceSize;
        mutable string m_What;
    };
}


#endif //LYNETX_BASEEXCEPTION_H
