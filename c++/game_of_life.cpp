#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;

const int GRID_SIZE = 100;
const int CELL_SIZE = 10;
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;


void iniciar_ventana(){
    RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Game of Life");
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();
        }
        window.clear(Color::Black);
        window.display();
    }
    
}




int main(){

    iniciar_ventana();

    return 0;
}