#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

const std::string EMPTY_LINE = "\n";

int main(int argc, char *argv[])
{
  std::ifstream file;
  std::string lineData;
  int totalCalCount = 0;
  int maxCal = 0;

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
          getline(file, lineData);

          maxCal = totalCalCount > maxCal ? totalCalCount : maxCal;
          totalCalCount = 0;
        } 

        int cal;
        std::stringstream(lineData) >> cal;
        totalCalCount += cal;
      }

      std::cout << maxCal;
  } else {
    std::cout << "Unable to open file";
  }
  
}