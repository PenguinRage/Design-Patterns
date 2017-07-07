#ifndef BUILDER_H
#define BUILDER_H


#include <string>

/**************************************************************************************************
 *   Builder Pattern
 *      Intent
 *          - Separate the construction of a complex object from its representation
 *              so that the same construction process can create different representations.
 *          - Parse a complex representation, create one of several targets.
 **************************************************************************************************/

namespace patterns {
    // Product
    class Hero {
    public:
        ~Hero() {}

        void setClass(std::string type) { m_class = type; }

        void setMagic(int magic) { m_magic = magic; }

        void setStrength(int strength) { m_strength = strength; }

        void setDexterity(int dexterity) { m_dexterity = dexterity; }

        std::string retrieveStats() {
            std::string stats;
            stats.append("--- " + m_class + " ---\n");
            stats.append("strength: " + std::to_string(m_strength) + "\n");
            stats.append("magic: " + std::to_string(m_magic) + "\n");
            stats.append("dexterity: " + std::to_string(m_dexterity) + "\n");
            return stats;
        }

    protected:
        std::string m_class = "hero";

    private:
        int m_magic, m_strength, m_dexterity;
    };

    // Default Hero Builder class
    class HeroBuilder {
    public:
        virtual ~HeroBuilder() {}

        Hero *get_hero() { return m_hero; }

        void createHero() { m_hero = new Hero(); }

        virtual void addClass() = 0;

        virtual void addMagic() = 0;

        virtual void addStrength() = 0;

        virtual void addDexterity() = 0;

    protected:
        Hero *m_hero;
    };

    // Mage Builder
    class MageBuilder : public HeroBuilder {
    public:
        virtual ~MageBuilder() {}

        virtual void addClass() { m_hero->setClass("Wizard"); }

        virtual void addMagic() { m_hero->setMagic(9); }

        virtual void addStrength() { m_hero->setStrength(3); }

        virtual void addDexterity() { m_hero->setDexterity(5); }
    };

    // Warrior Builder
    class WarriorBuilder : public HeroBuilder {
    public:
        virtual ~WarriorBuilder() {}

        virtual void addClass() { m_hero->setClass("Warrior"); }

        virtual void addMagic() { m_hero->setMagic(1); }

        virtual void addStrength() { m_hero->setStrength(9); }

        virtual void addDexterity() { m_hero->setDexterity(5); }
    };

    // Ranger Builder
    class RangerBuilder : public HeroBuilder {
    public:
        virtual ~RangerBuilder() {}

        virtual void addClass() { m_hero->setClass("Ranger"); }

        virtual void addMagic() { m_hero->setMagic(1); }

        virtual void addStrength() { m_hero->setStrength(5); }

        virtual void addDexterity() { m_hero->setDexterity(9); }
    };

    // Director
    class HeroSelector {
    public:
        virtual ~HeroSelector() {}

        void set_hero_builder(HeroBuilder *hero_builder) {
            m_hero_builder = hero_builder;
        }

        Hero *get_hero() { return m_hero_builder->get_hero(); }

        void constructHero() {
            m_hero_builder->createHero();

            // Build the components of our amazing hero
            m_hero_builder->addClass();
            m_hero_builder->addMagic();
            m_hero_builder->addStrength();
            m_hero_builder->addDexterity();
        }

    private:
        HeroBuilder *m_hero_builder;
    };
}


#endif // BUILDER_H
