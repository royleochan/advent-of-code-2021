#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Helper Functions //
std::vector<int> split_string_to_int(std::string str, char delim)
{
  std::stringstream stream(str);
  std::string temp_str;
  std::vector<int> result;

  while (std::getline(stream, temp_str, delim))
  {
    result.push_back(stoi(temp_str));
  }

  return result;
}

std::vector<int> parseBoard(std::string str)
{
  std::vector<int> result;
  std::string num = "";
  for (auto x : str)
  {
    if (x == ' ')
    {
      if (!num.empty())
      {
        result.push_back(stoi(num));
        num = "";
      }
    }
    else
    {
      num += x;
    }
  }

  if (!num.empty())
  {
    result.push_back(stoi(num));
  }

  return result;
}

std::vector<std::vector<int>> markBoard(std::vector<std::vector<int>> &board, int num)
{
  int n = board.size();
  int m = board[0].size();
  std::vector<std::vector<int>> positionsMarked;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (board[i][j] == num)
      {
        positionsMarked.push_back({i, j});
        board[i][j] = -1;
      }
    }
  }

  return positionsMarked;
}

bool hasBoardWon(std::vector<std::vector<int>> board, std::vector<std::vector<int>> newlyMarkedPositions)
{
  int n = board.size();
  int m = board[0].size();

  for (std::vector<int> position : newlyMarkedPositions)
  {
    int row = position[0];
    int col = position[1];
    bool rowWon = true;
    bool colWon = true;

    for (int i = 0; i < m; i++)
    {
      if (board[row][i] != -1)
      {
        colWon = false;
        break;
      }
    }

    for (int i = 0; i < n; i++)
    {
      if (board[i][col] != -1)
      {
        rowWon = false;
        break;
      }
    }

    return rowWon || colWon;
  }

  return false;
}

int calculateWinningScore(std::vector<std::vector<int>> board, int winningDraw)
{
  int n = board.size();
  int m = board[0].size();
  int unmarkedSum = 0;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (board[i][j] != -1)
      {
        unmarkedSum += board[i][j];
      }
    }
  }

  return unmarkedSum * winningDraw;
}

// Solutions //
int solution1(std::vector<int> numberDraws, std::vector<std::vector<std::vector<int>>> boards)
{
  int winningDraw;
  std::vector<std::vector<int>> winningBoard = {};

  for (int draw : numberDraws)
  {
    if (!winningBoard.empty())
    {
      break;
    }
    for (auto &board : boards)
    {
      std::vector<std::vector<int>> markedPositions = markBoard(board, draw);
      if (hasBoardWon(board, markedPositions))
      {
        winningDraw = draw;
        winningBoard = board;
        break;
      }
    }
  }

  return calculateWinningScore(winningBoard, winningDraw);
}

int solution2(std::vector<int> numberDraws, std::vector<std::vector<std::vector<int>>> boards)
{
  int winningDraw;
  std::vector<std::vector<int>> lastWinningBoard = {};

  for (int draw : numberDraws)
  {
    for (auto &board : boards)
    {
      if (!board.empty())
      {
        std::vector<std::vector<int>> markedPositions = markBoard(board, draw);
        if (hasBoardWon(board, markedPositions))
        {
          winningDraw = draw;
          lastWinningBoard = board;
          board = {};
        }
      }
    }
  }

  return calculateWinningScore(lastWinningBoard, winningDraw);
}

// Main //
int main(int argc, char const *argv[])
{
  std::vector<std::string> input;
  std::ifstream inputFile;
  std::string line;

  inputFile.open("input.txt");
  if (inputFile.is_open())
  {
    while (std::getline(inputFile, line))
    {
      input.push_back(line);
    }
    inputFile.close();
  }

  std::vector<int> numberDraws = split_string_to_int(input[0], ',');
  std::vector<std::vector<int>> board;
  std::vector<std::vector<std::vector<int>>> boards;

  for (int i = 2; i < input.size(); i++)
  {
    if (input[i] == "")
    {
      std::vector<std::vector<int>> newBoard(board);
      boards.push_back(newBoard);
      board = {};
    }
    else
    {
      board.push_back(parseBoard(input[i]));
    }
  }
  boards.push_back(board);

  std::cout << solution2(numberDraws, boards) << std::endl;
  return 0;
}
