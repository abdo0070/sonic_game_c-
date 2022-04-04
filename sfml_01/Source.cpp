#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
using namespace sf;
void move(RenderWindow& window, Sprite& sonic);
int score = 0, time1 = 10, time2 = 0;
int x, y;
int click = 0;
int main() {
	bool jumb = false, button = true;
	const int gravity = 18;
	int  mass = 50;
	// vec
	RenderWindow window(VideoMode(800, 600), "Sonic");
	window.setFramerateLimit(30);
	Texture sonicF;
	sonicF.loadFromFile("Tex/SonicAnimation.png");
	Sprite sonic(sonicF);
	// this to make photo subrectangles
	sf::IntRect r(0, 0, 40, 50);
	sonic.setScale(2.5f, 2.5f);
	// font and texts
	Font font;
	font.loadFromFile("Font/font.ttf");
	std::string t1 = "EXIT", t = "PLAY";
	Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold);
	text.setString(t);
	Text text1;
	text1.setFont(font);
	text1.setCharacterSize(24);
	text1.setFillColor(Color::White);
	text1.setStyle(Text::Bold);
	text1.setString(t1);
	// the mouse 
	Texture m;
	m.loadFromFile("Tex/mouse.png");
	Sprite mouse(m);
	mouse.setScale(0.08f, 0.08f);
	// this to set postitions of PLAY and EXIT
	int Ylimite = window.getSize().y;
	int select = 0;
	text.setPosition(window.getSize().x / 2, 150);
	text1.setPosition(window.getSize().x / 2, 450);
	// background
	RectangleShape background(Vector2f(window.getSize().x, window.getSize().y));
	Texture back;
	back.loadFromFile("Tex/background1.jfif");
	background.setTexture(&back);

	void UI(RenderWindow & window, Text & text, Text & text1, Sprite & mouse, RectangleShape & background);
	while (window.isOpen()) {
		Event event;


		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		//UPDATE 
		// this is the main game
		// DRAW
		window.clear(Color::White);
		//move(window,sonic);
		if (click == 0)
			UI(window, text1, text, mouse, background);
		if (click == 1)
			move(window, sonic);
		window.setMouseCursorVisible(false);
		window.display();
	}

}
void move(RenderWindow& window, Sprite& sonic) {
	sf::IntRect r(23 * x, y, 36, 41);
	sonic.setTextureRect(r);
	if (Keyboard::isKeyPressed(Keyboard::Down) && sonic.getPosition().y < window.getSize().y - .5 * sonic.getScale().y) {
		sonic.move(0.f, 10.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) && sonic.getPosition().y >= 0) {
		sonic.move(0.f, -10.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && sonic.getPosition().x <= window.getSize().x) {

		y = 0;
		/*	x++;
			x %= 10;*/
		sf::IntRect r(23 * x, y, 36, 41);
		sonic.setTextureRect(r);
		sonic.move(10.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && sonic.getPosition().x >= 0) {
		y = 1;
		//x++;
		//x %= 9;
		sf::IntRect r(36, y, -36, 41);
		sonic.setTextureRect(r);
		sonic.move(-10.f, 0.f);
	}
	window.draw(sonic);
}
void UI(RenderWindow& window, Text& text, Text& text1, Sprite& mouse, RectangleShape& background) {
	// draw
	window.draw(background);
	window.draw(mouse);
	window.draw(text);
	window.draw(text1);
	// this two switch between play and exit
	if (time1 < 10)
		time1++;
	if (time2 < 10)
		time2++;
	if (Keyboard::isKeyPressed(Keyboard::Up) && time1 >= 10 || Keyboard::isKeyPressed(Keyboard::Down) && time1 >= 10) {
		score++;
		time1 = 0;
	}
	if (score % 2 == 0) {
		text.setFillColor(Color::Red);
		text1.setFillColor(Color::Black);
	}
	if (score % 2 == 1) {
		text.setFillColor(Color::Black);
		text1.setFillColor(Color::Red);
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && score % 2 == 0 && time2 >= 10) {
		window.close();
		time2 = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && score % 2 == 1 && time2 >= 10) {
		std::cout << "play is pressed\n";
		click = 1;
		time2 = 0;
	}

	// Mouse postition and collistions
	mouse.setPosition(Mouse::getPosition().x, Mouse::getPosition().y);
	if (mouse.getGlobalBounds().intersects(text1.getGlobalBounds())) {
		text1.setFillColor(Color::Red);
		text.setFillColor(Color::Black);
	}
	if (mouse.getGlobalBounds().intersects(text.getGlobalBounds())) {
		text.setFillColor(Color::Red);
		text1.setFillColor(Color::Black);
	}
	if (mouse.getGlobalBounds().intersects(text1.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		click == 1;
	}
	if (mouse.getGlobalBounds().intersects(text.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		window.close();

	}
}
