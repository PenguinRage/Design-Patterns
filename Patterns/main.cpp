#include "singleton.hpp"
#include "abstractfactory.hpp"
#include "builder.hpp"

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

// Builder
bool builderCaseTest() // This method acts as a director for the builder test cases
{
    // builder testcases
    // simple usage
    RGB hot_pink = RGB::Builder().setRed(255).setGreen(105).setBlue(180).build();
    hot_pink.print(); // test p1

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
    if (builderCaseTest()) {
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
