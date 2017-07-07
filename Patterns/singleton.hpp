#ifndef SINGLETONS_H
#define SINGLETONS_H
#include <string>

/**************************************************************************************************
 *   Singleton Design Pattern
 *      Intent
 *          - Ensure a class has only one instance, and provide a global point of access to it.
 *          - Encapsulated "just-in-time initialization" or "initialization on first use".
 *
 *      Singleton should be considered only if all three of the following criteria are satisfied:
 *          - Ownership of the single instance cannot be reasonably assigned
 *          - Lazy initialization is desirable
 *          - Global access is not otherwise provided for
 **************************************************************************************************/


namespace patterns {

class Singleton {
private:
    Singleton() : name("My lovely singleton pattern") {};
    static Singleton* myInstance;

private:
    std::string name;

public:
    static Singleton* getInstance();

    void setName(std::string name) { this->name = name; }
    std::string getName() { return name; }
};


Singleton* Singleton::myInstance = nullptr;

Singleton* Singleton::getInstance() {
    if (myInstance == nullptr) {
        myInstance = new Singleton();
    }

    return myInstance;
}

}

#endif // SINGLETONS_H
