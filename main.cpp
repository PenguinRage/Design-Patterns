// Default Libraries
#include <iostream>
#include <map>

// Testing Parameters
#define CATCH_CONFIG_MAIN

#include "catch.hpp"

// Design Pattern Implementations
#include "Patterns/singleton.hpp"
#include "Patterns/abstractfactory.hpp"
#include "Patterns/builder.hpp"
#include "Patterns/prototype.hpp"
#include "Patterns/bridge.hpp"
#include "Patterns/adapter.hpp"
#include "Patterns/proxy.hpp"

using namespace patterns;
using namespace std;

TEST_CASE("Creational Design patterns", "[Testing Creational Design Patterns]") {
    // SINGLETON TEST CASES
    SECTION("Singleton") {
        auto instance = Singleton::getInstance();
        REQUIRE(instance->getName() == "My lovely singleton pattern");
        instance->setName("Ohh no it could be an Anti Pattern");
        REQUIRE(instance->getName() == "Ohh no it could be an Anti Pattern");
        instance = instance->getInstance();
        REQUIRE(instance->getName() != "My lovely singleton pattern");
        delete instance;
    }

    // ABSTRACT FACTORY TEST CASES
    SECTION("Abstract Factory") {
        AbstractFactory *factory = new HappyFactory();
        Emote *expression = factory->createEmote();

        REQUIRE(expression->draw() == "(⌒▽⌒)☆");

        delete expression;
        delete factory;

        factory = new SadFactory();
        expression = factory->createEmote();
        expression->draw();

        REQUIRE(expression->draw() == "（´＿｀）");

        delete expression;
        delete factory;
    }

    // BUILDER TEST CASES
    SECTION("Builder") {
        HeroSelector *heroSelector = new HeroSelector();
        HeroBuilder *magebuilder = new MageBuilder();
        HeroBuilder *warriorbuilder = new WarriorBuilder();

        heroSelector->set_hero_builder(magebuilder);
        heroSelector->constructHero();

        Hero *magi = heroSelector->get_hero();
        REQUIRE(magi->retrieveStats() == "--- Wizard ---\n"
                "strength: 3\n"
                "magic: 9\n"
                "dexterity: 5\n");

        heroSelector->set_hero_builder(warriorbuilder);
        heroSelector->constructHero();


        Hero *gladiator = heroSelector->get_hero();
        REQUIRE(gladiator->retrieveStats() != "--- Wizard ---\n"
                "strength: 3\n"
                "magic: 9\n"
                "dexterity: 5\n");
        REQUIRE(gladiator->retrieveStats() == "--- Warrior ---\n"
                "strength: 9\n"
                "magic: 1\n"
                "dexterity: 5\n");

        delete gladiator;
        delete magi;
        delete heroSelector;
        delete magebuilder;
        delete warriorbuilder;
    }

    SECTION("Prototype") {
        Virus *torrent = new Virus();
        REQUIRE(torrent->Download());
        PrototypeHandler *manager = new PrototypeHandler();
        manager->AddPrototype(torrent, 0);
        Virus *virus_clone = dynamic_cast<Virus *> (manager->GetPrototype(0));
        REQUIRE(virus_clone->GetVirusID() == torrent->GetVirusID());
    }


}

TEST_CASE("Behavioural Design Patterns", "[Testing Behavioural Design Patterns]") {

}

TEST_CASE("Structural Design Patterns", "[Testing Structural Design Patterns]") {
    SECTION("Bridge") {

        GameConsole *xbox = new Xbox(new Bioshock(), "Bioshock Infinite");
        GameConsole *playstation = new Xbox(new Fable(), "Fable 3");

        REQUIRE(xbox->play() == "Bioshock Infinite");
        REQUIRE(playstation->play() == "Fable 3");

        xbox->load(new Fable, "Fable 2");
        playstation->load(new Bioshock, "Bioshock");
        REQUIRE(playstation->play() == "Bioshock");

        delete xbox;
        delete playstation;
    }
    SECTION("Adapter") {
        Manjaro *my_dist = new ManjaroAdapter(
                "CPU~Dual core Intel Core i7-3517U (-HT-MCP-) speed/max~859/3000 MHz Kernel~4.9.31-1-MANJARO x86_64 Up~6:15 Mem~3908.2/7611.7MB HDD~256.1GB(13.4% used) Procs~191 Client~Shell inxi~2.3.9 ");
        REQUIRE(my_dist->showLogo() ==
                "CPU~Dual core Intel Core i7-3517U (-HT-MCP-) speed/max~859/3000 MHz Kernel~4.9.31-1-MANJARO x86_64 Up~6:15 Mem~3908.2/7611.7MB HDD~256.1GB(13.4% used) Procs~191 Client~Shell inxi~2.3.9 ");
    }
    SECTION("Protection Proxy") {
        Alcoholic *angst_teen = new Alcoholic(15);
        Alcohol *drink = new ProxyBar(angst_teen);
        REQUIRE(!drink->drink());
        angst_teen->set_age(19);
        REQUIRE(drink->drink());
        delete drink;
    }

    SECTION("Decorator") {

    }


}