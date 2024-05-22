/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Main
*/

#include <iostream>

#include "define.hpp"
#include "ArgParser/ArgParser.hpp"
#include "Display/Display.hpp"
#include "Network/NetworkHandler.hpp"

static void parseArguments(
    int argc,
    char *argv[],
    int &port,
    std::string &machine,
    bool &debug
)
{
    ArgParser parser;
    parser.setDefault("p", 4242, true)
        .setDefault("h", std::string("localhost"), true)
        .setDefault("d", false, false);

    try {
        parser.parse(argc, argv);
        port = parser.get<int>("p");
        machine = parser.get<std::string>("h");
        debug = parser.get<bool>("d");
    } catch (const ArgParserException &e) {
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
    NetworkHandler networkHandler(machine, port);
    networkHandler.start();

    Display display(networkHandler, debug);
    display.run();

    networkHandler.stop();

    return 0;
}
