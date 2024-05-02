/*This file creates the Game class for the Game of Life. It declares all the needed constructors, destructors,
 methods, and private variables that are needed to run the game. Creating a Game object essentially starts
 a new game of the Game of Life.
*/
#include <iostream>
using namespace std;

class Game{
public:
  Game();
  ~Game();
  void RandomlyGenerateInitialBoard(int h, int w, double p);
  void MapFileGenerateBoard();
  void DeallocateBoards();
  void SetBriefPauseTrue();
  void SetPressEnterTrue();
  void SetOutputFileTrue();
  bool GetBriefPause();
  bool GetPressEnter();
  bool GetOutputFile();
  void GenerateClassic();
  void GenerateMirror();
  void GenerateDoughnut();
  void FindNeighborsClassic();
  void FindNeighborsDoughnut();
  void FindNeighborsMirror();
  char ** GetBoard();
  int GetRows();
  int GetCols();
  void CheckIfEmpty();
  void CheckIfStablized();
private:
  char ** board;
  char ** nextBoard;
  int ** findNeighborsBoard;
  int cols;
  int rows;
  bool briefPause = false;
  bool pressEnter = false;
  bool outputFile = false;
  bool gameState = false;
  bool isEmpty = false;
  bool isStabilized = false;
};
