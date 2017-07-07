#ifndef DESIGN_PATTERNS_PROTOTYPE_H
#define DESIGN_PATTERNS_PROTOTYPE_H

#include <string>
#include <random>
#include <map>
#include <boost/functional/hash.hpp>

namespace patterns {

    class Prototype {
    public:
        virtual ~Prototype() {}

        virtual Prototype *Clone() = 0;
    };

    class AI : public Prototype {
    public:
        AI() {
            std::mt19937 rng;
            rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 999999);
            m_ai_id = dist6(rng);

        }

        virtual ~AI() {}

        bool Download() {
            return true;
        }

        virtual Prototype *Clone() {
            AI *t = new AI();
            t->m_ai_id = m_ai_id;
            return t;
        }

        unsigned long GetTorrentID() {
            return m_ai_id;
        }

    private:
        unsigned long m_ai_id;
    };

    class PrototypeHandler {
    public:
        PrototypeHandler() {
            m_prototype_map = new std::map<int, Prototype *>;
        }

        virtual ~PrototypeHandler() {
            delete m_prototype_map;
        }

        void AddPrototype(Prototype *p, int index) {
            (*m_prototype_map)[index] = p;
        }

        Prototype *GetPrototype(int index) {
            return m_prototype_map->at(index)->Clone();
        }

    private:
        std::map<int, Prototype *> *m_prototype_map;
    };

}

#endif //DESIGN_PATTERNS_PROTOTYPE_H
