// Default Libraries
#include <iostream>
#include <map>
#include <sstream>
#include <time.h>
#include "Patterns/command.hpp"

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
#include "Patterns/decorator.hpp"
#include "Patterns/composite.hpp"
#include "Patterns/fascade.hpp"
#include "Patterns/mediator.hpp"
#include "Patterns/flyweight.hpp"
#include "Patterns/interpreter.hpp"
#include "Patterns/state.hpp"
#include "Patterns/chainofcommand.hpp"
#include "Patterns/observer.hpp"
#include "Patterns/memento.hpp"
#include "Patterns/strategy.hpp"
#include "Patterns/templatemethod.hpp"
#include "Patterns/iterator.hpp"
#include "Patterns/visitor.hpp"

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
        // I made a unique identifier in the creation of a virus.. The virus can only be the same if a clone is created

        Virus *ebola = new Virus();
        Virus *flu = new Virus();
        REQUIRE(ebola->GetVirusID() != flu->GetVirusID());

        PrototypeHandler *virologist = new PrototypeHandler();
        virologist->AddPrototype(ebola, 0);
        virologist->AddPrototype(flu, 1);


        Virus *ebola_spawn = dynamic_cast<Virus *> (virologist->GetPrototype(0));
        Virus *flu_spawn = dynamic_cast<Virus *> (virologist->GetPrototype(1));

        REQUIRE(ebola_spawn->GetVirusID() == ebola->GetVirusID());
        REQUIRE(flu_spawn->GetVirusID() == flu->GetVirusID());
    }


}

TEST_CASE("Behavioural Design Patterns", "[Testing Behavioural Design Patterns]") {
    SECTION("Interpreter") {
        Tokenizer *t = new Tokenizer();
        std::vector<string> t_vector = t->splitTokens("- + 7 5 4", ' ');
        Expression *expression = t->readToken(&t_vector);
        REQUIRE(expression->interpret() == 8);

        t_vector = t->splitTokens("8", ' ');
        expression = t->readToken(&t_vector);
        REQUIRE(expression->interpret() == 8);

    }
    SECTION("Mediator") {
        Mediator *mediator = new ConcreteMediator();
        Person *personA = new ConcretePersonA(mediator);
        Person *personB = new ConcretePersonB(mediator);

        mediator->BuildRelation(personA, personB);
        personA->SendMessage("PersonA");
        personB->SendMessage("PersonB");

        delete personA;
        delete personB;
        delete mediator;
    }

    SECTION("State") {
        Account *account = new Account("Dr. Who");
        account->Withdraw(10.00);
        account->Withdraw(30.00);
        account->Withdraw(70.00);
        account->Deposit(234.00);
        account->Deposit(5000.00);
        account->Withdraw(5200.00);
        account->Deposit(1500.00);
        account->Deposit(1.00);
        account->Withdraw(1200.00);

        delete account;
    }

    SECTION("Chain Of Command") {
        Photo *p = new Photo("Y2013 Photo");
        processPhoto(*p);
    }

    SECTION("Observer") {
        Company *c1 = new Company("Google", "$", 123.0);
        cout << "Created company Google with Stock Price 123.0\n" << endl;

        Investor *i1 = new Investor("Billy");
        c1->Attach(i1);
        cout << "Created investor Billy following Google\n" << endl;

        c1->SetPrice(125.0);

        Investor *i2 = new Investor("Timmy");
        c1->Attach(i2);
        Investor *i3 = new Investor("Lenny");
        c1->Attach(i3);
        cout << "\nCreated investor Timmy and Lenny following Google\n" << endl;

        c1->SetPrice(145.0);

        c1->Detach(i1);
        c1->Detach(i3);
        cout << "\nInvestor Billy and Lenny not interested in Google anymore\n" << endl;

        c1->SetPrice(165.0);

        delete i1;
        delete i2;
        delete i3;
        delete c1;
    }

    SECTION ("Memento") {
        GitOriginator<string> *orig = new GitOriginator<string>();
        GitCaretaker<string> *care_taker = new GitCaretaker<string>();

        string commit_sha1 = "b4902e1292af8b331e43a51ba8bbf9511f292714";
        string commit_sha2 = "47ece89cc85705281e4e0d435ec8297fb7895846";
        string commit_sha3 = "b636032d633af4b6eb31abb1195045f133ae569c";

        orig->set_state(commit_sha1);
        care_taker->COMMIT(orig);
        REQUIRE(orig->get_State() == commit_sha1);

        orig->set_state(commit_sha2);
        care_taker->COMMIT(orig);
        REQUIRE(orig->get_State() == commit_sha2);

        orig->set_state(commit_sha3);
        care_taker->COMMIT(orig);
        REQUIRE(orig->get_State() == commit_sha3);

        care_taker->ROLLBACK(orig, 0);
        REQUIRE(orig->get_State() == commit_sha1);
    }

    SECTION("Strategy") {

        // test case 1
        int elements[] = {1, 12, 4, 7, 2, 6, 20, 22, 3, 10};
        vector<int> A(elements, elements + 10);

        Mergesort merge;
        Quicksort quick;
        Heapsort heap;


        SortingStrategies sorter;

        sorter.set_strategy(&heap);
        sorter.sort(A, (int) A.size(), 0, (int) A.size());

        for (int i = 0; i < A.size(); ++i) {
            cout << A[i] << " ";
        }
        cout << endl;

    }

    SECTION("Command") {
        Systemctl *systemctl = new Systemctl();

        Receiver *nginx = new Nginx();
        Receiver *psql = new PostgreSQL();

        Command *start = new Start(nginx);
        Command *stop = new Stop(nginx);
        Command *enable = new Enable(nginx);
        Command *disable = new Disable(nginx);

        systemctl->typeCommand(start);
        systemctl->terminalExecute();
        start->change(psql);
        systemctl->terminalExecute();
        systemctl->typeCommand(stop);
        systemctl->terminalExecute();
        stop->change(psql);
        systemctl->terminalExecute();

        delete start;
        delete stop;
        delete enable;
        delete disable;
        delete nginx;
        delete psql;
        delete systemctl;
    }

    SECTION("Template Method") {
        Games *new_game = new SonicAdventures();
        new_game->playGame();
        delete new_game;
        new_game = new MarioBros();
        new_game->playGame();
        delete new_game;
    }

    SECTION("Iterator") {
        PlaylistAggregate *aggregate = new PlaylistAggregate();

        aggregate->addSong("Astronaut - Rain (The Eden Project Remix)");
        aggregate->addSong("Kormac - Wash my hands");
        aggregate->addSong("Westworld Soundtrack - Violent Delights Have Violent Ends");

        Iterator *iter = aggregate->getIterator();

        while (iter->hasNext()) {
            cout << iter->next() << endl;
        }
        delete (aggregate);
        delete (iter);
    }

    SECTION("Visitor") {
        Piano *piano = new Piano();
        Sound *sound = new Sound();
        Violin *violin = new Violin();

        piano->plays(sound);
        violin->plays(sound);
        piano->plays(sound);

        delete sound;
        delete violin;
        delete piano;

    }

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
        Manjaro *my_dist = new ManjaroAdapter("Kernel~4.9.31-1-MANJARO x86_64");
        REQUIRE(my_dist->showLogo() == "Kernel~4.9.31-1-MANJARO x86_64");
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
        // Stock standard witcher game is out
        SteamGame *game = new Witcher3();
        REQUIRE(game->cost() == 39.99);

        // New DLC content has come out!!!
        game = new HeartOfStone(game);
        REQUIRE(game->cost() == (39.99 + 9.99));
        REQUIRE(game->play());

        // More DLC :)
        game = new BloodAndWine(game);
        REQUIRE(game->cost() > 50);
        REQUIRE(game->play());
    }

    SECTION ("Composite") {

        // Might add a find method into the composite to have return results
        Component *root = new Composite("/");
        Component *bin = new Composite("bin");
        Component *etc = new Composite("etc");
        Component *home = new Composite("home");
        Component *user_account = new Composite("penguinrage");

        bin->add(new Leaf("cat"));
        bin->add(new Leaf("top"));
        bin->add(new Leaf("cd"));

        etc->add(new Leaf("pacman.conf"));
        etc->add(new Leaf("rc.local"));

        home->add(user_account);

        user_account->add(new Leaf("bash.profile"));
        user_account->add(new Leaf(".vimrc"));

        root->add(bin);
        root->add(etc);
        root->add(home);
        //root->tree(0);

        REQUIRE(root->find("bash.profile"));
        REQUIRE(root->find("/"));
        REQUIRE(!root->find("fhusdhu"));

        delete user_account;
        delete home;
        delete etc;
        delete bin;
        delete root;
        //cout << endl;
    }
    SECTION("Fascade") {
        HeistFacade *heist = new HeistFacade(new Conman(4), new Robber(false), new Driver(true));
        REQUIRE(!heist->robTheBank());
        heist->trainTheTeam();
        heist->trainTheTeam();
        REQUIRE(heist->robTheBank());
    }

    SECTION("Flyweight") {
        string requests = "CCTTUTCC";
        const char *chars = requests.c_str();

        ASCIIFactory *factory = new ASCIIFactory();

        // For each character use a flyweight object
        for (size_t i = 0; i < requests.length(); i++) {
            ASCII *art = factory->GetArt(chars[i]);
            art->Display();
            if (chars[i] == 'C') REQUIRE(art->getName() == "Computer Ascii");
            else if (chars[i] == 'U') REQUIRE(art->getName() == "UFO Ascii");
            else if (chars[i] == 'T') REQUIRE(art->getName() == "TV Ascii");
        }

        //Clean memory
        delete factory;
    }
}
