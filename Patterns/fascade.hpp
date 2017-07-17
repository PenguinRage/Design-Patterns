//
// Created by penguinrage on 18/07/17.
//

#ifndef DESIGN_PATTERNS_FASCADE_HPP
#define DESIGN_PATTERNS_FASCADE_HPP

// This is a small example of a more complicated possible fascade
namespace patterns {

    class Conman {
    public:
        Conman(int skills) : m_skills(skills) {}

        ~Conman() {}

        void getReady() { m_skills++; }

        int persuasion() { return m_skills; }

    private:
        int m_skills;
    };

    class Robber {
    public:
        Robber(bool ready) : prepped(ready) {}

        ~Robber() {}

        void getReady() { prepped = true; }

        bool blowTheDoors() { return prepped; }

    private:
        bool prepped;
    };

    class Driver {
    public:
        Driver(bool ready) : prepped(ready) {}

        ~Driver() {}

        void arrive() { prepped = true; }

        bool ready() { return prepped; }

    private:
        bool prepped;
    };

    class HeistFacade {
    public:
        HeistFacade(Conman *conman, Robber *robber, Driver *driver) : m_conman(conman), m_robber(robber),
                                                                      m_driver(driver) {}

        ~HeistFacade() {
            delete m_conman;
            delete m_driver;
            delete m_robber;
        }

        void trainTheTeam() {
            m_conman->getReady();
            m_robber->getReady();
            m_driver->arrive();
        }

        bool robTheBank() {
            if (m_conman->persuasion() < 5) return false;
            if (!m_robber->blowTheDoors()) return false;
            if (!m_driver->ready()) return false;

            return true;

        }

    private:
        Conman *m_conman;
        Robber *m_robber;
        Driver *m_driver;
    };
}

#endif //DESIGN_PATTERNS_FASCADE_HPP
