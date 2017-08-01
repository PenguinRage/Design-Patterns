//
// Created by penguinrage on 20/07/17.
//

#ifndef DESIGN_PATTERNS_MEDIATOR_HPP
#define DESIGN_PATTERNS_MEDIATOR_HPP

#include <iostream>
#include <string>

namespace patterns {
    class Person;

    class Mediator {
    public:
        virtual void Send(const std::string &msg, Person *person) = 0;

        virtual ~Mediator() {}

        void BuildRelation(Person *a, Person *b) {
            m_a = a;
            m_b = b;
        }

    protected:
        Person *m_a;
        Person *m_b;
    };

    class ConcreteMediator : public Mediator {
    public:
        void Send(const std::string &msg, Person *person) {
            if (person == m_a) {
                std::cout << msg << "--Mediator--PersonB" << std::endl;
            } else if (person == m_b) {
                std::cout << msg << "--Mediator--PersonA" << std::endl;
            }
        }
    };

    class Person {
    public:
        Person(Mediator *md) : _md(md) {}

        virtual void SendMessage(const std::string &msg) = 0;

        virtual ~Person() {}

    protected:
        Mediator *_md;
    };

    class ConcretePersonA : public Person {
    public:
        ConcretePersonA(Mediator *md) : Person(md) {}

        void SendMessage(const std::string &msg) {
            _md->Send(msg, this);
        }

    };

    class ConcretePersonB : public Person {
    public:
        ConcretePersonB(Mediator *md) : Person(md) {}

        void SendMessage(const std::string &msg) {
            _md->Send(msg, this);
        }
    };
}

#endif //DESIGN_PATTERNS_MEDIATOR_HPP
