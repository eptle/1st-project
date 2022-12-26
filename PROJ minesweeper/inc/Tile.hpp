#pragma once
#include <SFML/Graphics.hpp>

namespace t
{
    class Tile
    {
    private:
        int m_View = 0;
        int m_Logic = 0;
    public:
        void set_view(int view);
        void set_logic(int logic);

        int get_view();
        int get_logic();
    };
}