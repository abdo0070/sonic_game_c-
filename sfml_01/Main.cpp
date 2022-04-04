#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
using namespace sf;
void update(RenderWindow& window, RectangleShape &rec);
void draw(RenderWindow& window, RectangleShape &rec);
int main() {
	RenderWindow window(VideoMode(1200, 800), "first game");
	RectangleShape rectangle (Vector2f(50.f, 50.f));
	rectangle.setFillColor(Color::Red);
	rectangle.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	 window.setFramerateLimit(120);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				window.close();
			}
			update(window, rectangle);
			draw(window, rectangle);
		}
	}
}
void update(RenderWindow& window, RectangleShape &rec)
{

	if (Keyboard::isKeyPressed(Keyboard::A)&&rec.getPosition().x>0) {
		rec.move(-10.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)&& rec.getPosition().y < window.getSize().y-rec.getSize().y) {
		rec.move(0.f, 10.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::W)&& rec.getPosition().y > 0) {
		rec.move(0.f, -10.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)&&rec.getPosition().x<(window.getSize().x)-rec.getSize().x) {
		rec.move(10.f,0.f);
	}
}
void draw(RenderWindow& window,RectangleShape &rec)
{
	window.clear(Color::White);
	window.draw(rec);
	window.display();
}
