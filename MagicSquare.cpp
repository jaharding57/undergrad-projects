/*
PIC 10B Homework 6, MagicSquare.cpp
Author: Johnathan Harding
Date: 2/19/2022
*/

#include "MagicSquare.h" //include necessary header files

//constructor
//magic vec constructed with 0 rows initially
MagicSquare::MagicSquare(int dim = 0) : n(dim), magicVec(0, std::vector<int>(dim, 0)), mMask(0, std::vector<int>(dim, 0)), 
nXn(dim*dim), numSols(0) {
	
	//mSum (sum that every row, columns, and both diagonals must equate to
	mSum = (dim * ((dim * dim) + 1)) / 2;

	//for initializing pot_vals, the set storing vals a cell could potentially be set to...
	for (int i = 1; i <= nXn; ++i) {
		pot_vals.insert(i);
	}

}

//taken function
bool MagicSquare::taken(int val) const {
		if (used_vals.find(val) == used_vals.end()) //if the value is found (using find and comparison to end of set)
		{
			return false; //if is essentially at end of set, the val is not already in set, return false 
		}
		else
		{
			return true; //if is not at end of set, the val is already in set, return true 
		}
}

//operator to read into a magic square object
std::istream& operator>>(std::istream& inputs, MagicSquare& MS) {
	std::string holder = ""; //initializing to empty string

	for (int i = 0; i < MS.n; ++i) {
		std::vector<int> nxtRow; //the "next row" of input to be added to the vec<vec<int>>
		for (int j = 0; j < MS.n; ++j) {
			std::string holder = ""; //resetting the value of holder at each j
			std::cin >> holder;
			if (holder == "*") //if holder is an asterisk... add a 0 to the next row to be added...
			{
				nxtRow.push_back(0);
			}
			else
			{
				int nHolder = std::stoi(holder); //otherwise, convert to an int
				nxtRow.push_back(nHolder); //add that valye to the new row to be added

				//remove user-locked value from pot_vals, cannot be reused at another cell in the magic square
				MS.pot_vals.erase(nHolder);
			}

		}
		MS.magicVec.push_back(nxtRow); //add the next row of input to the magic vec vec<vec<int>>

	}

	MS.mMask = MS.magicVec; //set the mask for the magic vecto to initial 
	return inputs;
}

//operator<< to allow for printing out a magic vector
std::ostream& operator<<(std::ostream& outputs, const MagicSquare& MS) {
		
	for (int i = 0; i < MS.n; ++i) {
			for (int j = 0; j < MS.n; ++j) {
				std::cout << MS.magicVec[i][j] << " "; //print the value at that index
			}
			std::cout << "\n";
		}

return outputs; //return to main (or wherever else)

}

//getNumSols() to get the number of solutions there were
int MagicSquare::getNumSols() const {
	return numSols; //return that data field
}

	//checkRow so far, needs to be adapted, but tested in  
bool MagicSquare::checkRow(size_t rowNum) const {
	size_t rowSum = 0; //initializing to 0

	for (size_t x = 0; x < n; ++x) {
		rowSum += magicVec[rowNum][x]; //add the value at the index x place back from loc
	}

	if (rowSum == mSum) { //if row == the necessary magic sum, then return true...

		return true;
	}
	else if (rowSum != mSum) { //if row != the necessary magic sum

		return false; //otherwise return false
	}
	
}

//to check all the columns
bool MagicSquare::checkColumns() const {
	for (size_t c = 0; c < n; ++c) { //want to only traverse columns after adding each row
		int colSum = 0;

		for (size_t r = 0; r < n; ++r) { //want to traverse row locition in each column
			colSum += magicVec[r][c];
		}

		if (colSum >= mSum) { //if any column is too big, stop exploring that branch
			
			return false;
		}

	}
	
	return true; //if each columns passes test, return true
}

//to check columns when square is full
bool MagicSquare::endCheckColumns() const {
	for (size_t c = 0; c < n; ++c) { //want to traverse columns only after each row locition in each column has been accounted for
		int colSum = 0;

		for (size_t r = 0; r < n; ++r) { //add...
			colSum += magicVec[r][c];
		}

		if (colSum != mSum) { //if total for each column is not equal to magic sum, return false to end that lineage
			
			return false;
		}

	}

	return true; //if each columns passes test, return true
}

//to check rows when square is full
bool MagicSquare::endCheckRows() const {
	size_t rowSum = 0;

	for (size_t i= 0; i < n; ++i) { 
		if (!checkRow(i)) { return false; } //if checkRow fails on any row, fail
	}

	return true; //else return true
} 


bool MagicSquare::checkDiagonals() const {
	//Top left to bottom right
	int firstSum = 0;
	for (size_t i =0; i < n; ++i) {
		firstSum += magicVec[i][i];
	}
	//check if is bad:
	if (firstSum != mSum) {	//if first diagonal does not match magic sum 
		return false;
	}
	

	int secondSum = 0;
	size_t r = n - 1;
	size_t c = 0;

	//Top right to bottom left
	for (size_t i=0; i < n; ++i) {
		secondSum += magicVec[r-i][c+i];
	}
	if (secondSum != mSum) {
		//std::cout << "second diagonal does not match magic sum ";
		return false;
	}
	if (secondSum == mSum) {
		//std::cout << "second diagonal matches magic sum ";
		return true;
	}
	else {
		//std::cout << "other case";
		return false;
	}
	//Now, for TRtoBL?
	
}

//checkValid
bool MagicSquare::checkValid() const {
	
	if (!endCheckRows()) {//check each row
        return false;
    }
    if (!endCheckColumns()) {	//check each column
        return false;
    }
    if (!checkDiagonals()) { //check diagonal sums
        return false;
    }
    else {return true;} //any other case, assume true

}

//empty
bool MagicSquare::empty(size_t loc) const {
	if (mMask[loc/n][loc%n] == 0) { //if user DID NOT set a value there, represented as 0 in mask
		return true;
	}
	if (mMask[loc/n][loc%n] != 0) { //if user DID set a value there, represented as anything other than zero in mask
		return false;
	}
	else {
		return false; //any other case
	}
}

//solveSquare
void MagicSquare::SolveSquare(size_t loc) {
	//base case, check the whole square
	//in case it just finished the whole square

	if (loc == nXn && checkValid()) { //original base-case option
		++numSols; //increase solutions count

		//print out 2D
		std::cout << *this << "\n"; //print out the MagicSquare
	}
	else if (loc < nXn) {

		if (loc / n == 1 && loc % n == 0) { //check first row IMMEDIATELY after completing it
			if (!checkRow(0)) {
				return;
			}
		}
		else if ((loc % n == 0) && (loc / n < (n - 1)) && (loc / n != 0)) { //if at first column AND in a valid row AND not at first row

			//do other checks
			if (!checkRow((loc / n) - 1)) { //check previous row (hence the -1)
				return;
			}
			if (!checkColumns()) { //check each column
				return;
			}
		}


		if (empty(loc)) { //if there is not a preset value 

			std::set<int> cpy_pot = pot_vals; /*must make copy bc cannot modify pot_vals in the loop
			if we base for loop on it! (e.g. "for (auto i : pot_vals)" )*/

			for (auto i : cpy_pot) {

				magicVec[loc / n][loc % n] = i; //set the current cell of magic square to i
				pot_vals.erase(i); //i can no longer be a potential value for future cells!

				SolveSquare(loc + 1); //THE ALL-IMPORTANT IMPORTANT RECURSIVE CALL HERE!!!

				//this is for when backtracking and need to change the value at that cell

				pot_vals.insert(i); //that value i can once again be a potential value for future cells
				magicVec[loc / n][loc % n] = 0; //reset value there 

			}

		}

		else
		{
			SolveSquare(loc + 1);
		} //otherwise, the cell is preset with a value provided by user, i.e. !empty(), so move to next fill next cell

	}
	return; //otherwise, return to previous cell OR to all the way out of recursion
}



		