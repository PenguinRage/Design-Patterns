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
        AI *torrent = new AI();
        REQUIRE(torrent->Download());
        PrototypeHandler *manager = new PrototypeHandler();
        manager->AddPrototype(torrent, 0);
        AI *torrent1_clone = dynamic_cast<AI *> (manager->GetPrototype(0));
        REQUIRE(torrent1_clone->GetTorrentID() == torrent->GetTorrentID());
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

        delete xbox;
        delete playstation;
    }
}