#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <fstream>
#include <cctype>

using namespace std;

int getNumberStacks(string line)
{
  int count = 0;
  std::string::iterator it = line.begin();
  while (it != line.end())
  {
    // Space before number
    ++it;
    // Iterate through number which can have more than one digit
    while (isdigit(*it))
    {
      ++it;
      count++;
    }
    // Space after number
    ++it;

    // Break if no stack after this
    if (it == line.end())
    {
      break;
    }
    
    // Space between stack numbers
    ++it;
  }
  return count;
}

pair<vector<stack<char>>, vector<string>> readInput(string filename)
{
  fstream file;
  file.open(filename);

  vector<stack<char>> stacks = {};
  vector<string> moveInstructions = {};

  if (file.is_open())
  {
    // Process the order of the crates
    // Read input from bottom to top since we are constructing each stack bottom up
    stack<string> readOrder = {};
    string line;
    // Process lines that define initial stack order
    while (getline(file, line))
    {
      // Don't process move instructions in this loop
      if (line == "") break;

      readOrder.emplace(line);
      cout << line << endl;
    }
    // Get number of stacks
    // Bottom most line that write the stack numbers
    // e.g 
    // [D] [P] [R] [W] [H] [R] [Z] [W] [S]
    //  1   2   3   4   5   6   7   8   9 
    line = readOrder.top();
    readOrder.pop();
    int numStacks = getNumberStacks(line);
    for (auto i = 0; i < numStacks; i++)
    {
      stacks.emplace_back();
    }
    

    // Construct elements in each stack
    while (!readOrder.empty())
    {
      line = readOrder.top();
      readOrder.pop();
      std::string::iterator it = line.begin();
      int stackNum = 0;
      while (it != line.end())
      {
        // At bracket before alphabet 
        // At Alphabet on stack
        ++it;
        if (isalpha(*it))
        {
          stacks.at(stackNum).emplace(*it);
          cout << "Emplacing " << *it << " to stack " << stackNum << endl;
        }
        // Move to space between stacks 
        it += 2;
        // Break if no stack after this
        if (it == line.end())
        {
          break;
        }
        
        // Move pointer onto next bracket
        ++it;
        stackNum++;
      }
    }

    // Process move instructions
    while (getline(file, line))
    {
      moveInstructions.emplace_back(line);
    } 

  } else {
    std::cout << "Unable to open file";
  }
  return make_pair(stacks, moveInstructions);
}

int main(int argc, char *argv[])
{

  if (argc < 2)
  {
    std::cout << "Insufficient arguments, provide the file name";
    return -1;
  }

  pair<vector<stack<char>>, vector<string>> input = readInput(argv[1]);
  vector<stack<char>> stacks = get<0>(input);
  vector<string> instructions = get<1>(input);
  stack<char> movingStack = {};

  for (std::vector<string>::iterator it = instructions.begin(); it != instructions.end(); ++it)
  {
    stringstream ss(*it);
    string line;
    int count = 0;
    int source = 0;
    int destination = 0;

    // Parse instruction to move items
    for (auto i = 0; i < 6; ++i)
    {
      getline(ss, line, ' ');
      if (i == 1) 
      {
        cout << "Index 1 " << line << endl;
        count = stoi(line);
      } else if (i == 3)
      {
        cout << "Index 3 " << line << endl;
        // Convert to 0-index
        source = stoi(line) - 1; 
      } else if (i == 5)
      {
        cout << "Index 5 " << line << endl;
        // Convert to 0-index
        destination = stoi(line) - 1;  
      }
    }

    // Execute instruction to move items
    for (auto i = 0; i < count; i++)
    {
      char el = stacks.at(source).top();
      movingStack.emplace(el);
      stacks.at(source).pop();
    }
    // Moves n-elements in the exact same order to another stack
    for (auto i = 0; i < count; i++)
    {
      char el = movingStack.top();
      movingStack.pop();
      stacks.at(destination).emplace(el);
    }
  }

  // Pop top item for each stack
  for (std::vector<stack<char>>::iterator it = stacks.begin(); it != stacks.end(); ++it)
  {
    cout << (*it).top();
  }
}