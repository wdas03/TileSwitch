#include "Game.h"

Game::Game() {}
Game::Game(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight), window(sf::VideoMode(windowWidth, windowHeight), "TileSwitch"), defaultFont(), musicFile(), clock(), mainView(), backgroundTexture(), background() {
	if (!defaultFont.loadFromFile( "Fonts/kenvector_future.ttf")) {}
	if (!musicFile.openFromFile( "Audio Files/mozart2.ogg"))
	  cout << "Could not load audio file!" << endl;
	musicFile.play();
	musicFile.setLoop(true);

	//Background image
	backgroundTexture.setRepeated(true);
	if (!backgroundTexture.loadFromFile("Textures/backgroundTile.png")) {}
	background.setSize(sf::Vector2f(windowWidth, windowHeight));
	background.setTexture(&backgroundTexture);

	mainView.setSize(windowWidth, windowHeight);
	mainView.setCenter(windowWidth / 2, windowHeight / 2);

	sf::Texture loadingBackground;
	loadingBackground.loadFromFile("Textures/loading_background.jpeg");
	sf::RectangleShape loadingImage;
	loadingImage.setTexture(&loadingBackground);
	loadingImage.setSize(sf::Vector2f(windowWidth, windowHeight));
	loadingImage.setPosition(0, 0);

	window.clear();
	window.draw(loadingImage);
	window.display();

	loadTextures();

	clock.restart();
}

void Game::restart() {
	window.clear();
	tileImage = NULL;
	numOfMoves = 0;
	difficulty = 0;
	completedImage = false;
	displaySubImages = false;
	displayMainMenu = false;
	displayImages = false;
	displayDifficultyPage = true;
	animalImages.clear();
	celebrityImages.clear();
	athleteImages.clear();
	
}

void Game::displayBackground() {
	window.draw(background);
	for (int i = 1; i < 5; i++) {
		sf::RectangleShape top(sf::Vector2f(windowWidth, windowHeight));
		top.setPosition(0, -(windowHeight * i));
		top.setTexture(&backgroundTexture);

		sf::RectangleShape bottom(sf::Vector2f(windowWidth, windowHeight));
		bottom.setPosition(0, windowHeight * i);
		bottom.setTexture(&backgroundTexture);

		window.draw(top);
		window.draw(bottom);
	}
}

void Game::setAthleteImages(int numPerRow) {
	athleteHeading.setPosition((windowWidth - athleteHeading.getLocalBounds().width) / 2, celebrityImages[celebrityImages.size() - 1].getPosition().y + windowHeight / 4.f + 50);
	int counter = 0;
	int x = 15;
	int y = athleteHeading.getPosition().y + 150;
	while (counter < athleteTextures.size()) {
		sf::RectangleShape tempImage;
		tempImage.setTexture(&athleteTextures[counter]);
		tempImage.setSize(sf::Vector2f(windowWidth / (numPerRow + 2), windowHeight / 4.f));
		tempImage.setPosition(x, y);
		tempImage.setOutlineThickness(4);
		tempImage.setOutlineColor(sf::Color::White);
		athleteImages.push_back(tempImage);
		if (counter % numPerRow == (numPerRow - 1) && counter != 0) {
			x = 15.f;
			y += (windowHeight / 4.f) + 100.f;
		}
		else {
			x += (windowWidth / numPerRow + 1) + 10.f;
		}
		counter++;
	}
}

void Game::setCelebrityImages(int numPerRow) {
	celebrityHeading.setPosition((windowWidth - celebrityHeading.getLocalBounds().width) / 2, animalImages[animalImages.size() - 1].getPosition().y + windowHeight / 4.f + 50);
	int counter = 0;
	int x = 15;
	int y = celebrityHeading.getPosition().y + 150;
	while (counter < celebrityTextures.size()) {
		sf::RectangleShape tempImage;
		tempImage.setTexture(&celebrityTextures[counter]);
		tempImage.setSize(sf::Vector2f(windowWidth / (numPerRow + 2), windowHeight / 4.f));
		tempImage.setPosition(x, y);
		tempImage.setOutlineThickness(4);
		tempImage.setOutlineColor(sf::Color::White);
		celebrityImages.push_back(tempImage);
		if (counter % numPerRow == (numPerRow - 1) && counter != 0) {
			x = 15.f;
			y += (windowHeight / 4.f) + 100.f;
		}
		else {
			x += (windowWidth / numPerRow + 1) + 10.f;
		}
		counter++;
	}
}

void Game::setAnimalImages(int numPerRow) {
	animalHeading.setPosition((windowWidth - animalHeading.getLocalBounds().width) / 2, 50);
	int counter = 0;
	int x = 15;
	int y = animalHeading.getPosition().y + (animalHeading.getLocalBounds().height * 2);
	while (counter < animalTextures.size()) {
		sf::RectangleShape tempImage;
		tempImage.setTexture(&animalTextures[counter]);
		tempImage.setSize(sf::Vector2f(windowWidth / (numPerRow + 2), windowHeight / 4.f));
		tempImage.setPosition(x, y);
		tempImage.setOutlineThickness(4);
		tempImage.setOutlineColor(sf::Color::White);
		animalImages.push_back(tempImage);
		if (counter % numPerRow == (numPerRow - 1) && counter != 0) {
			x = 15.f;
			y += (windowHeight / 4.f) + 100.f;
		}
		else {
			x += (windowWidth / numPerRow + 1) + 10.f;
		}
		counter++;
	}
}

void Game::setSpaceImages(int numPerRow) {
	spaceHeading.setPosition((windowWidth - spaceHeading.getLocalBounds().width) / 2, athleteImages[athleteImages.size() - 1].getPosition().y + windowHeight / 4.f + 50);
	int counter = 0;
	int x = 15;
	int y = spaceHeading.getPosition().y + 150;
	while (counter < spaceTextures.size()) {
		sf::RectangleShape tempImage;
		tempImage.setTexture(&spaceTextures[counter]);
		tempImage.setSize(sf::Vector2f(windowWidth / (numPerRow + 2), windowHeight / 4.f));
		tempImage.setPosition(x, y);
		tempImage.setOutlineThickness(3);
		tempImage.setOutlineColor(sf::Color::Black);
		athleteImages.push_back(tempImage);
		if (counter % numPerRow == (numPerRow - 1) && counter != 0) {
			x = 15.f;
			y += (windowHeight / 4.f) + 100.f;
		}
		else {
			x += (windowWidth / numPerRow + 1) + 10.f;
		}
		counter++;
	}
}


void Game::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			window.setView(sf::View(visibleArea));
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				restart();
			}
		}
		else if (event.type == sf::Event::MouseMoved) {
			playButton.setFont(defaultFont);
			playButton.setString("Play");
			playButton.setCharacterSize(84);
			playButton.setColor(sf::Color(0, 285, 284));
			playButton.setOutlineColor(sf::Color::White);
			playButton.setOutlineThickness(4);
			playButton.setPosition(sf::Vector2f(windowWidth / 3, windowHeight / 4));

			selectDifficulty.setFont(defaultFont);
			selectDifficulty.setString("Select Level");
			selectDifficulty.setCharacterSize(84);
			selectDifficulty.setColor(sf::Color::Blue);
			selectDifficulty.setStyle(sf::Text::Bold);
			selectDifficulty.setPosition((windowWidth - selectDifficulty.getLocalBounds().width) / 2, 100.f);

			easy.setFont(defaultFont);
			easy.setString("Easy");
			easy.setCharacterSize(64);
			easy.setColor(sf::Color::White);
			easy.setPosition((windowWidth - easy.getLocalBounds().width) / 2, selectDifficulty.getPosition().y + selectDifficulty.getLocalBounds().height + 150.f);

			intermediate.setFont(defaultFont);
			intermediate.setString("Intermediate");
			intermediate.setCharacterSize(64);
			intermediate.setColor(sf::Color::White);
			intermediate.setPosition((windowWidth - intermediate.getLocalBounds().width) / 2, easy.getPosition().y + easy.getLocalBounds().height + 50.f);

			hard.setFont(defaultFont);
			hard.setString("Hard");
			hard.setCharacterSize(64);
			hard.setColor(sf::Color::White);
			hard.setPosition((windowWidth - hard.getLocalBounds().width) / 2, intermediate.getPosition().y + intermediate.getLocalBounds().height + 50.f);

			master.setFont(defaultFont);
			master.setString("Master");
			master.setCharacterSize(64);
			master.setColor(sf::Color::White);
			master.setPosition((windowWidth - master.getLocalBounds().width) / 2, hard.getPosition().y + hard.getLocalBounds().height + 50.f);

			expert.setFont(defaultFont);
			expert.setString("Expert");
			expert.setCharacterSize(64);
			expert.setColor(sf::Color::White);
			expert.setPosition((windowWidth - expert.getLocalBounds().width) / 2, master.getPosition().y + master.getLocalBounds().height + 50.f);

			returnMainMenu.setFont(defaultFont);
			returnMainMenu.setString("Solve more tiles!");
			returnMainMenu.setCharacterSize(64);
			returnMainMenu.setColor(sf::Color::White);
			returnMainMenu.setOutlineThickness(2);
			returnMainMenu.setPosition((windowWidth - returnMainMenu.getLocalBounds().width) / 2.f, winText.getPosition().y + 200.f);

			handleMouseHover(event);
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				handleMouseClick(event);
			}
		}
	}
}

void Game::update() {
	if (displayImages) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			mainView.setCenter(mainView.getCenter().x, mainView.getCenter().y + 25);
			mainView.move(0, 25);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			mainView.setCenter(mainView.getCenter().x, mainView.getCenter().y - 25);
			mainView.move(0, -25);
		}
	}
}

void Game::render() {
	//Background image
	backgroundTexture.setRepeated(true);
	if (!backgroundTexture.loadFromFile("Textures/backgroundTile.png")) {}
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(windowWidth, windowHeight));
	background.setTexture(&backgroundTexture);

	// Opening text
	sf::Text text;
	text.setFont(defaultFont);
	text.setString("TileSwitch");
	text.setCharacterSize(84);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(sf::Vector2f(windowWidth / 3, windowHeight / 2));


	stringstream ss;
	int t = timeCompletion.asSeconds() - 2.5;
	ss << "Nice job! You completed the puzzle in " << t << " seconds and " << (int) numOfMoves << " moves!";
	winText.setFont(defaultFont);
	winText.setString(ss.str());
	winText.setCharacterSize(28);
	winText.setColor(sf::Color::White);
	winText.setPosition((float)(windowWidth - winText.getLocalBounds().width) / 2.f, (float)(windowHeight - winText.getLocalBounds().height) / 2.f);

	// Animal Heading
	animalHeading.setFont(defaultFont);
	animalHeading.setString("Animals");
	animalHeading.setCharacterSize(84);
	animalHeading.setColor(sf::Color::Blue);
	animalHeading.setOutlineColor(sf::Color::White);
	animalHeading.setOutlineThickness(5);

	// Celebrity Heading
	celebrityHeading.setFont(defaultFont);
	celebrityHeading.setString("Celebrities");
	celebrityHeading.setCharacterSize(84);
	celebrityHeading.setColor(sf::Color::Blue);
	celebrityHeading.setOutlineColor(sf::Color::White);
	celebrityHeading.setOutlineThickness(5);

	// Athlete Heading
	athleteHeading.setFont(defaultFont);
	athleteHeading.setString("Athletes");
	athleteHeading.setCharacterSize(84);
	athleteHeading.setColor(sf::Color::Blue);
	athleteHeading.setOutlineColor(sf::Color::White);
	athleteHeading.setOutlineThickness(5);

	// Space Heading
	spaceHeading.setFont(defaultFont);
	spaceHeading.setString("Space ImAGES");
	spaceHeading.setCharacterSize(84);
	spaceHeading.setColor(sf::Color::Blue);
	spaceHeading.setOutlineColor(sf::Color::White);
	spaceHeading.setOutlineThickness(5);

	mainView.setViewport(sf::FloatRect(0, 0, 1, 1));

	window.setView(mainView);

	window.clear();

	if (displayMainMenu) {
		displayBackground();
		window.draw(text);
		window.draw(playButton);
	}

	if (displayDifficultyPage) {
		displayBackground();
		window.draw(selectDifficulty);
		window.draw(easy);
		window.draw(intermediate);
		window.draw(hard);
		window.draw(master);
		window.draw(expert);
	}

	if (displayImages) {
		window.clear();
		displayBackground();
		window.draw(animalHeading);
		for (int i = 0; i<animalImages.size(); i++) {
			window.draw(animalImages[i]);
		}
		window.draw(celebrityHeading);
		for (int i = 0; i<celebrityImages.size(); i++) {
			window.draw(celebrityImages[i]);
		}
		window.draw(athleteHeading);
		for (int i = 0; i<athleteImages.size(); i++) {
			window.draw(athleteImages[i]);
		}
		window.draw(spaceHeading);
		for (int i = 0; i<spaceImages.size(); i++) {
			window.draw(spaceImages[i]);
		}
	}

	if (displaySubImages) {
		displayCompletionPage();

		sf::RectangleShape tileImg;
		tileImg.setTexture(&(tileImage->textureImage));
		tileImg.setSize(sf::Vector2f(windowWidth, windowHeight));
		tileImg.setPosition(0,0);

		time = clock.getElapsedTime();
		for (int i = 0; i < tileImage->imageNum; i++) {
			window.draw(tileImage->subImages[i].image);
		}

		while (time.asSeconds() < 3.5) {
			window.draw(tileImg);
			time += clock.getElapsedTime();
		}
	}

	if (completedImage) {
		sf::RectangleShape tileImg;
		tileImg.setTexture(&(tileImage->textureImage));
		tileImg.setSize(sf::Vector2f(windowWidth, windowHeight));
		tileImg.setPosition(0, 0);

		window.draw(tileImg);
		window.draw(winText);
		window.draw(returnMainMenu);
	}

	window.display();

}

void Game::loadAthleteTextures() {
	// Roger Federer
	sf::Texture rogerFederer;
	rogerFederer.loadFromFile("Images/Athletes/Roger-Federer-Wallpapers.jpg");
	athleteTextures.push_back(rogerFederer);

	// Roger Federer 2
	sf::Texture rogerFederer2;
	rogerFederer2.loadFromFile("Images/Athletes/Roger-Federer-Images.jpg");
	athleteTextures.push_back(rogerFederer2);

	// Rafael Nadal
	sf::Texture rafaNadal;
	rafaNadal.loadFromFile("Images/Athletes/rafael_nadal.jpg");
	athleteTextures.push_back(rafaNadal);

	// Pete sampras
	sf::Texture peteSampras;
	peteSampras.loadFromFile("Images/Athletes/pete_sampras.jpg");
	athleteTextures.push_back(peteSampras);

	// Tom Brady
	sf::Texture tomBrady;
	tomBrady.loadFromFile("Images/Athletes/tom_brady.jpg");
	athleteTextures.push_back(tomBrady);

	// Andy Murray
	sf::Texture andyMurray;
	andyMurray.loadFromFile("Images/Athletes/andy_murray.jpg");
	athleteTextures.push_back(andyMurray);

	// Roger Federer 3
	sf::Texture rf3;
	rf3.loadFromFile("Images/Athletes/roger_federer_3.jpg");
	athleteTextures.push_back(rf3);

	// Lebron James
	sf::Texture lj;
	lj.loadFromFile("Images/Athletes/lebron_james.jpeg");
	athleteTextures.push_back(lj);

	// Kyrie Irving
	sf::Texture ki;
	ki.loadFromFile("Images/Athletes/kyrie_irving.jpg");
	athleteTextures.push_back(ki);

	// Kobe Bryant
	sf::Texture kobe;
	kobe.loadFromFile("Images/Athletes/kobe_bryant.jpg");
	athleteTextures.push_back(kobe);

	// Novak Djokovic
	sf::Texture novak;
	novak.loadFromFile("Images/Athletes/novak_djokovic.jpg");
	athleteTextures.push_back(novak);

}

void Game::loadAnimalTextures() {
	// Lion
	sf::Texture lionTexture;
	lionTexture.loadFromFile("Images/Animals/lion.jpg");
	animalTextures.push_back(lionTexture);

	// Tiger
	sf::Texture tigerTexture;
	tigerTexture.loadFromFile("Images/Animals/tiger.jpg");
	animalTextures.push_back(tigerTexture);

	// Tiger 2
	sf::Texture tiger2;
	tiger2.loadFromFile("Images/Animals/tiger_2.jpg");
	animalTextures.push_back(tiger2);

	// Llama
	sf::Texture llamaTexture;
	llamaTexture.loadFromFile("Images/Animals/llama.jpg");
	animalTextures.push_back(llamaTexture);

	// Leopard
	sf::Texture leopardTexture;
	leopardTexture.loadFromFile("Images/Animals/leopard.jpg");
	animalTextures.push_back(leopardTexture);

	// Cheetah
	sf::Texture cheetahTexture;
	cheetahTexture.loadFromFile("Images/Animals/cheetah.jpg");
	animalTextures.push_back(cheetahTexture);

	// Hyena
	sf::Texture hyenaTexture;
	hyenaTexture.loadFromFile("Images/Animals/hyena.jpg");
	animalTextures.push_back(hyenaTexture);

	// Zebra
	sf::Texture zebraTexture;
	zebraTexture.loadFromFile("Images/Animals/zebra.jpg");
	animalTextures.push_back(zebraTexture);

	// Giraffe
	sf::Texture giraffeTexture;
	giraffeTexture.loadFromFile("Images/Animals/giraffe.jpg");
	animalTextures.push_back(giraffeTexture);

	// Alligator
	sf::Texture alligatorTexture;
	alligatorTexture.loadFromFile("Images/Animals/alligator.jpg");
	animalTextures.push_back(alligatorTexture);

	// Deer
	sf::Texture deerTexture;
	deerTexture.loadFromFile("Images/Animals/deer.jpg");
	animalTextures.push_back(deerTexture);

	// Wolf
	sf::Texture wolfTexture;
	wolfTexture.loadFromFile("Images/Animals/wolf.jpg");
	animalTextures.push_back(wolfTexture);

	// Ibex
	sf::Texture ibexTexture;
	ibexTexture.loadFromFile("Images/Animals/ibex.jpg");
	animalTextures.push_back(ibexTexture);

	// Dolphin
	sf::Texture dolphinTexture;
	dolphinTexture.loadFromFile("Images/Animals/dolphin.jpg");
	animalTextures.push_back(dolphinTexture);

	// Red Panda
	sf::Texture rp;
	rp.loadFromFile("Images/Animals/red_panda.jpg");
	animalTextures.push_back(rp);

	// Antelope
	sf::Texture antelope;
	antelope.loadFromFile("Images/Animals/antelope.jpg");
	animalTextures.push_back(antelope);

	// Gazelle
	sf::Texture gazelle;
	gazelle.loadFromFile("Images/Animals/gazelle.jpg");
	animalTextures.push_back(gazelle);
}

void Game::loadCelebrityTextures() {
	// Tom Cruise
	sf::Texture tomCruise;
	tomCruise.loadFromFile("Images/Celebrities/tom_cruise.jpg");
	celebrityTextures.push_back(tomCruise);

	// Matt Damon
	sf::Texture mattDamon;
	mattDamon.loadFromFile("Images/Celebrities/matt_damon.jpg");
	celebrityTextures.push_back(mattDamon);

	// Richard Gere
	sf::Texture richardGere;
	richardGere.loadFromFile("Images/Celebrities/richard_gere.jpeg");
	celebrityTextures.push_back(richardGere);

	// Leonardo Dicaprio
	sf::Texture leonardoDicaprio;
	leonardoDicaprio.loadFromFile("Images/Celebrities/leonardo_dicaprio.jpg");
	celebrityTextures.push_back(leonardoDicaprio);

	// Robert de Niro
	sf::Texture rn;
	rn.loadFromFile("Images/Celebrities/robert_deniro.jpg");
	celebrityTextures.push_back(rn);

	// Kevin Spacey
	sf::Texture ks;
	ks.loadFromFile("Images/Celebrities/kevin_spacey.jpg");
	celebrityTextures.push_back(ks);

	// Harrison Ford
	sf::Texture hf;
	hf.loadFromFile("Images/Celebrities/harrison_ford.jpg");
	celebrityTextures.push_back(hf);

	// Luke Bryan
	sf::Texture lukeBryan;
	lukeBryan.loadFromFile("Images/Celebrities/luke_bryan.jpg");
	celebrityTextures.push_back(lukeBryan);

}

void Game::loadSpaceTextures() {
	sf::Texture space1;
	space1.loadFromFile("Images/Space/space.jpg");
	spaceTextures.push_back(space1);

	sf::Texture space2;
	space2.loadFromFile("Images/Space/space_2.jpg");
	spaceTextures.push_back(space2);

	sf::Texture space3;
	space3.loadFromFile("Images/Space/space_3.jpg");
	spaceTextures.push_back(space3);

	sf::Texture space4;
	space4.loadFromFile("Images/Space/space_4.jpg");
	spaceTextures.push_back(space4);
}

void Game::loadTextures() {
	loadAnimalTextures();
	loadCelebrityTextures();
	loadAthleteTextures();
	loadSpaceTextures();
}

void Game::displayCompletionPage() {
	image.setTexture(&(tileImage->textureImage));
	image.setSize(sf::Vector2f(windowWidth, windowHeight));
	image.setPosition(0.f, 0.f);
}

void Game::displayTiledImage(int imageNum, string fileName) {
	sf::Texture imageTexture;
	if (!imageTexture.loadFromFile("Images/" + fileName)) {
		cout << "Could not load file!" << endl;
	}
	sf::RectangleShape tiledImage;
	tiledImage.setSize(sf::Vector2f((float)windowWidth, (float)windowHeight));
	tiledImage.setTexture(&imageTexture);

	tileImage = new TileImage(imageTexture, tiledImage, windowWidth, windowHeight, true);
	tileImage->textureFilePath = fileName;
	tileImage->splitImage(imageNum);

	tileImage->mixSubImages();
}

void Game::displayTiledImage(int imageNum, sf::Texture texture) {
	sf::RectangleShape tiledImage;
	tiledImage.setSize(sf::Vector2f((float)windowWidth, (float)windowHeight));
	tiledImage.setTexture(&texture);

	tileImage = new TileImage(texture, tiledImage, windowWidth, windowHeight, true);
	tileImage->splitImage(imageNum);

	tileImage->mixSubImages();
}

bool Game::clickedOn(sf::Event mouseEvent, sf::RectangleShape shape) {
	float clickPos_x = (float)mouseEvent.mouseButton.x;
	float clickPos_y = (float)mouseEvent.mouseButton.y;

	return (shape.getGlobalBounds().contains(clickPos_x, clickPos_y));
}

bool Game::clickedOn(sf::Event mouseEvent, sf::FloatRect float_rect) {
	float clickPos_x = (float)mouseEvent.mouseButton.x;
	float clickPos_y = (float)mouseEvent.mouseButton.y;

	return (float_rect.contains(clickPos_x, clickPos_y));
}

bool Game::clickedOnImage(sf::Vector2f mousePos, sf::RectangleShape shape) {
	float clickPos_x = mousePos.x;
	float clickPos_y = mousePos.y;

	return (shape.getGlobalBounds().contains(clickPos_x, clickPos_y));
}

bool Game::hoveredOver(sf::Event mouseEvent, sf::RectangleShape shape) {
	float clickPos_x = mouseEvent.mouseMove.x;
	float clickPos_y = mouseEvent.mouseMove.y;

	return (shape.getGlobalBounds().contains(clickPos_x, clickPos_y));
}

bool Game::hoveredOver(sf::Event mouseEvent, sf::FloatRect float_rect) {
	float clickPos_x = mouseEvent.mouseMove.x;
	float clickPos_y = mouseEvent.mouseMove.y;

	return (float_rect.contains(clickPos_x, clickPos_y));
}

bool Game::hoveredOverImage(sf::Vector2f mousePos, sf::RectangleShape shape) {

	float clickPos_x = mousePos.x;
	float clickPos_y = mousePos.y;

	return (shape.getGlobalBounds().contains(clickPos_x, clickPos_y));
}

void Game::handleMouseHover(sf::Event mouseEvent) {
	if (hoveredOver(mouseEvent, playButton.getGlobalBounds())) {
		playButton.setColor(sf::Color::Blue);
	}
	if (displayDifficultyPage) {
		if (hoveredOver(mouseEvent, easy.getGlobalBounds())) {
			easy.setColor(sf::Color(66, 244, 140));
		}
		if (hoveredOver(mouseEvent, intermediate.getGlobalBounds())) {
			intermediate.setColor(sf::Color(66, 244, 140));
		}
		if (hoveredOver(mouseEvent, hard.getGlobalBounds())) {
			hard.setColor(sf::Color(66, 244, 140));
		}
		if (hoveredOver(mouseEvent, master.getGlobalBounds())) {
			master.setColor(sf::Color(66, 244, 140));
		}
		if (hoveredOver(mouseEvent, expert.getGlobalBounds())) {
			expert.setColor(sf::Color(66, 244, 140));
		}
	}
	if (completedImage) {
		if (hoveredOver(mouseEvent, returnMainMenu.getGlobalBounds())) {
			returnMainMenu.setColor(sf::Color::Blue);
		}
	}
	if (displayImages) {
		for (int i = 0; i<animalImages.size(); i++) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
			if (hoveredOverImage(worldPos, animalImages[i])) {
				//cout << "Animal hover" << endl;
				animalImages[i].setOutlineColor(sf::Color(66, 244, 140));
			}
			else {
				animalImages[i].setOutlineColor(sf::Color::White);
			}
		}
	}
	if (displayImages) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
		for (int i = 0; i<celebrityImages.size(); i++) {
			if (hoveredOverImage(worldPos, celebrityImages[i])) {
				//cout << "celeb hover" << endl;
				celebrityImages[i].setOutlineColor(sf::Color(66, 244, 140));
			}
			else {
				celebrityImages[i].setOutlineColor(sf::Color::White);
			}
		}
	}
	if (displayImages) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
		for (int i = 0; i<athleteImages.size(); i++) {
			if (hoveredOverImage(worldPos, athleteImages[i])) {
				//cout << "celeb hover" << endl;
				athleteImages[i].setOutlineColor(sf::Color(66, 244, 140));
			}
			else {
				athleteImages[i].setOutlineColor(sf::Color::White);
			}
		}
	}
}

void Game::handleMouseClick(sf::Event mouseEvent) {
	
	if (displayMainMenu) {
		if (clickedOn(mouseEvent, playButton.getGlobalBounds())) {
			displayMainMenu = false;
			displayDifficultyPage = true;
		}
	}
	else if (displayDifficultyPage) {
		if (clickedOn(mouseEvent, easy.getGlobalBounds())) {
			setAnimalImages(5);
			setCelebrityImages(5);
			setAthleteImages(5);
			setSpaceImages(5);
			difficulty = 1;
			displayImages = true;
			displayDifficultyPage = false;
		}
		else if (clickedOn(mouseEvent, intermediate.getGlobalBounds())) {
			setAnimalImages(5);
			setCelebrityImages(5);
			setAthleteImages(5);
			setSpaceImages(5);
			difficulty = 2;
			displayImages = true;
			displayDifficultyPage = false;
		}
		else if (clickedOn(mouseEvent, hard.getGlobalBounds())) {
			setAnimalImages(5);
			setCelebrityImages(5);
			setAthleteImages(5);
			setSpaceImages(5);
			difficulty = 3;
			displayImages = true;
			displayDifficultyPage = false;
		}
		else if (clickedOn(mouseEvent, master.getGlobalBounds())) {
			setAnimalImages(5);
			setCelebrityImages(5);
			setAthleteImages(5);
			setSpaceImages(5);
			difficulty = 4;
			displayImages = true;
			displayDifficultyPage = false;
		}
		else if (clickedOn(mouseEvent, expert.getGlobalBounds())) {
			setAnimalImages(5);
			setCelebrityImages(5);
			setAthleteImages(5);
			setSpaceImages(5);
			difficulty = 5;
			displayImages = true;
			displayDifficultyPage = false;
		}

	}
	else if (displayImages) {
		switch (difficulty) {
		case 1:
			tileNum = 16;
			break;
		case 2:
			tileNum = 25;
			break;
		case 3:
			tileNum = 49;
			break;
		case 4:
			tileNum = 64;
			break;
		case 5: 
			tileNum = 81;
			break;
		}
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
		for (int i = 0; i < animalImages.size(); i++) {
			if (clickedOnImage(worldPos, animalImages[i])) {
				mainView.setCenter(windowWidth / 2, windowHeight / 2);
				clock.restart();
				displayImages = false;
				displaySubImages = true;
				displayTiledImage(tileNum, *animalImages[i].getTexture());
			}
		}
		for (int i = 0; i < celebrityImages.size(); i++) {
			if (clickedOnImage(worldPos, celebrityImages[i])) {
				mainView.setCenter(windowWidth / 2, windowHeight / 2);
				clock.restart();
				displayImages = false;
				displaySubImages = true;
				
				displayTiledImage(tileNum, *celebrityImages[i].getTexture());
			}
		}
		for (int i = 0; i < athleteImages.size(); i++) {
			if (clickedOnImage(worldPos, athleteImages[i])) {
				mainView.setCenter(windowWidth / 2, windowHeight / 2);
				clock.restart();
				displayImages = false;
				displaySubImages = true;
				displayTiledImage(tileNum, *athleteImages[i].getTexture());
			}
		}
	}
	else if (displaySubImages) {
		for (int i = 0; i < tileImage->imageNum; i++) {
			sf::RectangleShape shape = tileImage->getSubImages()[i].image;
			if (clickedOn(mouseEvent, shape)) {
				tileImage->selectedSubImages.push_back(tileImage->getSubImages()[i]);
			}
		}
		if (tileImage->selectedSubImages.size() == 2) {
			sf::RectangleShape shape = tileImage->selectedSubImages[0].image;
			sf::RectangleShape shape2 = tileImage->selectedSubImages[1].image;

			tileImage->swapSubImages(tileImage->selectedSubImages[0], tileImage->selectedSubImages[1]);
			tileImage->selectedSubImages.clear();

			numOfMoves++;

			cout << numOfMoves << endl;

			if (tileImage->imageCompleted()) {
				timeCompletion = clock.getElapsedTime();
				displaySubImages = false;
				completedImage = true;
				clock.restart();
			}
		}
	}
	if (completedImage) {
		if (clickedOn(mouseEvent, returnMainMenu.getGlobalBounds())) {
			cout << "Clicked on return" << endl;
			restart();
		}
	}
}