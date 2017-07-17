#ifndef DESIGN_PATTERNS_COMPOSITE_HPP
#define DESIGN_PATTERNS_COMPOSITE_HPP

#include <vector>
#include <string>
#include <iostream>


// Iteration through root dirctory

namespace patterns {

    class Component {
    public:
        Component() {}

        ~Component() {}

        virtual void add(Component *com) {}

        virtual void remove(Component *com) {}

        virtual void show(int level) = 0;

        void showEmpty(int level) {
            int count = 4 * level;
            for (int i = 0; i < count; i++) {
                std::cout << " ";
            }

        }
    };

    class Leaf : public Component {
    public:
        Leaf(std::string name) : m_name(name) {}

        ~Leaf() {}

        void show(int level) {
            showEmpty(level);
            std::cout << m_name << std::endl;
        }

    private:
        std::string m_name;
    };

    class Composite : public Component {
    public:

        Composite(std::string name) : m_name(name) {}

        ~Composite() {
            for (std::vector<Component *>::size_type i = 0; i != vec.size(); i++) {
                delete (vec[i]);
            }
        }

        void add(Component *com) { vec.push_back(com); }

        void remove(Component *com) {}

        void show(int level) {
            showEmpty(level);
            std::cout << m_name << std::endl;

            for (std::vector<Component *>::size_type i = 0; i != vec.size(); i++) {
                vec[i]->show(level + 1);
            }
        }

    private:
        std::string m_name;
        std::vector<Component *> vec;
    };

}
#endif //DESIGN_PATTERNS_COMPOSITE_HPP
