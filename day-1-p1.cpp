#include <iostream>
#include <string>
#include <sstream>

const std::string EMPTY_LINE = "\n";

int processCal(int cal, int maxCal)
{
  if (maxCal < cal)
  {
      return cal;
  }

  return maxCal;
};

int main()
{
  std::string lineData;
  int totalCalCount = 0;
  int maxCal = 0;
  while (getline(std::cin, lineData))
  {
    // Reset var for new elf and check if new maximum calories found
    if (lineData.length() == 0)
    {
      // Read second new line char in empty line
      getline(std::cin, lineData);

      maxCal = processCal(totalCalCount, maxCal);
      totalCalCount = 0;
    } 

    int cal;
    std::stringstream(lineData) >> cal;
    totalCalCount += cal;
  }

  // For last elf - since file does not end with \n\n
  maxCal = processCal(totalCalCount, maxCal);

  std::cout << maxCal;
}