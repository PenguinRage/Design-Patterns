//
// Created by penguinrage on 25/08/17.
//

#ifndef DESIGN_PATTERNS_VISITOR_HPP
#define DESIGN_PATTERNS_VISITOR_HPP

#include <iostream>

namespace patterns {
    class Operation;

    class Music {
    public:
        virtual void plays(Operation *op) = 0;
    };

    class Piano;

    class Violin;

    class Operation {
    public:
        virtual void playPiano(Piano *piano) = 0;

        virtual void playViolin(Violin *violin) = 0;
    };

    class Sound : public Operation {
    public:
        void playViolin(Violin *violin) {
            std::cout << "Violin: ♪♫•*¨*•.¸¸♫♪" << std::endl;
        }

        void playPiano(Piano *piano) {
            std::cout << "Piano: ♪♫•*¨*•.¸¸♫♪♪♫•*¨*•.¸¸♫♪♪♫•*¨*•.¸¸♫♪♪♫•*¨*•.¸¸♫♪" << std::endl;
        }
    };

    class Violin : public Music {
    public:
        void plays(Operation *op) {
            op->playViolin(this);
        }
    };

    class Piano : public Music {
    public:
        void plays(Operation *op) {
            op->playPiano(this);
        }
    };
}
#endif //DESIGN_PATTERNS_VISITOR_HPP
