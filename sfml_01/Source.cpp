#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
using namespace sf;
void move(RenderWindow& window, Sprite& sonic);
int main() {
	RenderWindow window(VideoMode(800, 600), "Sonic");
	window.setFramerateLimit(30);
	Texture sonicF;
	sonicF.loadFromFile("Tex/sonic.jfif");
	Sprite sonic(sonicF);
	sonic.setScale(0.4f, 0.4f);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		//update 
		window.clear(Color::White);
		move(window, sonic);
		// draw
		window.draw(sonic);
		window.display();
	}
}
void move(RenderWindow& window, Sprite& sonic) {
	if (Keyboard::isKeyPressed(Keyboard::Down) && sonic.getPosition().y < window.getSize().y - .5 * sonic.getScale().y) {
		sonic.move(0.f, 10.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) && sonic.getPosition().y >= 0) {
		sonic.move(0.f, -10.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && sonic.getPosition().x <= window.getSize().x) {
		sonic.move(10.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && sonic.getPosition().x >= 0) {
		sonic.move(-10.f, 0.f);
	}
}