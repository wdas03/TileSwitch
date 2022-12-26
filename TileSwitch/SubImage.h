#ifndef SUBIMAGE_H
#define SUBIMAGE_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class SubImage {
public: 
	SubImage(sf::RectangleShape image, int id, int vector_idx);
	sf::RectangleShape getImage();
	int getId();
	sf::RectangleShape image;
	int id;
	int vector_idx;
};

#endif
