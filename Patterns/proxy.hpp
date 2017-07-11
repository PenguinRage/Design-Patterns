//
// Created by penguinrage on 11/07/17.
//

#ifndef DESIGN_PATTERNS_PROXY_HPP
#define DESIGN_PATTERNS_PROXY_HPP

namespace patterns {
    // People like to drink but not everyone is legally allowed to drink so we can apply a protection proxy
#define LegalDrinkAge 18

    class Alcoholic {
    public:
        explicit Alcoholic(int age) : m_age(age) {
        }

        int age() { return m_age; }

        void set_age(int age) { m_age = age; }

    private:
        int m_age;
    };

    class Alcohol {
    public:
        virtual ~Alcohol() {}

        virtual bool drink() = 0;
    };

    class Wine : public Alcohol {
    public:
        virtual ~Wine() {}

        virtual bool drink() {
            return true;
        }
    };

    // The Bar has a bartender and he likes to check for id
    class ProxyBar : public Alcohol {
    public:
        explicit ProxyBar(Alcoholic *drinker) : m_drinker(drinker) {
            m_drink = new Wine();
        }

        virtual ~ProxyBar() {
            delete m_drink;
            delete m_drinker;
        }

        virtual bool drink() {
            return m_drinker->age() < LegalDrinkAge ? false : m_drink->drink();
        }

    private:
        Alcohol *m_drink;
        Alcoholic *m_drinker;
    };

}

#endif //DESIGN_PATTERNS_PROXY_HPP
