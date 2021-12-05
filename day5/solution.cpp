#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <map>
#include <algorithm>

// Helpers //
std::vector<std::string> split_string(std::string s, std::string delimiter)
{
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  std::string token;
  std::vector<std::string> res;

  while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
  {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(s.substr(pos_start));
  return res;
}

std::pair<std::pair<int, int>, std::pair<int, int>> parseLine(std::string line)
{
  std::vector<std::string> coordinates = split_string(line, " -> ");
  std::vector<std::string> start = split_string(coordinates[0], ",");
  std::vector<std::string> end = split_string(coordinates[1], ",");

  std::pair<int, int> startCoordinate;
  std::pair<int, int> endCoordinate;
  startCoordinate.first = stoi(start[0]);
  startCoordinate.second = stoi(start[1]);
  endCoordinate.first = stoi(end[0]);
  endCoordinate.second = stoi(end[1]);

  return {startCoordinate, endCoordinate};
}

void addPointToMap(std::map<std::pair<int, int>, int> &points, int first, int second)
{
  std::pair<int, int> point;
  point.first = first;
  point.second = second;
  if (points.count(point) >= 1)
  {
    points[point] += 1;
  }
  else
  {
    points[point] = 1;
  }
}

// Solutions //
int solution1(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> pairsVector)
{
  std::map<std::pair<int, int>, int> points;

  for (auto coordinates : pairsVector)
  {
    std::pair<int, int> start = coordinates.first;
    std::pair<int, int> end = coordinates.second;

    if (start.first == end.first or start.second == end.second)
    {
      for (int i = std::min(start.first, end.first); i < std::max(start.first, end.first) + 1; i++)
      {
        for (int j = std::min(start.second, end.second); j < std::max(start.second, end.second) + 1; j++)
        {
          addPointToMap(points, i, j);
        }
      }
    }
  }

  int result = 0;
  for (auto const &[point, count] : points)
  {
    if (count >= 2)
    {
      result += 1;
    }
  }

  return result;
}

int solution2(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> pairsVector)
{
  std::map<std::pair<int, int>, int> points;

  for (auto coordinates : pairsVector)
  {
    std::pair<int, int> start = coordinates.first;
    std::pair<int, int> end = coordinates.second;
    int x1 = start.first;
    int x2 = end.first;
    int y1 = start.second;
    int y2 = end.second;

    int dx = x1 == x2 ? 0 : x2 > x1 ? 1
                                    : -1;
    int dy = y1 == y2 ? 0 : y2 > y1 ? 1
                                    : -1;

    addPointToMap(points, x1, y1);
    while (x1 != x2 || y1 != y2)
    {
      x1 += dx;
      y1 += dy;
      addPointToMap(points, x1, y1);
    }
  }

  int result = 0;
  for (auto const &[point, count] : points)
  {
    if (count >= 2)
    {
      result += 1;
    }
  }

  return result;
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

  std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> coordinates;

  for (auto line : input)
  {
    coordinates.push_back(parseLine(line));
  }

  std::cout << solution2(coordinates) << std::endl;
  return 0;
}
