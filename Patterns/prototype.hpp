#ifndef DESIGN_PATTERNS_PROTOTYPE_H
#define DESIGN_PATTERNS_PROTOTYPE_H

#include <string>
#include <random>

namespace patterns {

    class Prototype {
    public:
        virtual ~Prototype() {}

        virtual Prototype *Clone() = 0;
    };

    class Torrent : public Prototype {
    public:
        Torrent() {
            std::mt19937 rng;
            rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 999999);
            m_torrent_id = dist6(rng);

        }

        virtual ~Torrent() {}

        bool Download() {
            return true;
        }

        virtual Prototype *Clone() {
            Torrent *t = new Torrent();
            t->m_torrent_id = m_torrent_id;
            return t;
        }

        unsigned long GetTorrentID() {
            return m_torrent_id;
        }

    private:
        unsigned long m_torrent_id;
    };


}

#endif //DESIGN_PATTERNS_PROTOTYPE_H
