#ifndef DESIGN_PATTERNS_STATE_HPP
#define DESIGN_PATTERNS_STATE_HPP

#include<iostream>
#include<string>

namespace patterns {
    using namespace std;

    //Forward Declaration
    class Account;

// The 'State' abstract class
    class State {
    public:
        Account *GetAccount(void);

        void SetAccount(Account *account);

        double GetBalance(void);

        void SetBalance(double balance);

        string GetStateName(void);

        virtual void Deposit(double amount)=0;

        virtual void Withdraw(double amount)=0;

        virtual void PayInterest(void) = 0;

    protected:
        Account *account_;
        double balance_;
        double interest_;
        double lowerLimit_;
        double upperLimit_;
        string stateName_;;
    };

// A 'ConcreteState' class
// Red indicates that account is overdrawn
    class RedState : State {
    public:
        RedState(State *state);

        void Deposit(double amount);

        void Withdraw(double amount);

        void PayInterest();

        void StateChangeCheck();

    private:

        RedState(); //Not allowed
        void Initialise();

        double serviceFee_;
    };

// A 'ConcreteState' class
// Silver indicates less interest bearing state
    class SilverState : State {
    public:
        SilverState(State *state);

        SilverState(double balance, Account *account);

        void Deposit(double amount);

        void Withdraw(double amount);

        void PayInterest();

        void StateChangeCheck();

    private:
        SilverState(); //Not allowed
        void Initialise();
    };

// A 'ConcreteState' class
// Gold indicates high interest bearing state
    class GoldState : State {
    public:
        GoldState(State *state);

        void Deposit(double amount);

        void Withdraw(double amount);

        void PayInterest();

        void StateChangeCheck();

    private:
        GoldState(); //Not allowed
        void Initialise();
    };


// The 'Context' class - defined here as its used for forward declaration
    class Account {
    public:
        Account(string owner);

        ~Account();

        double GetBalance(void);

        void Deposit(double amount);

        void Withdraw(double amount);

        void PayInterest();

        void SetState(State *state);

        State *GetState(void);

    private:
        State *state_;
        string owner_;

        Account();
    };


    Account *State::GetAccount(void) {
        return account_;
    }

    void State::SetAccount(Account *account) {
        account_ = account;
    }

    double State::GetBalance(void) {
        return balance_;
    }

    void State::SetBalance(double balance) {
        balance_ = balance;
    }

    string State::GetStateName(void) {
        return stateName_;
    }

    RedState::RedState(State *state) {
        this->balance_ = state->GetBalance();
        this->account_ = state->GetAccount();
        Initialise();
    }

    void RedState::Deposit(double amount) {
        balance_ += amount;
        StateChangeCheck();
    }

    void RedState::Withdraw(double amount) {
        double newAmount = amount + serviceFee_;
        if (balance_ - newAmount < lowerLimit_)
            cout << "No funds available for withdrawal!" << endl;
        else
            balance_ -= newAmount;
    }

    void RedState::PayInterest() {
        //No interest is paid
    }

    void RedState::StateChangeCheck() {
        if (balance_ > upperLimit_) {
            account_->SetState(reinterpret_cast<State *>(new SilverState(this)));
            delete this;
            return;
        }
    }

    void RedState::Initialise() {
        stateName_ = "Red";
        //Should come from a data source
        interest_ = 0.0;
        lowerLimit_ = -100.0;
        upperLimit_ = 0.0;
        serviceFee_ = 15.0;
    }

    SilverState::SilverState(State *state) {
        this->balance_ = state->GetBalance();
        this->account_ = state->GetAccount();
        Initialise();
    }

    SilverState::SilverState(double balance, Account *account) {
        this->balance_ = balance;
        this->account_ = account;
        Initialise();
    }

    void SilverState::Deposit(double amount) {
        balance_ += amount;
        StateChangeCheck();
    }

    void SilverState::Withdraw(double amount) {
        balance_ -= amount;
        StateChangeCheck();
    }

    void SilverState::PayInterest() {
        balance_ = balance_ * interest_;
        StateChangeCheck();
    }

    void SilverState::StateChangeCheck() {
        if (balance_ < lowerLimit_) {
            account_->SetState(reinterpret_cast<State *>(new RedState(this)));
            delete this;
            return;
        } else if (balance_ > upperLimit_) {
            account_->SetState(reinterpret_cast<State *>(new GoldState(this)));
            delete this;
            return;
        }
    }

    void SilverState::Initialise() {
        stateName_ = "Silver";
        //Should come from a data source
        interest_ = 1.0;
        lowerLimit_ = 0.0;
        upperLimit_ = 1000.0;
    }

    GoldState::GoldState(State *state) {
        this->balance_ = state->GetBalance();
        this->account_ = state->GetAccount();
        Initialise();
    }

    void GoldState::Deposit(double amount) {
        balance_ += amount;
        StateChangeCheck();
    }

    void GoldState::Withdraw(double amount) {
        balance_ -= amount;
        StateChangeCheck();
    }

    void GoldState::PayInterest() {
        balance_ = balance_ * interest_;
        StateChangeCheck();
    }

    void GoldState::StateChangeCheck() {
        if (balance_ < 0.0) {
            account_->SetState(reinterpret_cast<State *>(new RedState(this)));
            delete this;
            return;
        } else if (balance_ < lowerLimit_) {
            account_->SetState(reinterpret_cast<State *>(new SilverState(this)));
            delete this;
            return;
        } else if (balance_ > upperLimit_) {
            cout << "Your account is too big now. Please consider using Swiss banks" << endl;
        }
    }

    void GoldState::Initialise() {
        stateName_ = "Gold";
        //Should come from a data source
        interest_ = 5.0;
        lowerLimit_ = 1000.0;
        upperLimit_ = 10000000.0;
    }

    Account::Account(string owner) : owner_(owner) {
        state_ = reinterpret_cast<State *>(new SilverState(0.0, this)); //default
    }

    Account::~Account() {
        delete state_;
    }

    double Account::GetBalance(void) {
        return state_->GetBalance();
    }

    void Account::Deposit(double amount) {
        state_->Deposit(amount);
        cout << "Deposited $" << amount << endl;
        cout << "Balance   $" << GetBalance() << endl;
        cout << "Status     " << state_->GetStateName() << endl;
        cout << "\n";
    }

    void Account::Withdraw(double amount) {
        state_->Withdraw(amount);
        cout << "Withdrew  $" << amount << endl;
        cout << "Balance   $" << GetBalance() << endl;
        cout << "Status     " << state_->GetStateName() << endl;
        cout << "\n";
    }

    void Account::PayInterest() {
        state_->PayInterest();
        cout << "Interest Paid --------" << endl;
        cout << "Balance   $" << GetBalance() << endl;
        cout << "Status     " << state_->GetStateName() << endl;
        cout << "\n";
    }

    void Account::SetState(State *state) {
        state_ = state;
    }

    State *Account::GetState(void) {
        return state_;
    }
}

#endif //DESIGN_PATTERNS_STATE_HPP
