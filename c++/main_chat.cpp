#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int GRID_SIZE = 100;
const int CELL_SIZE = 10;
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;

// Función para inicializar la cuadrícula con valores aleatorios
void inicializarCuadricula(bool grid[GRID_SIZE][GRID_SIZE]) {
    std::srand(std::time(nullptr)); // Semilla para generar valores aleatorios

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = std::rand() % 2 == 0; // Asignar valor aleatorio (true o false)
        }
    }
}

// Función para contar el número de vecinos vivos de una celda en la cuadrícula
int contarVecinosVivos(bool grid[GRID_SIZE][GRID_SIZE], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Saltar la celda actual
            int neighborX = x + i;
            int neighborY = y + j;

            // Verificar límites de la cuadrícula y si la celda vecina está viva
            if (neighborX >= 0 && neighborX < GRID_SIZE && neighborY >= 0 && neighborY < GRID_SIZE && grid[neighborX][neighborY]) {
                count++;
            }
        }
    }
    return count;
}

// Función para aplicar las reglas del Juego de la Vida y actualizar el estado de la cuadrícula
void aplicarReglasJuego(bool grid[GRID_SIZE][GRID_SIZE]) {
    bool nextGrid[GRID_SIZE][GRID_SIZE]; // Cuadrícula auxiliar para almacenar el próximo estado

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int vecinosVivos = contarVecinosVivos(grid, i, j);
            if (grid[i][j]) {
                // Regla 1: Si una celda viva tiene menos de 2 o más de 3 vecinos vivos, muere por soledad o sobrepoblación
                nextGrid[i][j] = vecinosVivos == 2 || vecinosVivos == 3;
            } else {
                // Regla 2: Si una celda muerta tiene exactamente 3 vecinos vivos, revive
                nextGrid[i][j] = vecinosVivos == 3;
            }
        }
    }

    // Actualizar el estado de la cuadrícula con el próximo estado
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = nextGrid[i][j];
        }
    }
}

// Función para mostrar la cuadrícula en una ventana
void mostrarCuadricula(bool grid[GRID_SIZE][GRID_SIZE]) {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Juego de la Vida");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Dibujar la cuadrícula en la ventana
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                window.setFramerateLimit(120);

                // Definir el color de las celdas según su estado (viva o muerta)
                if (grid[i][j]) {
                    cell.setFillColor(sf::Color::White); // Celda viva
                } else {
                    cell.setFillColor(sf::Color::Black); // Celda muerta
                }

                // Posicionar cada celda en la ventana
                cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);

                // Dibujar la celda en la ventana
                window.draw(cell);
            }
        }

        window.display();

        // Aplicar las reglas del Juego de la Vida y actualizar la cuadrícula
        aplicarReglasJuego(grid);

        sf::sleep(sf::milliseconds(500)); // Esperar 500 ms antes de la siguiente actualización
    }
}

int main() {
    // Crear una matriz bidimensional para representar el tablero
    bool grid[GRID_SIZE][GRID_SIZE];

    // Inicializar la cuadrícula con valores aleatorios
    inicializarCuadricula(grid);

    // Mostrar la cuadrícula en una ventana
    mostrarCuadricula(grid);

    return 0;
}
