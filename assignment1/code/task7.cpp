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

int main(int argc, char* argv[]) 
{
  if (argc < 2) 
  {
    cerr << "enter 2 arguments!" << endl;
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
  {
    fileData.push_back(line);
  }
  file.close();
  
  // converting sequences to upper case 
  for (auto i = 0; i < fileData.size(); i++) 
  {
    if (fileData[i][0] != '>') 
    {
      for (auto j = 0; j < fileData[i].size(); j++) 
      {
        fileData[i][j] = toupper(fileData[i][j]);
      }
    }  
  }
  
  int numLines;
  int numSeq;
  vector<string> sequences;
  string tempSeq;
  string x = ">";
  fileData.push_back(x);
  for (const string& sequence : fileData) 
  {
    if (sequence[0] == '>') 
    {
      if (!tempSeq.empty()) 
      {
        sequences.push_back(tempSeq);
        tempSeq.clear();
      }
    }
    else 
    {
      tempSeq += sequence;
      tempSeq += '+';
    }
  }

  // removing garbage
  for (string& sequence : sequences) 
  {
    for (char& c : sequence) 
    {
      if (c != 'A' && 
          c != 'T' && 
          c != 'G' && 
          c != 'C' && 
          c != 'U' &&
          c != '+') {
        sequence.clear();
      }
    }
  }
  
  // DNA -> RNA 
  for (string& sequence : sequences) 
  {
    for (char& c : sequence) 
    {
      if (c == 'T') 
      {
        c = 'U';
      }
    }
  }

  // for lines 
  int lines = 0;
  for (string& sequence : sequences) 
  {
    for (char& c : sequence) 
    {
      if (c == '+') 
      {
        lines += 1;
      }
    }
  }

  // for sequences 
  int totalSeq = 0;
  for (string& sequence : sequences) 
  {
    if (!sequence.empty()) 
    {
      totalSeq += 1;
    }
  }

  // for GC content 
  double GC = 0.0;
  for (string& sequence : sequences) 
  {
    for (char& c : sequence) 
    {
      if (c == 'G' || c == 'C') 
      {
        GC += 1;
      } 
    }
  }


// for A U G C percentage 
  double A, U, G, C = 0.0;
  for (string& sequence : sequences) 
  {
    for (char& c : sequence) 
    {
      if (c == 'A') 
      {
        A += 1;
      }
      if (c == 'U') 
      {
        U += 1;
      }
      if (c == 'G') 
      {
        G += 1;
      }
      if (c == 'C') 
      {
        C += 1;
      } 
    }
  }
  double totalNuc = A + G + C + U;
  A = ((A / totalNuc) * 100) / 100;
  U = ((U / totalNuc) * 100) / 100;
  G = ((G / totalNuc) * 100) / 100;
  C = ((C / totalNuc) * 100) / 100;
  GC = ((GC / totalNuc) * 100) / 100;

  cout << "Lines: " << lines + totalSeq << endl;
  cout << "Sequences: " << totalSeq << endl;
  cout << "GC content: " << GC << endl;
  cout << "A: " << A << endl;
  cout << "C: " << C << endl;
  cout << "G: " << G << endl;
  cout << "U: " << U << endl;

  // cleaning sequences 
  vector<string> sequences2;
  string temp;
  for (string& sequence : sequences) 
  {
    for (char& c : sequence) 
    {
      if (c != '+') 
      {
        temp += c;
      }
    }
    sequences2.push_back(temp);
    temp.clear();
  }
    // finding hairpin
  vector<string> perfectHairpin;
  for (string& sequence : sequences2) 
  {
    string firstPart, lastPart;
    firstPart += sequence;
    lastPart += sequence;
    reverse(lastPart.begin(), lastPart.end());

    // cout << firstPart << endl;
    // cout << lastPart << endl;
    for (char& c : lastPart) 
    {
      if (c == 'A') 
      {
        c = 'U';
      } 
      else if (c == 'U') 
      {
        c = 'A';
      }
      else if (c == 'C') 
      {
        c = 'G';
      } 
      else if (c == 'G') 
      {
        c = 'C';
      }
    }

    // for odd sequence 
    if (sequence.size() % 2 == 1) 
    {
      int half = ((sequence.size() - 1) / 2);
      if (firstPart.substr(0, half - 1) == lastPart.substr(0, half - 1)) 
      {
        // cout << firstPart.substr(0, half) << endl;
        if (!firstPart.substr(0, half).empty()) 
        {
          perfectHairpin.push_back(firstPart.substr(0, half));
        }
      }
    }

    // for even sequences 
    else if (sequence.size() % 2 == 0) 
    {
      int half2 = (sequence.size() / 2);
      if (firstPart.substr(0, half2) == lastPart.substr(0, half2)) 
      {
        // cout << firstPart.substr(0, half2) << endl;
        if (!firstPart.substr(0, half2).empty()) 
        {
          perfectHairpin.push_back(firstPart.substr(0, half2));
        }
      }
    }
    firstPart.clear();
    lastPart.clear();
  }

  ofstream outputFile(argv[2]);
  if (outputFile.is_open()) 
  {
    for (string& s : perfectHairpin) 
    {
      outputFile << s << endl;
    }
    outputFile.close();
  }
  else 
  {
    cerr << "Unable to open the file." << endl;
  }
  return 0;
}