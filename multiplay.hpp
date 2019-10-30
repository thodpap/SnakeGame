#ifndef MULTIPLAY_HPP
#define MULTIPLAY_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"

void multiplayer(sf::RenderWindow *window,sf::Sprite s,
    sf::Sprite background,
    sf::Sprite food,
    sf::Sprite s2,
    sf::Sprite playAgain,
    sf::Sprite menu,
    sf::Text text)
{
    Game *Snake1,*Snake2;
    Snake1 = new Game();
    Snake2 = new Game(); 

    sf::Clock clock;
    float timer=0, delay=0.065;  
    
    Food *apple;
    apple = new Food();
    apple->x = rand() % N;
    apple->y = rand() % M;

    bool again = true;
    while(window->isOpen()){
        int score1 = Snake1->snake.size();
        int score2 = Snake2->snake.size();

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time; 
        sf::Event event; 
        while (window->pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ dx = -1; dy = 0; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ dy = 0; dx = 1; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){ dx = 0; dy = 1; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ dx = 0; dy = -1; } 

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){ dx2 = -1; dy2 = 0; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){ dy2 = 0; dx2 = 1; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){ dx2 = 0; dy2 = 1; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ dx2 = 0; dy2 = -1; }  

        if(timer > delay){
            timer = 0;
            Snake1->move(dx,dy,apple); 
            Snake2->move(dx2,dy2,apple); 
            Snake1->hitSnake(Snake2);
            Snake2->hitSnake(Snake1);
        }    
        
        window->clear(); 
        window->draw(background);

        text.setString("Red   Player: " + std::to_string(Snake1->snake.size()));
        text.setPosition(50,15);
        window->draw(text);

        text.setString("Green Player: " + std::to_string(Snake2->snake.size()));
        text.setPosition(50,40);
        window->draw(text);

        food.setPosition(apple->x * size,apple->y * size);
        window->draw(food); 

        if(!Snake1->gameOver){
            for(auto i = Snake1->snake.begin(); i != Snake1->snake.end(); ++i){
                s.setPosition((*i).x * size,(*i).y * size);
                window->draw(s);
            }
        }
        
        if(!Snake2->gameOver){
            for(auto i = Snake2->snake.begin(); i != Snake2->snake.end(); ++i){
                s2.setPosition((*i).x * size,(*i).y * size);
                window->draw(s2);
            }
        }

        if(Snake1->gameOver && Snake2->gameOver){
            again = false;

            playAgain.setPosition(160,65);
            window->clear();
            window->draw(background);

            text.setString("Red    Player: " + std::to_string(Snake1->snake.size()));
            text.setPosition(50,15);
            window->draw(text);

            text.setString("Green Player: " + std::to_string(Snake2->snake.size()));
            text.setPosition(50,40);
            window->draw(text);

            window->draw(playAgain);

            menu.setPosition(160,160);
            window->draw(menu);

            text.setString("Play Again");
            text.setPosition(190,82);
            window->draw(text);

            text.setString("Menu");
            text.setPosition(215,178);
            window->draw(text);

            text.setCharacterSize(30);
            if(Snake1->snake.size() > Snake2->snake.size()){
                text.setString("Red Player Won");
                text.setFillColor(sf::Color::Red);
                // text.setColor(sf::Color::Red);
                text.setPosition(120,250);
            }
            else if(Snake1->snake.size() < Snake2->snake.size()){
                text.setFillColor(sf::Color::White);
                text.setString("Green Player Won"); 
                text.setPosition(120,250);
            }
            else {
                text.setFillColor(sf::Color::Black);
                text.setString("Draw");
                text.setPosition(200,250);  
            }

            window->draw(text);

            window->display();
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Blue);
            while(!again){
                sf::Event event; 
                while (window->pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window->close();
                        return ;
                    }
                } 
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    sf::Vector2i mouse = sf::Mouse::getPosition();
                    sf::Vector2i window_pos = window->getPosition();
                    mouse.x -= window_pos.x - 8;
                    mouse.y -= window_pos.y - 34;
                    // std::cerr << "(" << mouse.x << " " << mouse.y << ")" << std::endl;

                    if(160 <= mouse.x && mouse.x <= 320 && 60 <= mouse.y && mouse.y < 115) 
                        again = true;  
                    if(160 <= mouse.x && mouse.x <= 320 && 160 <= mouse.y && mouse.y <= 215){
                        dx = dy = dx2 = dy2 = 0;
                        return ;
                    }
                } 
            }
            delete Snake1;
            delete Snake2;
            Snake1 = new Game();
            Snake2 = new Game();
            dx = dx2 = dy = dy2 = 0;
        } 
        window->display();
    }
}
#endif