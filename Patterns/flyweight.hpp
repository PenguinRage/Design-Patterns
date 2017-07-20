//
// Created by penguinrage on 21/07/17.
//

#ifndef DESIGN_PATTERNS_FLYWEIGHT_HPP
#define DESIGN_PATTERNS_FLYWEIGHT_HPP

#include<string>
#include<map>
#include <iostream>

namespace patterns {

    class ASCII {
    public:
        virtual void Display() { std::cout << m_art << std::endl; }

        virtual std::string getName() { return m_name; }

    protected:
        std::string m_name;
        std::string m_art;
    };

    class COMP_ASCII : public ASCII {
    public:
        COMP_ASCII() {
            m_name = 'Computer Ascii';
            m_art = "▐▓█▀▀▀▀▀▀▀▀▀█▓▌░▄▄▄▄▄░\n"
                    "▐▓█░░▀░░▀▄░░█▓▌░█▄▄▄█░\n"
                    "▐▓█░░▄░░▄▀░░█▓▌░█▄▄▄█░\n"
                    "▐▓█▄▄▄▄▄▄▄▄▄█▓▌░█████░\n"
                    "░░░░▄▄███▄▄░░░░░█████░";
        }
    };

    class UFO_ASCII : public ASCII {
    public:
        UFO_ASCII() {
            m_name = 'UFO Ascii';
            m_art = "▒▒▄▀▀▀▀▀▄▒▒▒▒▒▄▄▄▄▄▒▒▒\n"
                    "▒▐░▄░░░▄░▌▒▒▄█▄█▄█▄█▄▒\n"
                    "▒▐░▀▀░▀▀░▌▒▒▒▒▒░░░▒▒▒▒\n"
                    "▒▒▀▄░═░▄▀▒▒▒▒▒▒░░░▒▒▒▒\n"
                    "▒▒▐░▀▄▀░▌▒▒▒▒▒▒░░░▒▒▒▒";
        }
    };

    class TV_ASCII : public ASCII {
    public:
        TV_ASCII() {
            m_name = 'TV Ascii';
            m_art = "░▀▄░░▄▀\n"
                    "▄▄▄██▄▄▄▄▄░▀█▀▐░▌\n"
                    "█▒░▒░▒░█▀█░░█░▐░▌\n"
                    "█░▒░▒░▒█▀█░░█░░█\n"
                    "█▄▄▄▄▄▄███══════";
        }
    };

    // The 'FlyweightFactory' class
    class ASCIIFactory {

    public:
        virtual ~ASCIIFactory() {
            while (!m_ascii_art.empty()) {
                std::map<char, ASCII *>::iterator it = m_ascii_art.begin();
                delete it->second;
                m_ascii_art.erase(it);
            }
        }

        ASCII *GetArt(char key) {
            ASCII *art = NULL;
            if (m_ascii_art.find(key) != m_ascii_art.end()) {
                art = m_ascii_art[key];
            } else {
                switch (key) {
                    case 'C':
                        art = new COMP_ASCII();
                        break;
                    case 'U':
                        art = new UFO_ASCII();
                        break;
                        //...
                    case 'T':
                        art = new TV_ASCII();
                        break;
                    default:
                        std::cout << "Not Implemented" << std::endl;
                        throw ("Not Implemented");
                }
                m_ascii_art[key] = art;
            }
            return art;
        }

    private:
        std::map<char, ASCII *> m_ascii_art;
    };
}

#endif //DESIGN_PATTERNS_FLYWEIGHT_HPP
