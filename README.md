# SnakeGame
To compile, you first need to install SFML (a library for visual objects).

To install use: 
sudo apt-get install libsfml-dev

Now, to compile, use:
g++ -c main.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

And to execute the code:
./sfml-app
