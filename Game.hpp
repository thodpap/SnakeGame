#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <vector>
#include "string.h"


class Game{
public:
    Game();

    void move(int dx,int dy,Food *food); 
    void hitSnake(Game *Snake);
    std::vector<Point> snake; 
    bool gameOver;
}; 

Game::Game(){
    Point start;
    start.x = rand() % N; 
    start.y = rand()%M;
    snake.push_back(start);
    gameOver = false; 
}

void Game::move(int dx,int dy,Food *food){
    if(gameOver) 
        return;
    
    for(auto i = snake.end() - 1; i != snake.begin() - 1; --i){  
       if(i == snake.begin()){
            (*i).x += dx;                 
            (*i).y += dy; 

            if((*i).x < 0)       (*i).x = N - 1; 
            else if((*i).x >= N) (*i).x = 0; 
            else if((*i).y < 0)  (*i).y = M - 1; 
            else if((*i).y >= M) (*i).y = 0;
 //         if((*i).x < 0 || (*i).x >= N || (*i).y < 0 || (*i).y >= M){
 //               gameOver = true;
 //               return ;
 //           } 
           
            auto head = snake.begin();
             for(auto i = snake.begin() + 1; i != snake.end(); ++i){
                if((*i).x == (*head).x  && (*i).y == (*head).y){  
                    gameOver = true;
                    break;
                }
            }                
            if((*i).x == food->x && (*i).y == food->y){
                food->x = rand() % N;
                food->y = rand() % M;
                Point newSnake; 
                auto it = snake.end() - 1;
                if(dx == 1){ newSnake.x = (*it).x - 1; newSnake.y = (*it).y;  }
                else if(dx == -1){ newSnake.x = (*it).x + 1; newSnake.y = (*it).y; }
                else if(dy == 1){ newSnake.x = (*it).x; newSnake.y = (*it).y - 1;  }
                else if(dy == -1){ newSnake.x = (*it).x; newSnake.y = (*it).y + 1;  } 
                snake.push_back(newSnake);  
                break;
            } 
        }
        else{ 
            (*i).x = (*(i - 1)).x;
            (*i).y = (*(i - 1)).y; 
        }
    }
}  
void Game::hitSnake(Game *Snake){
    auto head = snake.begin();
    for(auto i = Snake->snake.begin(); i != Snake->snake.end(); ++i){
        if((*i).x == (*head).x && (*i).y == (*head).y){
            gameOver = true;
            break;       
        }
    }
}
#endif
