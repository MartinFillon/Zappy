/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Main
*/

#include <iostream>

#include "ArgParser/ArgParser.hpp"

int main(int argc, char *argv[])
{
    ArgParser parser;
    int port;
    std::string machine;

    parser.setDefault("p", 4242, true)
        .setDefault("h", std::string("local"), true);
    try {
        parser.parse(argc, argv);
        port = parser.get<int>("p");
        machine = parser.get<std::string>("h");
    } catch (const ArgParserException &e) {
        std::cerr << "Error: " << e.what() << " in " << e.where() << std::endl;
        return 84;
    }
    std::cout << "Machine: " << machine << std::endl;
    std::cout << "Port: " << port << std::endl;

    return 0;
}
