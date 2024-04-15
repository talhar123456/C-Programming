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

void median(const vector<double>& numbersList) 
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

void mean(const vector<double>& numbersList, const double& count)
{
  vector<double> sortedNumbers = numbersList;
  double sum = count;
  cout << remove_trailing_zeros(sum/ sortedNumbers.size());
  cout << " ";
}

void sum(const vector<double>& numbersList, const double& count)
{
  double sum = count;
  cout << remove_trailing_zeros(count);
  cout << " ";
}

void standardDeviation(const vector<double>& numbersList, const double& count)
{
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
    cout << remove_trailing_zeros(sqrt(variance));
    cout << " ";
  }
}

void firstQuartile(const vector<double>& numbersList)
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
    int temp = q1.size() / 2;
    double x = (q1[temp-1]+q1[temp]) / 2;
    cout << remove_trailing_zeros(x);
  }
  // if even
  else {
    vector<double> q1;
    int toSplit = (sortedNumbers.size() / 2);
    for (auto k = 0; k < toSplit; k++) 
    {
      q1.push_back(sortedNumbers[k]);
    }
    int temp = q1.size() / 2;
    double x = (q1[temp-1]+q1[temp]) / 2;
    cout << remove_trailing_zeros(x);
  }
  cout << " ";
}

void thirdQuartile(const vector<double>& numbersList)
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
    cout << remove_trailing_zeros(x);
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
    cout << remove_trailing_zeros(x);
  }
  // cout << " ";
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
    median(numbersList);
    mean(numbersList, count);
    sum(numbersList, count);
    standardDeviation(numbersList, count);
    firstQuartile(numbersList);
    thirdQuartile(numbersList);

    numbersList.clear();
    count = 0;
    cout << endl;
  }
  return 0;
}
