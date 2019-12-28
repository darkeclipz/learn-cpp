//#include <iostream>
//#include <chrono>
//
//// Example puzzles
////   easy:    530070000600195000098000060800060003400803001700020006060000280000419005000080079
////   hardest: 800000000003600000070090200050007000000045700000100030001000068008500010090000400
////   another: 002008050000040070480072000008000031600080005570000600000960048090020000030800900
////   extreme: 000000010000002003000400000000000500401600000007100000050000200000080040030910000
//
//int grid[81]; // Holds the puzzle grid in a 1D array.
//bool domains[81][9]; // Holds the numbers that are still available in each cell.
//int constraints[81]; // Holds the number of choices per cell.
//
//int nFoundSolutions = 0; // How many solutions we have currently found,
//						 // a Sudoku contains exactly one solution, but 
//						 // an invalid Sudoku could contain more.
//
//// All the indices in the grid for the different squares.
//int squares[9][9] = {
//	{0,  1,  2,  9,  10, 11, 18, 19, 20},	// square 1
//	{3,  4,  5,  12, 13, 14, 21, 22, 23},	// square 2
//	{6,  7,  8,  15, 16, 17, 24, 25, 26},	// square 3
//	{27, 28, 29, 36, 37, 38, 45, 46, 47},	// square 4
//	{30, 31, 32, 39, 40, 41, 48, 49, 50},	// square 5
//	{33, 34, 35, 42, 43, 44, 51, 52, 53},	// square 6
//	{54, 55, 56, 63, 64, 65, 72, 73, 74},	// square 7
//	{57, 58, 59, 66, 67, 68, 75, 76, 77},	// square 8
//	{60, 61, 62, 69, 70, 71, 78, 79, 80}	// square 9
//};
//
//int lookupRow[81];
//int lookupColumn[81];
//int lookupSquare[81] = {
//	0, 0, 0, 1, 1, 1, 2, 2, 2,
//	0, 0, 0, 1, 1, 1, 2, 2, 2,
//	0, 0, 0, 1, 1, 1, 2, 2, 2,
//	3, 3, 3, 4, 4, 4, 5, 5, 5,
//	3, 3, 3, 4, 4, 4, 5, 5, 5,
//	3, 3, 3, 4, 4, 4, 5, 5, 5,
//	6, 6, 6, 7, 7, 7, 8, 8, 8,
//	6, 6, 6, 7, 7, 7, 8, 8, 8,
//	6, 6, 6, 7, 7, 7, 8, 8, 8
//};
//
//
///*
//Prints the grid in the console.
//*/
//void PrintGrid() {
//	for (int i = 0; i < 81; i++) {
//		if (!(i % 9) && i != 0)  // Print a newline every 9 chars (except for the first line).
//			std::cout << std::endl;
//		std::cout << grid[i] << " ";
//	}
//	std::cout << std::endl;
//}
//
//
///*
//Check if a row r is valid. It iterates through all the grid indices for the row,
//which is i = {9r, 9r+1, 9r+2, 9r+3, ...}, and checks if each number only appears once.
//*/
//bool IsValidRow(int r) {
//	bool digits[10] = { false, false, false, false, false, false, false, false, false, false };
//	for (int i = 9 * r; i < 9 * r + 9; i++)  // i is in the index in the grid for row r.
//		if (!digits[grid[i]] || !grid[i])
//			digits[grid[i]] = true;
//		else
//			return false;
//	return true;
//}
//
//
///*
//Check if a column c is valid. It iterates through all the grid indices for the column,
//which is i = {c, c+9, c+2*9, c+3*9, ...}, and checks if each number only appears once.
//*/
//bool IsValidColumn(int c) {
//	bool digits[10] = { false, false, false, false, false, false, false, false, false, false };
//	for (int i = c; i < 81; i += 9)  // i is the index in the grid for column c.
//		if (!digits[grid[i]] || !grid[i])
//			digits[grid[i]] = true;
//		else
//			return false;
//	return true;
//}
//
//
///*
//Check if a square s is valid. It will retrieve the grid indices from the
//squares lookup array. Here i = {0, 1, ..., 9} is used to get the index, and then
//each digit is checked to only appear once.
//*/
//bool IsValidSquare(int s) {
//	bool digits[10] = { false, false, false, false, false, false, false, false, false, false };
//	for (int i = 0; i < 9; i++) {  // i is the index in the square lookup for square s.
//		int index = squares[s][i];
//		if (!digits[grid[index]] || !grid[index])
//			digits[grid[index]] = true;
//		else
//			return false;
//	}
//	return true;
//}
//
//
///*
//Check if the partial solution is valid. This checks each row, column, and square
//to only have each number 1..9 once.
//*/
//bool IsValidPartialSolution() {
//	// Check all the rows, columns, and squares to have exactly
//	// one number of 1..9.
//	for (int i = 0; i < 9; i++)
//		if (!IsValidRow(i) || !IsValidColumn(i) || !IsValidSquare(i))
//			return false;
//	return true;
//}
//
//
///*
//Prints the solution.
//*/
//void PrintSolution() {
//	std::cout << "Solution " << ++nFoundSolutions << ":\r\n";
//	PrintGrid();
//}
//
//
//bool* Prune(int i) {
//	bool mask[81];
//	if (grid[i] > 0) {
//		int row = lookupRow[i];
//		for (int j = 0; j < 9; j++) {
//			if (domains[9 * row + j][grid[i] - 1]) {
//				domains[9 * row + j][grid[i] - 1] = false;
//				constraints[9 * row + j]--;
//				mask[9 * row + j] = true;
//			}
//		}
//
//		int col = lookupColumn[i];
//		for (int j = 0; j < 9; j++) {
//			if (domains[col + 9 * j][grid[i] - 1]) {
//				domains[col + 9 * j][grid[i] - 1] = false;
//				constraints[col + 9 * j]--;
//				mask[col + 9 * j] = true;
//			}
//		}
//
//		int square = lookupSquare[i];
//		for (int j = 0; j < 9; j++) {
//			int index = squares[square][j];
//			if (domains[index][grid[i] - 1]) {
//				domains[index][grid[i] - 1] = false;
//				constraints[index]--;
//				mask[index] = true;
//			}
//		}
//
//		for (int j = 0; j < 9; j++)
//			domains[i][j] = false;
//		constraints[i] = 0;
//	}
//	return mask;
//}
//
//void Prune() {
//	for (int i = 0; i < 81; i++) {
//		Prune(i);
//	}
//}
//
//void Unprune(int i, bool* mask) {
//	if (grid[i] > 0) {
//		int row = lookupRow[i];
//		for (int j = 0; j < 9; j++) {
//			if (!domains[9 * row + j][grid[i] - 1] && mask[9 * row + j]) {
//				domains[9 * row + j][grid[i] - 1] = true;
//				constraints[9 * row + j]++;
//			}
//		}
//
//		int col = lookupColumn[i];
//		for (int j = 0; j < 9; j++) {
//			if (!domains[col + 9 * j][grid[i] - 1] && mask[col + 9 * j]) {
//				domains[col + 9 * j][grid[i] - 1] = true;
//				constraints[col + 9 * j]++;
//			}
//		}
//
//		int square = lookupSquare[i];
//		for (int j = 0; j < 9; j++) {
//			int index = squares[square][j];
//			if (!domains[index][grid[i] - 1] && mask[index]) {
//				domains[index][grid[i] - 1] = true;
//				constraints[index]++;
//			}
//		}
//
//		for (int j = 0; j < 9; j++) {
//			domains[i][j] = true;
//		}
//
//		constraints[i] = 9;
//		Prune(i);
//	}
//}
//
//
//int FindLeastConstrainedCell() {
//	int min = INT_MAX;
//	int index = 0;
//	int i = 0;
//	for (; i < 81; i++) {
//		if (constraints[i] != 0 && constraints[i] < min) {
//			min = constraints[i];
//			index = i;
//		}
//	}
//	return min >= 0 && min != INT_MAX ? index : -1;
//}
//
//
///*
//Search backtracking procedure for solving the puzzle. It first finds a cell
//that is empty (!= 0), and then it tries the values 1..9. If it is a valid
//partial solution, it will continue to the next cell. If all the cells are
//filled, we have found a solution.
//*/
//void Search() {
//	int cell = FindLeastConstrainedCell();
//	if (cell == -1)
//		return PrintSolution();
//	if (grid[cell] == 0) {  // Check if the cell is empty.
//		for (int i = 0; i < 9; i++) {  // Try each value in 1..9.
//
//			if (domains[cell][i]) {
//
//				// Make a choice and remove from domains
//				int nConstraints = constraints[cell];
//
//				constraints[cell] = 0;
//				grid[cell] = i + 1;   // Set the value of the cell.
//				bool* mask = Prune(cell);
//
//
//
//				Search(); // Continue searching with this value.
//
//				Unprune(cell, mask);
//
//				// Undo the removals and choice
//				grid[cell] = 0;   // Remove the value (backtrack).
//
//				constraints[cell] = nConstraints;
//
//			}
//		}
//	}
//	else Search();  // Cell is already filled, go to the next cell.
//}
//
//
//
//
//
///*
//Load a puzzle string (string containing 81 chars with 0 indicating an empty cell)
//into the grid array.
//*/
//void LoadPuzzle(std::string puzzleString) {
//	// Check if the puzzle string has the correct size.
//	if (puzzleString.size() != 81)
//		throw std::invalid_argument("invalid puzzle.");
//	for (int i = 0; i < 81; i++)
//		grid[i] = puzzleString[i] - 48; // 48 is the ASCII code for 0.
//}
//
//
//void Initialize() {
//	for (int i = 0; i < 81; i++) {
//		constraints[i] = 9;
//		for (int j = 0; j < 9; j++) {
//			domains[i][j] = true;
//		}
//	}
//	for (int i = 0; i < 9; i++)
//		for (int j = 0; j < 9; j++) {
//			lookupRow[i * 9 + j] = i;
//			lookupColumn[i * 9 + j] = j;
//		}
//}
//
//
//int main2(int argc, char* argv[])
//{
//	try {
//		if (argc < 2) {
//			std::cout << "Enter a puzzle string with: \r\n   - sudosolve.exe <puzzle string>\r\n";
//			return 1;
//		}
//
//		std::string sPuzzleString = argv[1];
//		LoadPuzzle(sPuzzleString);
//		Initialize();
//
//		std::cout << "-- Sudoku Solver --\r\n\r\n";
//		std::cout << "PuzzleString:\r\n" << sPuzzleString << std::endl;
//		std::cout << "\r\nPuzzle:\r\n";
//		PrintGrid();
//		std::cout << "\r\n";
//
//		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();  // Get start time
//		Prune();
//		Search(); // Start the backtrack procedure (at k=0).
//
//		if (!nFoundSolutions) std::cout << "Found no solutions.\r\n";
//		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();  // Get end time
//		std::cout << "\r\nExecuted in " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << " milliseconds" << std::endl;
//	}
//	catch (std::exception & e) {
//		std::cout << e.what() << std::endl;
//	}
//}
