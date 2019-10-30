#ifndef SINGLEPLAY_HPP
#define SINGLEPLAY_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "string.h"

void singlePlay(sf::RenderWindow *window,
    sf::Sprite s,
    sf::Sprite background,
    sf::Sprite food,
    sf::Sprite playAgain,
    sf::Sprite menu,
    sf::Text text)
{
    FILE *input,*output;
    input = fopen("highscore.txt","r");
    
    fscanf(input,"%d",&total_high_score);  
    fclose(input);

    output = fopen("highscore.txt","w");
    
    Game *Snake;
    Snake = new Game();
    // Make food;  

    sf::Clock clock;
    float timer=0, delay=0.065;  
    
    bool again = true;

    Food *apple;
    apple = new Food();
    apple->x = rand() % N;
    apple->y = rand() % M;
    
    while (window->isOpen()){  
        int score = Snake->snake.size();

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time; 
        sf::Event event; 
        while (window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                if(total_high_score < high_score) 
                    total_high_score = high_score; 
                fprintf(output, "%d",total_high_score); 
                fclose(output);
                window->close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ dx = -1; dy = 0; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ dy = 0; dx = 1; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){ dx = 0; dy = 1; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ dx = 0; dy = -1; }  

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){ dx = -1; dy = 0; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){ dy = 0; dx = 1; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){ dx = 0; dy = 1; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ dx = 0; dy = -1; }  

        if(timer > delay){
            timer = 0;
            Snake->move(dx,dy,apple);
        }  

        if(score > high_score)
            high_score = score;
        if(total_high_score < high_score)
            total_high_score = high_score;

        window->clear(); 
        window->draw(background);

        text.setString("High Score: " + std::to_string(total_high_score));
        text.setPosition(50,15);
        window->draw(text);

        text.setString("Score       : " + std::to_string(score));
        text.setPosition(50,40);
        window->draw(text); 

        food.setPosition(apple->x * size,apple->y * size);
        window->draw(food); 
        if(!Snake->gameOver){
            for(auto i = Snake->snake.begin(); i != Snake->snake.end(); ++i){
                s.setPosition((*i).x * size,(*i).y * size);
                window->draw(s);
            }
        }
        
        if(Snake->gameOver){
            again = false; 

            if(total_high_score < high_score) 
                total_high_score = high_score; 
            
            playAgain.setPosition(160,65);
            window->draw(playAgain);

            menu.setPosition(160,160);
            window->draw(menu);

            text.setString("Play Again");
            text.setPosition(190,82);
            window->draw(text);

            text.setString("Menu");
            text.setPosition(215,178);
            window->draw(text);
            window->display();

            while(!again){
                sf::Event event; 
                while (window->pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        fprintf(output, "%d",total_high_score); 
                        fclose(output);
                        window->close();
                        return ;
                    } 
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    sf::Vector2i mouse = sf::Mouse::getPosition();
                    sf::Vector2i window_pos = window->getPosition();
                    mouse.x -= window_pos.x;
                    mouse.y -= window_pos.y; 
                    // std::cerr << "(" << mouse.x << " " << mouse.y << ")" << std::endl;
                    
                    if(150 <= mouse.x && mouse.x <= 310 && 30 <= mouse.y && mouse.y <= 85) 
                        again = true;  
                    if(150 <= mouse.x && mouse.x <= 310 && 125 <= mouse.y && mouse.y <= 180){
                        fprintf(output, "%d",total_high_score); 
                        fclose(output);
                        return ;
                    }
                } 
            } 
            delete Snake;
            Snake = new Game();
            dx = 0;
            dy = 0;
        } 
        window->display();
    }
    fclose(output);
}
#endif