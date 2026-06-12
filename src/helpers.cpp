#include "../include/helpers.h"
#include <iostream>
#include <iomanip>
#include <array>
#include <vector>
#include <fstream>
#include <format>
using namespace std;

array<array<char,10>,10> grid {{
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
}};
array<array<int,10>,10> gridCount{};
array<int,2> lastWordIndexes{};
bool wasHorizontal = false, wasVertical = false;
int wLen = 0;
vector<History> wordsHist{};

void placeFirstWord(string word,int row,int col,bool isHorizontal,bool isVertical){
    if(isHorizontal){
        for (size_t j = 0; j < word.length(); j++)
        {
           grid.at(row).at(col) = word.at(j);
           gridCount.at(row).at(col)+=1;
           col++;
        }
        
    }else if (isVertical)
    {
        for (size_t i = 0; i < word.length(); i++)
        {
           grid.at(row).at(col) = word.at(i);
           gridCount.at(row).at(col)+=1;
           row++;
        }
    }
    
}

void enterFirstWord(){
    string word;
    int row,col;
    int verOrHor;
    cout << "Enter fist word:";
    getline(cin,word);
    wLen = word.length();
    cout << endl;

    cout << "Enter position(0-9):";
    cin >> row >> col;
    if (row > 9 || row < 0 || col > 9 || col < 0)
    {
        cout << "Enter from 0 to 9\n";
        return;
    }
    lastWordIndexes.at(0) = row;
    lastWordIndexes.at(1) = col;
    
    cout << endl;

    cout << "Enter if you want vertical(1) or horizontal(2):";
    cin >> verOrHor;
    if (verOrHor == 1)
    {
        wasVertical = true;
        wasHorizontal = false;
    }else if (verOrHor == 2)
    {
        wasVertical = false;
        wasHorizontal = true;
    }else {
        cout << "Enter 1 or 2 !\n";
        return;
    }
    
    wordsHist.push_back({word,row,col,wasHorizontal,wasVertical});
    placeFirstWord(
        wordsHist.back().word,wordsHist.back().row,wordsHist.back().col,
        wordsHist.back().placeHor,wordsHist.back().placeVert);

}


bool checkSpaces(int found,int currentWLen,int i,int j){
    if (wordsHist.back().placeHor)
    {   
        int endRow = i + currentWLen - found;
        int startRow = i - found;
        if (endRow  < 10 &&  grid.at(endRow).at(j) != ' ')
           return false;
        if (startRow -1 >= 0 &&  grid.at(startRow-1).at(j) != ' ')
            return false;
        int row{startRow};
        while (row < endRow)
        {
           if (grid.at(row).at(j)!= ' ' && row != i)
            return false;
            row++;    
        }
        row = startRow;
        
        while (row < endRow)
        {
            if (j - 1 >= 0 && row != i && grid.at(row).at(j-1) != ' ')
                return false;
            if(j + 1 < 10 && row != i && grid.at(row).at(j+1) != ' ')
                return false;
            row++;
            
        }
        return true;
       
    }
    if (wordsHist.back().placeVert)
    {
        int endCol = j + currentWLen - found;
        int startCol = j - found;

        if (endCol  < 10 &&  grid.at(i).at(endCol) != ' ')
            return false;
        if ( startCol -1 >= 0 &&  grid.at(i).at(startCol - 1) != ' ')
           return false;
        
        int col{startCol};
        
        while (col < endCol)
        {
            if(grid.at(i).at(col) != ' ' && col != j ) 
            return false;
            col++;
        }
        
        col = startCol;
        while (col < endCol)
        {
            if (i - 1 >= 0 && col != j && grid.at(i-1).at(col) != ' ')
                return false;
            if(i + 1 < 10 && col != j && grid.at(i+1).at(col) != ' ')
                return false;
            col++;
            
        } 
        return true;   
    }
    
    return false;
}

bool repetedWords(string word){
    for (size_t i = 0; i < wordsHist.size(); i++)
        if (word == wordsHist.at(i).word)
           return true;
        
     
    return false;
    
}



bool isSafe(string word){
    if (repetedWords(word))
        return false;
    
    if (wordsHist.back().placeHor)
    {   bool safe{false};
        int i = lastWordIndexes.at(0);
        int currentWLen{word.length()}; 
        for (int j = lastWordIndexes.at(1); j < wLen + lastWordIndexes.at(1) && j < 10; j++)
        {  
            if (word.find(grid.at(i).at(j)) != string::npos )
            {   int found = word.find(grid.at(i).at(j));
                    
                if( (i - found ) >= 0 
                && (i + currentWLen - found ) <= 10
                ){ 
                   
                    if (checkSpaces(found,currentWLen,i,j))
                    {
                        lastWordIndexes.at(0) = i - found;
                        lastWordIndexes.at(1) = j;
                        safe = true;     
                    }
                            
                }
            }
                
        }
        return safe;
    }

     if (wordsHist.back().placeVert)
    {   
        int j = lastWordIndexes.at(1);
        bool safe{false};
        int currentWLen{word.length()}; 
        for (int i = lastWordIndexes.at(0); i < wLen + lastWordIndexes.at(0) && i < 10 ; i++)
        {   
            if (word.find(grid.at(i).at(j)) != string::npos )
            {   int found = word.find(grid.at(i).at(j));
                
                if( j - found  >= 0 
                && j + currentWLen - found <= 10 )
                {   
                    if (checkSpaces(found,currentWLen,i,j))
                    {   
                        lastWordIndexes.at(0) = i;
                        lastWordIndexes.at(1) = j - found;
                        safe = true; 
                    }    
                            
                }
            }
                
        }
        return safe;
    }
    
    return false;

}

void placeWord(string word){
    int letterIndexVer = lastWordIndexes.at(0);
    int letterIndexHor = lastWordIndexes.at(1);
    
    if (wordsHist.back().placeHor)
    {   
        for (size_t i = 0 ; i < word.length(); i++){
           grid.at(letterIndexVer).at(letterIndexHor) = word.at(i);
           gridCount.at(letterIndexVer).at(letterIndexHor) += 1;
           letterIndexVer++;
        }           
       
        wLen = word.length();
        wordsHist.push_back({
            word,lastWordIndexes.at(0),lastWordIndexes.at(1),false,true
        });
        return;
    }
    else if (wordsHist.back().placeVert)
    {   
        
        for (size_t j = 0; j < word.length(); j++){
            grid.at(letterIndexVer).at(letterIndexHor) = word.at(j);
            gridCount.at(letterIndexVer).at(letterIndexHor) += 1;
            letterIndexHor++;
        }
        
        wLen = word.length();
        wordsHist.push_back({
            word,lastWordIndexes.at(0),lastWordIndexes.at(1),true,false
        });

        return;   
        
    }
   
    
    
}
void removeWord(string word){

    int letterIndexVer = wordsHist.back().row;
    int letterIndexHor = wordsHist.back().col;

    
    if (wordsHist.back().placeVert)
    {
        for (size_t i = 0; i < word.length(); i++) {
            if (gridCount.at(letterIndexVer).at(letterIndexHor) == 1)
                grid.at(letterIndexVer).at(letterIndexHor) = ' ';

            gridCount.at(letterIndexVer).at(letterIndexHor)--;
            letterIndexVer++;
        }
    }
   
    else if (wordsHist.back().placeHor)
    {
        for (size_t j = 0; j < word.length(); j++) {
            if (gridCount.at(letterIndexVer).at(letterIndexHor) == 1)
                grid.at(letterIndexVer).at(letterIndexHor) = ' ';

            gridCount.at(letterIndexVer).at(letterIndexHor)--;
            letterIndexHor++;
        }
    }

    wordsHist.pop_back();

    lastWordIndexes.at(0) = wordsHist.back().row;
    lastWordIndexes.at(1) = wordsHist.back().col;
    wLen = wordsHist.back().word.length();
}



bool crossWord(){
    ifstream fin{"data/The Oxford 5000.txt"};
    string word;
//     if (!fin.is_open()) {
//     cout << "ERROR: file not found!\n";
//     return false;
// }
    while(fin >> word){
        
        if (isSafe(word))
        {   
            placeWord(word);
               
            if (crossWord())
            {
                return true;
            }
           removeWord(word);
            
        }
    }
    return true;     
}

void printCrossWord(){
     for(auto& gr : grid ){
            for(char& c : gr){
                cout << format("{:<2}",c);
            }
            cout << endl;
        }
}
