/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** InfoBox
*/

#pragma once

#include <chrono>
#include <raylib.h>
#include <string>
#include <vector>

namespace GUI
{
  class InfoBox {
    public:
      InfoBox();
      void display(int x, int y, int width, int height) const;

      bool isPrint() const {
        return m_print;
      };

      void setPrint(bool val) {
        m_print = val;
      };

      int getSize() const {
        return m_size;
      };

    private:
      bool m_print;
      int m_size;
  };
}
