#include "singleton.h"
#include "abstractfactory.h"

#include <string>
#include <iostream>

using namespace patterns;
using namespace std;

// Singletons
bool singletonsCaseTest()
{
    // Singleton test casing
    auto instance = Singleton::getInstance();
    cout << instance->getName() << " \033[1;32mOK\033[0m" << endl;
    delete instance;
    return 0;
}


// Abstract Factory
bool abstractFactoryCaseTest()
{
    // Abstract Factory test casing
    AbstractFactory* factory = new HappyFactory();
    Emote* expression = factory->createEmote();
    expression->draw();

    delete expression;
    delete factory;

    factory = new SadFactory();
    expression = factory->createEmote();
    expression->draw();

    delete expression;
    delete factory;
    return 0;
}

int main()
{
    int numberOfTestsFailed = 0;

    if (singletonsCaseTest()) {
        numberOfTestsFailed++;
    }
    if (abstractFactoryCaseTest()) {
        numberOfTestsFailed++;
    }
    if (0 == numberOfTestsFailed)
    {
        std::cout << "All Tests Passed!" << std::endl;
    }
    else
    {
        std::cout << numberOfTestsFailed << " Tests Failed" << std::endl;
    }
}
