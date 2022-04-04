#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace sf;
// the defination of functions
void hoop(RenderWindow &window , CircleShape & c);
void shooting_ball(RenderWindow& window, CircleShape& c1 ,CircleShape& c2);
int main() {
	RenderWindow window(VideoMode(800, 600), "Shooting");
	// first circle define
	CircleShape c1(50.f);
	c1.setFillColor(Color::Blue);
	c1.setOutlineThickness(5);
	c1.setOutlineColor(Color::Magenta);
	c1.setPosition(0.f, 5.f);
	// second circle define 
	CircleShape c2(35.f);
	c2.setFillColor(Color::Red);
	c2.setPosition(Vector2f(0.f, window.getSize().y - c1.getRadius() * 2 - 15.f));
	window.setFramerateLimit(60);
	// the main while for the game
	while (window.isOpen()) {
		Event event;
		// this for close the window 
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		hoop(window, c1);
		shooting_ball(window, c2,c1);
		window.display();
		window.clear(Color::White);
	}
}
int dir;
void hoop(RenderWindow& window, CircleShape& c) {
	if (c.getPosition().x <= 0) {
	dir = 1;
	}
	else if (c.getPosition().x+c.getRadius()*2 >= window.getSize().x) {
		dir = 0;
	}
	if (dir == 0) {
		c.move(-7.f, 0);
	}
	else{
		c.move(7.f, 0);
	}
	window.draw(c);
}
int score;
bool isShot = false;
void shooting_ball(RenderWindow &window,CircleShape &c1, CircleShape& c2) {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		isShot = true;
	}
	if(!isShot) {
		c1.setPosition(Mouse::getPosition(window).x, c1.getPosition().y);
	}
	else {
		c1.move(0, -20.f);
	}
	if (c1.getGlobalBounds().intersects(c2.getGlobalBounds())) {
		score++;
	}
	if (c1.getPosition().y <= 0||c1.getGlobalBounds().intersects(c2.getGlobalBounds())) {
		// reset the position of the ball
		isShot = false;
		c1.setPosition(Vector2f(0.f, window.getSize().y - c1.getRadius() * 2 - 15.f));
	}
	window.draw(c1);
}