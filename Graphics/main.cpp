
#include <SFML/Graphics.hpp>
#include <functional> 
#include <cmath> 
#include <iostream>
void drawGraph(sf::RenderWindow& window, std::function<float(float)> func, float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x); 

      
        float screenX = 400 + x * scaleX;
        float screenY = 300 - y * scaleY;

        
        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}


float f1(float x) {
    return 0.1f * x * x - 5.0f;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graphs: y = 0.1x^2 - 5 and x = 0");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(16);
    coordinatesText.setFillColor(sf::Color::White);
    coordinatesText.setPosition(10, 10);

    sf::CircleShape userPoint(3);
    userPoint.setFillColor(sf::Color::Yellow);
    bool userPointExists = false;

    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(50, 300);
    xAxis[0].color = sf::Color::White;
    xAxis[1].position = sf::Vector2f(750, 300);
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 50);
    yAxis[0].color = sf::Color::White;
    yAxis[1].position = sf::Vector2f(400, 550);
    yAxis[1].color = sf::Color::White;
    sf::ConvexShape xArrow(3);
    xArrow.setPoint(0, sf::Vector2f(750, 300));
    xArrow.setPoint(1, sf::Vector2f(740, 295));
    xArrow.setPoint(2, sf::Vector2f(740, 305));
    xArrow.setFillColor(sf::Color::White);

    sf::ConvexShape yArrow(3);
    yArrow.setPoint(0, sf::Vector2f(400, 50));
    yArrow.setPoint(1, sf::Vector2f(395, 60));
    yArrow.setPoint(2, sf::Vector2f(405, 60));
    yArrow.setFillColor(sf::Color::White);

    sf::Text xLabel, yLabel;
    xLabel.setFont(font);
    yLabel.setFont(font);
    xLabel.setString("X");
    yLabel.setString("Y");
    xLabel.setCharacterSize(16);
    yLabel.setCharacterSize(16);
    xLabel.setFillColor(sf::Color::White);
    yLabel.setFillColor(sf::Color::White);
    xLabel.setPosition(760, 310);
    yLabel.setPosition(410, 40);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
             
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    
                    float mathX = (mousePos.x - 400) / 20.0f;
                    float mathY = -(mousePos.y - 300) / 20.0f;

                    
                    userPoint.setPosition(mousePos.x - userPoint.getRadius(),
                        mousePos.y - userPoint.getRadius());
                    userPointExists = true;

                    
                    std::string area = "Border";
                    const float eps = 1e-3f;

                    
                    bool onParabola = std::fabs(mathY - f1(mathX)) < eps;
                    bool onVerticalLine = std::fabs(mathX - 0.0f) < eps;

                    if (onParabola || onVerticalLine) {
                        area = "Border";
                    }
                    
                    else if (mathX > 0 && mathY > f1(mathX)) {
                        area = "Area 1";
                    }
                    else if (mathX > 0 && mathY < f1(mathX)) {
                        area = "Area 2";
                    }
                    else if (mathX < 0 && mathY > f1(mathX)) {
                        area = "Area 3";
                    }
                    else if (mathX < 0 && mathY < f1(mathX)) {
                        area = "Area 4";
                    }

                    
                    std::string coordinateString = "Coordinates: (" +
                        std::to_string(mathX).substr(0, 5) + ", " +
                        std::to_string(mathY).substr(0, 5) + ")\nPosition: " + area;
                    coordinatesText.setString(coordinateString);
                }
            }
        }

        
        window.clear(sf::Color::Black);

        
        window.draw(xAxis);
        window.draw(yAxis);
        window.draw(xArrow);
        window.draw(yArrow);
        window.draw(xLabel);
        window.draw(yLabel);

        
        sf::VertexArray grid(sf::Lines);
        for (int i = -10; i <= 10; i++) {
            if (i == 0) continue;

            
            float xPos = 400 + i * 20;
            grid.append(sf::Vertex(sf::Vector2f(xPos, 50), sf::Color(50, 50, 50)));
            grid.append(sf::Vertex(sf::Vector2f(xPos, 550), sf::Color(50, 50, 50)));

            
            float yPos = 300 + i * 20;
            grid.append(sf::Vertex(sf::Vector2f(50, yPos), sf::Color(50, 50, 50)));
            grid.append(sf::Vertex(sf::Vector2f(750, yPos), sf::Color(50, 50, 50)));
        }
        window.draw(grid);

        
        for (int i = -10; i <= 10; i += 2) {
            if (i == 0) continue;

           
            sf::Text xText;
            xText.setFont(font);
            xText.setString(std::to_string(i));
            xText.setCharacterSize(12);
            xText.setFillColor(sf::Color::White);
            xText.setPosition(400 + i * 20 - 10, 310);
            window.draw(xText);

            
            sf::Text yText;
            yText.setFont(font);
            yText.setString(std::to_string(-i));
            yText.setCharacterSize(12);
            yText.setFillColor(sf::Color::White);
            yText.setPosition(410, 300 + i * 20 - 10);
            window.draw(yText);
        }

        
        drawGraph(window, f1, -10.0f, 10.0f, 20.0f, 20.0f, sf::Color::Blue);

        
        sf::VertexArray verticalLine(sf::Lines, 2);
        verticalLine[0] = sf::Vertex(sf::Vector2f(400, 50), sf::Color::Red);
        verticalLine[1] = sf::Vertex(sf::Vector2f(400, 550), sf::Color::Red);
        window.draw(verticalLine);

        
        sf::Text line1Label, line2Label;
        line1Label.setFont(font);
        line2Label.setFont(font);
        line1Label.setString("y = 0.1x^2 - 5");
        line2Label.setString("x = 0");
        line1Label.setCharacterSize(14);
        line2Label.setCharacterSize(14);
        line1Label.setFillColor(sf::Color::Blue);
        line2Label.setFillColor(sf::Color::Red);
        line1Label.setPosition(500, 100);
        line2Label.setPosition(410, 250);
        window.draw(line1Label);
        window.draw(line2Label);

        
        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
        }

        
        window.display();
    }

    return 0;
}