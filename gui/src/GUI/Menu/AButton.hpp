/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Button
*/

#pragma once

#include "IButton.hpp"
#include <string>

namespace GUI {

enum ButtonState {
  DEFAULT,
  HOVER,
  PRESSED
};

template <typename F, typename T>
class AButton : public IButton<F, T>
{
  public:
    AButton(const std::string &name, T &val, std::function<void(T&)> funct):
        m_name(name), m_funct(funct), m_state(DEFAULT), m_val(val) {};

  protected:
    std::string m_name;
    std::function<void(T&)> m_funct;
    ButtonState m_state;
    T &m_val;
};

} // namespace GUI
