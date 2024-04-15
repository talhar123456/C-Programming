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

vector<vector<double>> numberListArrange;

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

void zScore(vector<double>& numbersList, double& count)
{
  double standardDeviation = 0.0;
  double mean = 0.0;
  mean = count / numbersList.size();
  if (numbersList.size() > 1) 
  {
    double sumSquaredDifferences = 0.0;
    for (auto& num : numbersList) 
    {
      sumSquaredDifferences += ((num - mean) * (num - mean));
    }
    double variance = 0.0;
    variance = sumSquaredDifferences / (numbersList.size() - 1);
    standardDeviation = sqrt(variance);
  }
  for (auto& x : numbersList) 
  {
    x = remove_trailing_zeros(((x - mean) / standardDeviation));
    
  }
  numberListArrange.push_back(numbersList);
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
    while (iss >> number) {
      numbers.push_back(number);
    }
    lines.push_back(numbers);
  }

  bool isSquareMatrix = true;

  // Checking if it's a square matrix
  for (auto i = 0; i < lines.size(); i++)
  {
    if (lines.size() != lines[i].size()) 
    {
      isSquareMatrix = false;
    }
  }

  // for all columns 
  if (isSquareMatrix) 
  {
    int numRows = lines.size();
    int numCol = lines[1].size();
    for (auto i = 0; i < numCol; i++) 
    {
      for (auto j = 0; j < numRows; j++) 
      {
        numbersList.push_back(lines[j][i]);
        count += lines[j][i];
      }
      zScore(numbersList, count);
      numbersList.clear();
      count = 0;
    }
  }
  else 
  {
    cout << "enter a valid square matrix!" << endl;
  }

  for (int i = 0; i < numberListArrange.size(); i++)
  {
    for (int j = 0; j < numberListArrange[i].size(); j++)
    if (j == numberListArrange[i].size() - 1)
    {
      cout << numberListArrange[j][i];
    }
    else 
    {
      cout << numberListArrange[j][i] << " ";
    }
    cout << endl;
  }

  return 0;
}