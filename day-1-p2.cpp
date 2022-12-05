#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>

const std::string EMPTY_LINE = "\n";

int main(int argc, char *argv[])
{
  std::ifstream file;
  std::string lineData;
  int totalCalCount = 0;
  std::priority_queue<int, std::vector<int>, std::greater<int>> topCalories = {};
  int numElInHeap = 0;

  if (argc < 2)
  {
    std::cout << "Insufficient arguments, provide the file name";
    return -1;
  }

  file.open(argv[1]);
  if (file.is_open())
  {
    while (getline(file, lineData))
      {
        // Reset var for new elf and check if new maximum calories found
        if (lineData.length() == 0)
        {
          // Read second new line char in empty line
          // line contains 2 new lines, getline reads till the first \n
          getline(std::cin, lineData);
          if (topCalories.size() < 3)
          {
            topCalories.push(totalCalCount);
            std::cout << "Adding " << totalCalCount << " to the heap\n";
          } else if (topCalories.top() < totalCalCount) {
            std::cout << "Removing " << topCalories.top() << " and adding " << totalCalCount << " to the heap\n";
            topCalories.pop();
            topCalories.push(totalCalCount);
          }
          totalCalCount = 0;
        } 

        int cal;
        std::stringstream(lineData) >> cal;
        totalCalCount += cal;
      }

      int sum = 0; 
      while (!topCalories.empty())
      {
        sum += topCalories.top();
        topCalories.pop();
      }
      std::cout << sum;
  } else {
    std::cout << "Unable to open file";
  }
}