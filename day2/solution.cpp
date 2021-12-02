#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

const std::string FORWARD = "forward";
const std::string DOWN = "down";
const std::string UP = "up";

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

int solution1(std::vector<std::string> commands)
{
  int horizontalPosition = 0;
  int verticalPosition = 0;

  for (std::string &command : commands)
  {
    std::vector<std::string> parsed_command = split_string(command, ' ');
    std::string direction = parsed_command[0];
    int units = stoi(parsed_command[1]);

    if (direction == FORWARD)
    {
      horizontalPosition += units;
    }
    if (direction == DOWN)
    {
      verticalPosition += units;
    }
    if (direction == UP)
    {
      verticalPosition -= units;
    }
  }

  return horizontalPosition * verticalPosition;
}

int solution2(std::vector<std::string> commands)
{
  int horizontalPosition = 0;
  int verticalPosition = 0;
  int aim = 0;

  for (std::string &command : commands)
  {
    std::vector<std::string> parsed_command = split_string(command, ' ');
    std::string direction = parsed_command[0];
    int units = stoi(parsed_command[1]);

    if (direction == FORWARD)
    {
      horizontalPosition += units;
      verticalPosition += aim * units;
    }
    if (direction == DOWN)
    {
      aim += units;
    }
    if (direction == UP)
    {
      aim -= units;
    }
  }

  return horizontalPosition * verticalPosition;
}

int main(int argc, char const *argv[])
{
  std::vector<std::string> commands;
  std::ifstream inputFile;
  std::string line;

  inputFile.open("input.txt");
  if (inputFile.is_open())
  {
    while (std::getline(inputFile, line))
    {
      commands.push_back(line);
    }
    inputFile.close();
  }

  std::cout << solution2(commands) << std::endl;
  return 0;
}
