//
// Created by DengXu on 2016/10/4.
//

#include "BServerPkg.h"
#include <assert.h>

namespace lynetx
{
    BServerPkg::BServerPkg()
    {
        this->m_pkgType = PACKAGE_BYTE;
        this->m_encoder = PACKAGE_GBK;
        this->m_phead = NULL;
        this->m_pbody = NULL;
    }

    BServerPkg::BServerPkg(const PACKAGE_TYPE pkgType, const PACKAGE_ENCODER encoder)
    {
        this->m_pkgType = pkgType;
        this->m_encoder = encoder;
        this->m_phead = NULL;
        this->m_pbody = NULL;
    }

    BServerPkg::BServerPkg(const PACKAGE_TYPE pkgType,
              const PACKAGE_ENCODER encoder, const PACKAGE_HEAD *phead, const PACKAGE_BODY *pbody)
    {
        assert(phead);
        assert(pbody);
        this->m_pkgType = pkgType;
        this->m_encoder = encoder;

        memcpy(this->m_phead, phead, sizeof(*phead));
        memcpy(this->m_pbody, pbody, sizeof(*pbody));
    }

    BServerPkg::~BServerPkg()
    {

    }

    void BServerPkg::SetPackageHead(const PACKAGE_HEAD *phead)
    {
        if (phead)
        {
            memcpy(this->m_phead, phead, sizeof(*phead));
        }
    }

    PACKAGE_HEAD *BServerPkg::GetPackageHead()
    {
        return NULL;
    }

    void BServerPkg::SetPackageBody(const PACKAGE_BODY *pbody)
    {

    }

    PACKAGE_BODY *BServerPkg::GetPackageBody()
    {
        return NULL;
    }

    unsigned char *BServerPkg::GetPackageData() const
    {
        return NULL;
    }

}