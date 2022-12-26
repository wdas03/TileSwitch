#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TileImage.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Game {
public:
	Game();
	Game(int windowWidth, int windowHeight);
	void run();
	void displayCompletionPage();

	void loadTextures();
	void loadCelebrityTextures();
	void setCelebrityImages(int numPerRow);
	void loadAnimalTextures();
	void setAnimalImages(int numPerRow);
	void loadAthleteTextures();
	void setAthleteImages(int numPerRow);
	void loadSpaceTextures();
	void setSpaceImages(int numPerRow);

	void displayBackground();
	void displayTiledImage(int imageNum, string fileName);
	void displayTiledImage(int imageNum, sf::Texture texture);
	void handleMouseClick(sf::Event mouseEvent);
	void handleMouseHover(sf::Event mouseEvent);
	bool clickedOn(sf::Event mouseEvent, sf::RectangleShape shape);
	bool clickedOn(sf::Event mouseEvent, sf::FloatRect float_rect);
	bool clickedOnImage(sf::Vector2f mousePos, sf::RectangleShape shape);
	bool hoveredOver(sf::Event mouseEvent, sf::RectangleShape shape);
	bool hoveredOver(sf::Event mouseEvent, sf::FloatRect float_rect);
	bool hoveredOverImage(sf::Vector2f mousePos, sf::RectangleShape shape);

	void restart();
	
	bool displaySubImages = false;
	bool displayMainMenu = true;
	bool displayImages = false;
	bool completedImage = false;
	bool displayDifficultyPage = false;
	int difficulty;
	int tileNum;
private:
	void processEvents();
	void update();
	void render();

	sf::RenderWindow window;
	sf::Font defaultFont;
	sf::Music musicFile;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Clock clock;
	sf::Time time;
	sf::View mainView;
	sf::Text animalHeading;
	sf::Text celebrityHeading;
	sf::Text athleteHeading;
	sf::Text spaceHeading;
	sf::Text selectDifficulty;
	sf::Text easy;
	sf::Text intermediate;
	sf::Text hard;
	sf::Text master;
	sf::Text expert;
	sf::Text winText;
	sf::Text returnMainMenu;

	sf::Time timeCompletion;
	int numOfMoves = 0;

	vector<SubImage> subImages;
	vector<sf::Texture> celebrityTextures;
	vector<sf::RectangleShape> celebrityImages;
	vector<sf::Texture> animalTextures;
	vector<sf::RectangleShape> animalImages;
	vector<sf::Texture> athleteTextures;
	vector<sf::RectangleShape> athleteImages;
	vector<sf::Texture> spaceTextures;
	vector<sf::RectangleShape> spaceImages;

	sf::Texture textureImage;
	sf::RectangleShape image;
	sf::Text playButton;
	TileImage *tileImage = NULL;
	int windowWidth;
	int windowHeight;
};


#endif
