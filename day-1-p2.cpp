#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <sstream>

const std::string EMPTY_LINE = "\n";

void processCal(int cal, std::priority_queue<int, std::vector<int>, std::greater<int>> &pq)
{
    if (pq.size() < 3)
      {
        pq.push(cal);
        std::cout << "Adding " << cal << " to the heap\n";
      } else if (pq.top() < cal) {
        std::cout << "Removing " << pq.top() << " and adding " << cal << " to the heap\n";
        pq.pop();
        pq.push(cal);
      }
      
};

int main()
{
  std::string lineData;
  int totalCalCount = 0;
  std::priority_queue<int, std::vector<int>, std::greater<int>> topCalories = {};
  int numElInHeap = 0;

  while (getline(std::cin, lineData))
  {
    // Reset var for new elf and check if new maximum calories found
    if (lineData.length() == 0)
    {
      // Read second new line char in empty line
      // line contains 2 new lines, getline reads till the first \n
      getline(std::cin, lineData);
      processCal(totalCalCount, topCalories);
      totalCalCount = 0;
    } 

    int cal;
    std::stringstream(lineData) >> cal;
    totalCalCount += cal;
  }
  // For last elf - since file does not end with \n\n
  processCal(totalCalCount, topCalories);

  int sum = 0; 
  while (!topCalories.empty())
  {
    sum += topCalories.top();
    topCalories.pop();
  }
  std::cout << sum;
}