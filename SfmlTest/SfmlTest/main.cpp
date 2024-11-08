#include <SFML/Graphics.hpp>
#include <String>
using namespace std;

//struct celda {
//public:
//    float posX;
//    float posY;
//    string tipoCelda; //suelo,pared,caja,personaje?
//};
sf::RectangleShape matrizGrande[3][3];
sf::Font font = sf::Font();

sf::Text initText(string value, int x, int y) {
    sf::Text text = sf::Text();
    sf::Vector2f size = sf::Vector2f(15, 15);
    text.setFont(font);
    text.setString(value);
    text.setPosition(x, y);
    text.setFillColor(sf::Color::Blue);
    return text;
}

void initMatriz(sf::RenderWindow& window , int I , int  J) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sf::RectangleShape matriz[3][3];
            sf::Text matrizLetras[3][3];
            sf::RectangleShape nuevaCelda;
            sf::Vector2f size = sf::Vector2f(30,30);
            nuevaCelda.setSize(size);
            float x = ((j * 32) + 100) + (J * 96);
            float y = ((i * 32) + 100) + (I * 96); 
            nuevaCelda.setPosition(x,y);
            matriz[i][j] = nuevaCelda;
            window.draw(matriz[i][j]);
            sf::Text nuevoTexto = initText(to_string(i), x, y);
            matrizLetras[i][j] = nuevoTexto;
            window.draw(matrizLetras[i][j]);
        }
    }
    
}
int main() {
    // Crear una ventana de 800x600 píxeles con el título "SFML Window"
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    sf::RectangleShape btnNuevoJuego = sf::RectangleShape();
    btnNuevoJuego.setPosition(600, 50);
    sf::Vector2f vector = sf::Vector2f(185, 50);
    btnNuevoJuego.setSize(vector);
    sf::Text btnText = initText("Nuevo Juego",600,50);
    
    if (!font.loadFromFile("Helnore-Regular.ttf")) {  
        return -1;                         
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                initMatriz(window, i, j);
            }
        }
        window.draw(btnNuevoJuego);
        window.draw(btnText);
        window.display();
    }

    return 0;
}