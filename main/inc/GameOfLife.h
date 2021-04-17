#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <vector>

class GameOfLife {
public:
  GameOfLife();
  GameOfLife(GameOfLife&) = delete;
  GameOfLife& operator=(GameOfLife&) = delete;

  //! Main function (runs the game)
  void Run();

private:
  //! Get window size, create board, and set initial values
  void Initialize();

  //! Write the board to a string and print it to the terminal
  void Draw();

  //! Unused. I wanted to use the backspace character to clear the drawing
  void Clear();

  //! Updates the board using the game rules
  void Update();

  //! Utility: counts a cell's live neighbors
  int CountLiveNeighbors(const int ind);

  //! Utility: checks rules and returns whether the cell should live or die
  bool CheckRules(bool alive, int numLiveNeighbors);

  //! Takes an index and converts it to a row, column tuple
  void IndtoRC(const int ind, std::vector<int>& rc);

  //! Takes a row, column tuple and returns an index
  int RCtoInd(std::vector<int> rc);

  //! Board width
  int m_wid;

  //! Board height
  int m_hei;

  //! Board stored as a 1-D vector of booleans (alive or dead)
  std::vector<bool> m_board;
};

#endif