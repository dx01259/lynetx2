//
// Created by DengXu on 2016/10/13.
//

#ifndef LYNETX_TMAP_H
#define LYNETX_TMAP_H

#include "Mutex.h"
#include<map>
#include<vector>

using namespace std;

namespace lynetx{

    template <class K, class V, class MUTEX_TYPE=THREAD_MUTEX>
    class TMap {
    public:
        TMap() {}

        virtual ~TMap() {}

    public:
        int find(const K &key, V &value) {
            AUTO_GUARD(g, MUTEX_TYPE, m_Lock);

            typename map<K, V>::iterator iter;
            iter = vmap.find(key);
            if (iter == vmap.end())
                return -1;
            value = iter->second;
            return 0;
        }

        V findex(const K &key, const V &value) {
            AUTO_GUARD(g, MUTEX_TYPE, m_Lock);

            try {
                typename map<K, V>::iterator iter;
                iter = vmap.find(key);
                if (iter != vmap.end()) {
                    return iter->second;
                } else {
                    return vmap[key] = value;
                }
            }
            catch (...) {
            }

            throw "key not found in map";
        }

        int set(const K &key, const V &value) {
            AUTO_GUARD(g, MUTEX_TYPE, m_Lock);

            try {
                vmap[key] = value;
                return 0;
            }
            catch (...) {
                return -1;
            }
        }

        size_t get_all_values(vector<V> &values) {
            AUTO_GUARD(g, MUTEX_TYPE, m_Lock);

            try {
                values.clear();
                values.reserve(vmap.size());
                typename map<K, V>::iterator iter;
                iter = vmap.begin();
                for (; iter != vmap.end(); ++iter) {
                    values.push_back(iter->second);
                }
                return values.size();
            }
            catch (...) {
                return -1;
            }

        }

        void remove(const K &key) {
            AUTO_GUARD(g, MUTEX_TYPE, m_Lock);

            try {
                typename map<K, V>::iterator iter;
                iter = vmap.find(key);
                if (iter != vmap.end())
                    vmap.erase(iter);
            }
            catch (...) {
                return;
            }
        }

        size_t size() {
            AUTO_GUARD(g, MUTEX_TYPE, m_Lock);

            return vmap.size();
        }

        void clear() {
            AUTO_GUARD(g, MUTEX_TYPE, m_Lock);

            try {
                vmap.clear();
            }
            catch (...) {
                return;
            }
        }

    private:
        map<K, V> vmap;
        MUTEX_TYPE m_Lock;
    };
}

#endif //LYNETX_TMAP_H
