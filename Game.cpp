/*This file is the actual implementation of all the methods, constructors, and destructors of the game class.
  Everything about how the game works is coded in this class.
*/
#include "Game.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <string>
using namespace std;

//default constructor
Game::Game(){
}

//destructor
Game::~Game(){
};

/*
Function name: RandomlyGenerateInitialBoard
What it does: Generates a random generation 0 board if user selects random
@param: int height, int width, double popDensity
@return: none
*/
void Game::RandomlyGenerateInitialBoard(int height, int width, double popDensity){
  rows = height;
  cols = width;
  srand (time(NULL));
  int counter = 0;
  int totalPossiblePopulation = rows * cols;
  int populationDensity = round(popDensity * totalPossiblePopulation);
  board = new char* [rows];
  for(int i=0;i<rows;i++){
    board[i] = new char[cols];
  }
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      int randNum = rand() % 3;
      if(counter < populationDensity){
        if(randNum == 0){
          board[i][j] = '-';
        }
        else{
          board[i][j] = 'X';
          counter++;
        }
      }
      else{
        board[i][j] = '-';
      }
    }
  }
  findNeighborsBoard = new int* [rows];
  for (int i = 0; i < rows; i++){
    findNeighborsBoard[i] = new int[cols];
  }
  gameState = true;
}

/*
Function name: MapFileGenerateBoard
What it does: Creates generation 0 board based on map file user gives
@param: none
@return: none
*/
void Game::MapFileGenerateBoard(){
  string filePath;
  ifstream mapFile;
  int lineNumber = 1;
  int i = 0;
  cout << "Type in file name for map file: " << endl;
  cin >> filePath;
  mapFile.open(filePath);
  if(!mapFile.is_open()){
    cout << "Could not open map file." << endl;
  }
  while (!mapFile.fail()){
    if(lineNumber == 1){
      mapFile >> rows;
      lineNumber++;
    }
    else if(lineNumber == 2){
      mapFile >> cols;
      lineNumber++;
    }
    else if(lineNumber == 3){
      string rowInput;
      mapFile >> rowInput;
      board = new char* [rows];
      for(int i=0;i<rows;i++){
        board[i] = new char[cols];
      }
      for(int j=0;j<rowInput.length();j++){
        board[i][j] = rowInput[j];
      }
      lineNumber++;
      i++;
    }
    else{
      string rowInput;
      mapFile >> rowInput;
      for(int j=0;j<rowInput.length();j++){
        board[i][j] = rowInput[j];
      }
      i++;
    }
  }
  mapFile.close();
  findNeighborsBoard = new int* [rows];
  for (int i = 0; i < rows; i++){
    findNeighborsBoard[i] = new int[cols];
  }
  gameState = true;
}

void Game::DeallocateBoards(){
  for(int i=0;i<rows;i++){
    delete[] board[i];
  }
  delete[] board;
  for(int i=0;i<rows;i++){
    delete[] nextBoard[i];
  }
  delete[] nextBoard;
  for(int i=0;i<rows;i++){
    delete[] findNeighborsBoard[i];
  }
  delete[] findNeighborsBoard;
}

/*
Function name: SetBriefPauseTrue
What it does: Sets briefPause private variable to true
@param: none
@return: none
*/
void Game::SetBriefPauseTrue(){
  briefPause = true;
}

/*
Function name: SetOutputFileTrue
What it does: Sets outputFile private variable to true
@param: none
@return: none
*/
void Game::SetOutputFileTrue(){
  outputFile = true;
}

/*
Function name: SetPressEnterTrue
What it does: Sets pressEnter private variable to true
@param: none
@return: none
*/
void Game::SetPressEnterTrue(){
  pressEnter = true;
}

/*
Function name: GenerateClassic
What it does: Simulates Game of Life using Classic mode settings
@param: none
@return: none
*/
void Game::GenerateClassic(){
  int generationCounter = 0;
  if(briefPause == true){
    while(gameState){
      if((isEmpty == true) || (isStabilized == true)){
        gameState = false;
        cout << "Simulation has ended." << endl;
      }
      else if(generationCounter == 0){
        cout << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            cout << board[i][j];
          }
          cout << endl;
        }
        generationCounter++;
        sleep(2);
      }
      else{
        nextBoard = new char* [rows];
        for(int i=0;i<rows;i++){
          nextBoard[i] = new char[cols];
        }
        FindNeighborsClassic();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            if(board[i][j] == '-' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
          }
        }
        sleep(2);
        cout << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            cout << nextBoard[i][j];
          }
          cout << endl;
        }
        CheckIfEmpty();
        CheckIfStablized();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            board[i][j] = nextBoard[i][j];
          }
        }
        generationCounter++;
      }
    }
  }
  else if(pressEnter == true){
    while(gameState){
      if((isEmpty == true) || (isStabilized == true)){
        gameState = false;
        cout << "Simulation has ended." << endl;
      }
      else if(generationCounter == 0){
        cout << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            cout << board[i][j];
          }
          cout << endl;
        }
        generationCounter++;
        cin.get();
      }
      else{
        nextBoard = new char* [rows];
        for(int i=0;i<rows;i++){
          nextBoard[i] = new char[cols];
        }
        FindNeighborsClassic();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            if(board[i][j] == '-' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
          }
        }
        cout << "Press ENTER key to continue..." << endl;
        cin.get();
        cout << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            cout << nextBoard[i][j];
          }
          cout << endl;
        }
        CheckIfEmpty();
        CheckIfStablized();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            board[i][j] = nextBoard[i][j];
          }
        }
        generationCounter++;
      }
    }
  }
  else if(outputFile == true){
    string outputFileName;
    cout << "Enter name of output file: " << endl;
    cin >> outputFileName;
    ofstream outputfile;
    outputfile.open(outputFileName, ios_base::app);
    while(gameState){
      if((isEmpty == true) || (isStabilized == true)){
        gameState = false;
        outputfile << "Simulation has ended." << endl;
      }
      else if(generationCounter == 0){
        outputfile << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            outputfile << board[i][j];
          }
          outputfile << endl;
        }
        generationCounter++;
      }
      else{
        nextBoard = new char* [rows];
        for(int i=0;i<rows;i++){
          nextBoard[i] = new char[cols];
        }
        FindNeighborsClassic();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            if(board[i][j] == '-' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
          }
        }
        outputfile << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            outputfile << nextBoard[i][j];
          }
          outputfile << endl;
        }
        CheckIfEmpty();
        CheckIfStablized();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            board[i][j] = nextBoard[i][j];
          }
        }
        generationCounter++;
      }
    }
    outputfile.close();
    cout << "Printed to output file " << outputFileName << endl;
  }
}

/*
Function name: GenerateMirror
What it does: Simulates Game of Life using Mirror mode settings
@param: none
@return: none
*/
void Game::GenerateMirror(){
  int generationCounter = 0;
  if(briefPause == true){
    while(gameState){
      if((isEmpty == true) || (isStabilized == true)){
        gameState = false;
        cout << "Simulation has ended." << endl;
      }
      else if(generationCounter == 0){
        cout << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            cout << board[i][j];
          }
          cout << endl;
        }
        generationCounter++;
        sleep(2);
      }
      else{
        nextBoard = new char* [rows];
        for(int i=0;i<rows;i++){
          nextBoard[i] = new char[cols];
        }
        FindNeighborsMirror();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            if(board[i][j] == '-' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
          }
        }
        sleep(2);
        cout << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            cout << nextBoard[i][j];
          }
          cout << endl;
        }
        CheckIfEmpty();
        CheckIfStablized();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            board[i][j] = nextBoard[i][j];
          }
        }
        generationCounter++;
      }
    }
  }
  else if(pressEnter == true){
    while(gameState){
      if((isEmpty == true) || (isStabilized == true)){
        gameState = false;
        cout << "Simulation has ended." << endl;
      }
      else if(generationCounter == 0){
        cout << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            cout << board[i][j];
          }
          cout << endl;
        }
        generationCounter++;
        cin.get();
      }
      else{
        nextBoard = new char* [rows];
        for(int i=0;i<rows;i++){
          nextBoard[i] = new char[cols];
        }
        FindNeighborsMirror();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            if(board[i][j] == '-' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
          }
        }
        cout << "Press ENTER key to continue..." << endl;
        cin.get();
        cout << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            cout << nextBoard[i][j];
          }
          cout << endl;
        }
        CheckIfEmpty();
        CheckIfStablized();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            board[i][j] = nextBoard[i][j];
          }
        }
        generationCounter++;
      }
    }
  }
  else if(outputFile == true){
    string outputFileName;
    cout << "Enter name of output file: " << endl;
    cin >> outputFileName;
    ofstream outputfile;
    outputfile.open(outputFileName, ios_base::app);
    while(gameState){
      if((isEmpty == true) || (isStabilized == true)){
        gameState = false;
        outputfile << "Simulation has ended." << endl;
      }
      else if(generationCounter == 0){
        outputfile << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            outputfile << board[i][j];
          }
          outputfile << endl;
        }
        generationCounter++;
      }
      else{
        nextBoard = new char* [rows];
        for(int i=0;i<rows;i++){
          nextBoard[i] = new char[cols];
        }
        FindNeighborsMirror();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            if(board[i][j] == '-' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
          }
        }
        outputfile << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            outputfile << nextBoard[i][j];
          }
          outputfile << endl;
        }
        CheckIfEmpty();
        CheckIfStablized();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            board[i][j] = nextBoard[i][j];
          }
        }
        generationCounter++;
      }
    }
    outputfile.close();
    cout << "Printed to output file " << outputFileName << endl;
  }
}

/*
Function name: GenerateDoughnut
What it does: Simulates Game of Life using Doughnut mode settings
@param: none
@return: none
*/
void Game::GenerateDoughnut(){
  int generationCounter = 0;
  if(briefPause == true){
    while(gameState){
      if((isEmpty == true) || (isStabilized == true)){
        gameState = false;
        cout << "Simulation has ended." << endl;
      }
      else if(generationCounter == 0){
        cout << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            cout << board[i][j];
          }
          cout << endl;
        }
        generationCounter++;
        sleep(2);
      }
      else{
        nextBoard = new char* [rows];
        for(int i=0;i<rows;i++){
          nextBoard[i] = new char[cols];
        }
        FindNeighborsDoughnut();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            if(board[i][j] == '-' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
          }
        }
        sleep(2);
        cout << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            cout << nextBoard[i][j];
          }
          cout << endl;
        }
        CheckIfEmpty();
        CheckIfStablized();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            board[i][j] = nextBoard[i][j];
          }
        }
        generationCounter++;
      }
    }
  }
  else if(pressEnter == true){
    while(gameState){
      if((isEmpty == true) || (isStabilized == true)){
        gameState = false;
        cout << "Simulation has ended." << endl;
      }
      else if(generationCounter == 0){
        cout << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            cout << board[i][j];
          }
          cout << endl;
        }
        generationCounter++;
        cin.get();
      }
      else{
        nextBoard = new char* [rows];
        for(int i=0;i<rows;i++){
          nextBoard[i] = new char[cols];
        }
        FindNeighborsDoughnut();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            if(board[i][j] == '-' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
          }
        }
        cout << "Press ENTER key to continue..." << endl;
        cin.get();
        cout << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            cout << nextBoard[i][j];
          }
          cout << endl;
        }
        CheckIfEmpty();
        CheckIfStablized();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            board[i][j] = nextBoard[i][j];
          }
        }
        generationCounter++;
      }
    }
  }
  else if(outputFile == true){
    string outputFileName;
    cout << "Enter name of output file: " << endl;
    cin >> outputFileName;
    ofstream outputfile;
    outputfile.open(outputFileName, ios_base::app);
    while(gameState){
      if((isEmpty == true) || (isStabilized == true)){
        gameState = false;
        outputfile << "Simulation has ended." << endl;
      }
      else if(generationCounter == 0){
        outputfile << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            outputfile << board[i][j];
          }
          outputfile << endl;
        }
        generationCounter++;
      }
      else{
        nextBoard = new char* [rows];
        for(int i=0;i<rows;i++){
          nextBoard[i] = new char[cols];
        }
        FindNeighborsDoughnut();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            if(board[i][j] == '-' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] <= 1){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 2){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] == 3){
              nextBoard[i][j] = 'X';
            }
            else if(board[i][j] == '-' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
            else if(board[i][j] == 'X' && findNeighborsBoard[i][j] >= 4){
              nextBoard[i][j] = '-';
            }
          }
        }
        outputfile << "Generation " << generationCounter << endl;
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            outputfile << nextBoard[i][j];
          }
          outputfile << endl;
        }
        CheckIfEmpty();
        CheckIfStablized();
        for(int i=0;i<rows;i++){
          for(int j=0;j<cols;j++){
            board[i][j] = nextBoard[i][j];
          }
        }
        generationCounter++;
      }
    }
    outputfile.close();
    cout << "Printed to output file " << outputFileName << endl;
  }
}

/*
Function name: FindNeighborsClassic
What it does: Finds neighbors under the Classic mode rules
@param: none
@return: none
*/
void Game::FindNeighborsClassic(){
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      int numNeighbors = 0;

      //Northwest Corner
      if((i == 0) && (j == 0)){
        if(board[0][1] != '-'){
          numNeighbors++;
        }
        if(board[1][1] != '-'){
          numNeighbors++;
        }
        if(board[1][0] != '-'){
          numNeighbors++;
        }
      }

      //Northeast Corner
      else if((i == 0) && (j == (cols - 1))){
        if(board[0][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[1][cols-2] != '-'){
          numNeighbors++;
        }
        if(board[1][cols - 1] != '-'){
          numNeighbors++;
        }
      }

      //Southwest Corner
      else if((i == (rows - 1)) && (j == 0)){
        if(board[rows - 2][0] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][1] != '-'){
          numNeighbors++;
        }
        if(board[rows-1][1] != '-'){
          numNeighbors++;
        }
      }

      //Southeast Corner
      else if((i == (rows - 1)) && (j == (cols - 1))){
        if(board[rows - 2][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][cols - 2] != '-'){
          numNeighbors++;
        }
      }

      //North edge
      else if(i == 0){
        if(board[0][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[0][j + 1] != '-'){
          numNeighbors++;
        }
        if(board[1][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[1][j] != '-'){
          numNeighbors++;
        }
        if(board[1][j + 1] != '-'){
          numNeighbors++;
        }
      }

      //West edge
      else if(j == 0){
        if(board[i - 1][0] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][0] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][1] != '-'){
          numNeighbors++;
        }
        if(board[i][1] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][1] != '-'){
          numNeighbors++;
        }
      }

      //South edge
      else if(i == (rows - 1)){
        if(board[rows - 1][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][j + 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][j] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][j + 1] != '-'){
          numNeighbors++;
        }
      }

      //East edge
      else if(j == (cols - 1)){
        if(board[i - 1][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[i][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][cols - 2] != '-'){
          numNeighbors++;
        }
      }

      //Middle
      else{
        if(board[i - 1][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][j] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][j + 1] != '-'){
          numNeighbors++;
        }
        if(board[i][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[i][j + 1] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][j] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][j + 1] != '-'){
          numNeighbors++;
        }
      }
      findNeighborsBoard[i][j] = numNeighbors;
    }
  }
}

/*
Function name: FindNeighborsDoughnut
What it does: Finds neighbors using Doughnut mode rules
@param: none
@return: none
*/
void Game::FindNeighborsDoughnut(){
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      int numNeighbors = 0;

      //Northwest
      if((i == 0) && (j == 0)){
        if(board[0][1] != '-'){
          numNeighbors++;
        }
        if(board[1][1] != '-'){
          numNeighbors++;
        }
        if(board[1][0] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][0] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][1] != '-'){
          numNeighbors++;
        }
        if(board[0][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[1][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][cols - 1]){
          numNeighbors++;
        }
      }

      //Northeast
      else if((i == 0) && (j == (cols - 1))){
        if(board[0][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[1][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[1][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[0][0] != '-'){
          numNeighbors++;
        }
        if(board[1][0] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][0] != '-'){
          numNeighbors++;
        }
      }

      //Southwest
      else if((i == (rows - 1)) && (j == 0)){
        if(board[rows - 2][0] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][1] != '-'){
          numNeighbors++;
        }
        if(board[0][0] != '-'){
          numNeighbors++;
        }
        if(board[0][1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[0][cols - 1] != '-'){
          numNeighbors++;
        }
      }

      //Southeast
      else if((i == (rows - 1)) && (j == (cols - 1))){
        if(board[rows - 2][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][0] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][0] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[0][0] != '-'){
          numNeighbors++;
        }
      }

      //North edge
      else if(i == 0){
        if(board[0][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[0][j + 1] != '-'){
          numNeighbors++;
        }
        if(board[1][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[1][j] != '-'){
          numNeighbors++;
        }
        if(board[1][j + 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][j] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][j + 1] != '-'){
          numNeighbors++;
        }
      }

      //West edge
      else if(j == 0){
        if(board[i - 1][0] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][0] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][1] != '-'){
          numNeighbors++;
        }
        if(board[i][1] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][1] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[i][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][cols - 1] != '-'){
          numNeighbors++;
        }
      }

      //South edge
      else if(i == (rows - 1)){
        if(board[rows - 1][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][j + 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][j] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][j + 1] != '-'){
          numNeighbors++;
        }
        if(board[0][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[0][j] != '-'){
          numNeighbors++;
        }
        if(board[0][j + 1] != '-'){
          numNeighbors++;
        }
      }

      //East edge
      else if(j == (cols - 1)){
        if(board[i - 1][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][cols - 1] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[i][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][0] != '-'){
          numNeighbors++;
        }
        if(board[i][0] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][0] != '-'){
          numNeighbors++;
        }
      }

      //Middle
      else{
        if(board[i - 1][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][j] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][j + 1] != '-'){
          numNeighbors++;
        }
        if(board[i][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[i][j + 1] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][j] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][j + 1] != '-'){
          numNeighbors++;
        }
      }
      findNeighborsBoard[i][j] = numNeighbors;
    }
  }
}

/*
Function name: FindNeighborsMirror
What it does: Finds neighbors using Mirror mode rules
@param: none
@return: none
*/
void Game::FindNeighborsMirror(){
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      int numNeighbors = 0;

      //Northwest
      if((i == 0) && (j == 0)){
        if(board[0][0] != '-'){
          numNeighbors += 3;
        }
        if(board[0][1] != '-'){
          numNeighbors += 2;
        }
        if(board[1][1] != '-'){
          numNeighbors++;
        }
        if(board[1][0] != '-'){
          numNeighbors += 2;
        }
      }

      //Northeast
      else if((i == 0) && (j == (cols - 1))){
        if(board[0][cols - 1] != '-'){
          numNeighbors += 3;
        }
        if(board[0][cols - 2] != '-'){
          numNeighbors += 2;
        }
        if(board[1][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[1][cols - 1] != '-'){
          numNeighbors += 2;
        }
      }

      //Southwest
      else if((i == (rows - 1)) && (j == 0)){
        if(board[rows - 1][0] != '-'){
          numNeighbors += 3;
        }
        if(board[rows - 2][0] != '-'){
          numNeighbors += 2;
        }
        if(board[rows - 2][1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][1] != '-'){
          numNeighbors += 2;
        }
      }

      //Southeast
      else if((i == (rows - 1)) && (j == (cols - 1))){
        if(board[rows - 1][cols - 2] != '-'){
          numNeighbors += 3;
        }
        if(board[rows - 2][cols - 1] != '-'){
          numNeighbors += 2;
        }
        if(board[rows - 2][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][cols - 2] != '-'){
          numNeighbors += 2;
        }
      }

      //North edge
      else if(i == 0){
        if(board[i][j] != '-'){
          numNeighbors++;
        }
        if(board[0][j - 1] != '-'){
          numNeighbors += 2;
        }
        if(board[0][j + 1] != '-'){
          numNeighbors += 2;
        }
        if(board[1][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[1][j] != '-'){
          numNeighbors++;
        }
        if(board[1][j + 1] != '-'){
          numNeighbors++;
        }
      }

      //West edge
      else if(j == 0){
        if(board[i][j] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][0] != '-'){
          numNeighbors += 2;
        }
        if(board[i + 1][0] != '-'){
          numNeighbors += 2;
        }
        if(board[i - 1][1] != '-'){
          numNeighbors++;
        }
        if(board[i][1] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][1] != '-'){
          numNeighbors++;
        }
      }

      //South edge
      else if(i == (rows - 1)){
        if(board[i][j] != '-'){
          numNeighbors++;
        }
        if(board[rows - 1][j - 1] != '-'){
          numNeighbors += 2;
        }
        if(board[rows - 1][j + 1] != '-'){
          numNeighbors += 2;
        }
        if(board[rows - 2][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][j] != '-'){
          numNeighbors++;
        }
        if(board[rows - 2][j + 1] != '-'){
          numNeighbors++;
        }
      }

      //East edge
      else if(j == (cols - 1)){
        if(board[i][j] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][cols - 1] != '-'){
          numNeighbors += 2;
        }
        if(board[i + 1][cols - 1] != '-'){
          numNeighbors += 2;
        }
        if(board[i - 1][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[i][cols - 2] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][cols - 2] != '-'){
          numNeighbors++;
        }
      }

      //Middle
      else{
        if(board[i - 1][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][j] != '-'){
          numNeighbors++;
        }
        if(board[i - 1][j + 1] != '-'){
          numNeighbors++;
        }
        if(board[i][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[i][j + 1] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][j - 1] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][j] != '-'){
          numNeighbors++;
        }
        if(board[i + 1][j + 1] != '-'){
          numNeighbors++;
        }
      }
      findNeighborsBoard[i][j] = numNeighbors;
    }
  }
}

/*
Function name: CheckIfEmpty
What it does: Checks if nextBoard is empty and changes isEmpty to true if so, so simulation can end
@param: none
@return: none
*/
void Game::CheckIfEmpty(){
  int xCounter = 0;
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      if(nextBoard[i][j] == 'X'){
        xCounter++;
      }
    }
  }
  if(xCounter == 0){
    isEmpty = true;
  }
}

/*
Function name:  CheckIfStablized
What it does: Checks if nextBoard is equal to board and sets isStabilized to true if it is, so simulation can end
@param: none
@return: none
*/
void Game::CheckIfStablized(){
  int equalCounter = 0;
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      if(nextBoard[i][j] == board[i][j]){
        equalCounter++;
      }
    }
  }
  int totalPossiblePopulation = rows * cols;
  if(equalCounter == totalPossiblePopulation){
    isStabilized = true;
  }
}
