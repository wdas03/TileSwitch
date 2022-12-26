#include "TileImage.h"

TileImage::TileImage(sf::Texture textureImage, sf::RectangleShape tileImage, int windowWidth, int windowHeight, bool display) : textureImage(textureImage), tileImage(tileImage), imageSize(textureImage.getSize()), windowWidth(windowWidth), windowHeight(windowHeight), display(display) {}

bool TileImage::imageCompleted() {
	for (int i = 0; i < subImages.size(); i++) {
		if (subImages[i].id == (i + 1)) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

void TileImage::mixSubImages() {
	for (int i = 0; i < imageNum;i++) {
		mt19937 rng;
		rng.seed(random_device()());
		uniform_int_distribution<mt19937::result_type> distImageNum(0, imageNum - 1);
		swapSubImages(subImages[i], subImages[distImageNum(rng)]);
	}
}

void TileImage::swapSubImages(SubImage image1, SubImage image2) {
	sf::Vector2f oldImage1_size = image1.image.getSize();
	sf::Vector2f oldImage2_size = image2.image.getSize();

	sf::RectangleShape oldImage1 = image1.image;
	sf::RectangleShape oldImage2 = image2.image;

	image1.image.setPosition(oldImage2.getPosition());
	image2.image.setPosition(oldImage1.getPosition());

	image1.image.setSize(oldImage2_size);
	image2.image.setSize(oldImage1_size);

	image1.image.setOutlineColor(sf::Color::White);
	image2.image.setOutlineColor(sf::Color::White);

	SubImage newImage1(image2.image, image1.id, image2.vector_idx);
	SubImage newImage2(image1.image, image2.id, image1.vector_idx);

	subImages[image1.vector_idx - 1] = newImage2;
	subImages[image2.vector_idx - 1] = newImage1;
}

void TileImage::splitImage() {
	int counter = 1;
	int x = 0;
	int y = 0;
	int textureX = 0;
	int textureY = 0;
	int imageWidth = (int)imageSize.x;
	int imageHeight = (int)imageSize.y;

	while (counter < 10) {
		sf::RectangleShape subImg;
		subImg.setSize(sf::Vector2f((float)windowWidth / 3, (float)windowHeight / 3));
		subImg.setPosition(sf::Vector2f((float)x, (float)y));
		subImg.setTexture(&textureImage);
		subImg.setTextureRect(sf::IntRect((float)textureX, (float)textureY, (float) (imageWidth / 3), (float) (imageHeight / 3)));
		subImg.setOutlineThickness(3);
		subImg.setOutlineColor(sf::Color::Cyan);
		SubImage img(subImg, counter, counter);
		subImages.push_back(img);

		if (counter % 3 == 0) {
			x = 0;
			textureX = 0;
			textureY += imageHeight / 3;
			y += windowHeight / 3;
		}
		else {
			textureX += imageWidth / 3;
			x += windowWidth / 3;
		}

		counter++;
	}
}

void TileImage::splitImage(int newImageNum) {
	imageNum = newImageNum;
	int counter = 1;
	int numPerRow = (int) sqrt(imageNum);
	int x = 0;
	int y = 0;
	int textureX = 0;
	int textureY = 0;
	int imageWidth = (int)imageSize.x;
	int imageHeight = (int)imageSize.y;

	while (counter < imageNum + 1) {
		sf::RectangleShape subImg;
		subImg.setTexture(&textureImage);
		subImg.setTextureRect(sf::IntRect((float)textureX, (float)textureY, (float) (imageWidth / numPerRow), (float) (imageHeight / numPerRow)));
		subImg.setOutlineThickness(2);
		subImg.setOutlineColor(sf::Color::White);
		subImg.setSize(sf::Vector2f((float) (windowWidth - (2 * subImg.getOutlineThickness())) / numPerRow, (float) (windowHeight - (2 * subImg.getOutlineThickness())) / numPerRow));
		subImg.setPosition(sf::Vector2f((float)x, (float)y));
		SubImage img(subImg, counter, counter);
		subImages.push_back(img);

		if (counter % numPerRow == 0) {
			x = 0;
			textureX = 0;
			textureY += imageHeight / numPerRow;
			y += windowHeight / numPerRow;
		}
		else {
			textureX += imageWidth / numPerRow;
			x += windowWidth / numPerRow;
		}

		counter++;
	}
}

const vector<SubImage>& TileImage::getSubImages() const {
	return subImages;
}

vector<SubImage>& TileImage::getSubImages() {
	return subImages;
}

sf::Vector2f TileImage::getImageSize() {
	return imageSize;
}

sf::Texture TileImage::getTextureImage() {
	return textureImage;
}

sf::RectangleShape TileImage::getTileImage() {
	return tileImage;
}