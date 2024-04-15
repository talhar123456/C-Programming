#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <typeinfo>

using namespace std;

double remove_trailing_zeros(double number) 
{
  stringstream ss;
  ss << setprecision(16);
  ss << number;
  string s = ss.str();

  if (s.find(".") != string::npos) 
  {
    s.erase(s.find_last_not_of("0") + 1, string::npos);
    if (s.back() == '.') 
    {
        s.pop_back();
    }
  }

  double result = stod(s);
  if (result != floor(result)) 
  {
    result = round(result * 100) / 100;
  }
  return result;
}

void scaling(const vector<double>& numbersList, const double& count) 
{
  vector<double> sortedNumbers = numbersList;
  double sum = count;
  for (auto i = 0; i < sortedNumbers.size(); ++i) 
  {
    if (i == sortedNumbers.size() - 1)
    {
      cout << remove_trailing_zeros(sortedNumbers[i] / sum);
    }
    else cout << remove_trailing_zeros(sortedNumbers[i] / sum) << " ";
  }
}

int main() 
{
  vector<double> numbersList;
  double count = 0;
  // this is a vector of vectors
  vector<vector<double>> lines; 
  string line;
  // getting input
  while (getline(cin, line) && line != "." && !line.empty()) 
  {
    vector<double> numbers;
    // splitting each number in a line
    istringstream iss(line);
    double number;
    while (iss >> number) 
    {
      numbers.push_back(number);
    }
    lines.push_back(numbers);
  }
  for (auto i = 0; i < lines.size(); i++) 
  {
    for (auto j = 0; j < lines[i].size(); j++) 
    {
      numbersList.push_back(lines[i][j]);
      count += lines[i][j];
    }
    scaling(numbersList, count);
    numbersList.clear();
    count = 0;
    cout << endl;
  }
  return 0;
}
