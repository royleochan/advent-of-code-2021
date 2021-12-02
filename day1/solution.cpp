#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int solution1(std::vector<int> depths)
{
    int count = 0;
    int n = depths.size();

    if (n == 0)
    {
        return 0;
    }

    for (int i = 1; i < n; i++)
    {
        if (depths[i] > depths[i - 1])
        {
            count += 1;
        }
    }

    return count;
}

int solution2(std::vector<int> depths)
{
    int count = 0;
    int n = depths.size();

    if (n < 3)
    {
        return 0;
    }
    int left = 0;
    int right = 3;
    int curr_window_sum = depths[0] + depths[1] + depths[2];

    while (right < n)
    {
        left += 1;
        right += 1;
        int next_window_sum = 0;
        for (int i = left; i < right; i++)
        {
            next_window_sum += depths[i];
        }
        next_window_sum > curr_window_sum ? count += 1 : 0;
        curr_window_sum = next_window_sum;
    }

    return count;
}

int main(int argc, char const *argv[])
{
    std::vector<int> depths;
    std::ifstream inputFile;
    std::string line;

    inputFile.open("input.txt");
    if (inputFile.is_open())
    {
        while (std::getline(inputFile, line))
        {
            depths.push_back(stoi(line));
        }
        inputFile.close();
    }

    std::cout << solution2(depths) << std::endl;
    return 0;
}
