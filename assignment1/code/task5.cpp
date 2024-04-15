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
#include <regex>

using namespace std;

double remove_trailing_zeros(double number) {
    ostringstream oss;
    oss << fixed << setprecision(2) << number;
    string formattedResult = oss.str();

    formattedResult = regex_replace(formattedResult, regex("0+$"), "");

    if (formattedResult.back() == '.') {
        formattedResult.pop_back();
    }

    double result = stod(formattedResult);

    return result;
}

void median(vector<double>& numbersList) 
{
  vector<double> sortedNumbers = numbersList;
  // sorting vector
  sort(sortedNumbers.begin(), sortedNumbers.end());
  if (sortedNumbers.size() % 2 == 1) 
  {
    int temp = ((sortedNumbers.size() - 1) / 2) + 1;
    cout << remove_trailing_zeros(sortedNumbers[temp - 1]);
  } 
  else 
  {
    int temp = sortedNumbers.size() / 2;
    double x = (sortedNumbers[temp - 1] + sortedNumbers[temp]) / 2;
    cout << remove_trailing_zeros(x);
  }
  cout << " ";
}

void mean(vector<double>& numbersList, const double& count)
{
  vector<double> sortedNumbers = numbersList;
  double sum = count;
  cout << remove_trailing_zeros(sum/ sortedNumbers.size());
  cout << " ";
}

void sum(vector<double>& numbersList, const double& count)
{
  double sum = count;
  cout << remove_trailing_zeros(count);
  cout << " ";
}

void firstQuartile(vector<double>& numbersList)
{
  vector<double> sortedNumbers = numbersList;
  // sorting vector
  sort(sortedNumbers.begin(), sortedNumbers.end());
  // finding mod
  // if odd number
  if (sortedNumbers.size() % 2 == 1) 
  {
    vector<double> q1;
    int toSplit = ((sortedNumbers.size()-1) / 2) - 1;
    for (auto k = 0; k <= toSplit; k++) 
    {
      q1.push_back(sortedNumbers[k]);
      // cout << numbersList[k];
    }
    double temp = q1.size() / 2;
    double x = (q1[temp-1]+q1[temp]) / 2;
    cout << remove_trailing_zeros(x * 2);
  }
  // if even
  else {
    vector<double> q1;
    int toSplit = (sortedNumbers.size() / 2);
    for (auto k = 0; k < toSplit; k++) 
    {
      q1.push_back(sortedNumbers[k]);
    }
    double temp = q1.size() / 2;
    double x = (q1[temp-1]+q1[temp]) / 2;
    cout << remove_trailing_zeros(x * 2);
  }
  cout << " ";
}

void thirdQuartile(vector<double>& numbersList)
{
  vector<double> sortedNumbers = numbersList;
  // sorting vector
  sort(sortedNumbers.begin(), sortedNumbers.end());
  
  // finding mod
  // if odd number
  if (sortedNumbers.size() % 2 == 1) 
  {
    vector<double> q3;
    int toSplit = ((sortedNumbers.size() - 1) / 2) + 1;
    for (auto k = toSplit; k < sortedNumbers.size(); k++) 
    {
      q3.push_back(sortedNumbers[k]);
      // cout << numbersList[k] << "***";
    }
    int temp = q3.size() / 2;
    double x = (q3[temp-1]+q3[temp]) / 2;
    cout << remove_trailing_zeros(x * 2);
  }
  // if even
  else 
  {
    vector<double> q3;
    int toSplit = (sortedNumbers.size() / 2);
    for (auto k = toSplit; k < sortedNumbers.size(); k++) 
    {
      q3.push_back(sortedNumbers[k]);
      // cout << numbersList[k];
    }
    int temp = q3.size() / 2;
    double x = (q3[temp-1]+q3[temp]) / 2;
    cout << remove_trailing_zeros(x * 2);
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

  bool isSquareMatrix = true;

  // Checking if it's a square matrix
  for (auto i = 0; i < lines.size(); i++) 
  {
    if (lines.size() != lines[i].size()) 
    {
      isSquareMatrix = false;
    }
  }

  // for all rows
  if (isSquareMatrix) 
  {  
    for (auto i = 0; i < lines.size(); i++) 
    {
      for (auto j = 0; j < lines[i].size(); j++) 
      {
        numbersList.push_back(lines[i][j]);
        count += lines[i][j];
      }
      median(numbersList);
      mean(numbersList, count);
      sum(numbersList, count);
      firstQuartile(numbersList);
      thirdQuartile(numbersList);
      numbersList.clear();
      count = 0;
      cout << endl;
    }
  }
  else 
  {
    cout << "enter a valid square matrix!" << endl;
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
      median(numbersList);
      mean(numbersList, count);
      sum(numbersList, count);
      firstQuartile(numbersList);
      thirdQuartile(numbersList);
      numbersList.clear();
      count = 0;
      cout << endl;
    }
  }
  else 
  {
    cout << "enter a valid square matrix!" << endl;
  }

  // for diagonal 
  if (isSquareMatrix) 
  {  
    for (auto i = 0; i < lines.size(); i++) 
    {
      numbersList.push_back(lines[i][i]);
      count += lines[i][i];
    }
    median(numbersList);
    mean(numbersList, count);
    sum(numbersList, count);
    firstQuartile(numbersList);
    thirdQuartile(numbersList);
    numbersList.clear();
    count = 0;
    cout << endl;
  }
  else 
  {
    cout << "enter a valid square matrix!" << endl;
  }
  
  // for lower triangle
  if (isSquareMatrix) 
  {  
    for (int i = 1; i < lines.size(); i++) 
    {
      for (int j = 0; j < i; j++) 
      {
        numbersList.push_back(lines[i][j]);
        count += lines[i][j];
      }
    }
  }
  else 
  {
    cout << "enter a valid square matrix!" << endl;
  }
  median(numbersList);
  mean(numbersList, count);
  sum(numbersList, count);
  firstQuartile(numbersList);
  thirdQuartile(numbersList);
  cout << endl;
  return 0;
}
