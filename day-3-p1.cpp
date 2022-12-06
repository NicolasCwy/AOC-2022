#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

vector<string> readInput(string filename) {
  fstream file;
  string line;
  vector<string> input;

  file.open(filename);
  if (file.is_open())
  {
    while (getline(file, line))
    {
      input.emplace_back(line);
    }

  } else {
    std::cout << "Unable to open file";
  }

  return input;
}

int main(int argc, char *argv[])
{

  if (argc < 2)
  {
    std::cout << "Insufficient arguments, provide the file name";
    return -1;
  }

  vector<string> input = readInput(argv[1]);

  int totalPriority = 0;
  // For each rucksack
  for (vector<string>::iterator it = input.begin(); it != input.end(); ++it)
  {
    string c1 = (*it).substr(0, (*it).size() / 2);
    string c2 = (*it).substr((*it).size() / 2, (*it).size() / 2);

    unordered_set<char> inC1 = {c1.begin(), c1.end()};
    unordered_set<char> seen = {};

    for (const char& x: c2)
    {
      // count items in compartment two - if item not seen before ('seen' hashset) and in compartment one (check compartment 1 hashset) add priority
      if (inC1.count(x) == 1 && seen.count(x) == 0)
      {
        // ASCII capital letters are from 65 to 90
        if (int(x) <= 90)
        {
          totalPriority += int(x) - int('A') + 27;
        } else {
          totalPriority += int(x) - int('a') + 1;
        }
        
        seen.insert(x);
      }
    }
  }

  std::cout << totalPriority;
}