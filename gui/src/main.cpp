/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Main
*/

#include <iostream>

#include "ArgParser/ArgParser.hpp"
#include "GUI/Display.hpp"
#include "Network/Handler.hpp"
#include "define.hpp"

static void parseArguments(int argc, char *argv[], int &port, std::string &machine, bool &debug)
{
    ArgParser::ArgParser parser;
    parser.setDefault("p", 4242, true).setDefault("h", std::string("localhost"), true).setDefault("d", false, false);

    try {
        parser.parse(argc, argv);
        port = parser.get<int>("p");
        machine = parser.get<std::string>("h");
        debug = parser.get<bool>("d");
    } catch (const ArgParser::Error &e) {
        std::cerr << "Error: " << e.what() << " in " << e.where() << std::endl;
        throw std::runtime_error("Argument parsing failed");
    }
}

int main(int argc, char *argv[])
{
    int port;
    std::string machine;
    bool debug;

    try {
        parseArguments(argc, argv, port, machine, debug);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return ERROR;
    }

    GUI::Display display(machine, port, debug);
    display.run();

    return SUCCESS;
}
