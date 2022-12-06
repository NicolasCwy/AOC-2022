#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <iterator>

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
  vector<string>::iterator it = input.begin();
  while (it != input.end())
  {
    string e1 = *it;
    ++it;
    string e2 = *it;
    ++it;
    string e3 = *it;
    ++it;

    unordered_set<char> inE1 = {e1.begin(), e1.end()};
    unordered_set<char> inE1AndE2 = {};
    unordered_set<char> inAllSets = {};

    for (const char& x : e2) {
      if (inE1.count(x) == 1) {
        inE1AndE2.insert(x);
      }
    }

    for (const char& x : e3) {
      if (inE1AndE2.count(x) == 1) {
        inAllSets.insert(x);
      }
    }

    for (const char& x: inAllSets)
    {
      // ASCII capital letters are from 65 to 90
      if (int(x) <= 90)
      {
        totalPriority += int(x) - int('A') + 27;
      } else {
        totalPriority += int(x) - int('a') + 1;
      }
    }
  }

  std::cout << totalPriority;
}