#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    // Labirinto
    std::vector<std::vector<int>> labirinto = {
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 0, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 0, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0}
    };

    // Configurações da janela
    const int tileSize = 30;
    const int rows = labirinto.size();
    const int cols = labirinto[0].size();
    sf::RenderWindow window(sf::VideoMode(cols * tileSize, rows * tileSize), "Labirinto");

    // Carregando texturas
    sf::Texture textureWhite, textureBlack;
    textureWhite.create(tileSize, tileSize);
    textureBlack.create(tileSize, tileSize);
    sf::Uint8* pixelsWhite = new sf::Uint8[tileSize * tileSize * 4];
    sf::Uint8* pixelsBlack = new sf::Uint8[tileSize * tileSize * 4];
    for (int i = 0; i < tileSize * tileSize * 4; i += 4) {
        pixelsWhite[i] = 255;  // R
        pixelsWhite[i + 1] = 255;  // G
        pixelsWhite[i + 2] = 255;  // B
        pixelsWhite[i + 3] = 255;  // A (opacidade)
        pixelsBlack[i] = 0;  // R
        pixelsBlack[i + 1] = 0;  // G
        pixelsBlack[i + 2] = 0;  // B
        pixelsBlack[i + 3] = 255;  // A (opacidade)
    }
    textureWhite.update(pixelsWhite);
    textureBlack.update(pixelsBlack);
    delete[] pixelsWhite;
    delete[] pixelsBlack;

    // Loop principal
    while (window.isOpen()) {
        // Processamento de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Desenho do labirinto
        window.clear();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                sf::Sprite sprite;
                sprite.setPosition(j * tileSize, i * tileSize);
                sprite.setTexture(labirinto[i][j] == 0 ? textureWhite : textureBlack);
                window.draw(sprite);
            }
        }
        window.display();
    }

    return 0;
}
