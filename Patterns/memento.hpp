//
// Created by penguinrage on 26/07/17.
//

#ifndef DESIGN_PATTERNS_MEMENTO_HPP
#define DESIGN_PATTERNS_MEMENTO_HPP

#include <iostream>
#include <vector>

namespace patterns {

    template<typename T>
    class GitMemento {
    public:
        virtual ~GitMemento() {}

        T state() const { return m_state; }

        void set_state(T state) { m_state = state; }

    private:
        T m_state;
    };

    template<typename T>
    class GitOriginator {
    public:
        virtual ~GitOriginator() {}

        GitMemento<T> *CreateMemento() {
            GitMemento<T> *m = new GitMemento<T>();
            m->set_state(m_state);
            return m;
        }

        void SetMemento(GitMemento<T> *m) {
            m_state = m->state();
        }

        void set_state(const T &state) { m_state = state; }

        T get_State() const { return m_state; }

    private:
        T m_state;
    };

    template<typename T>
    class GitCaretaker {
    public:
        virtual ~GitCaretaker() {}

        void COMMIT(GitOriginator<T> *orig) {
            m_mementos.push_back(orig->CreateMemento());
        }

        void ROLLBACK(GitOriginator<T> *orig, int state_number) {
            orig->SetMemento(m_mementos[state_number]);
        }

    private:
        std::vector<GitMemento<T> *> m_mementos;
    };
}
#endif //DESIGN_PATTERNS_MEMENTO_HPP
