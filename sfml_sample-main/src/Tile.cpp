#include <Tile.hpp>
#include <SFML/Graphics.hpp>

namespace t
{
    void Tile::set_view(int view) { m_View = view; }
    void Tile::set_logic(int logic) { m_Logic = logic; }

    int Tile::get_view() { return m_View; }
    int Tile::get_logic() { return m_Logic; }

}