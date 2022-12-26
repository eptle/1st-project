#include <iostream>
#include <SFML/Graphics.hpp>
#include <Tile.hpp>
#include <time.h>

int const H = 10;
int const W = 10;
int const size = 32;

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(320, 384), L"Сапёр");
    setlocale(LC_ALL, "Rus");
    //для каждой клетки указывем вид и наличие мины
    int bomb_quantity = 0;
    t::Tile tiles[H][W];
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
        {
            tiles[i][j].set_view(10);
            if (rand() % 5 == 0)
            {
                tiles[i][j].set_logic(9);
                bomb_quantity++;
            }
        }
    bool game_over = false;
    bool is_win = false;
    std::cout << bomb_quantity << std::endl;

    srand(time(NULL));

    //загрузка текстуры
    sf::Texture cell;
    cell.loadFromFile("C:\\Users\\eptel\\Desktop\\PROJECT\\sfml_sample-main\\src\\tileset.jpg");
    sf::Sprite sprite(cell); 

    //считаем мины вокруг клетки
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
        {
            int cnt = 0;
            if (tiles[i][j].get_logic() == 9)                               continue;
            if (tiles[i][j - 1].get_logic() == 9 && j != 0)                 cnt++;
            if (tiles[i][j + 1].get_logic() == 9 && j != H)                 cnt++;
            if (tiles[i - 1][j - 1].get_logic() == 9 && i != 0 && j != 0)   cnt++;
            if (tiles[i - 1][j].get_logic() == 9 && i != 0)                 cnt++;
            if (tiles[i - 1][j + 1].get_logic() == 9 && i != 0 && j != H)   cnt++;
            if (tiles[i + 1][j - 1].get_logic() == 9 && i != H && j != 0)   cnt++;
            if (tiles[i + 1][j].get_logic() == 9 && i != H)                 cnt++;
            if (tiles[i + 1][j + 1].get_logic() == 9 && i != H && j != H)   cnt++;
            //устанавливаем, сколько мин вокруг клетки
            if (cnt != 0)
                tiles[i][j].set_logic(cnt);
        }

    //загружаем шрифт и устанавливаем его параметры
    sf::Font font;
    font.loadFromFile("C:\\Users\\eptel\\Desktop\\PROJECT\\sfml_sample-main\\src\\RussoOne-Regular.ttf");

    sf::Text final_text;
    final_text.setFont(font);
    final_text.setColor(sf::Color::White);
    final_text.setCharacterSize(18);
    final_text.setPosition(24, 8 + 32*10);

    sf::Text text;
    text.setFont(font);

    //счетчик, чтобы считать количество клеток для победы
    int cnt = 0;
    while (window.isOpen())
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        int x = pos.x / size;
        int y = pos.y / size;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


            //считывыем нажатия клавиш
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && game_over)
            {
                std::cout << "RESTART" << std::endl;
                for (int i = 0; i < H; i++)
                    for (int j = 0; j < W; j++)
                        tiles[i][j].set_logic(0);

                for (int i = 0; i < H; i++)
                {
                    for (int j = 0; j < W; j++)
                    {
                        tiles[i][j].set_view(10);
                        if (rand() % 5 == 0)
                        {
                            tiles[i][j].set_logic(9);
                            bomb_quantity++;
                        }
                    }
                }
                //считаем мины вокруг клетки
                for (int i = 0; i < H; i++)
                {
                    for (int j = 0; j < W; j++)
                    {
                        int cnt = 0;
                        if (tiles[i][j].get_logic() == 9)                               continue;
                        if (tiles[i][j - 1].get_logic() == 9 && j != 0)                 cnt++;
                        if (tiles[i][j + 1].get_logic() == 9 && j != H)                 cnt++;
                        if (tiles[i - 1][j - 1].get_logic() == 9 && i != 0 && j != 0)   cnt++;
                        if (tiles[i - 1][j].get_logic() == 9 && i != 0)                 cnt++;
                        if (tiles[i - 1][j + 1].get_logic() == 9 && i != 0 && j != H)   cnt++;
                        if (tiles[i + 1][j - 1].get_logic() == 9 && i != H && j != 0)   cnt++;
                        if (tiles[i + 1][j].get_logic() == 9 && i != H)                 cnt++;
                        if (tiles[i + 1][j + 1].get_logic() == 9 && i != H && j != H)   cnt++;
                        //устанавливаем, сколько мин вокруг клетки
                        if (cnt != 0)
                            tiles[i][j].set_logic(cnt);
                    }
                }
                bool game_over = false;
                bool is_win = false;
                break;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && game_over)
            {
                return 0;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    if (x > H || y > H)
                        game_over = false;

                    else if (tiles[x][y].get_logic() == 9)
                    {
                        game_over = true;
                    }

                    else if(tiles[x][y].get_logic() != 9 && tiles[x][y].get_view() == 10 && !game_over)
                    {
                        cnt++;
                        std::cout << cnt << std::endl;
                        if (cnt >= (100 - bomb_quantity))
                        {
                            game_over = true;
                            is_win = true;
                        }
                    }

                    tiles[x][y].set_view(tiles[x][y].get_logic());
                }
                else if (event.key.code == sf::Mouse::Right)
                {
                    if (tiles[x][y].get_view() == 10)
                        tiles[x][y].set_view(11);
                    else if (tiles[x][y].get_view() == 11)
                        tiles[x][y].set_view(10);
                }
            }
        }

        //ставим текстуру скрытой клетки
        window.clear(sf::Color(0, 0, 0));
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                sprite.setTextureRect(sf::IntRect(tiles[i][j].get_view() * size, 0, size, size));
                sprite.setPosition(i * size, j * size);
                window.draw(sprite);
            }
        }

        //текст при завершении игры
        if (game_over)
        {
            if (is_win)
            {
                final_text.setString(L"Поздравляю с победой! По новой?\n[Y] — Да\t[N] — Нет");
                window.draw(final_text);
            }
            else 
            {
                final_text.setString(L"Хорошая попытка! Ещё раз?\n[Y] — Да\t[N] — Нет");
                window.draw(final_text);
            }
        }

        if (!game_over)
        {
                final_text.setString(L"awd");
                window.draw(final_text);
        }

        window.display();
    }

    return 0;
}