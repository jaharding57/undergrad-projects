/*
PIC 10B Homework 6, MagicSquare.h
Author: Johnathan Harding
Date: 2/19/2022
*/

#ifndef _MAGICSQUARE_H_
#define _MAGICSQUARE_H_

#include <iostream> //include necessary header files
#include <string>
#include <vector>
#include <set>

/**
@class MagicSquare class that holds a 2D vector representing a magic square of 
n by n dimensions, determined by user. Has support functions that aim to generate 
solutions of the magic square, including those with user determined values at certain cells. A solution is
generated when a square is recursively filled up cell-by-cell and each row, column, and diagonal each sum to
the "magic sum."
*/
class MagicSquare {

	/**
	Reads from a square of asterisks and numbers at user-specified locitions into
	a MagicSquare. friend to allow for modifying private members.
	@param inputs The istream object reading from.
	@param m The MagicSquare object read into.
	@return Returns the modified istream of what is returned (if a return)
	*/
	friend std::istream& operator>>(std::istream& inputs, MagicSquare& m);

	/**
	Reads from a square of asterisks and numbers at user-specified locitions into
	a MagicSquare. friend to allow for accessing private members.
	@param outputs The ostream object reading from a MagicSquare object.
	@param MS The MagicSquare object reads from.
	@return Returns the modified ostream of what is returned (if a return)
	*/
	friend std::ostream& operator<<(std::ostream& outputs, const MagicSquare& MS);

private:
	//member variables
	
	// n, the user's input for dimensions
	int n;

	//the 2D (thus square) "magic vector" that is recursively filled up
	std::vector<std::vector<int>> magicVec;
	
	//the mask used to check if a given locition has a set locition
	std::vector<std::vector<int>> mMask;

	//the square of the user's value of n
	int nXn;

	//mSum (sum that every row, columns, and both diagonals must equate to
	int mSum;

	//numSols (the number of solutions for a given MagicSquare)
	int numSols;

	//pot_vals, the set storing values a cell could potentially be set to
	std::set<int> pot_vals;

	//used_vals, the set storing the values already not used in the set, used in taken()
	std::set<int> used_vals;

public:
	/**
	The constructor that makes magicVec a vector of vectors, both of size n, in addition to initialing all member variables properly.
	@param dim The dimensions of the magic square.
	*/
	MagicSquare(int dim);

	/**
	Accessor for the number of solutions for a square, for used in main
	@return numSols for an implicitly passed MagicSquare object.
	*/
	int getNumSols() const;

	/* DIAGNOSTIC FUNCTIONS FOR TESTING A POTENTIAL SOLUTION IN PROGRESS*/

		/**
		Takes an implicitly passed MagicSquare object and return if 
		a given row is equal to magic sum.
		@param loc the locition of the cell within the magic square at the end of the row to be checked.
		@return Returns true or false based on sum of row
		*/
		bool checkRow(size_t rowNum) const;

		/**
		Takes an implicitly passed MagicSquare object and return if each column of the 
		generated locsible solution adds up to the magic sum.
		@return Returns true or false based on sum of columns.
		*/
		bool checkColumns() const;

		/**
		Takes an implicitly passed MagicSquare object and return if each column of the
		generated locsible solution adds up to the magic sum.
		@return Returns true or false based on sum of columns.
		*/
		bool endCheckColumns() const;

		/**
		Takes an implicitly passed MagicSquare object and returns whether or not
		all rows each add up to the MagicSum, when an entire square is full.
		@return Returns true or false based on sum of each row
		*/
		bool endCheckRows() const;

		/**
		Takes an implicitly passed MagicSquare object and return if both 
		diagonals sum to the magic sum for the magic square. 
		@return Returns true or false based on the respective sums of both diagonals, true if both are == magic sum, false if either is not.
		*/
		bool checkDiagonals() const;

		/**
		Determines if a given locition in the "mask" (a unaltered copy of the original user input) used for the 
		Magic Square is empty (i.e., the user did not lock a value there)		
		@param loc A particular cell in the magic square to be checked for "emptiness."
		@return Returns true or false based on the mask's record of that cell's 
		emptiness.
		*/
		bool empty(size_t loc) const;

		/**
		Determines if a locsible value for a cell has already been used in magic square.
		@param val The candidate value to see if used.
		@return True or false if value is used/unused.
		*/ 
		bool taken(int val) const;

		/**
		Takes an implicitly passed MagicVec and evaluate its 
		magic vector to check if all rows, all columns, 
		and each diagonal adds up to the magic sum.		
		@return True if the potential solution is a real solution, false if not.
		*/
		bool checkValid() const;

	/**
	Recursive function SolveSquare. Uses support functions and recursion to
	fill up an 2D vector of ints with n^2 cells and checks if it is a solution (if the square fills up).
	Solutions of the magic square (if there are any). Takes a MagicSquare object as 
	implicit argument and generates tries solutions.
	@param loc Index tracking the number of cells already filled in a potential
	solution for the MagicSquare.
	*/	
	void SolveSquare(size_t loc);

};

#endif // _MAGICSQUARE_H_