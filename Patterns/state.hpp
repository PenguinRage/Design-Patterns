#ifndef DESIGN_PATTERNS_STATE_HPP
#define DESIGN_PATTERNS_STATE_HPP

#include <exception>
#include <stdexcept>


namespace patterns {

    // Machine Object
    class Machine {
        friend class AbstractState;

    public:
        Machine(int inStockQuantity) : mStockQuantity(inStockQuantity), m_state(new Normal()) {}

        ~Machine() { delete m_state; }

        void sell(int quantity) { m_state->sell(*this, quantity); }

        void refill(int quantity) { m_state->refill(*this, quantity); }

        int getCurrentStock() { return mStockQuantity; }

    private:
        int mStockQuantity;
        AbstractState *m_state;
    };

    // State Interface
    class AbstractState {
    public:
        virtual void sell(Machine &machine, int quantity) = 0;

        virtual void refill(Machine &machine, int quantity) = 0;

        virtual ~AbstractState() {}

    protected:
        void setState(Machine &machine, AbstractState *state) {
            AbstractState *aux = machine.m_state;
            machine.m_state = state;
            delete aux;
        }

        void updateStock(Machine &machine, int quantity) {
            machine.mStockQuantity = quantity;
        }
    };

    // State Normal operations of vending machine
    class Normal : public AbstractState {
    public:
        virtual void sell(Machine &machine, int quantity) {
            int currStock = machine.getCurrentStock();
            if (currStock < quantity) {
                throw std::runtime_error("Not enough stock");
            }

            updateStock(machine, currStock - quantity);

            if (machine.getCurrentStock() == 0) {
                setState(machine, new SoldOut());
            }
        }

        virtual void refill(Machine &machine, int quantity) {
            int currStock = machine.getCurrentStock();
            updateStock(machine, currStock + quantity);
        }

        virtual ~Normal() {}
    };

    // Soldout state
    class SoldOut : public AbstractState {
    public:
        virtual void sell(Machine &machine, int quantity) {
            throw std::runtime_error("Sold out!");
        }

        virtual void refill(Machine &machine, int quantity) {
            updateStock(machine, quantity);
            setState(machine, new Normal());
        }

        virtual ~SoldOut() {}
    };
}


#endif //DESIGN_PATTERNS_STATE_HPP
