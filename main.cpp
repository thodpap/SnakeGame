#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <cstdlib>
#include <unistd.h>
#include "Game.hpp"
#include "singleplay.hpp"
#include "multiplay.hpp"
#include "string.h"
#include "loadGraphics.hpp"

int main(){
    srand(time(0));
    
    sf::RenderWindow window(sf::VideoMode(w, h),"Snak egame");    
    window.setFramerateLimit(60);
    
    loadGraphics();

    sf::Sprite s(t),background(t2),food(t3),menu(t4),s2(t5),playAgain(t6); 
    sf::Sprite singleplay(t7),multiplay(t8);

    Game *Snake1,*Snake2;
    Snake1 = new Game();
    Snake2 = new Game();
    // Make food;  

    sf::Clock clock;
    float timer=0, delay=0.075;  
    
    Food *apple;
    apple = new Food();
    apple->x = rand() % N;
    apple->y = rand() % M;

    bool again = true;
    
    // Load Font
    sf::Font font;
    if(!font.loadFromFile("font/Arial.ttf")){
        std::cerr << "error" << std::endl;
    }
    sf::Text text;
    text.setFont(font);

    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Blue);
    text.setStyle(sf::Text::Bold);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.draw(background);
        
        singleplay.setPosition(160,65);
        window.draw(singleplay);

        text.setString("1 Player");
        text.setPosition(195,82);
        window.draw(text);

        multiplay.setPosition(160,160);
        window.draw(multiplay);

        text.setString("2 Players");
        text.setPosition(195,178);
        window.draw(text);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i mouse = sf::Mouse::getPosition();
            sf::Vector2i window_pos = window.getPosition();
            mouse.x -= window_pos.x;
            mouse.y -= window_pos.y;  
            
            if(150 <= mouse.x && mouse.x <= 310 && 30 <= mouse.y && mouse.y <= 85) {
                sf::sleep(sf::milliseconds(150));
                singlePlay(&window,s,background,food,playAgain,menu,text);
                sf::sleep(sf::milliseconds(300));
            }
            dx = dy = 0;
            dy2 = dx2 = 0;
            if(150 <= mouse.x && mouse.x <= 310 && 125 <= mouse.y && mouse.y <= 185) {
                sf::sleep(sf::milliseconds(150));
                multiplayer(&window,s,background,food,s2,playAgain,menu,text);
                sf::sleep(sf::milliseconds(200));
            }
        }
        window.display(); 
    }
    return 0;
}
