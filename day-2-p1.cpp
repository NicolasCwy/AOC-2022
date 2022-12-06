#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <fstream>

std::unordered_map<std::string, std::string> weakness = {{"scissors", "rock"},
  {"rock", "paper"},
  {"paper", "scissors"}};

std::unordered_map<std::string, std::string> inputToSymbol= {{"A", "rock"},
  {"B", "paper"},
  {"C", "scissors"},
  {"X", "rock"},
  {"Y", "paper"},
  {"Z", "scissors"}};

std::unordered_map<std::string, int> symbolScore = {{"rock", 1},
    {"paper", 2},
    {"scissors", 3}};

// Returns true if x is y's weakness
bool xBeatsY(std::string x, std::string y) {
  return weakness.at(y) == x;
}

std::vector<std::pair<std::string, std::string>> getInput(std::string filename) {
  std::fstream file;
  std::string line;
  std::vector<std::pair<std::string, std::string>> input;

  file.open(filename);
  if (file.is_open())
  {
    while (getline(file, line))
    {
      // split line into 2 characters
      // first character is opponent
      // second char is me
      std::stringstream ss(line);
      std::string colOne;
      std::string colTwo;

      ss >> colOne;
      ss >> colTwo;

      std::pair<std::string, std::string> pair = std::make_pair(inputToSymbol.at(colOne), inputToSymbol.at(colTwo));
      input.emplace_back(pair);
    }

  } else {
    std::cout << "Unable to open file";
  }

  return input;
}

int main(int argc, char *argv[])
{
  int score = 0;

  if (argc < 2)
  {
    std::cout << "Insufficient arguments, provide the file name";
    return -1;
  }

  std::vector<std::pair<std::string, std::string>> input = getInput(argv[1]);
  // iterate through input
  for (std::vector<std::pair<std::string, std::string>>::iterator it = input.begin(); it != input.end(); ++it)
  {
    std::string oppSymbol = std::get<0>(*it);
    std::string mySymbol = std::get<1>(*it);

    // Score from comparing choice with opponents
    // 1. beat opponent (col 2 beat col 1) 
    if (weakness.at(oppSymbol) == mySymbol) {
      score += 6;
    // 2. beaten by opponent (col 1 beat col 2)
    } else if (weakness.at(mySymbol) == oppSymbol) {
    // 3. Neither beat each other (Draw)
    } else {
      score += 3;
    }
    // Score from choosing a symbol
    score += symbolScore.at(mySymbol);
  }

  std::cout << score;
}