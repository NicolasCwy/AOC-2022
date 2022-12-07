#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <utility>

using namespace std;

pair<int, int> getLimits(string input) {
  stringstream ss (input);
  string leftLimit, rightLimit;
  getline(ss, leftLimit, '-');
  getline(ss, rightLimit, '-');
  return make_pair(stoi(leftLimit), stoi(rightLimit));
}

vector<pair<pair<int, int>, pair<int, int>>> readInput(string filename)
{
  fstream file;
  string line;
  vector<pair<pair<int, int>, pair<int, int>>> input;

  file.open(filename);
  if (file.is_open())
  {
    while (getline(file, line))
    {
      stringstream ss (line);
      string first, second;
      getline(ss, first, ',');
      getline(ss, second, ',');
      input.emplace_back(make_pair(getLimits(first), getLimits(second)));
    }

  } else {
    std::cout << "Unable to open file";
  }

  return input;
}

/**
 * Contains is when the bounds of x are within or equal to the bounds of Y or equal to the bounds of y
 * e.g x=(3, 3) y=(3,3) y contains x
 * e.g x=(3,3) y=(2,4) y contains x
 * x=(3,3) y=(1, 2) y does not contain x 
 */
bool xContainsY(pair<int, int> x, pair<int, int> y)
{
  return get<0>(y) <= get<0>(x) && get<1>(y) >= get<1>(x);
}

/**
 * Checks that one elfs planned work overlaps the other (if x intersects y, y intersects x)
 * This function has chosen to vary the limits of x and fix y
 * 
 * e.g checking xLeftLimit (work denoted by numbers)
 * x work  * 2 3 4 * *
 * y work  1 2 * * * *
 *  
 * y finds that x's left limit intersects
 * 
 * e.g checking xRightLimit
 * x work  * 2 3 4 * *
 * y work  * * * 4 5 *
 * 
 * y finds that x's left limit does not intersect but x's right limit does
*/
bool xIntersectsY(pair<int, int> x, pair<int, int> y)
{
  int xLeftLimit = get<0>(x);
  int xRightLimit = get<1>(x);
  int yLeftLimit = get<0>(y);
  int yRightLimit = get<1>(y);
  return (yLeftLimit <= xLeftLimit && yRightLimit >= xLeftLimit) ||
    (yLeftLimit <= xRightLimit && yRightLimit >= xRightLimit) ||
    xContainsY(x, y) ||
    xContainsY(y, x);
}

int main(int argc, char *argv[])
{

  if (argc < 2)
  {
    std::cout << "Insufficient arguments, provide the file name";
    return -1;
  }

  vector<pair<pair<int, int>, pair<int, int>>> input = readInput(argv[1]);

  int pairs = 0;
  for (vector<pair<pair<int, int>, pair<int, int>>>::iterator it=input.begin(); it != input.end(); ++it)
  {
    pair<int, int> e1 = get<0>(*it);
    pair<int, int> e2 = get<1>(*it); 

    if (xIntersectsY(e1, e2))
    {
      pairs++;
    }
  }
  std::cout << pairs; 
}