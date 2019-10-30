#ifndef STRING_H
#define STRING_H

#define N 30
#define M 20

const int size = 16;

#define w size * N
#define h size * M
int total_high_score = 0;
int high_score;
int dx = 0, dy = 0;   
int dx2 = 0,dy2 = 0;

struct Point{
    int x,y;
};
class Food{
public: 
    int x,y;
};

sf::Texture t,t2,t3,t4,t5,t6,t7,t8,t9;	

#endif