#include <string>
#include <iostream>
using namespace std;

class BattleShip{
    public:
        void board(int x[], int y[], int pos[], int limit[], string character[]);
	bool validPlacement(int x, int y, int pos, int limit);
};

int main(){

    cout << " *** Welcome! ***";
    cout << endl << "You will be playing against Commander Ender Wiggin, - ";
    cout << "the greatest in battleship strategy!";
    cout << endl << "";
    cout << endl << " Please place your ships and begin the battle!!! \n";
    cout << endl << " * The pieces, the spaces required, and their symbols are: \n";
    cout << " * Carrier -> 5 spaces\n"; //C
    cout << " * Battle Ship -> 4 spaces\n"; //B
    cout << " * Destroyer -> 3 spaces\n"; //D
    cout << " * Submarine -> 3 spaces\n"; //S
    cout << " * Patrol Boat -> 2 spaces\n"; //P 
    
    BattleShip sample;

    string ships[5] = {"Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat"};
    string shipChar[5] = {"C", "B", "D", "S", "P"};
    int xCoord[5];
    int yCoord[5];
    int direction[5];

    int lim[5] = {5, 4, 3, 3, 2};

    for (int i = 0; i < 5; i++) {

	int a, b, d;

	cout << endl << "Where would you like to place your " << ships[i] << "?" << endl << "";
   	cout << "x: ";
	cin >> a;
	cout << "y: ";
	cin >> b;

	cout << "Horizontally or vertically? (0 or 1)";
	cin >> d;
	
	if (!sample.validPlacement(a, b, d, lim[i])) {
		cout << "Error";
		exit(1);
	}

	// storing values
	xCoord[i] = a;
	yCoord[i] = b;
	direction[i] = d;

	// sample test
	sample.board(xCoord, yCoord, direction, lim, shipChar);
	 
	// collision verification
    }

	sample.board(xCoord, yCoord, direction, lim, shipChar);	
}


void BattleShip::board(int x[], int y[], int pos[], int limit[], string character[]){ 
    int rows = 10;
    int cols = 10;

    string gameBoard[cols][rows];

    // horizontal header
    for(int i = 0; i < rows; i++){ 
        gameBoard[0][i] = i;
        cout << " |" << i << "|";
    }

    for(int j = 1; j < rows; j++){ 
        cout << "\n";
        gameBoard[j][0] = j;

	// vertical header
	cout << " |" << j << "| ";


	for (int a = 0; a < cols; a++) {
	for(int k = 1; k < cols; k++){ 

		// horizontal
		if (pos[a] == 0) {
			// j checks rows
			if (j == y[a]) {
				// place ship initial where ship should be
				if ((k >= x[a]) && (k < (limit[a] + x[a]))) {
					gameBoard[j][k] = character[a];
			//		cout << "|" << gameBoard[j][k] << "| ";
				}/*
				else {
					gameBoard[j][k] = " ";
				}*/

				//cout << "|" << gameBoard[j][k] << "| ";
			}

		}

		// vertical 
		if (pos[a] == 1) {
			if ((j >= y[a]) && (j < (limit[a] + y[a]))) {	
				if (k == x[a]) {
					gameBoard[j][k] = character[a];
			
			//	cout << "|" << gameBoard[j][k] << "| ";
				}/*
				else {
					gameBoard[j][k] = " ";
				}*/
			}
		}

	}

	cout << "|" << gameBoard[j][k] << "| ";	
	}
    }
}

bool BattleShip::validPlacement(int x, int y, int pos, int limit) {

	bool condition = true;

	// general positioning
	if ((x < 0) || (y < 0) || (x > 9) || (y > 9)) {
		condition = false;
		cout << endl << "Out of Bounds";
	}

	// horizontal rules
	if (pos == 0) {	
		if ((limit + x) > 9) {
			condition = false;
			cout << endl << "Invalid x-coordinate";
		}
	}

	// vertical rules
	if (pos == 1) {
		if ((limit + y) > 9) {
			condition = false;
			cout << endl << "Invalid y-coordinate";
		}
	}

	return condition;
}


// class BattleShip(){ }
