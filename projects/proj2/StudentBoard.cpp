#include "Board.hpp"
#include "BoardValues.hpp"

#include <algorithm>
#include <iostream>

/********************************************************************
 * A class that creates a board for a Battleship game and will 
 * print it out.
 *
 * @author Sarah Rockow
 * @version Winter 2022
 *
 * Notes:
 * 
 * I guessed on a lot of this and I tried using some of the 
 * constructor logic from the vector project to get this 
 * working. I did not use count or the comparator.
 * 
 *
 * Glitches
 *
 * -> the board does not print properly and my brain is dead
 *
 * -> after around 10 turns, there's a segmentation fault, so
 *  I probably need to free some memory with the destructor, 
 *  but I'm not sure where it should be called in StudentGame
 * *****************************************************************/

/********************************************************************
  Constructor that returns a Board object
 ********************************************************************/
Board::Board(){
	// int* grid from private in Board.hpp; WIDTH/HEIGHT defined 
	grid = new int[WIDTH * HEIGHT];

	// initialize the board
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			(grid[(i * WIDTH) + j]) = EMPTY;
		}
	}
	
}

/********************************************************************
  Copy constructor that creates a deep copy of a board

  @param other - the board to be copied
  Sources: 
  www.ibm.com/docs/en/zos/2.4.0?topic=only-copy-assignment-operators-c
 ********************************************************************/
Board::Board(const Board& other) {
	Board *grid = new Board(other);
}


/********************************************************************
  Copy operator that creates a shallow copy of a board

  @param other - a board
 ********************************************************************/
Board& Board::operator=(const Board& other){
	this->grid = other.grid;
	return *this;
}


/********************************************************************
  Destructor that frees memory
 ********************************************************************/
Board::~Board(){
	delete(grid);
}

/********************************************************************
  Function to set a board's visibility
 ********************************************************************/
void Board::setVisible(bool v){
	// visible comes from Board.hpp
	visible = v;
}

/********************************************************************
 Operator overload? function that will return an error if an illegal
 coordinate is given by the user. Code provided by instructor.

 @param index - the x coordinate given by user or computer
 ********************************************************************/
int& Board::Internal::operator[](int index){
	/*if (index >= WIDTH) {
		throw std::out_of_range(std::to_string(index) + 
		" is greater value than or equal to grid width of " + 
		std::to_string(WIDTH));
	}*/

	return _grid[index];
}


/********************************************************************
 Operator overload? function that will return an error if an illegal
 coordinate is given by the user. Code provided by instructor.

 @param index - the y coordinate given by user or computer
 ******************************************************************/
Board::Internal Board::operator[](int index){
	/*if (index >= HEIGHT) {
		throw std::out_of_range(std::to_string(index) + 
		" is greater value than or equal to grid height of " 
		+ std::to_string(HEIGHT));
	}*/

	return Board::Internal(grid+(index * WIDTH));
}


/********************************************************************
  Function to overload the stream operator to print out the board.

  @param os - var of type ostream; used to choose the stream
  @param b - a board
 *******************************************************************/
std::ostream& operator<<(std::ostream& os, Board const& b){
//https://stackoverflow.com/questions/45172025/about-stdostream-constructor
	
	// column header
	for (int i = 0; i < WIDTH; i++) {
		os << i << "   ";
	}

	// new line
	os << std::endl;

	os << "---------------------------------------------" << std::endl;


	// grid
	for (int i = 0; i < WIDTH; i++) {
		// row header
		os << i << "| ";

		// for printing data
		for (int j = 0; j < HEIGHT; j++) {
			os << "  " << (char) (b.grid[(i * WIDTH) + j]) << "   ";
		}

		// new line
		os << std::endl;
	}

	return os;
}

/********************************************************************
  Function to return the number of defeated ships
 ********************************************************************/
int Board::count() const{
	int count = 0;
	
	// doesn't work the way I want it to
/*
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if ((char) (this->grid[(i * WIDTH) + j]) != EMPTY)) {
				count += 1;
			}
		}
	}
*/
	return count;
}

/********************************************************************
  Function to determine winning player
 ********************************************************************/
bool Board::operator< (const Board& other){

	// doesn't work the way I want to
/*	
	if (this->count > other->count) {
		return true;
	}
*/	
	return false;
}
