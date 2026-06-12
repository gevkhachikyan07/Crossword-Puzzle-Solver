#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <string>
#include <vector>
#include <array>
#include <fstream>

struct History
{
    std::string word;
    int row,col;
    bool placeHor;
    bool placeVert;
};

extern std::array<std::array<char,10>,10> grid;
extern std::array<std::array<int,10>,10> gridCount;
extern std::ifstream fin;
extern std::array<int,2> lastWordIndexes;
extern bool wasHorizontal, wasVertical;
extern int wLen;
extern std::vector<History> wordsHist;

void placeFirstWord(std::string word,int row,int col,bool isHorizontal,bool isVertical);
bool checkSpaces(int found,int currentWLen,int i,int j);
bool repetedWords(std::string word);
bool isSafe(std::string word);
void placeWord(std::string word);
void removeWord(std::string word);
bool crossWord();
void printCrossWord();
void enterFirstWord();




#endif
