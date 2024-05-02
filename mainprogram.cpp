/*This file actually runs a game of the Game of Life using the Game.h and Game.cpp files. It first start by asking
  the user to choose a map file or random assignment. After it asks for the mode the user wants to play in.
  After it asks if the user wants a brief pause between generations, press enter to continue, or output to an output file.
  Once picking all the options, the simulation will play in accordance the options the user selected.
*/
#include "Game.h"
#include <iostream>
using namespace std;

int main(){
  string mapFileOrRandom;
  string mode;
  string pauseEnterOrOutput;
  Game aGame;
  cout << "Would you like to provide a map file or just have random assignment? Type in 'map file' or 'random':" << endl;
  getline(cin, mapFileOrRandom);
  while(mapFileOrRandom != "map file" && mapFileOrRandom != "random"){
    cout << "Invalid choice. Enter 'map file' or 'random':" << endl;
    getline(cin, mapFileOrRandom);
  }
  cout << "Choose which mode you'd like to play in. Type in 'Classic' or 'Doughnut' or 'Mirror':" << endl;
  getline(cin, mode);
  while(mode != "Classic" && mode != "Doughnut" && mode != "Mirror"){
    cout << "Invalild choice. Enter 'Classic' or 'Doughnut' or 'Mirror':" << endl;
    getline(cin, mode);
  }
  cout << "Would you like a brief pause between generations, press the ENTER key in order to load the next generation, or output to a file?" << endl;
  cout << "Type in 'brief pause', 'enter', or 'output file': " << endl;
  getline(cin, pauseEnterOrOutput);
  while(pauseEnterOrOutput != "brief pause" && pauseEnterOrOutput != "enter" && pauseEnterOrOutput != "output file"){
    cout << "Invalid choice. Enter 'brief pause', 'enter', or 'output file':" << endl;
    getline(cin, pauseEnterOrOutput);
  }
  if(pauseEnterOrOutput == "brief pause"){
    aGame.SetBriefPauseTrue();
  }
  else if(pauseEnterOrOutput == "enter"){
    aGame.SetPressEnterTrue();
  }
  else if(pauseEnterOrOutput == "output file"){
    aGame.SetOutputFileTrue();
  }
  if(mapFileOrRandom == "map file"){
    aGame.MapFileGenerateBoard();
  }
  else{
    int height;
    int width;
    double initPopDensity;
    cout << "Please enter the dimensions you'd like for your world, starting with the height (whole number): " << endl;
    cin >> height;
    cout << "Now enter the width (whole number): " << endl;
    cin >> width;
    cout << "Enter a decimal value between 0 and 1 to set intial population density of your world: " << endl;
    cin >> initPopDensity;
    while(initPopDensity > 1.0 || initPopDensity < 0.0){
      cout << "Invalid value. Enter a decimal value between 0 and 1: " << endl;
      cin >> initPopDensity;
    }
    aGame.RandomlyGenerateInitialBoard(height, width, initPopDensity);
  }
  if(mode == "Classic"){
    aGame.GenerateClassic();
  }
  else if(mode == "Doughnut"){
    aGame.GenerateDoughnut();
  }
  else if(mode == "Mirror"){
    aGame.GenerateMirror();
  }
  aGame.DeallocateBoards();
  return 0;
}
