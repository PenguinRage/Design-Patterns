//
// Created by penguinrage on 22/07/17.
//

#ifndef DESIGN_PATTERNS_INTERPRETER_HPP
#define DESIGN_PATTERNS_INTERPRETER_HPP

#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stdexcept>

// A simple interpreter
namespace patterns {

    // Expression Interface
    class Expression {
    public:
        virtual ~Expression() {}

        virtual int interpret() = 0;
    };


    // Empty
    class Null : public Expression {
    public:
        virtual ~Null() {}

        virtual int interpret() {
            throw std::logic_error("Uncomplete Expression");
        }
    };


    // Number
    class Number : public Expression {
    public:
        explicit Number(int num) : m_number(num) {}

        virtual ~Number() {}

        virtual int interpret() { return m_number; }

    private:
        int m_number;
    };


    // Addition
    class Add : public Expression {
    public:
        Add(Expression *left, Expression *right) : m_left(left), m_right(right) {}

        virtual ~Add() {
            delete m_left;
            delete m_right;
        }

        virtual int interpret() { return m_left->interpret() + m_right->interpret(); }

    private:
        Expression *m_left;
        Expression *m_right;
    };

    // Subtract
    class Subtract : public Expression {
    public:
        Subtract(Expression *left, Expression *right) : m_left(left), m_right(right) {}

        virtual ~Subtract() {
            delete m_left;
            delete m_right;
        }

        virtual int interpret() { return m_left->interpret() - m_right->interpret(); }

    private:
        Expression *m_left;
        Expression *m_right;
    };

    // Tokenizer
    class Tokenizer {
    public:
        virtual ~Tokenizer() {}

        // Tokenizer splits tokens
        void split(const std::string &s, char delim, std::vector<std::string> *elems) {
            std::stringstream ss(s);
            std::string item;
            while (getline(ss, item, delim)) {
                elems->push_back(item);
            }
        }

        std::vector<std::string> splitTokens(const std::string &s, char delim) {
            std::vector<std::string> elems;
            split(s, delim, &elems);
            return elems;
        }

        Expression *readToken(std::vector<std::string> *token_vector) {
            return readNextToken(token_vector);
        }

        Expression *readNextToken(std::vector<std::string> *token_vector) {
            std::string token = (std::string) token_vector->at(0);
            if (token == "+" || token == "-") {
                return readNonTerminal(token_vector);
            } else {
                int number = atoi(token.c_str());
                token_vector->erase(token_vector->begin());
                return new Number(number);
            }
        }

        Expression *readNonTerminal(std::vector<std::string> *token_vector) {
            std::string token = (std::string) token_vector->at(0);
            token_vector->erase(token_vector->begin());
            Expression *left = readNextToken(token_vector);
            Expression *right = readNextToken(token_vector);
            if (token == "+") {
                return new Add(left, right);
            } else if (token == "-") {
                return new Subtract(left, right);
            }
            return new Null();
        }
    };
}

#endif //DESIGN_PATTERNS_INTERPRETER_HPP
