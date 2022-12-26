#include "SubImage.h"

SubImage::SubImage(sf::RectangleShape image, int id, int vector_idx) : image(image), id(id), vector_idx(vector_idx) {}

sf::RectangleShape SubImage::getImage() {
	return image;
}

int SubImage::getId() {
	return id;
}