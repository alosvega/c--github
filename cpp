#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
//FUNCTION PROTOTYPES---------------------------------------------------------


//FUNCTION PROTOTYPES---------------------------------------------------------
void map(int humanRow, int humanColumn, int clickerRow, int clickerColumn, bool mode);
void displayMenu();
string userModeChoice();
bool checkPerimeter(int humanRow, int humanColumn, int clickerRow, int clickerColumn);
bool gameOver(int humanRow, int humanColumn, int clickerRow, int clickerColumn);
void moveHuman(int & humanRow, int & humanColumn, int numRows, int numCols);
bool isValidLocation(int i, int j, int numRows, int numCols);
string askUserDirection();
bool validDirectionMove(string direction, int & clickerRow, int & clickerColumn, int numRows, int numCols);

//menu functions
// int userOption = 0; //this is a global variable
// void map();
//int startHuman();
//void human ();
//
//int usrNum();
//bool optionValidation();
//void branch();
//void easyMode();
//void hardMode();

//STARTING POINT-------------------------------------------------------------------
int main(){
    int numRows = 6;
    int numCols = 8;

    // get the user choice
    string choice = userModeChoice();

    bool mode = choice == "1";

    // initialize the random number generator
    srand(time(0));

    int turns = 0;

    // the location of the clicker
    int clickerRow = rand() % numRows;  // returns an int between 0 and 6
    int clickerColumn = rand() % numCols; // returns an int between 0 and 8

    int humanRow = rand() % numRows;  // returns an int between 0 and 6
    int humanColumn = rand() % numCols; // returns an int between 0 and 8
    // the purpose of this loop is to make sure that the Clicker and Human DO NOT BEGIN THE GAME at the same position
    while( humanRow==clickerRow && humanColumn==clickerColumn ) {
        humanRow = rand() % numRows;
        humanColumn = rand() % numCols;
    }



    while( !gameOver(humanRow, humanColumn, clickerRow, clickerColumn) ) {
        cout << endl;
        turns++;
        cout << "Turn " << turns << endl;
        map(humanRow, humanColumn, clickerRow, clickerColumn, mode);
        if( turns%2== 0 ){
            string direction = askUserDirection();
            while( !validDirectionMove(direction, clickerRow, clickerColumn, numRows, numCols) ) {
                direction = askUserDirection();
            }
        }
        else {
            bool sound = checkPerimeter(humanRow, humanColumn, clickerRow, clickerColumn);
            if( sound ) {
                cout << "The Clicker makes a sound . . . it heard something move!!!" << endl;
            }
            else {
                cout << "The Clicker makes a sound . . . silence rings." << endl;
            }
            moveHuman(humanRow, humanColumn, numRows, numCols);
        }
    }

    cout << "The Clicker has found the human! *injects with fungus*" << endl;

    //terminate
    return 0;
}
//DEFINING FUNCTIONS----------------------------------------------------------------------------------------------



/*
 * Description/Problem:
 * Format the map
 * Input:
 * int humanRow, humanColumn, clickerRow, clickerColumn,
 * Output:
 * Map with Human and Clicker displayed
 */
void map(int humanRow, int humanColumn, int clickerRow, int clickerColumn, bool mode){
	const int rows = 6;
	const int col = 8;
//	const char human = 'H';

    for( int i=0; i<rows; i++ ) {
        // print the -----------
        for( int j=0; j<(col*4); j++ ) {
            cout << "-";
        }
        cout << endl;


        // add a row
        /*
        |  ||  ||  ||  ||  ||  ||  ||  |
        */
        cout << "|";
        // this is printing cells for cols 0 to col-2
        for( int j=0; j<(col-1); j++ ) {
            // true is for Easy mode
            if( i==humanRow && j==humanColumn && mode == true) {
                cout << "H ||";
            }
            else if( i==clickerRow && j==clickerColumn ) {
                cout << "C ||";
            }
            else{
                cout << "  ||";
            }
        }
        // this is printing the last column
        if( i==humanRow && humanColumn==col-1 && mode==true) {
            cout << "H |" << endl;
        }
        else if( i==clickerRow && clickerColumn==col-1 ) {
            cout << "C |" << endl;
        }
        else {
            cout << "  |" << endl;
        }
    }
    for( int j=0; j<(col*4); j++ ) {
        cout << "-";
    }
    cout << endl;
    cout << endl;

// 	for (int row = 1; row <= rows; row++) {
// 		for (int column = 1; column <= col; column++) { //why is it 48 and not 32??
// 			if (row%2!=0 && column<=col){
// 					cout << "--";
// 			}
//             else if (((column == 1) && (row%2==0))|| ((column == col) && (row%2==0)) ){
//                 cout << "|";
//             }
//             else if (column%3==0){
//                 cout << "||";
//             }
// //				else if ((row = randomHuman)){
// //					cout << "H";
// //				}
//             else {
//                 cout << "  ";
//             }
//         }
//         cout << endl;
//     }
	//trying to get the human into the map at a random position!
//	srand(time(0));
//	int startHuman = ((col==2) + rand() % ((col ==23)-(col==2)+1));
//	do {
//		cout<< human;
//	}while (startHuman);
	}

//functions

/*
 * Description/Problem:
 * Display the menu to the user
 * Input:
 * No input in void function
 * Output:
 * Menu displayed to user
 */
void displayMenu(){
	cout << "Do you want to play in easy mode or hard mode?\n";
	cout << "Enter 1 for easy or 0 for hard: ";
}


/*
 * Description/Problem:
 * Display the menu to the user and receive input
 * Have validation for the input
 * Input:
 * Input into string choice
 * Output:
 * If invalid, user is asked to re-enter
 */
string userModeChoice() {
    displayMenu();
    string choice;
    getline(cin, choice);
    if( !(choice=="1" || choice=="0" )) {
        cout << "Invalid choice!" << endl;
        cout << "Re-enter!" << endl;
        return userModeChoice();
    }
    return choice;
}


/*
 * Description/Problem:
 * To move around the Human and Clicker
 * determine if they are within each others perimeter
 *
 * Input:
 * int humanRow, humanColumn, clickerRow, clickerColumn
 *
 * Output:
 * An updated version of where the Clicker and Human are
 *
 */
bool checkPerimeter(int humanRow, int humanColumn, int clickerRow, int clickerColumn) {
    // check the 8 cells around

    // check north-east cell
    if( clickerRow-1 == humanRow && clickerColumn+1 == humanColumn ) {
        return true;
    }
    // check east cell
    if( clickerRow == humanRow && clickerColumn+1 == humanColumn ) {
        return true;
    }
    // check south-east cell
    if( clickerRow+1 == humanRow && clickerColumn+1 == humanColumn ) {
        return true;
    }
    // check south cell
    if( clickerRow+1 == humanRow && clickerColumn == humanColumn ) {
        return true;
    }
    // check south-west cell
    if( clickerRow+1 == humanRow && clickerColumn-1 == humanColumn ) {
        return true;
    }
    // check west cell
    if( clickerRow == humanRow && clickerColumn-1 == humanColumn ) {
        return true;
    }
    // check north west cell
    if( clickerRow-1 == humanRow && clickerColumn-1 == humanColumn ) {
        return true;
    }
    // check north cell
    if( clickerRow-1 == humanRow && clickerColumn == humanColumn ) {
        return true;
    }
    return false;
}


/*
 * Description/Problem:
 * Ask user where they want to move the Clicker
 * Input:
 * Input for string direction
 *
 * Output:
 * Return the string of user input
 *
 */
string askUserDirection() {
    cout << "Which direction do you want to move? ";
    string direction;
    getline(cin, direction);
    if( direction=="left" ||  direction=="right" ||  direction=="up" ||  direction=="down" ) {
        return direction;
    }
    else {
        return askUserDirection();
    }
}


/*
 * Description/Problem:
 * Validation for direction user input
 * Input:
 * direction from askUserDirection function
 *
 * Output:
 * true or false value
 *
 */
bool validDirectionMove(string direction, int & clickerRow, int & clickerColumn, int numRows, int numCols) {

    // check east cell
    if( direction=="right" && isValidLocation(clickerRow,clickerColumn+1,numRows,numCols ) ) {
        clickerColumn++;
        return true;
    }
    // check south cell
    if( direction=="down" && isValidLocation(clickerRow+1,clickerColumn,numRows,numCols ) ) {
        clickerRow++;
        return true;
    }
    // check west cell
    if( direction=="left" && isValidLocation(clickerRow,clickerColumn-1,numRows,numCols ) ) {
        clickerColumn--;
        return true;
    }
    // check north cell
    if( direction=="up" && isValidLocation(clickerRow-1,clickerColumn,numRows,numCols ) ) {
        clickerRow--;
        return true;
    }
    return false;
}


/*
 * Description/Problem:
 * Check if the clicker and the human are in the same location
 * Input:
 * None
 * Output:
 * None
 *
 */
bool gameOver(int humanRow, int humanColumn, int clickerRow, int clickerColumn) {
    return (humanRow == clickerRow && humanColumn==clickerColumn);
}

/*
 * Description/Problem:
 * Check if i,j is a valid location within the map with numrows and numcolumns
 * Input:
 * int i, j, numRows, & numCols
 * Output:
 * Integers are returned
 */
// valid values of i: i>=0 && i<numrows
// valid values of j: j>=0 && j<numCols
bool isValidLocation(int i, int j, int numRows, int numCols) {
    return (i>=0 && j>=0 && i<numRows && j<numCols);
}

/*
 * Description/Problem:
 * Move human in one of the 8 possible directions
 * Input:
 * int humanRow, humanColumn, numRows, & numCols
 * Output:
 * Human moving a random direction on the map
 */
void moveHuman(int & humanRow, int & humanColumn, int numRows, int numCols) {
    // 8 values - each denotes a direction
    // value 0 : possible move to north east from current location
    // value 1 : possible move to east from current location
    // value 2 : possible move to south east from current location
    // value 3 : possible move to south from current location
    // value 4 : possible move to south west from current location
    // value 5 : possible move to west from current location
    // value 6 : possible move to north west from current location
    // value 7 : possible move to north from current location

    int direction = rand() % 8;

    // if random direction is north east
    if( direction== 0 ) {
        // check if move to north east is a valid location
        if( isValidLocation(humanRow-1, humanColumn+1, numRows, numCols) ) {
            // move
            humanRow--;
            humanColumn++;
            // return
            return;
        }
        // else if north east is moving the human out of the map
        else {
            // recur - try another direction
            moveHuman(humanRow, humanColumn, numRows, numCols);
        }
    }
    // if random direction is east
    else if( direction== 1 ) {
        // check if move to east is a valid location
        if( isValidLocation(humanRow, humanColumn+1, numRows, numCols) ) {
            // move
            humanColumn++;
            // return
            return;
        }
        // else if east is moving the human out of the map
        else {
            // recur - try another direction
            moveHuman(humanRow, humanColumn, numRows, numCols);
        }
    }
    // if random direction is south east
    else if( direction== 2 ) {
        // check if move to south east is a valid location
        if( isValidLocation(humanRow+1, humanColumn+1, numRows, numCols) ) {
            // move
            humanRow++;
            humanColumn++;
            // return
            return;
        }
        // else if south east is moving the human out of the map
        else {
            // recur - try another direction
            moveHuman(humanRow, humanColumn, numRows, numCols);
        }
    }
    // if random direction is south
    else if( direction==3 ) {
        // check if move to south is a valid location
        if( isValidLocation(humanRow+1, humanColumn, numRows, numCols) ) {
            // move
            humanRow++;
            // return
            return;
        }
        // else if south is moving the human out of the map
        else {
            // recur - try another direction
            moveHuman(humanRow, humanColumn, numRows, numCols);
        }
    }
    // if random direction is south west
    else if( direction==4 ) {
        // check if move to south west is a valid location
        if( isValidLocation(humanRow+1, humanColumn-1, numRows, numCols) ) {
            // move
            humanRow++;
            humanColumn--;
            // return
            return;
        }
        // else if south west is moving the human out of the map
        else {
            // recur - try another direction
            moveHuman(humanRow, humanColumn, numRows, numCols);
        }
    }
    // if random direction is west
    else if( direction==5 ) {
        // check if move to west is a valid location
        if( isValidLocation(humanRow, humanColumn-1, numRows, numCols) ) {
            // move
            humanColumn--;
            // return
            return;
        }
        // else if west is moving the human out of the map
        else {
            // recur - try another direction
            moveHuman(humanRow, humanColumn, numRows, numCols);
        }
    }
    // if random direction is north west
    else if( direction==6 ) {
        // check if move to north west is a valid location
        if( isValidLocation(humanRow-1, humanColumn-1, numRows, numCols) ) {
            // move
            humanColumn--;
            humanRow--;
            // return
            return;
        }
        // else if north west is moving the human out of the map
        else {
            // recur - try another direction
            moveHuman(humanRow, humanColumn, numRows, numCols);
        }
    }
    // if random direction is north
    else if( direction==7 ) {
        // check if move to north is a valid location
        if( isValidLocation(humanRow-1, humanColumn, numRows, numCols) ) {
            // move
            humanRow--;
            // return
            return;
        }
        // else if north is moving the human out of the map
        else {
            // recur - try another direction
            moveHuman(humanRow, humanColumn, numRows, numCols);
        }
    }
}

// void human(){
// 	if (rows%2==0 && (column == 2)+ 3){
// 		cout << "H";
// 	}
// }

// int usrNum(){
// 	int num = 0;
// 	cout << "Enter 1 for easy or 0 for hard: ";
// 	cin >> num;
// 	return num;
// }

// void easyMode(){
// 	map();

// }

// void hardMode(){
// 	map();

// }

// void branch(){
// 	if (userOption == 1){
// 		easyMode();
// 	}
// 	else if (userOption == 0){
// 		hardMode();
// 	}

// }


// bool optionValidation(){
// 	if ((userOption == 0) && (userOption == 1)){
// 		return true;
// 	}
// 	else{
// 		return false;
// 	}
// }
//trying to put human  in map at random position
//int startHuman(){
//		map();
//		srand(time(0));
//		int startHuman = ((col==2) + rand() % ((col ==23)-(col==2)+1));
//		cout << startHuman;
//}
//
////code to move human randomly
//void human(){
//	map();
//	srand(time(0));
//	if ((int x = 1 +rand()% (9-1+1)) == 1){
//		cout << "Up";
//		}
//	else if ((int x = 1 +rand()% (9-1+1)) == 2){
//		cout << "Down";
//	}
//	else if ((int x = 1 +rand()% (9-1+1)) == 3){
//		cout << "Left";
//	}
//	else if ((int x = 1 +rand()% (9-1+1)) == 4){
//		cout <<"Right";
//	}
//	else if ((int x = 1 +rand()% (9-1+1)) == 5){
//		cout << "Diagonal Up Right";
//	}
//	else if ((int x = 1 +rand()% (9-1+1)) == 6){
//		cout << "Diagonal up left";
//	}
//	else if ((int x = 1 +rand()% (9-1+1)) == 7){
//		cout << "Diagonal down right";
//	}
//	else ((int x = 1 +rand()% (9-1+1)) == 8){
//		cout << "Diagonal down left";
//	}
//}

