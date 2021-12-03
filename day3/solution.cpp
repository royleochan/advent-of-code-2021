#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const std::string OXYGEN = "oxygen";
const std::string CARBON = "carbon";

int solution1(std::vector<std::string> input)
{
  std::string gamma = "";
  std::string epsilon = "";

  for (int i = 0; i < input[0].size(); i++)
  {
    int countZero = 0;
    int countOne = 0;

    for (int j = 0; j < input.size(); j++)
    {
      if (input[j][i] == '1')
      {
        countOne += 1;
      }
      if (input[j][i] == '0')
      {
        countZero += 1;
      }
    }

    if (countOne > countZero)
    {
      gamma += "1";
      epsilon += "0";
    }
    else
    {
      gamma += "0";
      epsilon += "1";
    }
  }

  return stoi(gamma, 0, 2) * stoi(epsilon, 0, 2);
}

template <typename T, typename Pred>
auto FilterCopyIf(std::vector<T> &vec, Pred p)
{
  std::vector<T> out;
  std::copy_if(begin(vec), end(vec), std::back_inserter(out), p);
  return out;
}

int calculateRating(std::vector<std::string> gasVector, std::string type)
{
  std::string result = "";

  for (int i = 0; i < gasVector[0].size(); i++)
  {
    int countZero = 0;
    int countOne = 0;

    for (int j = 0; j < gasVector.size(); j++)
    {
      if (gasVector[j][i] == '1')
      {
        countOne += 1;
      }
      if (gasVector[j][i] == '0')
      {
        countZero += 1;
      }
    }

    if (type == OXYGEN)
    {
      if (countOne >= countZero)
      {
        result += "1";
        gasVector = FilterCopyIf(gasVector, [i](std::string &elem)
                                 { return elem[i] == '1'; });
      }
      else
      {
        result += "0";
        gasVector = FilterCopyIf(gasVector, [i](std::string &elem)
                                 { return elem[i] == '0'; });
      }
    }
    else
    {
      if (countZero <= countOne)
      {
        result += "0";
        gasVector = FilterCopyIf(gasVector, [i](std::string &elem)
                                 { return elem[i] == '0'; });
      }
      else
      {
        result += "1";
        gasVector = FilterCopyIf(gasVector, [i](std::string &elem)
                                 { return elem[i] == '1'; });
      }
    }

    if (gasVector.size() == 1)
    {
      result += gasVector[0].substr(i + 1);
      break;
    }
  }

  return stoi(result, 0, 2);
}

int solution2(std::vector<std::string> input)
{
  std::vector<std::string> oxygenVector(input);
  std::vector<std::string> carbonVector(input);

  return calculateRating(oxygenVector, OXYGEN) * calculateRating(carbonVector, CARBON);
}

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

  std::cout << solution2(input) << std::endl;
  return 0;
}
