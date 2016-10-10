//
// Created by DengXu on 2016/10/5.
//

#include "UtilXml.h"

namespace lynetx {

    UtilXml::UtilXml()
            :m_isOpenFile(false)
    {
    }

    UtilXml::UtilXml(const char *file)
            :m_isOpenFile(false)
    {
        this->Open(file);
    }

    UtilXml::UtilXml(FILE *file)
            :m_isOpenFile(false)
    {
        this->Open(file);
    }

    UtilXml::~UtilXml()
    {
        Close();
    }

    bool UtilXml::Open(const char *file)
    {
        if (m_isOpenFile)
            return true;
        this->m_XmlDocument.LoadFile(file);
        if (this->m_XmlDocument.Error())
        {
            m_isOpenFile = false;
            this->m_XmlDocument.PrintError();
            return false;
        }
        m_isOpenFile = true;
        return true;
    }

    bool UtilXml::Open(FILE *file)
    {
        if (m_isOpenFile)
            return true;
        this->m_XmlDocument.LoadFile(file);
        if (this->m_XmlDocument.Error())
        {
            m_isOpenFile = false;
            this->m_XmlDocument.PrintError();
            return false;
        }
        m_isOpenFile = true;
        return true;
    }

    void UtilXml::Close()
    {
        this->m_XmlDocument.Clear();
        m_isOpenFile = false;
    }

    string & UtilXml::GetElement(const string key, string &value)
    {
        return GetElement(key, value, "");
    }

    string & UtilXml::GetElement(const string key, string &value, const string defValue)
    {
        value = defValue;
        if (this->m_isOpenFile)
        {
            XMLElement *pRoot = this->m_XmlDocument.FirstChildElement(key.c_str());
            if (pRoot)
            {
                value = pRoot->GetText();
            }
        }

        return value;
    }
}