#include "Board.hpp"
#include "Direction.hpp"
#include "Game.hpp"
#include "Ship.hpp"
#include <iostream>
#include <random>


/******************************************************************
 * A text-based Battleship game that will allow one user to play
 * against a computer. 
 *
 * @author	 Sarah Rockow
 * @collaborator Amaka Ezuruonye
 * @version	 Winter 2022
 *
 * Notes: Originally started by trying to create the project in one
 * 'Battleship' file with Amaka, but ultimately tried to use the
 * starter code. 
 *
 * Glitches 
 *
 * -> the board will not print properly and a lot of the
 * values are getting overridden
 *
 * -> when I printed the board, it looked like my logic was 
 *  backwards for vertical and horizontal, but I can't figure 
 *  out how to fix it
 *
 * -> ended up using rand() for the computer; I found an article
 *  about how to use uniform distribution, but I couldn't get it 
 *  to work
 *
 * -> couldn't figure out how to isolate player and computer ships
 *  to keep track of the hits with addHits(), so I ended up making
 *  global variables to keep track for me
 * ****************************************************************/

// to keep track of the score
int compHits = 0;
int playerHits = 0;


// to keep track of turns
int i = 0;

/********************************************************************
  Constructor will create the ships vector and add ships to it
 ********************************************************************/
Game::Game(){

	// ASCII character codes are provided in BoardValues.hpp
	// initialize ships
	Ship* carrier = new Ship(5, "Carrier", CARRIER);
	Ship* battle = new Ship(4, "Battleship", BATTLESHIP);
	Ship* destroyer = new Ship(3, "Destroyer", DESTROYER);
	Ship* sub = new Ship(3, "Submarine", SUBMARINE);
	Ship* patrol = new Ship(2, "Patrol Boat", PATROLBOAT);

	// hold all ships; provided in Ships.hpp
	ships = {*carrier, *battle, *destroyer, *sub, *patrol};
}

/********************************************************************
  Begin Game - 
  let's user and then computer setup boards then calls run()
 ********************************************************************/
void Game::beginGame(){
	// welcome message from video
	std::cout << "|------------ BATTLESHIP --------------|" 
		<< std::endl;
	std::cout << "You will play versus Admiral Hopper, "
		"the greatest of computer players! ";
	std::cout << "Place your ships, and good luck to you!" 
		<< std::endl;

	// let user set up ships first; player provided in Ships
	player = *(new Board());
	placeShips();

	// let computer set up ships; computer provided in Ships
	computer = *(new Board());
	placeShipsPC();

	// start game
	run();
}

/********************************************************************
  Handle the human placing ships
 ********************************************************************/
void Game::placeShips(){
	int x, y, d;
	Direction dir;

	std::cout << std::endl << "The pieces are:" << std::endl;
	std::cout << std::endl;

	std::cout << "\tCarrier [5 spaces]\n";
	std::cout << "\tBattleship [4 spaces]\n";
	std::cout << "\tDestroyer [3 spaces]\n";
	std::cout << "\tSubmarine [3 spaces]\n";
	std::cout << "\tPatroal Boat [2 spaces]\n\n";


	for (int i = 0; i < 5; i++) {
		// prompt user and place ships
		std::cout << std::endl << "Enter x-coordinate and press enter; "
			"repeat for y\n\n";

		std::cout << "Where do you wish to place the "
			<< ships.at(i) << "?\n";

		std::cin >> x;
		std::cin >> y;

		std::cout << std::endl << "Horizontally or vertically?"
			" (1 or 0)\n";

		std::cin >> d;

		std::cout << std::endl << "Attempting to place the ship "
			"at [" << x << ", " << y;

		if (d == 0) {
			std::cout << "] horizontally.\n\n";
			dir = HORIZONTAL;	
		}

		if (d == 1) {
			std::cout << "] vertically.\n\n" << std::endl;
			dir = VERTICAL;
		}

		// check for valid placement
		if (!place(x, y, dir, ships.at(i), player)) {
			std::cout << "Try again\n";
			i--; // reset w/o exiting
		}

		std::cout << player << std::endl;
	}


}

/********************************************************************
  Handle the computer placing ships
 ********************************************************************/
void Game::placeShipsPC(){

	int x, y;
	Direction dir;


	for (int i = 0; i < 5; i++) {
		// couldn't figure out the rand() alternative
		//https://stackoverflow.com/questions/288739
		// /generate-random-numbers-uniformly-over-an-entire-range

		x = rand() % (10 - 1 + 1) + 1;
		y = rand() % (10 - 1 + 1) + 1;

		// direction will be alternated
		if ((i % 2) == 0) {
			dir = HORIZONTAL;
		}
		else {
			dir = VERTICAL;
		}

		// check for valid placement
		if (!place(x, y, dir, ships.at(i), computer)) {
			std::cout << "\nTry again\n\n";
			i--; // reset w/o exiting
		}

		std::cout << computer << std::endl;
	}
}

/********************************************************************
  Helper method that checks if it is safe to put a ship at a 
  particular spot with a particular direction.
 ********************************************************************/
bool Game::place(const int& x, const int& y, Direction d, const Ship& s, Board& b){

	bool condition = true;

	// case 1: out of bounds (negative)
	if ((x < 0) || (y < 0) || (x > WIDTH) || (y > HEIGHT)) {
		condition = false;
	}

	// case 2a: horizontal out of bounds
	if (d == HORIZONTAL){
		if ((s.getSpaces() + x) > WIDTH) {
			condition = false;
		}
	}

	// case 2b: vertical out of bounds
	if (d == VERTICAL) {
		if ((s.getSpaces() + y) > HEIGHT) {	
			condition = false;
		}
	}

	// case 3: collision detection
	if (d == HORIZONTAL) {
		for (int i = 0; i < s.getSpaces(); i++) {
			// y stays the same; x grows
			if (b[x + i][y] == EMPTY) {
				b[x + i][y] = s.getChr();
			}
			else {
				condition = false;
				std::cout << "Collision detected\n";
			}
		}
	}


	if (y == VERTICAL) {
		for (int i = 0; i < s.getSpaces(); i++) {
			// x stays the same; y grows
			if(b[x][y + i] == EMPTY) {
				b[x][y + i] = s.getChr();
			}
			else {
				condition = false;
				std::cout << "Collision detected\n";
			}
		}
	}	

	return condition;
}

/********************************************************************
  Call human turn/computer turn until someone wins
 ********************************************************************/
void Game::run() {

	bool condition;

	// checking to see if all sihps have been hit	
	for (int i = 0; i < 5; i++) {
		if (ships.at(i).getHits() == ships.at(i).getSpaces()) {
			condition = false;
		}
	}

	if (playerHits == 17 || compHits == 17) {
		condition = false;
	}

	if (playerHits == 17) {
		std::cout << "\n\nYOU WON!!!\n\n";
		exit(1);
	}

	if (compHits == 17) {
		std::cout << "\n\nComputer won :(\n\n";
		exit(1);
	}

	while (condition) {
		
	       
		if ((i % 2) == 0) {
			humanTurn();
		}

		else {
			computerTurn();
		}
		i += 1;
	}
}

/********************************************************************
  Call human turn
 ********************************************************************/
void Game::humanTurn(){

	int x, y;

	// prompt for coordinates
	std::cout << "\nWhich coordinate do you wish to attack?\n";
	std::cin >> x;
	std::cin >> y;

	// check for a hit
	if (computer[x][y] != EMPTY) {
		computer[x][y] = HIT;	
		// can't figure out how to isolate ships for addHit()
		compHits += 1;
		std::cout << "\nPlayer HIT!\n";
	}

	else {
		computer[x][y] = MISS;
		std::cout << "\nPlayer miss\n";
	}
}

/********************************************************************
  Call computer turn
 ********************************************************************/
void Game::computerTurn(){

	int x, y;

	// choose coordinates
	x = rand() % (10 - 1 + 1) + 1;
	y = rand() % (10 - 1 + 1) + 1;

	if (player[x][y] != EMPTY) {
		player[x][y] = HIT;

		playerHits += 1;
		std::cout << "\nComputer HIT!\n";
	}

	else {
		player[x][y] = MISS;
		std::cout << "\nComputer miss\n";
	}

	std::cout << "\nPlayer Board\n";
	std::cout << player;
}


/********************************************************************
  Create a game instance and start
 ********************************************************************/
int main(int argc, char** argv){
	(void)argc;
	(void)argv;
	Game g;



	g.beginGame();

	return 0;
}
