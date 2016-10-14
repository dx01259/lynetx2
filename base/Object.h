//
// Created by DengXu on 2016/10/11.
//

#ifndef LYNETX_OBJECT_H
#define LYNETX_OBJECT_H

namespace lynetx {

    class Object
    {
    public:
        Object();

    protected:
        virtual void *process(void *param) = 0;
    };
}
#endif //LYNETX_OBJECT_H
