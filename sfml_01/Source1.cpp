#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<ctime>
#include<SFML/Audio.hpp>
#include<iostream>

#define X 36
#define Y 41
#define WIDTH 1280
#define HEIGHT 720
#define size 3

using namespace sf;
using namespace std;

struct enemies
{
	Texture enemytexture;
	Sprite enemy;
	bool isvisible = true;
}; enemies enemy[size];


void SONIC_ANIMATION(RenderWindow& window, Sprite& sonic, View& camera);
void GameWorld(RenderWindow& window, Sprite& flag, Sprite Catus[5], Sprite Block1[10], Sprite spritesndblock[10], Sprite Block2[10], Sprite backgroundArr[10], Sprite& ground, Sprite& background);
void UI(RenderWindow& window, Text& text, Text& text1, Sprite& mouse, RectangleShape& background);
void Intersections(RenderWindow& window, Sprite& sonic, Sprite catus[5], Sprite& flag, Sprite coin[], Sprite coin1[], Sprite coin2[], Sound& sound, enemies enemy[], Text& text0, Sound& soundout, Text& text03, int& Score);
void CameraView(RenderWindow& window, View& camera, Sprite& sonic, Text& text0, Text& text02, Text& text03);
void RESUME(RenderWindow& window, Text& text, Text& text1, Sprite& mouse, RectangleShape& background);
void jump(RenderWindow& window, Sprite& sonic);
void drow_coin(RenderWindow& window, Sprite coin[], Sprite coin1[], Sprite coin2[], Sprite& sonic, Texture Cointure); //
void enemiesload_draw(RenderWindow& window, enemies enemy[], int& enemyanmationcounter); //
enemies enemies_move(RenderWindow& window, enemies enemy[], float Deltatime, Clock& clock); //
void calculatetime(int&, int&, Clock&); //
void How_we_want_Time(int, int, Text& text2, RenderWindow&);
void COLLITION(Sprite& Sonic, Sprite bolcks[5], float blockPos, float newPosForSonicGround, float heightForJump, bool& flag);
void END(RenderWindow& window, Text& LEVEL2, Text& EXIT);

// this for jump 
const int gravity = 6;
bool isJumping = false;
bool isBottom = true;
float SONICGROUND = -300.f, JUMPHEGHIT = 200.f;


int score = 0, time1 = 10, time2 = 0, time001 = 0, timer002, sonic_lives = 0, SCORE = 0;
int x = 0, y = 0;
int click = 0;
struct pos {
	int x, y;
}sonicPos;

bool rs = false, sdsad = false, sb = false;
static const int SONIC_Y_BUTTOM = HEIGHT - 60;

int rings = 0, coinanmationcounter = 0, enemyanmationcounter = 0, enemyanmationcounter1 = 0;

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



	Text exitForEnd;
	exitForEnd.setFont(font);
	exitForEnd.setCharacterSize(24);
	exitForEnd.setFillColor(Color::White);
	exitForEnd.setStyle(Text::Bold);
	exitForEnd.setString("EXIT");


	Text LEVEL2;
	LEVEL2.setFont(font);
	LEVEL2.setCharacterSize(24);
	LEVEL2.setFillColor(Color::White);
	LEVEL2.setStyle(Text::Bold);
	LEVEL2.setString("LEVEL2");



	exitForEnd.setPosition((float)camera.getCenter().x / 2, (float)camera.getCenter().x / 2);
	LEVEL2.setPosition((float)camera.getCenter().x / 2, (float)camera.getCenter().x / 3);

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
	Stblock.loadFromFile("Tex/nfirstblock.PNG");
	Sprite stblock;
	stblock.setTexture(Stblock);
	stblock.setScale(0.3, 0.35);
	Sprite spritesstblock[5];
	for (int i = 0; i < 5; i++) {
		spritesstblock[i] = stblock;
		spritesstblock[i].setPosition(250 + ((float)i * 1120), 223);
	}

	//second block 
	Texture Ndblock;
	Ndblock.loadFromFile("Tex/firstblock.PNG");
	Sprite ndblock;
	ndblock.setTexture(Ndblock);
	ndblock.setScale(0.45f, 0.45f);
	Sprite spritesndblock[5];
	for (int i = 0; i < 5; i++) {
		spritesndblock[i] = ndblock;
		spritesndblock[i].setPosition(850 + ((float)i * 1420), 237);
	}

	Sprite spritesndblock1[5];
	for (int i = 0; i < 5; i++) {
		spritesndblock1[i] = ndblock;
		spritesndblock1[i].setScale(0.55f, 0.8f);
		spritesndblock1[i].setPosition(1047 + ((float)i * 1420), 153);
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

	cout << "ddd";
	int Score = 0, timer = 0;
	float time = 0;

	Clock  Time_clock, enemydeltatime, enemiesclock;
	float DeltaTime = 0;
	int minutes = 0;

	Texture Cointure;
	Cointure.loadFromFile("Tex/coins1.PNG");
	Sprite coin[4];
	for (size_t i = 0; i < 4; i++) {
		coin[i].setPosition(630 + (i * 40), 310);
		coin[i].setTexture(Cointure);
		coin[i].setScale(0.2, 0.2);

	}

	Sprite coin1[4];
	for (size_t i = 0; i < 4; i++) {
		coin1[i].setPosition(320 + (i * 70), 195); //300 + (i * 1000), 223
		coin1[i].setTexture(Cointure);
		coin1[i].setScale(0.2, 0.2);

	}

	Sprite coin2[3];
	for (size_t i = 0; i < 3; i++) {
		coin2[i].setPosition(880 + (i * 30), 225);//850 + ((float)i * 1000), 170
		coin2[i].setTexture(Cointure);
		coin2[i].setScale(0.2, 0.2);

	}
	//مهمه بس لسه معملتهاش
	/*if (camera.getCenter().x > coin2[3].getPosition().x) {
		for (size_t i = 0; i < 4; i++) {
			coin[i].setPosition(630 + (i * 40), 310);
			coin1[i].setPosition(320 + (i * 70), 195);
		}
		for (size_t i = 0; i < 3; i++) {

			coin2[i].setPosition(880 + (i * 30), 225);
		}
	}*/
	Font font0;
	font0.loadFromFile("Tex/PlayfairDisplay-Bold.ttf");
	Text text0;
	text0.setFont(font0);
	text0.setString("Rings : " + to_string(rings));
	text0.setFillColor(Color(75, 67, 75, 255));
	text0.setPosition(10, 10);
	text0.setScale(.75, .75);
	text0.setCharacterSize(32);

	Text text02;
	text02.setFont(font0);
	text02.setString("Time : " + to_string(time));
	text02.setFillColor(Color(70, 67, 70, 255));
	text02.setPosition(10, 50);
	text02.setScale(.75, .75);
	text02.setCharacterSize(32);

	Text text03;
	text03.setFont(font0);
	text03.setString("Score : " + to_string(Score));
	text03.setFillColor(Color(70, 67, 75, 240));
	text03.setPosition(10, 90);
	text03.setScale(.75, .75);
	text03.setCharacterSize(32);

	SoundBuffer soundb;
	soundb.loadFromFile("Tex/Ringsound (2).ogg");
	Sound sound;
	sound.setBuffer(soundb);

	SoundBuffer sound_out;
	sound_out.loadFromFile("Tex/ring_out.OGG");
	Sound soundout;
	soundout.setBuffer(sound_out);

	SoundBuffer sound_ground;
	sound_ground.loadFromFile("Tex/con_out1.ogg");
	Sound soundground;
	soundground.setBuffer(sound_ground);
	soundground.play();
	enemy[0].enemy.setPosition(500, 250);
	if (enemyanmationcounter1 == 1) {
		enemy[1].enemy.setPosition(enemy[2].enemy.getPosition().x, enemy[2].enemy.getPosition().y + 20);
	}
	while (window.isOpen()) {
		Event event;

		int seconds = Time_clock.getElapsedTime().asSeconds();
		DeltaTime = enemydeltatime.restart().asSeconds();
		enemies emove = enemies_move(window, enemy, DeltaTime, enemiesclock);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			cout << sf::Mouse::getPosition(window).x << endl;


			cout << sf::Mouse::getPosition(window).y << endl << "*" << endl;
		}


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
			GameWorld(window, flag, spritescactus, spritesstblock, spritesndblock, spritesndblock1, spritesbackground, ground, background);

			enemiesload_draw(window, enemy, enemyanmationcounter);
			enemies_move(window, enemy, DeltaTime, enemiesclock);
			Intersections(window, sonic, spritescactus, flag, coin, coin1, coin2, sound, enemy, text0, soundout, text03, SCORE);
			jump(window, sonic);
			CameraView(window, camera, sonic, text0, text02, text03);
			window.setView(camera);
			window.draw(sonic);
			window.draw(flag);
			window.draw(text0);
			window.draw(text02);
			window.draw(text03);
			drow_coin(window, coin, coin1, coin2, sonic, Cointure);
			calculatetime(seconds, minutes, Time_clock);
			How_we_want_Time(seconds, minutes, text02, window);
			COLLITION(sonic, spritesndblock, -233.f, -220.f, 50.f, sdsad);
			cout << SONICGROUND << endl;
			if (Keyboard::isKeyPressed(Keyboard::Tab)) {
				rs = true;
			}
		}
		if (click == 1 && rs) {
			RESUME(window, text1, text2, mouse, backgroundForEnd);
		}
		if (click == 2) {
			END(window, exitForEnd, LEVEL2);
		}





		exitForEnd.setPosition((float)camera.getCenter().x, 150.f);
		LEVEL2.setPosition((float)camera.getCenter().x, 250.f);
		window.setMouseCursorVisible(false);

		cout << camera.getCenter().x << endl;
		window.display();
	}
}
void Intersections(RenderWindow& window, Sprite& sonic, Sprite catus[5], Sprite& flag, Sprite coin[], Sprite coin1[], Sprite coin2[], Sound& sound, enemies enemy[], Text& text0, Sound& soundout, Text& text03, int& SCORE) {

	// this for Catus
	for (int i = 0; i < 5; i++)
	{
		if (sonic.getGlobalBounds().intersects(catus[i].getGlobalBounds())) {
			// WHAT WILL HAPPEND
		}
	}
	// this for flag 

	if (sonic.getGlobalBounds().intersects(flag.getGlobalBounds())) {
		click = 2;
	}

	for (int i = 0; i < 4; i++) {
		if (sonic.getGlobalBounds().intersects(coin[i].getGlobalBounds())) {
			coin[i].setPosition(coin[i].getPosition().x + 1000.f, coin[i].getPosition().y);
			rings++;
			text0.setString("Rings : " + to_string(rings));
			sound.play();
		}
		if (sonic.getGlobalBounds().intersects(coin1[i].getGlobalBounds())) {
			coin1[i].setPosition(coin1[i].getPosition().x + 1000.f, coin1[i].getPosition().y);
			rings++;
			text0.setString("Rings : " + to_string(rings));
			sound.play();
		}

	}
	for (int i = 0; i < 3; i++) {
		if (sonic.getGlobalBounds().intersects(coin2[i].getGlobalBounds())) {
			coin2[i].setPosition(coin2[i].getPosition().x + 1000.f, coin2[i].getPosition().y);
			rings++;
			text0.setString("Rings : " + to_string(rings));
			sound.play();
		}
	}
	for (int i = 0; i < 4; i++) {
		if (sonic.getGlobalBounds().intersects(enemy[1].enemy.getGlobalBounds())) {
			enemy[1].enemy.setScale(0, 0);
			//sonic.setScale(0, 0);

			rings = 0;
			text0.setString("Rings : " + to_string(rings));
			sound.play();
		}
	}
	//int e_x = enemy[0].enemy.getPosition().x;
	int e_y = enemy[0].enemy.getPosition().y;
	if (sonic.getGlobalBounds().intersects(enemy[0].enemy.getGlobalBounds())) {
		if (sonic.getGlobalBounds().intersects(enemy[0].enemy.getGlobalBounds()) && sonic.getPosition().y + 130 == e_y)

		{
			SCORE = SCORE + 100;
			text03.setString("Score : " + to_string(SCORE));
			//enemy[0].enemy.setScale(0, 0); 

		}
		SCORE = SCORE + 100;
		enemy[0].enemy.setPosition(enemy[0].enemy.getPosition().x + 500.f, enemy[0].enemy.getPosition().y);
		rings = 0;
		text0.setString("Rings : " + to_string(rings));
		soundout.play();

	}
	//if (sonic.getGlobalBounds().intersects(enemy[2].enemy.getGlobalBounds())) {
	//	if (sonic.getGlobalBounds().intersects(enemy[2].enemy.getGlobalBounds()) && sonic.getPosition().y + 130 == e_y)

	//	{
	//		score = score + 100;
	//		text03.setString("Score : " + to_string(score));
	//		//enemy[0].enemy.setScale(0, 0); 

	//	}score = score + 100;
	//	enemy[2].enemy.setPosition(enemy[2].enemy.getPosition().x + 500.f, enemy[2].enemy.getPosition().y);
	//	rings = 0;
	//	text0.setString("Rings : " + to_string(rings));
	//	soundout.play();
	//}
}

void SONIC_ANIMATION(RenderWindow& window, Sprite& sonic, View& camera) {
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		y = 0;
		sonic.setTextureRect(IntRect(X * x, y * Y, X, Y));
		x++;
		x %= 9;
		sonic.move(20.f, 0.f);
	}

	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		y = 0;
		sonic.setTextureRect(IntRect(X * x, Y * y, -X, Y));
		x %= 9;
		x++;
		if (x > 9) {
			x = 0;
		}
		sonic.move(-20.f, 0.f);
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
	if (Keyboard::isKeyPressed(Keyboard::Space) /*&& !standOn || Keyboard::isKeyPressed(Keyboard::Space) && SONICGROUND == -220.0f*/)
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

	if (sonicPos.y <= 0 - JUMPHEGHIT)
	{
		isJumping = false;
	}
	//sonic step.
}
void CameraView(RenderWindow& window, View& camera, Sprite& sonic, Text& text0, Text& text02, Text& text03) {
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		camera.move(Vector2f(20.f, 0.f));
		text0.move(20.f, 0.f);
		text02.move(20.f, 0.f);
		text03.move(20.f, 0.f);

	}
	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		camera.move(Vector2f(-5.3f, 0.f));
		text0.move(-20.f, 0.f);
		text02.move(-20.f, 0.f);
		text03.move(-20.f, 0.f);
	}
	sonic.setOrigin(sonic.getGlobalBounds().width, SONICGROUND - sonicPos.y);
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
void GameWorld(RenderWindow& window, Sprite& flag, Sprite Catus[5], Sprite Block1[10], Sprite spritesndblock[10], Sprite Block2[10], Sprite backgroundArr[10], Sprite& ground, Sprite& background) {

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
		window.draw(spritesndblock[i]);
	}


	/*for (int i = 0; i < 5; i++) {
		window.draw(ndblock1[i]);
	}*/

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
void drow_coin(RenderWindow& window, Sprite coin[], Sprite coin1[], Sprite coin2[], Sprite& sonic, Texture Cointure) {
	coinanmationcounter %= 4;
	coinanmationcounter++;
	/*if (time001 < 3)
		time001++;
	if (time001 >= 3) {
		time001 = 0;*/
	for (int i = 0; i < 4; i++) {

		coin[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
		window.draw(coin[i]);
	}
	for (int i = 0; i < 4; i++) {
		coin1[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
		window.draw(coin1[i]);
	}
	for (int i = 0; i < 3; i++) {
		coin2[i].setTextureRect(IntRect(coinanmationcounter * 127.75, coinanmationcounter * 127.75, 127.75, 127.75));
		window.draw(coin2[i]);
	}


}
void collision_enemies_and_coin(RenderWindow& window, Sprite& sonic, Sprite coin[], Sound& sound, enemies enemy[], Text& text, Sound& soundout, Text& text3, int& score) {

	for (int i = 0; i < 4; i++) {
		if (sonic.getGlobalBounds().intersects(coin[i].getGlobalBounds())) {
			coin[i].setScale(20, 20);
			rings++;
			text.setString("Rings : " + to_string(rings));
			sound.play();
		}
	}

	//int e_x = enemy[0].enemy.getPosition().x;
	int e_y = enemy[0].enemy.getPosition().y;
	if (sonic.getGlobalBounds().intersects(enemy[0].enemy.getGlobalBounds())) {
		if (sonic.getGlobalBounds().intersects(enemy[0].enemy.getGlobalBounds()) && sonic.getPosition().y == e_y)

		{
			SCORE = +100;
			text3.setString("Score : " + to_string(SCORE));
			enemy[0].enemy.setScale(0, 0);
		}
		rings = 0;
		text.setString("Rings : " + to_string(rings));
		soundout.play();

	}
}
void enemiesload_draw(RenderWindow& window, enemies enemy[], int& enemyanmationcounter) {

	enemy[0].enemytexture.loadFromFile("Tex/enemy3.png");
	enemy[1].enemytexture.loadFromFile("Tex/nshots.png");
	enemy[2].enemytexture.loadFromFile("Tex/enemy03.png");
	for (int i = 0; i < size; i++) {
		enemy[i].enemy.setTexture(enemy[i].enemytexture);
		enemy[i].enemy.setScale(1, 1);

	}
	enemyanmationcounter %= 6;
	enemyanmationcounter++;
	enemyanmationcounter1 %= 2;
	enemyanmationcounter1++;
	/*if (timer002 < 8)
		timer002++;
	if (timer002 >= 8) {
		timer002 = 0;*/

	enemy[1].enemy.setTextureRect(IntRect(0, enemyanmationcounter * 46, 17, 46));
	window.draw(enemy[1].enemy);
	enemy[2].enemy.setTextureRect(IntRect(enemyanmationcounter1 * 49.5, 0, 49.5, 35));
	window.draw(enemy[2].enemy);
	enemy[0].enemy.setTextureRect(IntRect(enemyanmationcounter * 41, 0, 38, 44));

	if (enemy[0].isvisible)
		window.draw(enemy[0].enemy);
}
enemies enemies_move(RenderWindow& window, enemies enemy[], float Deltatime, Clock& enemiesclock) {
	int seconds_for_enemies = enemiesclock.getElapsedTime().asSeconds();
	int velocity = 2.f;
	int displacement = 20.f;
	for (int i = 0; i < size; i++) {
		if (velocity * seconds_for_enemies <= displacement) {
			enemy[i].enemy.move(20.f * Deltatime, 0);
			if (i == 1) {
				enemy[i].enemy.move(0, 20.f * Deltatime);
				continue;
			}
		}
		else {
			if (i == 1) {
				enemy[i].enemy.move(0, 20.f * Deltatime);
				continue;
			}
			enemy[i].enemy.move(-20.f * Deltatime, 0);
			if ((velocity * seconds_for_enemies) == 2 * displacement)
				enemiesclock.restart();
		}
	}

	for (int i = 0; i < size; i++)
		return enemy[i];
}
void calculatetime(int& seconds, int& minutes, Clock& Time_clock) {
	if (seconds == 60) {
		Time_clock.restart();
		minutes++;
	}
}
void How_we_want_Time(int seconds, int minutes, Text& text02, RenderWindow& window) {
	if (seconds < 10) {
		if (minutes < 10)
			text02.setString("Time: 0" + to_string(minutes) + ":0" + to_string(seconds));
		else
			text02.setString("Time: " + to_string(minutes) + ":0" + to_string(seconds));

	}
	else {
		if (minutes < 10)
			text02.setString("Time: 0" + to_string(minutes) + ":" + to_string(seconds));
		else
			text02.setString("Time: " + to_string(minutes) + ":" + to_string(seconds));
	}
}
void COLLITION(Sprite& Sonic, Sprite bolcks[5], float blockPos, float newPosForSonicGround, float heightForJump, bool& flag) {
	for (int i = 0; i < 5; i++)
	{
		if (Sonic.getGlobalBounds().intersects(bolcks[i].getGlobalBounds()) && -300.f - (float)sonicPos.y >= blockPos) {
			flag = true;
		}
	}
	if (flag && Sonic.getGlobalBounds().intersects(bolcks[0].getGlobalBounds())) {
		SONICGROUND = newPosForSonicGround;
		JUMPHEGHIT = heightForJump;
		std::cout << "got it ....." << std::endl;
	}
	else if (flag && Sonic.getGlobalBounds().intersects(bolcks[1].getGlobalBounds())) {
		SONICGROUND = newPosForSonicGround;
		JUMPHEGHIT = heightForJump;
		std::cout << "got it ....." << std::endl;
	}
	else if (flag && Sonic.getGlobalBounds().intersects(bolcks[2].getGlobalBounds())) {
		SONICGROUND = newPosForSonicGround;
		JUMPHEGHIT = heightForJump;
		std::cout << "got it ....." << std::endl;
	}

	else if (flag && Sonic.getGlobalBounds().intersects(bolcks[3].getGlobalBounds())) {
		SONICGROUND = newPosForSonicGround;
		JUMPHEGHIT = heightForJump;
		std::cout << "got it ....." << std::endl;
	}

	else if (flag && Sonic.getGlobalBounds().intersects(bolcks[4].getGlobalBounds())) {
		SONICGROUND = newPosForSonicGround;
		JUMPHEGHIT = heightForJump;
		std::cout << "got it ....." << std::endl;
	}

	// this is the main problem
	else {
		SONICGROUND = -300.f;
	}

	if (SONICGROUND == -300.f) {
		JUMPHEGHIT = 120.f;
		flag = false;
	}
}
void END(RenderWindow& window, Text& LEVEL2, Text& EXIT) {
	// draw
	window.draw(LEVEL2);
	window.draw(EXIT);

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
		LEVEL2.setFillColor(Color::Red);
		EXIT.setFillColor(Color::Black);
	}
	if (score % 2 == 1) {
		LEVEL2.setFillColor(Color::Black);
		EXIT.setFillColor(Color::Red);
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
}
