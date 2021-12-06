#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <array>

// Helpers //
std::vector<std::string> split_string(std::string str, char delim)
{
  std::stringstream stream(str);
  std::string temp_str;
  std::vector<std::string> result;

  while (std::getline(stream, temp_str, delim))
  {
    result.push_back(temp_str);
  }

  return result;
}

// Solutions //
// Naive vector implementation
int solution1(std::vector<int> &fishes)
{
  const int SIMULATION_DAYS = 80; // Question Part 1 Specification

  for (int i = 0; i < SIMULATION_DAYS; i++)
  {
    std::vector<int> temp;
    for (auto &time : fishes)
    {
      if (time == 0)
      {
        time = 6;
        temp.push_back(8);
      }
      else
      {
        time -= 1;
      }
    }
    fishes.insert(fishes.end(), temp.begin(), temp.end());
  }

  return fishes.size();
}

// Optimized implementation: store number of fish for each timer value
unsigned long long solution2(std::vector<int> fishes)
{
  const int SIMULATION_DAYS = 256; // Question Part 2 Specification
  std::array<unsigned long long, 9> timers = {0};

  for (auto &time : fishes)
  {
    timers[time] += 1;
  }

  for (int i = 0; i < SIMULATION_DAYS; i++)
  {
    std::array<unsigned long long, 9> temp = {0};
    for (int j = 0; j < 9; j++)
    {
      if (j == 0)
      {
        temp[8] += timers[0];
        temp[6] += timers[0];
      }
      else
      {
        temp[j - 1] += timers[j];
      }
      temp[j] -= timers[j];
    }

    for (int j = 0; j < 9; j++)
    {
      timers[j] += temp[j];
    }
  }

  return std::accumulate(timers.begin(), timers.end(), 0LL);
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

  std::vector<std::string> dataVector = split_string(input[0], ',');
  std::vector<int> fishes;
  for (auto &data : dataVector)
  {
    fishes.push_back(stoi(data));
  }

  std::cout << solution2(fishes) << std::endl;
  return 0;
}
