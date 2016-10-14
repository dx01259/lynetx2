//
// Created by DengXu on 2016/10/10.
//

#include "BaseFunc.h"
#include "config.h"
#include <dirent.h>
#include <sys/stat.h>
#include <climits>
#include <errno.h>


using namespace std;

namespace lynetx {

    bool BaseFunc::InvalidTime(const BaseTime &time)
    {
        struct tm tmp = time.GetTime();

        if(tmp.tm_year < 1900)
            return true;
        else if(tmp.tm_mon<0 || tmp.tm_mon>11)
            return true;
        else if(tmp.tm_mday<1 || tmp.tm_mday>31)
            return true;
        else if(tmp.tm_hour<0 || tmp.tm_hour>23)
            return true;
        else if(tmp.tm_min<0 || tmp.tm_min>59)
            return true;
        else if(tmp.tm_sec<0 || tmp.tm_sec>60)
            return true;

        return false;
    }

    int BaseFunc::mkdir_p(const char *pathname, mode_t mode)
    {
        char curpath[PATH_MAX]={0};
        char pdir[PATH_MAX] = {0};
        char *saveptr=NULL;
        memcpy(pdir, pathname, strlen(pathname));
        char *ndir = strtok_r(pdir, "/", &saveptr);
        if(NULL != ndir)
        {
            do{
                int curlen = strlen(curpath);
                if(!strncmp(ndir, ".", strlen(ndir)) || !strncmp(ndir, "..", strlen(ndir)))
                {
                    snprintf(&curpath[curlen], PATH_MAX-curlen, "%s/",ndir);
                }
                else
                {
                    if(curpath[-1+curlen] != '/')
                    {
                        snprintf(&curpath[curlen], PATH_MAX-curlen, "/%s", ndir);
                    }
                    else
                        snprintf(&curpath[curlen], PATH_MAX-curlen, "%s", ndir);
                    if(!opendir(curpath))
                    {
                        if(0 != mkdir(curpath, mode))
                        {
#ifdef __MAC_OS__
                            printf("创建目录: %s失败, %s", curpath, strerror(errno));
#elif __LINUX_OS__
                            printf_f("创建目录: %s失败, %s", curpath, strerror(errno));
#endif
                            return errno;
                        }
                    }
                }
            }while((ndir=strtok_r(NULL, "/", &saveptr)));
        }

        return 0;

    }
}