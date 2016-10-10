//
// Created by DengXu on 2016/10/4.
//

#ifndef LYNETX_BSERVERPKG_H
#define LYNETX_BSERVERPKG_H

#include <string>

using namespace std;

namespace lynetx {

    enum PACKAGE_TYPE{PACKAGE_BYTE, PACKAGE_XML, PACKAGE_JSON};
    enum PACKAGE_ENCODER{PACKAGE_GBK, PACKAGE_UTF8, PACKAGE_UNICODE, PACKAGE_ISO8895};

    typedef struct PACKAGE_DATA
    {
        string name;
        string data;
    }PackageData;

    typedef struct PACKAGE_HEAD
    {
        int length;
        PackageData data;
    }PackageHead;

    typedef struct PACKAGE_BODY
    {
        int length;
        PackageData data;
    }PackageBody;

    /**
     * 数据包类主要是用来将发送的数据统一管理起来
     * @param type    数据包类型
     * @param encoder 数据包编码格式
     * @param head    数据包头部
     * @param body    数据包包体
     */
    class BServerPkg
    {
    public:
        BServerPkg();

        /**
         * 设置数据包的类型和编码
         * @param type 指定数据包的类型
         * @param encoder 指定数据包的编码
         * @return
         */
        BServerPkg(const PACKAGE_TYPE pkgType, const PACKAGE_ENCODER encoder);

        /**
         * 设置数据包的类型，编码，数据头部，数据包体
         * @param type 指定数据包的类型
         * @param encoder 指定数据包的编码
         * @param head 指定数据包的头部
         * @param body 指定数据包的包体
         * @return
         */
        BServerPkg(const PACKAGE_TYPE pkgType, const PACKAGE_ENCODER encoder,
                   const PACKAGE_HEAD *phead, const PACKAGE_BODY *pbody);

        virtual ~BServerPkg();

        /**
         * 获取数据包中数据包的类型，例如是PACKAGE_BYTE
         * @return 返回数据包类型
         */
        inline PACKAGE_TYPE GetPackageType(){ return this->m_pkgType; }

        /**
         * 获取数据包的编码格式，例如PACKAGE_GBK
         * @return 返回数据包编码格式
         */
        inline PACKAGE_ENCODER GetPackageEncoder(){ return this->m_encoder; }

        /**
         * 设置数据包头部
         * @param head 数据包的头部
         */
        void SetPackageHead(const PACKAGE_HEAD *phead);

        /**
         * 获取数据包的头部
         * @return 返回数据包的头部
         */
        PACKAGE_HEAD *GetPackageHead();

        /**
         * 设置数据包的包体
         * @param body 返回数据包的包体
         */
        void SetPackageBody(const PACKAGE_BODY *pbody);

        /**
         * 获取数据包的包体
         * @return 返回数据包的包体
         */
        PACKAGE_BODY *GetPackageBody();

        /**
         * 获取发送的数据字符信息
         * @return 返回需要发送的字节流
         */
        unsigned char *GetPackageData() const ;

        /**
         * 设置数据包的字节流长度
         * @param length 数据包字节流长度
         */
        void SetPackageLength(size_t length){ this->m_length = length; }

        /**
         * 获取数据包的字节流长度
         * @return 返回数据包的字节流长度
         */
        inline size_t GetPackageLength() const { return this->m_length; }

    private:
        PACKAGE_TYPE m_pkgType;
        PACKAGE_ENCODER m_encoder;
        PACKAGE_HEAD *m_phead;
        PACKAGE_BODY *m_pbody;
        size_t m_length;
    };
}

#endif //LYNETX_BSERVERPKG_H
