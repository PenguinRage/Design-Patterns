//
// Created by penguinrage on 9/08/17.
//

#ifndef DESIGN_PATTERNS_TEMPLATEMETHOD_HPP
#define DESIGN_PATTERNS_TEMPLATEMETHOD_HPP

#include <iostream>

namespace patterns {
    class Games {
    protected:
        std::string gameName = "NULL";

        virtual void playLevel1() {}

        virtual void playLevel2() {}

        virtual void playLevel3() {}

    public:
        Games(std::string name) : gameName(name) {};

        virtual ~Games() {};

        void playGame() {
            playLevel1();
            playLevel2();
            playLevel3();
        }
    };

    class SonicAdventures : public Games {
    public:
        SonicAdventures() : Games("Sonic Adventures") {}

        virtual void playLevel1() {
            std::cout << "Zone 1 Theme song" << std::endl;
        }

        virtual void playLevel2() {
            std::cout << "Zone 2 Theme song" << std::endl;
        }

        virtual void playLevel3() {
            std::cout << "Zone 3 Theme song" << std::endl;
        }
    };

    class MarioBros : public Games {
    public:
        MarioBros() : Games("Super Mario Brothers") {}

        virtual void playLevel1() {
            std::cout << "Mario theme song" << std::endl;
        }

        virtual void playLevel2() {
            std::cout << "Underground Theme Song" << std::endl;
        }

        virtual void playLevel3() {
            std::cout << "Underwater theme song" << std::endl;
        }
    };
}



#endif //DESIGN_PATTERNS_TEMPLATEMETHOD_HPP
