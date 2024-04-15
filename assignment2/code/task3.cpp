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

int main(int argc, const char *argv[])
{
  if (argc < 3) 
  {
    cerr << "enter 3 arguments!" << endl;
    return 1;
  }
  ifstream file(argv[1]);
  if (!file.is_open()) 
  {
    cerr << "error opening file!" << endl;
    return 1;
  }
  vector<string> fileData;
  string line;
  while (getline(file, line)) 
  if (!line.empty())
  {
    fileData.push_back(line);
  }
  file.close();

  // some pre-processing 
  string duplicate = fileData.back();
  istringstream iss(duplicate);
  vector<string> duplicateVec;
  string word;
  while (iss >> word) 
  {
    duplicateVec.push_back(word);
  }
  string temp;
  temp += "chr";
  temp += to_string(stoi(duplicateVec[0].substr(duplicateVec[0].length() - 1)) + 1);
  duplicateVec[0] = temp;

  int num = 0;
  num = stoi(duplicateVec[1]) + 1;
  duplicateVec[1] = num;
  ostringstream oss;
  for (auto& word : duplicateVec) 
  {
    oss << word << " ";
  }
  string mergedString = oss.str();
  fileData.push_back(mergedString);


  vector<vector<string>> genes;
  vector<string> words;
  
  for (auto& line : fileData) 
  {
    if (!line.empty()) 
    {
      istringstream iss(line);
      string word;

      while (iss >> word) 
      {
        words.push_back(word);
      }
      genes.push_back(words);
      words.clear();
    }
  }

  vector<int> chromosome;
  for (auto& gene : genes) 
  {
    chromosome.push_back(stoi(gene[0].substr(gene[0].length() - 1)));
  }
  bool chromosomeIsSorted = is_sorted(chromosome.begin(), chromosome.end());

  bool isSorted;

  if (chromosomeIsSorted)
  {
    for (int i = 0; i < genes.size(); i++)
    {
      if (i == genes.size() - 1 || genes[i].empty())
      {
        break;
      }
      else 
      {
        if (genes[i][0] == genes[i + 1][0]) 
        {
          if (stoi(genes[i][1]) < stoi(genes[i + 1][1]))
          {
            isSorted = true;
          }
          else 
          {
            cerr << "An error occured" << endl;
            isSorted = false;
            exit(1);
          }
        }
        else 
        {
          continue;
        }
      }
    }
  }
  else 
  {
    cerr << "An error occured" << endl;
    isSorted = false;
    exit(1);
  }

  if (isSorted)
  {
    int cluster = 1;
    string temp;
    for (int i = 0; i < genes.size(); i++)
    {

      // for second last iteration
      if (i == genes.size() - 2)
      {
        if (genes[i][0] != genes[i + 1][0])
        {
          temp = "cluster=";
          temp += to_string(cluster);
          genes[i].push_back(temp);
          temp.clear();
          cluster += 1;
          temp = "cluster=";
          temp += to_string(cluster);
          genes[i + 1].push_back(temp);
          temp.clear();
        }
        else 
        {
          double a, b;
          a = (stoi(genes[i][1]) + stoi(genes[i][2]) / 2);
          b = (stoi(genes[i + 1][1]) + stoi(genes[i + 1][2]) / 2);
          if (abs(a - b) < stoi(argv[2]))
          {
            temp = "cluster=";
            temp += to_string(cluster);
            genes[i].push_back(temp);
            genes[i + 1].push_back(temp);
            temp.clear();
          }
        }
        break;
      }

      else 
      {
        if (genes[i][0] != genes[i + 1][0])
        {
          temp = "cluster=";
          temp += to_string(cluster);
          genes[i].push_back(temp);
          temp.clear();
          cluster += 1;
          temp = "cluster=";
          temp += to_string(cluster);
          genes[i + 1].push_back(temp);
          temp.clear();
        }
        else 
        {
          double a, b;
          a = (stoi(genes[i][1]) + stoi(genes[i][2]) / 2);
          b = (stoi(genes[i + 1][1]) + stoi(genes[i + 1][2]) / 2);
          if (abs(a - b) < stoi(argv[2]))
          {
            temp = "cluster=";
            temp += to_string(cluster);
            genes[i].push_back(temp);
            genes[i + 1].push_back(temp);
            temp.clear();
          }
          else 
          {
            temp = "cluster=";
            temp += to_string(cluster);
            genes[i].push_back(temp);
            temp.clear();
            cluster += 1;
            temp = "cluster=";
            temp += to_string(cluster);
            genes[i + 1].push_back(temp);
            temp.clear();
          }
        }
      }
    }
  }

  for (auto& gene : genes) 
  {
    if (gene.size() > 4) 
    {
      gene.resize(gene.size() - 1);
    }
  }

  genes.resize(genes.size() - 1);

  for (auto& gene : genes)
  {
    for (auto& x : gene)
    {
      cout << x << "\t";
    }
    cout << endl;
  }

  ofstream outputFile(argv[3]);
  if (outputFile.is_open()) 
  {
    for (int i = 0; i < genes.size(); i++) 
    {
      for (int j = 0; j < genes[i].size(); j++) 
      {
        if (j == genes[i].size() - 1)
        {
          outputFile << genes[i][j];
        }
        else 
        {
          outputFile << genes[i][j] << "\t";
        }
      }
      outputFile << endl;
    }
    outputFile.close();
  }
  else 
  {
    cerr << "Unable to open the file." << endl;
  }
  return 0;
}
