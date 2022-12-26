#ifndef TILEIMAGE_H
#define TILEIMAGE_H

#include <SFML/Graphics.hpp>
#include "SubImage.h"
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>

using namespace std;

class TileImage {
public:
	TileImage(sf::Texture textureImage, sf::RectangleShape tileImage, int windowWidth, int windowHeight, bool display);
	sf::Texture getTextureImage();
	sf::RectangleShape getTileImage();
	sf::Vector2f getImageSize();
	const vector<SubImage>& getSubImages() const;
	vector<SubImage>& getSubImages();
	void splitImage();
	void splitImage(int newImageNum);
	void swapSubImages(SubImage image1, SubImage image2);
	void mixSubImages();
	bool imageCompleted();

	bool display;
	vector<SubImage> selectedSubImages;
	vector<SubImage> subImages;
	sf::Texture textureImage;
	string textureFilePath;
	sf::RectangleShape tileImage;
	sf::Vector2f imageSize;
	bool completed = false;
	int imageNum=9;
	int windowWidth;
	int windowHeight;
};

#endif
