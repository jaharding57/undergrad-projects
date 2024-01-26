/*
PIC 10C Homework 3, compare.cpp
Author: Johnathan Harding
Date: 4/17/2022
*/

#include "compare.h"

//to generate the vector of chars storing a file (the matches matrix for a compareFiles object
std::vector<char> CompareFiles::textStore(const std::string& fileName) {

    std::vector<char> fileStore = {}; //initializing the vector to be empty
    std::string c = ""; //defining an empty, hidden character at the beginning of the vector of chars
    fileStore.push_back(c[0]); //adding

    std::ifstream file_data; //filestream object for pulling data from the textfile 
    file_data.open(fileName); //opening the file

    //file opening fail flag, activated if cannot open file
    if (file_data.fail())
    {
        std::cout << "Error opening the file \n"; //proper error message
    }

    //initializing variables
    char input;

    while (true) { //loop forever until break
        if (file_data.peek() == EOF) { //if the next char is EOF 
            break; //end loop

        }

        input = file_data.get(); //input is equal to the next char in the stream 
        fileStore.push_back(input); //add that char to the vector for the file

    }


    file_data.close(); //closing the filestream

    return fileStore; //returning char-vec storing all of a file's chars

}

//to generate the matches matrix for a compareFiles object
std::vector<std::vector<bool>> CompareFiles::genMatches(const std::vector<char>& text1, const std::vector<char>& text2) {

    size_t lim1 = text1.size(); //defining the bounds for the matrix 
    size_t lim2 = text2.size();

    std::vector<std::vector<bool>> matches = {}; //initializing 2D matrix as empty

    for (size_t rw = 0; rw < lim1; ++rw) { //nested for loops for 2D generation 
        matches.push_back(std::vector<bool>{}); //adding the next row

        for (size_t col = 0; col < lim2; ++col) { //adding the next cell in a row

            if (text1[rw] == text2[col]) { //if the two files match in that position
                matches[rw].push_back(1); //add a true 
            }
            else { //otherwise
                matches[rw].push_back(0); //add a false
            }
        }

    }

    return matches; //return matches matrix containing the positions of each shared char ("word")
}

//to generate the length of the longest common subseqence, as well as which positions the chars contained within are 
std::vector<std::vector<int>> CompareFiles::genCount(const std::vector<std::vector<bool>>& mMap) {

    size_t lim1 = mMap.size(); //setting the bounds for the number of rows
    size_t lim2 = mMap[0].size(); //setting the bounds for the number of columns

    std::vector<std::vector<int>> count(lim1, std::vector<int>(lim2, 0));

    //building the matrix before calculating count sizes
    for (size_t rw = 0; rw < lim1; ++rw) { //outer nested for loop to add the rows

        for (size_t col = 0; col < lim2; ++col) { //inner nested for loop to add the columns

            if (rw == 0 || col == 0)
            {
                count[rw][col] = 1; //adding the next cell in the row, adding a 1 for first row and column

            }
            else
            {
                count[rw][col] = 0; //adding the next matrix in the row, default set to zero

            }

        }
    }

    //counting
    for (size_t rw = 0; rw < lim1; ++rw) {

        for (size_t col = 0; col < lim2; ++col) {

            //checking if we in top row or column
            if (rw == 0 || col == 0)
            {
                continue; //do not alter the cell

            }
            else
            {
                //std::cout << "else\n";
                if (mMap[rw][col] == false)
                {
                    int maxOf = std::max(count[rw][col - 1], count[rw - 1][col]); //move either one row up or one column backwards
                    count[rw][col] = maxOf; //set the cell to the max of the cell above or to the left

                }
                else
                {
                    count[rw][col] = count[rw - 1][col - 1] + 1; //set the cell to the next largest plus one
                }
            }

        }

    }

    return count;
}

//to generate actual LSS
std::string CompareFiles::backTrack(const std::vector<char>& text2, const std::vector<std::vector<bool>>& matches, const std::vector<std::vector<int>>& count) {

    size_t rw = count.size() - 1; //defining coordinates of the last cell in the counts matrix 
    size_t col = count[0].size() - 1;


    std::string opStr = ""; //intializing output string
    std::string charHold = "";

    while (count[rw][col] != 1) { //while traversining the count matrix and not in first row || column (edge of matrix) 

        if (matches[rw][col] == true) //check if matches is true at a tile
        {
            charHold = text2[col]; //store the char to be prepended to the string 

            std::string tmp = charHold; //set tmp string to store the char to be prepended 
            tmp += opStr; //add opStr's current contents to 
            opStr = tmp; //reset opStr to include prepend 

            rw = rw - 1; //move one row backwards
            col = col - 1; //move one column up 

            continue; //move to next iteration

        }
        else if (count[rw][col - 1] > count[rw - 1][col]) //find neighboring tile with highest count
        {
            col = col - 1; //move one column backwards
            continue; //continue to the next iteration

        }
        else
        {

            rw = rw - 1; //move one row up
            continue; //continue to the next iteration
        }


    }

    return opStr; //return the full longest common sub-sequence
}

//to obtain the text overlap of two text files for printing
const std::string& CompareFiles::getOverlap() const {
    return overlap;
}

// to obtain the size of the overlap of two text files for printing.
size_t CompareFiles::getOverlapSz() const {
    return overlap.size();
}

//class constructor 
CompareFiles::CompareFiles(const fs::path& file1, const fs::path& file2) : text1(), text2(), overlap(""), matches(), count() {

    std::vector<std::vector<bool>> matches; //matches boolean matrix
    std::vector<std::vector<int>> count; //count boolean matrix

    std::string fileName1 = file1.string(); //getting file names as std::strings from fs::path::string()
    std::string fileName2 = file2.string(); //getting file names as std::strings from fs::path::string()


    std::vector<char> vec1 = textStore(fileName1); //storing the text within these as char-vecs
    std::vector<char> vec2 = textStore(fileName2);

    //generate matches matrix
    matches = genMatches(vec1, vec2);

    //generate count matrix
    count = genCount(matches);

    //calculating the overlap between the 2 files to be compared
    overlap = backTrack(vec2, matches, count);

}