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
#include <cstdlib>
#include <random>
#include <type_traits>
#include <map>

using namespace std;

vector<double> generateV1 (unsigned int n, unsigned int m, unsigned int s, double p, unsigned int k) 
{
  mt19937_64 generator(s);
  negative_binomial_distribution<int> distribution(k, p);

  vector<double> v1(n);

  for (int i = 0; i < n; i++) 
  {
    v1[i] = (distribution(generator));
  }

  return v1;
}

vector<double> generateV2 (unsigned int n, unsigned int m, unsigned int s, double p, unsigned int k) 
{
  s = s * 2;
  mt19937_64 generator(s);
  negative_binomial_distribution<int> distribution(k, p);

  vector<double> v2(m);

  for (int i = 0; i < m; i++) 
  {
    v2[i] = (distribution(generator));
  }

  return v2;
}

double mean (vector<double> x) 
{
  double  sum = 0.0;
  double mean = 0.0;
  for (auto& num : x) 
  {
    sum += num;
  }
  mean = (sum / x.size());
  return mean;
}

double standardDeviation(vector<double> y, double count)
{
  double mean = 0.0;
  mean = count / y.size();
  double variance = 0.0;
  if (y.size() > 1) 
  {
    double sumSquaredDifferences = 0.0;
    for (auto& num : y) 
    {
      sumSquaredDifferences += ((num - mean) * (num - mean));
    }
    variance = sumSquaredDifferences / (y.size() - 1);
  }
  return sqrt(variance);
}

double variance(vector<double> y, double count)
{
  double mean = 0.0;
  mean = count / y.size();
  double variance = 0.0;
  if (y.size() > 1) 
  {
    double sumSquaredDifferences = 0.0;
    for (auto& num : y) 
    {
      sumSquaredDifferences += ((num - mean) * (num - mean));
    }
    variance = sumSquaredDifferences / (y.size() - 1);
  }
  return variance;
}

double scalingV1 (double num) 
{
  return log2(fabs(num) + 1);
}

double scalingV2 (double num) 
{
  return log2(fabs(num) + 1);
}
double tStatistics (vector<double> v1, vector<double> v2, double mean1, double mean2, double variance1, double variance2, double sp, double t, double sum1, double sum2)
{
  sum1 = accumulate(v1.begin(), v1.end(), 0.0);
  sum2 = accumulate(v2.begin(), v2.end(), 0.0);
  mean1 = mean(v1);
  mean2 = mean(v2);
  variance1 = variance(v1, sum1);
  variance2 = variance(v2, sum2);
  int v1Size = v1.size();
  int v2Size = v2.size();
  sp = sqrt(((v1Size - 1) * variance1 + (v2Size - 1) * variance2) / (v1Size + v2Size - 2));
  t = (mean1 - mean2) / (sp * sqrt(1.0 / v1Size + 1.0 / v2Size));
  return t;
}

vector<double> generateAndShuffleIntegers(int n, unsigned int s) {
    vector<double> integers(n);
    iota(integers.begin(), integers.end(), 1);

    mt19937_64 generator(s * 7);
    shuffle(integers.begin(), integers.end(), generator);

    return integers;
}

bool isEven(double num) {
    return fmod(num, 2.0) == 0;
}

int main(int argc, const char* argv[]) {

  if (argc != 6) 
  {
    cerr << "Invalid number of arguements. Usage: ./program n m s p k" << endl;
    return 1;
  }
  if (
    atoi(argv[1]) >= 0 &&
    atoi(argv[2]) >= 0 &&
    atoi(argv[3]) >= 0 &&
    atof(argv[4]) >= 0 &&
    atoi(argv[5]) >= 0
  ) 
  {
    unsigned int n, m, s, k;
    double p;
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    s = atoi(argv[3]);
    p = atof(argv[4]);
    k = atoi(argv[5]);
    vector<double> v1 = generateV1 (n, m, s, p, k);
    vector<double> v2 = generateV2 (n, m, s, p, k);
    
    double count = 0.0;
    for (auto& num : v1) 
    {
      count += num;
    }

    double count2 = 0.0;
    for (auto& num : v2) 
    {
      count2 += num;
    }

    // for v1 
    cout << setprecision(3) << "V1 Mean: " << mean (v1) << endl;
    cout << setprecision(3) << "V1 Sample standard deviation: " << standardDeviation (v1, count) << endl;
    cout << "V1 Top " << v1.size() << " elements: ";
    vector<double> scalingV1Arrange;
    vector<double> unScaledV1;
    for (auto& num : v1) 
    {
      unScaledV1.push_back(scalingV1(num));
      scalingV1Arrange.push_back(scalingV1(num));
    }
    sort(scalingV1Arrange.begin(), scalingV1Arrange.end(), greater<double>());
    for (int i = 0; i < scalingV1Arrange.size(); i++) 
    {
      if (i == scalingV1Arrange.size() - 1)
      {
        cout << setprecision(3) << scalingV1Arrange[i] << endl;
      }
      else 
      {
        cout << setprecision(3) << scalingV1Arrange[i] << ", ";
      }
    }

    // for v2 
    cout << setprecision(3) << "V2 Mean: " << mean (v2) << endl;
    cout << setprecision(3) << "V2 Sample standard deviation: " << standardDeviation (v2, count2) << endl;
    cout << "V2 Top " << v2.size() << " elements: ";
    vector<double> scalingV2Arrange;
    for (auto& num : v2) 
    {
      scalingV2Arrange.push_back(scalingV2(num));
    }
    sort(scalingV2Arrange.begin(), scalingV2Arrange.end(), greater<double>());
    for (int i = 0; i < scalingV2Arrange.size(); i++) 
    {
      if (i == scalingV2Arrange.size() - 1)
      {
        cout << setprecision(3) << scalingV2Arrange[i] << endl;
      }
      else 
      {
        cout << setprecision(3) << scalingV2Arrange[i] << ", ";
      }
    }
    cout << endl;
    double mean1, mean2, variance1, variance2, sp, t, t2, sum1, sum2 = 0.0;
    t = tStatistics (v1, v2, mean1, mean2, variance1, variance2, sp, t, sum1, sum2);
    t2 = tStatistics (scalingV1Arrange, scalingV2Arrange, mean1, mean2, variance1, variance2, sp, t, sum1, sum2);
    cout << "Comparing V1 and V2..." << endl;
    cout << "Unscaled t-statistic: " << t <<endl;
    cout << "Comparing log2 scaled V1 and V2..." << endl;
    cout << "Scaled t-statistic: " << t2 <<endl;

    int v1Size = v1.size();
    int v2Size = v2.size();
    int df_total = v1Size + v2Size - 2;
    cout << "Total degrees of freedom: " << df_total <<endl;

    vector<double> shuffledIntegers = generateAndShuffleIntegers(n, s);

    vector<double> resultVector;
    for (int i = 0; i < shuffledIntegers.size(); i++)
    {
      resultVector.push_back(shuffledIntegers[i] * unScaledV1[i]);
    }
    
    vector<int> roundValues;
    vector<int> sortedRoundValues;
    for (auto& num : resultVector) 
    {
      roundValues.push_back(round(num));
    }

    map<int, double> intMap;
    for (int i = 0; i < resultVector.size(); i++) 
    {
      intMap[roundValues[i]] = resultVector[i];
    }

    vector<int> evenNum;
    vector<int> oddNum;
    for (auto& i : roundValues) 
    {
      if (i % 2 == 0)
      {
        evenNum.push_back(i);
      }
      else oddNum.push_back(i);
    }
    sort(evenNum.rbegin(), evenNum.rend());
    sort(oddNum.begin(), oddNum.end());
    sortedRoundValues.insert(sortedRoundValues.end(), evenNum.begin(), evenNum.end());
    sortedRoundValues.insert(sortedRoundValues.end(), oddNum.begin(), oddNum.end());

    cout << "Sorted vector: ";
    for (int i = 0; i < sortedRoundValues.size(); i++) 
    {
      for (auto& pair : intMap) 
      {
        if (sortedRoundValues[i] == pair.first) 
        {
          if (i == sortedRoundValues.size() - 1)
          {
            cout << pair.second;
          }
          else cout << pair.second << ", ";
        }
      }
    }
  }
  else 
  {
    cerr << "Invalid data type" << endl;
    exit(1);
  }

  return 0;
}
