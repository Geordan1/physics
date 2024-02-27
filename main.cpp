#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
//includes
class ball {
    public:
        int x;
        int y;
        int xSpeed;
        int ySpeed;
        int width;
        int height;
        void init(int x_, int y_, int x_speed, int y_speed) {
            x = x_;
            y = y_;
            xSpeed = x_speed;
            ySpeed = y_speed;
            width = 20;
            height = 20;
        }
        sf::Vector2f updateSize() {
            return sf::Vector2f(width,height);
        }
        sf::Vector2f updtaePos() {
            x += xSpeed;
            y += ySpeed;
            return sf::Vector2f(x,y);
        }
        void checkBounce() {
            if (y > 600-height) {
                y = 600-height;
                ySpeed = 0-ySpeed;
            }
        }
};
//classes

//functions
int main() {
    sf::RenderWindow window(sf::VideoMode(1000,600), "phiysics", sf::Style::Close | sf::Style::None);
    window.setFramerateLimit(30);
    std::vector<ball*> balls;
    balls.reserve(10);
    int grav = 1;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousepos = sf::Mouse::getPosition(window);
                balls.push_back(new ball);
                balls[balls.size()-1]->init(980, 580, 0-(1000-((int)mousepos.x))/30, (0-(600-((int)mousepos.y))/30)*2);
            }
        }
        window.clear(sf::Color(0,0,0));
        for (int i = 0; i < balls.size(); i++) {
            sf::RectangleShape shape;
            balls[i]->checkBounce();
            balls[i]->ySpeed += grav;
            std::cout<<balls[i]->x<<std::endl;
            std::cout<<balls[i]->y<<std::endl;
            shape.setSize(balls[i]->updateSize());
            shape.setPosition(balls[i]->updtaePos());
            shape.setFillColor(sf::Color(255,255,255));
            window.draw(shape);
        }
        window.display();
    }
    return 0;
}
//main