#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#define SIZE 3
#define GRID_SIZE 9

class sudokuMatriz {
public:
    struct MiniMatriz {
        int valores[SIZE][SIZE];

        bool esInicial[SIZE][SIZE]; 

        MiniMatriz() {
            for (int i = 0; i < SIZE; ++i)
                for (int j = 0; j < SIZE; ++j)
                    esInicial[i][j] = false; 
        }
    };

    MiniMatriz matrizGrande[SIZE][SIZE];

    sudokuMatriz() {
        srand(static_cast<unsigned int>(time(0)));
        inicializarMatriz();
        generarTablero();
    }


    void inicializar() {
        srand(static_cast<unsigned int>(time(0)));
        inicializarMatriz();
        generarTablero();
    }

    void inicializarMatriz() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int x = 0; x < SIZE; ++x) {
                    for (int y = 0; y < SIZE; ++y) {
                        matrizGrande[i][j].valores[x][y] = 0;
                        matrizGrande[i][j].esInicial[x][y] = false;  
                    }
                }
            }
        }
    }
    void cambiarValor(int fila, int col, int nuevoValor) {
        if (fila < 0 || fila >= GRID_SIZE || col < 0 || col >= GRID_SIZE) {
            std::cerr << "Error: Índices fuera de rango" << std::endl;
            return;
        }

        if (matrizGrande[fila / SIZE][col / SIZE].esInicial[fila % SIZE][col % SIZE]) {
            std::cerr << "Error: No se puede cambiar el valor inicial en (" << fila << ", " << col << ")" << std::endl;
            return;
        }

        matrizGrande[fila / SIZE][col / SIZE].valores[fila % SIZE][col % SIZE] = nuevoValor;
    }

    void generarTablero() {
        int numeroIniciales = 20;
        while (numeroIniciales > 0) {
            int fila = rand() % GRID_SIZE;
            int col = rand() % GRID_SIZE;
            int num = 1 + rand() % GRID_SIZE;

            if (obtenerValor(fila, col) == 0 && esSeguro(fila, col, num)) {
                matrizGrande[fila / SIZE][col / SIZE].valores[fila % SIZE][col % SIZE] = num;
                matrizGrande[fila / SIZE][col / SIZE].esInicial[fila % SIZE][col % SIZE] = true;  
                numeroIniciales--;
            }
        }
    }

    bool esValido() const {
        for (int i = 0; i < GRID_SIZE; i++) {
            bool numerosFila[GRID_SIZE + 1] = { false };
            bool numerosColumna[GRID_SIZE + 1] = { false };

            for (int j = 0; j < GRID_SIZE; j++) {
                int numFila = obtenerValor(i, j);
                if (numFila != 0) {
                    if (numerosFila[numFila]) {
                        return false; 
                    }
                    numerosFila[numFila] = true;
                }
                int numColumna = obtenerValor(j, i);
                if (numColumna != 0) {
                    if (numerosColumna[numColumna]) {
                        return false; 
                    }
                    numerosColumna[numColumna] = true;
                }
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                bool numerosSubmatriz[GRID_SIZE + 1] = { false };

                for (int x = 0; x < SIZE; x++) {
                    for (int y = 0; y < SIZE; y++) {
                        int num = matrizGrande[i][j].valores[x][y];
                        if (num != 0) {
                            if (numerosSubmatriz[num]) {
                                return false; 
                            }
                            numerosSubmatriz[num] = true;
                        }
                    }
                }
            }
        }

        return true;
    }

    bool esSeguro(int fila, int col, int num) {
        int gridRow = fila / SIZE, gridCol = col / SIZE;

        for (int i = 0; i < GRID_SIZE; i++) {
            if (obtenerValor(fila, i) == num || obtenerValor(i, col) == num) {
                return false;
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (matrizGrande[gridRow][gridCol].valores[i][j] == num) {
                    return false;
                }
            }
        }
        return true;
    }

    int obtenerValor(int fila, int col) const {
        return matrizGrande[fila / SIZE][col / SIZE].valores[fila % SIZE][col % SIZE];
    }
   
    bool resolver() {
        return resolverSudoku(0, 0);
    }

    bool resolverSudoku(int fila, int col) {
        if (fila == GRID_SIZE) {
            return true;
        }

        if (col == GRID_SIZE) {
            return resolverSudoku(fila + 1, 0);
        }
        if (obtenerValor(fila, col) != 0) {
            return resolverSudoku(fila, col + 1);
        }


        for (int num = 1; num <= GRID_SIZE; num++) {

            if (esSeguro(fila, col, num)) {

                cambiarValor(fila, col, num);

 
                if (resolverSudoku(fila, col + 1)) {
                    return true;
                }
                cambiarValor(fila, col, 0);
            }
        }

        return false;
    }



    void mostrar() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int x = 0; x < SIZE; ++x) {
                for (int j = 0; j < SIZE; ++j) {
                    for (int y = 0; y < SIZE; ++y) {
                        std::cout << matrizGrande[i][j].valores[x][y] << " ";
                    }
                    std::cout << " | ";
                }
                std::cout << std::endl;
            }
            std::cout << "-----------------------------" << std::endl;
        }
    }
};