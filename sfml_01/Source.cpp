#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>

#define X 36
#define Y 41
#define WIDTH 1280
#define HEIGHT 720

using namespace sf;
void SONIC_ANIMATION(RenderWindow& window, Sprite& sonic, View& camera);
void GameWorld(RenderWindow& window, Sprite& flag, Sprite Catus[5], Sprite Block1[10], Sprite Block2[10], Sprite backgroundArr[10], Sprite& ground, Sprite& background);
void UI(RenderWindow& window, Text& text, Text& text1, Sprite& mouse, RectangleShape& background);
void Intersections(RenderWindow& window, Sprite& Sonic, Sprite catus[5], Sprite& flag);
void CameraView(RenderWindow& window, View& camera, Sprite& sonic);
void RESUME(RenderWindow& window, Text& text, Text& text1, Sprite& mouse, RectangleShape& background);
void jump(RenderWindow& window, Sprite& sonic);
void END();

int score = 0, time1 = 10, time2 = 0;
int x = 0, y = 0;
int click = 0;
struct pos {
	int x, y;
}sonicPos;

bool rs = false;
static const int SONIC_Y_BUTTOM = HEIGHT - 60;

float frame = 0.f;
float frameSpeed = 0.4f;
const int changeCount = 5;
const int gravity = 5;
bool isJumping = false;
bool isBottom = true;
int main(void) {
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Sonic");
	window.setFramerateLimit(30);
	// Camera view
	View camera;
	camera.setCenter(Vector2f(350.f, 200.f));
	camera.setSize(Vector2f(800.f, 400.f));
	// SONIC
	Texture sonicF;
	sonicF.loadFromFile("Tex/SonicAnimation.png");
	Sprite sonic(sonicF);
	// this to make photo subRectangles
	sonic.setTextureRect(IntRect(x * X, Y * 41, X, Y));



	// font and texts
	Font font;
	font.loadFromFile("Font/font.ttf");
	std::string exit = "EXIT", play = "PLAY", resume = "RESUME";
	Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold);
	text.setString(play);
	Text text1;
	text1.setFont(font);
	text1.setCharacterSize(24);
	text1.setFillColor(Color::White);
	text1.setStyle(Text::Bold);
	text1.setString(exit);

	Text text2;
	text2.setFont(font);
	text2.setCharacterSize(24);
	text2.setFillColor(Color::White);
	text2.setStyle(Text::Bold);
	text2.setString(resume);

	text.setPosition((float)window.getSize().x / 2, 150.f);
	text1.setPosition((float)window.getSize().x / 2, 450.f);
	text2.setPosition((float)camera.getCenter().x / 2, 150.f);

	sonicPos.x = (int)sonic.getGlobalBounds().width;
	sonicPos.y = SONIC_Y_BUTTOM;
	// the mouse 
	Texture Mouse;
	Mouse.loadFromFile("Tex/mouse.png");
	Sprite mouse(Mouse);
	mouse.setScale(0.08f, 0.08f);

	// this to set postitions of PLAY and EXIT
	int Ylimite = window.getSize().y;
	int select = 0;
	// background for UI
	RectangleShape backgroundForUI(Vector2f((float)window.getSize().x, (float)window.getSize().y));
	Texture back;
	back.loadFromFile("Tex/background.jpg");
	backgroundForUI.setTexture(&back);

	// background for End 

	Texture backEnd;
	RectangleShape backgroundForEnd(Vector2f(camera.getCenter().x, camera.getCenter().y));
	backEnd.loadFromFile("Tex/background.jfif");
	backgroundForEnd.setTexture(&backEnd);


	//Background for GAME
	Texture Background;
	Background.loadFromFile("Tex/background.JPEG");
	Sprite background;
	background.setTexture(Background);
	background.setScale(0.5f, 0.6f);
	background.setPosition(-50.f, 0.f);
	Sprite spritesbackground[10];
	for (int i = 0; i < 10; i++) {
		spritesbackground[i] = background;
		spritesbackground[i].setPosition(-50.f + ((float)i * 565), 0);
	}

	//ground
	Texture Ground;
	Ground.loadFromFile("Tex/ground.PNG");
	Sprite ground;
	ground.setTexture(Ground);
	ground.setScale(0.5f, 0.6f);
	ground.setPosition(-50, 343);
	Sprite spritesground[20];
	for (int i = 0; i < 20; i++) {
		spritesground[i] = ground;
		spritesground[i].setPosition(-50 + ((float)i * 410), 343);
	}

	//First Block 
	Texture Stblock;
	Stblock.loadFromFile("Tex/firstblock.PNG");
	Sprite stblock;
	stblock.setTexture(Stblock);
	stblock.setScale(0.5, 0.5);
	Sprite spritesstblock[5];
	for (int i = 0; i < 5; i++) {
		spritesstblock[i] = stblock;
		spritesstblock[i].setPosition(300 + ((float)i * 1000), 223);
	}

	//second block 
	Texture Ndblock;
	Ndblock.loadFromFile("Tex/secondblock.PNG");
	Sprite ndblock;
	ndblock.setTexture(Ndblock);
	ndblock.setScale(0.35f, 0.35f);
	Sprite spritesndblock[5];
	for (int i = 0; i < 5; i++) {
		spritesndblock[i] = ndblock;
		spritesndblock[i].setPosition(850 + ((float)i * 1000), 170);
	}

	//Cactus
	Texture Cactus;
	Cactus.loadFromFile("Tex/cactus.PNG");
	Sprite cactus;
	cactus.setTexture(Cactus);
	cactus.setScale(0.23f, 0.23f);
	Sprite spritescactus[5];
	for (int i = 0; i < 5; i++) {
		spritescactus[i] = cactus;
		spritescactus[i].setPosition(350 + ((float)i * 1000), 235);
	}

	//Flag
	Texture Flag;
	Flag.loadFromFile("Tex/flag.PNG");
	Sprite flag;
	flag.setTexture(Flag);
	flag.setScale(0.5, 0.5);
	flag.setPosition(5200, 127);


	sonic.setOrigin(sonic.getGlobalBounds().width, -300);

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

		if (click == 0)
			UI(window, text1, text, mouse, backgroundForUI);
		if (click == 1 && !rs) {
			SONIC_ANIMATION(window, sonic, camera);
			GameWorld(window, flag, spritescactus, spritesstblock, spritesndblock, spritesbackground, ground, background);
			Intersections(window, sonic, spritescactus, flag);
			jump(window, sonic);
			CameraView(window, camera, sonic);
			window.setView(camera);
			window.draw(sonic);
			window.draw(flag);
			if (Keyboard::isKeyPressed(Keyboard::Tab)) {
				rs = true;
			}
		}
		if (click == 1 && rs) {
			RESUME(window, text1, text2, mouse, backgroundForEnd);
		}
		window.setMouseCursorVisible(false);
		window.display();
	}
}
void Intersections(RenderWindow& window, Sprite& Sonic, Sprite catus[5], Sprite& flag) {

	// this for Catus
	for (int i = 0; i < 5; i++)
	{
		if (Sonic.getGlobalBounds().intersects(catus[i].getGlobalBounds())) {
			// WHAT WILL HAPPEND
		}
	}
	// this for flag 

	if (Sonic.getGlobalBounds().intersects(flag.getGlobalBounds())) {
		click = 2;
	}
	// for Coin



	// for Animals


	// for enemies


}
void SONIC_ANIMATION(RenderWindow& window, Sprite& sonic, View& camera) {
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		y = 0;
		sonic.setTextureRect(IntRect(X * x, y * Y, X, Y));
		x++;
		x %= 9;
		sonic.move(4.f, 0.f);
	}

	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		y = 0;
		sonic.setTextureRect(IntRect(X * x, Y * y, -X, Y));
		x %= 9;
		x++;
		if (x > 9) {
			x = 0;
		}
		sonic.move(-4.f, 0.f);
	}

	else if (Keyboard::isKeyPressed(Keyboard::Space)) {
		// here will be jump animation

	}

	else {
		y = 1;
		sonic.setTextureRect(IntRect(x * X - 5, y * Y, X, Y));
		x %= 1;
		x++;
		if (x > 1) {
			x = 0;
		}
	}

}
void jump(RenderWindow& window, Sprite& sonic) {
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		//std::cout << "Space is pressed";
		if (isBottom && !isJumping)
		{
			//make jumping stage;
			isJumping = true;
			isBottom = false;
		}
	}

	//sonic jump(up and down)
	if (isJumping)
	{
		sonicPos.y -= gravity;
	}
	else
	{
		sonicPos.y += gravity;
	}
	//sonic jump limit, sonic bottom limit.
	if (sonicPos.y >= 0)
	{
		sonicPos.y = 0;
		isBottom = true;
	}

	if (sonicPos.y <= 0 - 100)
	{
		isJumping = false;
	}
	//sonic step.

	frame += frameSpeed;
	if (frame > changeCount)
	{
		frame -= changeCount;
	}

}
void CameraView(RenderWindow& window, View& camera, Sprite& sonic) {
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		camera.move(Vector2f(4.f, 0.f));
	}
	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		camera.move(Vector2f(-5.3f, 0.f));
	}
	sonic.setOrigin(sonic.getGlobalBounds().width, -300 - sonicPos.y);
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

	if (Keyboard::isKeyPressed(Keyboard::Tab))
		rs = false;
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
		//std::cout << "play is pressed\n";
		click = 1;
		time2 = 0;
	}

	// Mouse postition and collistions
	mouse.setPosition((float)Mouse::getPosition().x, (float)Mouse::getPosition().y);
	if (mouse.getGlobalBounds().intersects(text1.getGlobalBounds())) {
		text1.setFillColor(Color::Red);
		text.setFillColor(Color::Black);
	}
	if (mouse.getGlobalBounds().intersects(text.getGlobalBounds())) {
		text.setFillColor(Color::Red);
		text1.setFillColor(Color::Black);
	}
	if (mouse.getGlobalBounds().intersects(text1.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		click = 1;
	}
	if (mouse.getGlobalBounds().intersects(text.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		window.close();
	}
}
void GameWorld(RenderWindow& window, Sprite& flag, Sprite Catus[5], Sprite Block1[10], Sprite Block2[10], Sprite backgroundArr[10], Sprite& ground, Sprite& background) {

	for (int i = 0; i < 10; i++) {
		window.draw(backgroundArr[i]);
	}
	window.draw(background);
	//for (int i = 0; i < 20; i++) {
	//	window.draw(Block1[i]);
	//}
	window.draw(ground);

	for (int i = 0; i < 5; i++) {
		window.draw(Block1[i]);
	}

	for (int i = 0; i < 5; i++) {
		window.draw(Block2[i]);
	}

	for (int i = 0; i < 5; i++) {
		window.draw(Catus[i]);
	}
}
void RESUME(RenderWindow& window, Text& text, Text& text1, Sprite& mouse, RectangleShape& background) {
	// code 
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
		//std::cout << "play is pressed\n";
		click = 1;
		time2 = 0;
	}

	// Mouse postition and collistions
	mouse.setPosition((float)Mouse::getPosition().x, (float)Mouse::getPosition().y);
	if (mouse.getGlobalBounds().intersects(text1.getGlobalBounds())) {
		text1.setFillColor(Color::Red);
		text.setFillColor(Color::Black);
	}
	if (mouse.getGlobalBounds().intersects(text.getGlobalBounds())) {
		text.setFillColor(Color::Red);
		text1.setFillColor(Color::Black);
	}
	if (mouse.getGlobalBounds().intersects(text1.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		click = 1;
	}
	if (mouse.getGlobalBounds().intersects(text.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		window.close();
	}
}
void END() {}