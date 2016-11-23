//
// Created by DengXu on 2016/10/5.
//

#ifndef LYNETX_UTILXML_H
#define LYNETX_UTILXML_H

#include "tinyxml2/tinyxml2.h"
#include <stdio.h>
#include <string>

using namespace std;
using namespace tinyxml2;

namespace lynetx {

    class UtilXml
    {
    public:
        /**
         * 此结构体只创建对象，并没有打开XML文件
         * 需要调用Open函数，打开相关XML文件。
         * @return 无
         */
        UtilXml();

        /**
         * 此结构体函数，打开XML文件
         * @param file XML文件的路径
         * @return
         */
        UtilXml(const char *file);

        /**
         * 此结构体函数，打开指向XML文件的文件指针
         * @param file 指向XML文件的文件指针
         * @return
         */
        UtilXml(FILE *file);

        /**
         * 析构函数，释放对应的资源空间。
         */
        virtual ~UtilXml();

        /**
         * 打开指向XML文件
         * @param file 指向XML文件的路径
         * @return 成功返回true，失败返回false
         */
        bool Open(const char *file);

        /**
         * 打开指向XML文件
         * @param file 指向打开XML文件的指针
         * @return 成功返回true，失败返回false
         */
        bool Open(FILE *file);

        /**
         * 获取读取的XML文件的节点值
         * @param key 节点名称
         * @param value 节点返回的值
         * @return 返回节点的值
         */
        string & GetElement(const string key, string &value);

        /**
         * 获取读取的XML文件的节点值
         * @param key 节点名称
         * @param value 节点返回的值
         * @param defValue 返回节点的值
         * @return
         */
        string & GetElement(const string key, string &value, const string defValue);

        /**
         * 释放系统占用的资源
         */
        void Close();

    protected:
        XMLDocument m_XmlDocument;
    private:
        bool m_isOpenFile;
    };
}


#endif //LYNETX_UTILXML_H
