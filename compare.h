/*
PIC 10C Homework 3, compare.h
Author: Johnathan Harding
Date: 4/17/2022
*/

#ifndef _COMPARE_H_ //header guards to prevent linker errors at compile time
#define _COMPARE_H_

#include <iostream> //inclusion of necessary header files
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem; //aliasing to allow more concise programming 

/**
@class CompareFiles This class defines an object constructed from two fs::path objects
 */
class CompareFiles {

private:

    std::vector<char> text1; //texts files to be compared
    std::vector<char> text2;

    std::string overlap; //std::string holding the overlap of the two files

    std::vector<std::vector<bool>> matches; //matches boolean matrix

    std::vector<std::vector<int>> count; //count boolean matrix

    //support functions for generation:

    /**
    textStore() enters a text file's contents into a vector of chars
    @param fileName The name/path of a text file, which is then read from.
    @return Returns a vector of chars with a size() the same as the number of chars in a text file
     */
    std::vector<char> textStore(const std::string& fileName); //to store text files in a vector of chars

    /**
    genMatches() accepts two vectors of chars, storing the chars of two texts, and compares them char by char.
    @param text1 The first char vector to be compared.
    @param text2 The second char vector to be compared.
    @return A 2D matrix of bools representing all the matching chars between two text files.
    */
    std::vector<std::vector<bool>> genMatches(const std::vector<char>& text1, const std::vector<char>& text2);

    /**
    genCount() accepts a 2D matrix of bools representing all the matching chars between two text files to generate a count matrix.
    @param mMap The matches matrix to be generated from.
    @return Returns a vector of ints counting the longest common sub-sequence of chars.
     */
    std::vector<std::vector<int>> genCount(const std::vector<std::vector<bool>>& mMap);

    /**
    backtrack()
    @param text2 The second of the two text files. (Only one is needed as the relavent chars for constructing the LCSS are the same anyway).
    @param matches The matches matrix for two text files that were compared.
    @param count The count matrix for two text files that were compared.
    @returns a string containing the longest common sub-sequence
     */
    std::string backTrack(const std::vector<char>& text2, const std::vector<std::vector<bool>>& matches, const std::vector<std::vector<int>>& count); //to generate actual LSS

public:

    /**
    getOverlap() to obtain the overlap of two text files for printing.
    @return a std::string holding the overlap.
    */
    const std::string& getOverlap() const;

    /**
    getOverlap() to obtain the size of the overlap of two text files for printing.
    @return an int equal to the size of the std::string holding the overlap of two text files.
    */
    size_t getOverlapSz() const;

    /**
    constructor. creates a new comparison object for two text files.
    @param file1 The first text file of the pair comparison.
    @param file2 The second text file of the pair comparison.
    @returns a newly created pair comparison object.
     */
    CompareFiles(const fs::path& file1, const fs::path& file2);

};

#endif //_COMPARE_H_