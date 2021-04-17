#include "GameOfLife.h"
#include "utilities.h"
#include <iostream>
#include <string>

GameOfLife::GameOfLife() : m_hei(0), m_wid(0) {}

void GameOfLife::Initialize() {
  Utils::GetWindowSize(m_wid, m_hei);
  m_board.resize(m_wid * m_hei);
  for(int i = 0; i < m_wid * m_hei; ++i) {
    m_board[i] = false;
  }

  // Manually create the simkin glider
  m_board[RCtoInd({1, 1})] = true;
  m_board[RCtoInd({1, 2})] = true;
  m_board[RCtoInd({2, 1})] = true;
  m_board[RCtoInd({2, 2})] = true;

  m_board[RCtoInd({1, 8})] = true;
  m_board[RCtoInd({1, 9})] = true;
  m_board[RCtoInd({2, 8})] = true;
  m_board[RCtoInd({2, 9})] = true;

  m_board[RCtoInd({4, 5})] = true;
  m_board[RCtoInd({4, 6})] = true;
  m_board[RCtoInd({5, 5})] = true;
  m_board[RCtoInd({5, 6})] = true;

  m_board[RCtoInd({10, 23})] = true;
  m_board[RCtoInd({10, 24})] = true;
  m_board[RCtoInd({10, 26})] = true;
  m_board[RCtoInd({10, 27})] = true;
  m_board[RCtoInd({11, 22})] = true;
  m_board[RCtoInd({11, 28})] = true;
  m_board[RCtoInd({12, 22})] = true;
  m_board[RCtoInd({12, 29})] = true;
  m_board[RCtoInd({13, 22})] = true;
  m_board[RCtoInd({13, 23})] = true;
  m_board[RCtoInd({13, 24})] = true;
  m_board[RCtoInd({13, 28})] = true;
  m_board[RCtoInd({14, 27})] = true;

  m_board[RCtoInd({12, 32})] = true;
  m_board[RCtoInd({12, 33})] = true;
  m_board[RCtoInd({13, 32})] = true;
  m_board[RCtoInd({13, 33})] = true;

  m_board[RCtoInd({18, 21})] = true;
  m_board[RCtoInd({18, 22})] = true;
  m_board[RCtoInd({19, 21})] = true;
  m_board[RCtoInd({20, 22})] = true;
  m_board[RCtoInd({20, 23})] = true;
  m_board[RCtoInd({20, 24})] = true;
  m_board[RCtoInd({21, 24})] = true;

  if(m_board.size() > m_wid * m_hei) {
    std::cout << "Something went wrong initializing the size" << std::endl;
  }
  for(int i = 0; i < m_hei; ++i) {
    std::cout << std::endl;
  }
}

void GameOfLife::Draw() {
  std::string str(m_board.size(), ' ');
  for(int i = 0; i < str.size(); ++i) {
    if(m_board[i]) {
      str[i] = 'X';
    }
  }
  std::cout << str;
}

void GameOfLife::Clear() {
  std::string str(m_board.size(), '\b');
  std::cout << str;
}

void GameOfLife::Update() {
  std::vector<bool> newBoard(m_wid*m_hei, false);
  for(int i = 0; i < m_hei*m_wid; ++i) {
    int numLiveNeighbors = CountLiveNeighbors(i);
    newBoard[i] = CheckRules(m_board[i], numLiveNeighbors);
  }
  m_board = newBoard;
}

int GameOfLife::CountLiveNeighbors(const int ind) {
  std::vector<int> rc;
  rc.resize(2);
  IndtoRC(ind, rc);

  int numLiveNeighbors = 0;
  numLiveNeighbors += m_board[RCtoInd({rc[0]-1, rc[1]  })]; // U
  numLiveNeighbors += m_board[RCtoInd({rc[0]-1, rc[1]+1})]; // UR
  numLiveNeighbors += m_board[RCtoInd({rc[0]  , rc[1]+1})]; // R
  numLiveNeighbors += m_board[RCtoInd({rc[0]+1, rc[1]+1})]; // DR
  numLiveNeighbors += m_board[RCtoInd({rc[0]+1, rc[1]  })]; // D
  numLiveNeighbors += m_board[RCtoInd({rc[0]+1, rc[1]-1})]; // DL
  numLiveNeighbors += m_board[RCtoInd({rc[0]  , rc[1]-1})]; // L
  numLiveNeighbors += m_board[RCtoInd({rc[0]-1, rc[1]-1})]; // UL

  return numLiveNeighbors;
}

bool GameOfLife::CheckRules(bool alive, int numLiveNeighbors) {
  if(alive) {
    if (numLiveNeighbors < 2 || numLiveNeighbors > 3) return false;
    return true;
  } else {
    if (numLiveNeighbors == 3) return true;
    return false;
  }

  return false;
}

void GameOfLife::IndtoRC(const int ind, std::vector<int>& rc) {
  rc[0] = ind / m_wid;
  rc[1] = ind % m_wid;
}

int GameOfLife::RCtoInd(std::vector<int> rc) {
  int r = rc[0];
  int c = rc[1];
  if (r < 0) r = m_hei - 1;
  if (r >= m_hei) r = 0;
  if (c < 0) c = m_wid - 1;
  if (c >= m_wid) c = 0;

  int ind = r*m_wid + c;
  return ind;
}


void GameOfLife::Run() {
  Initialize();
  Draw();
  while(true) {
    Update();
    Draw();
    Utils::sleep(10);
  };
}