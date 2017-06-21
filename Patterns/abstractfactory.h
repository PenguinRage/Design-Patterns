#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <string>
#include <iostream>

/**************************************************************************************************
 *   Abstract Factory Design Pattern
 *      Intent
 *          - Provide an interface for creating families of related or
 *               dependent objects without specifying their concrete classes.
 *          - A hierarchy that encapsulates: many possible "platforms",
 *               and the construction of a suite of "products".
 *          - The new operator considered harmful.
 **************************************************************************************************/

namespace patterns {

class Emote {
public:
    virtual void draw() = 0;
    virtual ~Emote(){}

private:
    std::string emote = "";
};

class Happy : public Emote {
public:
    void draw() {
        std::cout << "(⌒▽⌒)☆" << std::endl;
    }
};

class Sad : public Emote {
public:
    void draw() {
        std::cout << "（´＿｀）" << std::endl;
    }
};

class AbstractFactory
{
public:
    virtual ~AbstractFactory(){};
    virtual Emote* createEmote() = 0;
};

class HappyFactory : public AbstractFactory
{
public:
    // this can be extended out to many different versions of happy
    Emote* createEmote() {
        return new Happy();
    }
};

class SadFactory : public AbstractFactory
{
public:
    // this can be extended out to many different versions of sad
    Emote* createEmote() {
        return new Sad();
    }
};

}
#endif // ABSTRACTFACTORY_H
