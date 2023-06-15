#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

const int GRID_SIZE = 100;
const int CELL_SIZE = 10;
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;

bool matriz[GRID_SIZE][GRID_SIZE];

void reglas_juego();
int confirmar_vecinos(bool matriz[GRID_SIZE][GRID_SIZE], int x, int y);

void iniciar_ventana(){
    RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Game of Life");
    window.setFramerateLimit(120);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();
        }

        window.clear(Color::Black);
        for (int i = 0; i < GRID_SIZE; i++)
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                RectangleShape cell(Vector2f(CELL_SIZE, CELL_SIZE));
                if (matriz[i][j])
                {
                    cell.setFillColor(Color::White);
                }else{
                    cell.setFillColor(Color::Black);
                }

                cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                window.draw(cell);
            }
    
        }
        window.display();
        reglas_juego();
        //sleep(milliseconds(300));
    }
    
}


void reglas_juego(){

    bool matriz_aux[GRID_SIZE][GRID_SIZE];

    int vecinos_vivos;
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            vecinos_vivos = confirmar_vecinos(matriz, i, j);

            if(matriz[i][j]){
                if(vecinos_vivos == 2 || vecinos_vivos == 3){
                    matriz_aux[i][j] = 1;
                }
                else{
                    matriz_aux[i][j] = 0;
                }
            }
            else
            {
                if(vecinos_vivos == 3){
                    matriz_aux[i][j] = 1;
                }
            }
        }
    
    }

    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            matriz[i][j] = matriz_aux[i][j];
        }
    }
}


int confirmar_vecinos(bool matriz[GRID_SIZE][GRID_SIZE], int x, int y){
    int vecinos = 0;
    for(int i=-1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if (i == 0 && j == 0) continue;
            int vecinox=i+x;
            int vecinoy=j+y;

            if(matriz[vecinox][vecinoy] && vecinox < GRID_SIZE && vecinoy < GRID_SIZE && vecinox >= 0 && vecinoy >= 0){
                vecinos++;
            }
        }
    }
    return vecinos;
}


int main(){

    srand(time(0));

    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            matriz[i][j] = rand() % 2;
        }
    }

    iniciar_ventana();
    return 0;
}