#ifndef DESIGN_PATTERNS_OBSERVER_HPP
#define DESIGN_PATTERNS_OBSERVER_HPP


#include<iostream>
#include<string>
#include<list>


namespace patterns {
//Forward Declaration
    class Stock;

    // The 'Observer' interface
    class InvestorInterface {
    public:
        virtual void Update(Stock *stock) {};
    };

    // The 'Subject' abstract class
    class Stock {
    public:
        Stock(std::string symbol, double price) : symbol_(symbol), price_(price) {}

        void Attach(InvestorInterface *investor) {
            investors_.push_back(investor);
        }

        void Detach(InvestorInterface *investor) {
            investors_.remove(investor);
        }

        void Notify() {
            std::list<InvestorInterface *>::iterator it = investors_.begin();
            while (it != investors_.end()) {
                (*it)->Update(this);
                ++it;
            }
        }

        double GetPrice(void) {
            return price_;
        }

        void SetPrice(double price) {
            price_ = price;
            Notify();
        }

        std::string GetSymbol(void) {
            return symbol_;
        }

    private:
        std::string symbol_;
        double price_;
        std::list<InvestorInterface *> investors_;

        Stock();
    };

    // The 'ConcreteSubject' class
    class Company : public Stock {
    public:
        Company(std::string name, std::string symbol, double price) : name_(name), Stock(symbol, price) {}

        std::string GetName(void) {
            return name_;
        }

    private:
        std::string name_;
    };

    // The 'ConcreteObserver' class
    class Investor : public InvestorInterface {
    public:
        Investor(std::string name) : name_(name) {}

        void Update(Stock *stock) {
            std::cout << "Notified " << name_ << " about " << (reinterpret_cast<Company *>(stock))->GetName() \
 << " change to " << stock->GetSymbol() << stock->GetPrice() << std::endl;
        }

    private:
        std::string name_;

        Investor();
    };
}

#endif //DESIGN_PATTERNS_OBSERVER_HPP
