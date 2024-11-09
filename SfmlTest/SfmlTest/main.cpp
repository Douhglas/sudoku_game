#include <SFML/Graphics.hpp>
#include <string>
#include "sudokuMatriz.h"
#include "fileManager.h"

using namespace std;

const int CELL_SIZE = 30;
const int SPACING = 5;    
const int GRID_SIZEe = 9;  

sudokuMatriz sudokuMat;
bool isSelected = false;
sf::Font font;
int selectedRow = -1;
int selectedCol = -1;

sf::Text initText(const string& value, int x, int y) {
    sf::Text text;
    text.setFont(font);
    text.setString(value);
    text.setCharacterSize(20); 
    text.setPosition(x, y);
    text.setFillColor(sf::Color::Blue);
    return text;
}

void initMatriz(sf::RenderWindow& window) {
    for (int i = 0; i < GRID_SIZEe; i++) {
        for (int j = 0; j < GRID_SIZEe; j++) {
            sf::RectangleShape nuevaCelda;
            nuevaCelda.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            float x = (j * (CELL_SIZE + SPACING)) + 100; 
            float y = (i * (CELL_SIZE + SPACING)) + 100;
            nuevaCelda.setPosition(x, y);

            if (i == selectedRow && j == selectedCol) {
                nuevaCelda.setFillColor(sf::Color::Yellow); 
            }
            else {
                nuevaCelda.setFillColor(sf::Color::White);
            }

            window.draw(nuevaCelda);

            int valor = sudokuMat.obtenerValor(i, j);
            if (valor != 0) { 
                sf::Text nuevoTexto = initText(to_string(valor), x + 5, y + 5); 
                window.draw(nuevoTexto);
            }
        }
    }
}

void handleMouseClick(int mouseX, int mouseY) {
    for (int i = 0; i < GRID_SIZEe; i++) {
        for (int j = 0; j < GRID_SIZEe; j++) {
            float x = (j * (CELL_SIZE + SPACING)) + 100;
            float y = (i * (CELL_SIZE + SPACING)) + 100;

            if (mouseX >= x && mouseX <= x + CELL_SIZE &&
                mouseY >= y && mouseY <= y + CELL_SIZE) {

                selectedRow = i;
                selectedCol = j;
                isSelected = true;
                return;
            }
        }
    }
}

void handleNumberInput(int number) {
    if (isSelected && selectedRow != -1 && selectedCol != -1) {
        sudokuMat.cambiarValor(selectedRow, selectedCol, number);
    }
}

void handleNewGameClick(int mouseX, int mouseY) {
    float btnX = 600;
    float btnY = 50;
    float btnWidth = 185;
    float btnHeight = 50;

    if (mouseX >= btnX && mouseX <= btnX + btnWidth &&
        mouseY >= btnY && mouseY <= btnY + btnHeight) {
        sudokuMat.inicializar();
        selectedRow = -1;
        selectedCol = -1;
        isSelected = false;
    }
}

void handleSolveClick(int mouseX, int mouseY) {
    float btnX = 600;
    float btnY = 190; 
    float btnWidth = 185;
    float btnHeight = 50;

    if (mouseX >= btnX && mouseX <= btnX + btnWidth &&
        mouseY >= btnY && mouseY <= btnY + btnHeight) {
        if (sudokuMat.resolver()) {
            cout << "Sudoku resuelto!" << endl;
        }
        else {
            cout << "No tiene solución." << endl;
        }
    }
}

void handleCheckClick(int mouseX, int mouseY) {
    float btnX = 600;
    float btnY = 120;
    float btnWidth = 185;
    float btnHeight = 50;

    if (mouseX >= btnX && mouseX <= btnX + btnWidth &&
        mouseY >= btnY && mouseY <= btnY + btnHeight) {
        if (sudokuMat.esValido()) {
            cout << "Es Valido" << endl;
        }
        else {
            cout << "No es Valido" << endl;
        }
    }
}
string obtenerNombreArchivo(sf::RenderWindow& window, const string& mensaje) {
    sf::Text prompt;
    prompt.setFont(font);
    prompt.setString(mensaje);
    prompt.setCharacterSize(20);
    prompt.setFillColor(sf::Color::White);
    prompt.setPosition(100, 250);

    string nombreArchivo;
    sf::Text archivoTexto = initText("", 300, 300);

    while (true) {
        window.clear();
        window.draw(prompt);
        archivoTexto.setString(nombreArchivo);
        window.draw(archivoTexto);
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !nombreArchivo.empty()) {
                    nombreArchivo.pop_back(); 
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                    nombreArchivo += static_cast<char>(event.text.unicode);
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                return nombreArchivo; 
            }
        }
    }
}

void handleGuardarClick(int mouseX, int mouseY, sf::RenderWindow& window) {
    float btnX = 600;
    float btnY = 260;
    float btnWidth = 185;
    float btnHeight = 50;

    if (mouseX >= btnX && mouseX <= btnX + btnWidth && mouseY >= btnY && mouseY <= btnY + btnHeight) {
        string nombreArchivo = obtenerNombreArchivo(window, "Ingrese el nombre del archivo para guardar, Presiona enter al terminar:");
        fileManager::guardarMatriz(sudokuMat, nombreArchivo + ".txt");
    }
}

void handleCargarClick(int mouseX, int mouseY, sf::RenderWindow& window) {
    float btnX = 600;
    float btnY = 330;
    float btnWidth = 185;
    float btnHeight = 50;

    if (mouseX >= btnX && mouseX <= btnX + btnWidth && mouseY >= btnY && mouseY <= btnY + btnHeight) {
        string nombreArchivo = obtenerNombreArchivo(window, "Ingrese el nombre del archivo para cargar, Presiona enter al terminar:");
        fileManager::cargarMatriz(sudokuMat, nombreArchivo + ".txt");
        sudokuMat.mostrar();
    }
}



int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sudoku");

    if (!font.loadFromFile("Helnore-Regular.ttf")) {
        return -1;
    }

    sf::RectangleShape btnNuevoJuego;
    btnNuevoJuego.setSize(sf::Vector2f(185, 50));
    btnNuevoJuego.setPosition(600, 50);
    sf::Text btnTextNew = initText("Nuevo Juego", 620, 60);

    sf::RectangleShape btnRevisar;
    btnRevisar.setSize(sf::Vector2f(185, 50));
    btnRevisar.setPosition(600, 120);
    sf::Text btnTextCheck = initText("Revisar", 650, 130);

    sf::RectangleShape btnResolver;
    btnResolver.setSize(sf::Vector2f(185, 50));
    btnResolver.setPosition(600, 190);
    sf::Text btnTextSolve = initText("Resolver", 650, 200);

    sf::RectangleShape btnGuardar;
    btnGuardar.setSize(sf::Vector2f(185, 50));
    btnGuardar.setPosition(600, 260);
    sf::Text btnTextSave = initText("Guardar", 650, 270);

    sf::RectangleShape btnCargar;
    btnCargar.setSize(sf::Vector2f(185, 50));
    btnCargar.setPosition(600, 330);
    sf::Text btnTextLoad = initText("Cargar", 650, 340);


    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Instrucciones:\n- Haga clic en una celda para seleccionarla.\n- Presione un número (1-9) para cambiar el valor.\n- Haga clic en 'Nuevo Juego' para reiniciar.\n- Haga clic en 'Revisar' para validar el Sudoku.");
    instructions.setCharacterSize(18);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(800 - instructions.getLocalBounds().width - 20, 600 - instructions.getLocalBounds().height - 20);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    handleNewGameClick(mouseX, mouseY);
                    handleCheckClick(mouseX, mouseY);
                    handleGuardarClick(mouseX, mouseY,window);
                    handleCargarClick(mouseX, mouseY,window);
                    
                    handleSolveClick(mouseX, mouseY);  
                    handleMouseClick(mouseX, mouseY);
                }
            }
            if (event.type == sf::Event::KeyPressed && isSelected) {
                if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9) {
                    int number = event.key.code - sf::Keyboard::Num0;
                    handleNumberInput(number);
                }
            }
        }

        window.clear();
        initMatriz(window);
        window.draw(btnNuevoJuego);
        window.draw(btnTextNew);
        window.draw(btnRevisar);
        window.draw(btnTextCheck);
        window.draw(btnResolver);   
        window.draw(btnTextSolve);   
        window.draw(instructions);
        window.draw(btnGuardar);
        window.draw(btnTextSave);
        window.draw(btnCargar);
        window.draw(btnTextLoad);

        window.display();
    }

    return 0;
}
