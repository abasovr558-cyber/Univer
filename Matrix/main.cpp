#include <SFML/Graphics.hpp>
#include <string>

int main() {
    const int windowSize = 500;
    const int gridSize = 10;
    const int cellSize = windowSize / gridSize;
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Matrix");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(j * cellSize, i * cellSize);

                if (i + j <= gridSize - 1) {
                    if ((i + j) % 2 == 0) {
                        cell.setFillColor(sf::Color::White); 
                    }
                    else {
                        cell.setFillColor(sf::Color(144, 238, 144)); 
                    }
                }
                else {
                    cell.setFillColor(sf::Color::White);
                }

                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);

                window.draw(cell);
            }
        }

        window.display();
    }

    return 0;
}