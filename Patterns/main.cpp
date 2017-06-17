#include <QCoreApplication>
#include "singleton.h"
#include <string>
#include <iostream>

using namespace patterns;
using namespace std;

int main(int argc, char *argv[])
{
    // Singleton test casing
    auto instance = Singleton::getInstance();
    cout << instance->getName() << endl;



    QCoreApplication a(argc, argv);
    return a.exec();
}
