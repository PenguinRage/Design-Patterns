#ifndef DESIGN_PATTERNS_DECORATOR_HPP
#define DESIGN_PATTERNS_DECORATOR_HPP
// Steam sells and plays Witcher3 with additional DLC Hearts of Stone and Blood and Wine
#include <string>

namespace patterns {

    class SteamGame {
    public:
        SteamGame() {}

        virtual ~SteamGame() {}

        virtual bool play() = 0;

        virtual double cost() = 0;
    };

    class Witcher3 : public SteamGame {
    public:
        Witcher3() {}

        ~Witcher3() {}

        bool play() {
            return true;
        }

        double cost() { return 39.99; }
    };

    class SteamGameDecorator : public SteamGame {
    private:
        SteamGame *m_videogame;

    public:
        SteamGameDecorator(SteamGame *videogame) : m_videogame(videogame) {};

        ~SteamGameDecorator() { delete m_videogame; };

        virtual bool play() { m_videogame->play(); };

        virtual double cost() { return m_videogame->cost(); };
    };

    class BloodAndWine : public SteamGameDecorator {
    public:
        BloodAndWine(SteamGame *videogame) : SteamGameDecorator(videogame) {};

        double cost() { return SteamGameDecorator::cost() + 14.99; }
    };

    class HeartOfStone : public SteamGameDecorator {
    public:
        HeartOfStone(SteamGame *videogame) : SteamGameDecorator(videogame) {};

        double cost() { return SteamGameDecorator::cost() + 9.99; }
    };

}

#endif //DESIGN_PATTERNS_DECORATOR_HPP
