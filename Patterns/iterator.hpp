//
// Created by penguinrage on 9/08/17.
//

#ifndef DESIGN_PATTERNS_ITERATOR_HPP
#define DESIGN_PATTERNS_ITERATOR_HPP

#include <iostream>
#include <vector>

namespace patterns {

    class Iterator {
    public:
        virtual const char *next() = 0;

        virtual bool hasNext() = 0;
    };

    class Aggregate {
    public:
        virtual Iterator *getIterator() = 0;

        virtual const char *getSong(int) = 0;

        virtual int size() = 0;
    };

    class PlaylistIterator : public Iterator {
    public:
        PlaylistIterator(Aggregate *aggregate)
                : m_current(0), m_aggregate(aggregate) {}

        const char *next() {
            const char *item = m_aggregate->getSong(m_current);
            m_current++;
            return item;
        }

        bool hasNext() {
            return !(m_current >= m_aggregate->size() || m_aggregate->getSong(m_current) == NULL);
        }

    private:
        Aggregate *m_aggregate;
        int m_current;
    };

    class PlaylistAggregate : public Aggregate {
    public:
        PlaylistAggregate() {}

        void addSong(const char *value) {
            m_playlist.push_back(value);
        }

        Iterator *getIterator() {
            Iterator *iter = new PlaylistIterator(this);
            return iter;
        }

        const char *getSong(int index) {
            return m_playlist[index];
        }

        int size() {
            return (int) m_playlist.size();
        }

    private:
        std::vector<const char *> m_playlist;
    };

}
#endif //DESIGN_PATTERNS_ITERATOR_HPP
