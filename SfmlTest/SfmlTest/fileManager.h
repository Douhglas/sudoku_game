#pragma once
#include <fstream>
#include "sudokuMatriz.h"
#include <iostream>
#include <string>
#include <sstream>

class fileManager {
public:
    static void guardarMatriz(const sudokuMatriz& sudoku, const std::string& nombreArchivo) {
        std::ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo para guardar" << std::endl;
            return;
        }

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int x = 0; x < SIZE; ++x) {
                    for (int y = 0; y < SIZE; ++y) {
                        archivo << sudoku.matrizGrande[i][j].valores[x][y] << " ";
                    }
                    archivo << std::endl;
                }
                archivo << "-----------------------------" << std::endl;
            }
        }

        archivo.close();
        std::cout << "Matriz guardada en " << nombreArchivo << std::endl;
    }

    static void cargarMatriz(sudokuMatriz& sudoku, const std::string& nombreArchivo) {
        std::ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo para cargar" << std::endl;
            return;
        }

        std::string linea;
        int i = 0, j = 0, x = 0, y = 0; 

        while (getline(archivo, linea)) {

            if (linea.find("-----") != std::string::npos) {
                j++;
                if (j == SIZE) {
                    j = 0;
                    i++;
                }
                x = 0; 
                continue;
            }

            std::istringstream ss(linea);
            int valor;
            y = 0; 
            while (ss >> valor) {
                sudoku.matrizGrande[i][j].valores[x][y] = valor;
                y++;
            }
            x++; 
            if (x == SIZE) {
                x = 0;
            }
        }

        archivo.close();
        std::cout << "Matriz cargada desde " << nombreArchivo << std::endl;
    }
};
