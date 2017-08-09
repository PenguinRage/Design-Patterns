//
// Created by penguinrage on 9/08/17.
//

#ifndef DESIGN_PATTERNS_COMMAND_HPP
#define DESIGN_PATTERNS_COMMAND_HPP

#include <iostream>

namespace patterns {

    // Command Interface
    class Command {
    public:
        virtual void execute() = 0;
    };

    // systemctl commands - Linux style - Incase your not familiar see link below
    // https://www.digitalocean.com/community/tutorials/how-to-use-systemctl-to-manage-systemd-services-and-units

    // Receiver
    class Receiver {
    public:
        virtual void start() = 0;

        virtual void stop() = 0;

        virtual void enable() = 0;

        virtual void disable() = 0;
    };

    class Nginx : public Receiver {
    public:
        void start() {
            _running = true;
            std::cout << "Nginx has started" << std::endl;
        }

        void stop() {
            _running = false;
            std::cout << "Nginx has stopped" << std::endl;
        }

        void enable() {
            _running = true;
            _enabled = true;
            std::cout << "Nginx is enabled" << std::endl;
        }

        void disable() {
            _running = false;
            _enabled = false;
            std::cout << "Nginx is disabled" << std::endl;
        }

    private:
        bool _running;
        bool _enabled;
    };

    class PostgreSQL : public Receiver {
    public:
        void start() {
            _running = true;
            std::cout << "PostgreSQL has started" << std::endl;
        }

        void stop() {
            _running = false;
            std::cout << "PostgreSQL has stopped" << std::endl;
        }

        void enable() {
            _running = true;
            _enabled = true;
            std::cout << "PostgreSQL is enabled" << std::endl;
        }

        void disable() {
            _running = false;
            _enabled = false;
            std::cout << "PostreSQL is disabled" << std::endl;
        }

    private:
        bool _running;
        bool _enabled;
    };

    //ConcreteCommand1
    class Start : public Command {
    public:
        Start(Receiver *receiver)
                : _receiver(receiver) {
        }

        void execute() {
            _receiver->start();
        }

    private:
        Receiver *_receiver;
    };

    //ConcreteCommand2
    class Stop : public Command {
    public:
        Stop(Receiver *receiver)
                : _receiver(receiver) {
        }

        void execute() {
            _receiver->stop();
        }

    private:
        Receiver *_receiver;
    };

    //ConcreteCommand3
    class Enable : public Command {
    public:
        Enable(Receiver *receiver)
                : _receiver(receiver) {
        }

        void execute() {
            _receiver->enable();
        }

    private:
        Receiver *_receiver;
    };

    //ConcreteCommand4
    class Disable : public Command {
    public:
        Disable(Receiver *receiver)
                : _receiver(receiver) {
        }

        void execute() {
            _receiver->disable();
        }

    private:
        Receiver *_receiver;
    };

    //Invoker
    class Systemctl {
    public:
        void typeCommand(Command *command) {
            _command = command;
        }

        void terminalExecute() {
            _command->execute();
        }

    private:
        Command *_command;
    };


}

#endif //DESIGN_PATTERNS_COMMAND_HPP
