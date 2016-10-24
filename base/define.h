//
// Created by DengXu on 2016/10/11.
//

#ifndef LYNETX_DEFINE_H
#define LYNETX_DEFINE_H

#include "config.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define check_zero(retval) \
do{\
	if(0 != retval)\
	{\
		printf("参数返回的值为:%d,系统错误信息:%s", retval, strerror(errno));\
		exit(0);\
	}\
}while(0)

#define check_nozero(retval) \
do{\
	if(0 == retval)\
	{\
		printf("参数返回的值为:%d,系统错误信息:%s", retval, strerror(errno));\
		exit(0);\
	}\
}while(0)

#define delete_memory(ptr)\
do{\
	if(ptr)\
	{\
		delete ptr;\
		ptr = NULL;\
	}\
}while(0)

#define delete_arrmemory(ptr)\
do{\
	if(ptr)\
	{\
		delete[] ptr;\
		ptr = NULL;\
	}\
}while(0)

#define free_memory(ptr)\
do{\
	if(ptr)\
	{\
		free(ptr);\
		ptr = NULL;\
	}\
}while(0)

typedef void (*callback_func)(void *);

#endif //LYNETX_DEFINE_H
