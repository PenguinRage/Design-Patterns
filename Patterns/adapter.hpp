#ifndef DESIGN_PATTERNS_ADAPTER_HPP
#define DESIGN_PATTERNS_ADAPTER_HPP

#include <string>

namespace patterns {
    // Manjaro is a rebrand of the Arch Distro
    class Manjaro {
    public:
        virtual std::string showLogo() = 0;

    };

    // Arch Linux Distro is always frequently updating stuff that could lead to breaks
    class Arch {
    public:
        Arch(std::string name, std::string des = "AHHH Not Stable") : m_name(name), m_description(des) {}

        std::string getName() {
            return m_name;
        }

    private:
        std::string m_name = "Some Arch Distro";
        std::string m_description;
    };

    // Let's reskin Arch to a manjaro distro
    class ManjaroAdapter : public Manjaro, private Arch {
    public:
        ManjaroAdapter(std::string name) : Arch(name, "Ohhh better stability") {}

        virtual std::string showLogo() {
            return getName();
        }
    };

}

#endif //DESIGN_PATTERNS_ADAPTER_HPP
