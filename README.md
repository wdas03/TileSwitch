# TileSwitch
Interactive tile switch puzzle game made in C++ using SFML.

## Setup
Make sure sfml is installed:

    brew install sfml

## Run Program
From TileSwitch/TileSwitch, run:

    g++ -Wall -std=c++11 *.cpp -Iinclude -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -o game

Then:

    ./game

## How to Play
<img src="images/1.png">

Select level:
<img src="images/2.png">

Memorize image:
<img src="images/3.png">

Put scrambled image to original:
<img src="images/4.png">
