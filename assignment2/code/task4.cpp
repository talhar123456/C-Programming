#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int matchScore = 1;
const int mismatchScore = -1;
const int gapScore = -1;

void backtrack(const vector<vector<int>>& score, const string& sequence1, const string& sequence2, int i, int j, string alignment1, string alignment2, vector<string>& alignments);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <sequence1> <sequence2>" << endl;
        return 1;
    }

    string sequence1 = argv[1];
    string sequence2 = argv[2];

    // Create and initialize matrix to store scores
    vector<vector<int>> score(sequence1.length() + 1, vector<int>(sequence2.length() + 1, 0));
    for (int i = 1; i <= sequence1.length(); ++i) {
        score[i][0] = score[i - 1][0] + gapScore;
    }
    for (int j = 1; j <= sequence2.length(); ++j) {
        score[0][j] = score[0][j - 1] + gapScore;
    }

    // matrix creation
    for (int i = 1; i <= sequence1.length(); ++i) {
        for (int j = 1; j <= sequence2.length(); ++j) {
            int match = score[i - 1][j - 1] + (sequence1[i - 1] == sequence2[j - 1] ? matchScore : mismatchScore);
            int gapA = score[i - 1][j] + gapScore;
            int gapB = score[i][j - 1] + gapScore;

            score[i][j] = max({match, gapA, gapB});
        }
    }

    // Output best alignment score
    cout << score[sequence1.length()][sequence2.length()] << endl;

    // Backtrack 
    vector<string> alignments;
    string alignment1, alignment2;
    int i = sequence1.length(), j = sequence2.length();

    backtrack(score, sequence1, sequence2, i, j, alignment1, alignment2, alignments);

    for (auto i = 0; i < alignments.size(); i++) 
    {
        cout << alignments[i] << endl;

        if ((i + 1) % 2 == 0 && i + 1 < alignments.size()) {
            cout << endl;
        }
    }

    return 0;
}

void backtrack(const vector<vector<int>>& score, const string& sequence1, const string& sequence2, int i, int j, string alignment1, string alignment2, vector<string>& alignments) {
    if (i == 0 && j == 0) {
        reverse(alignment1.begin(), alignment1.end());
        reverse(alignment2.begin(), alignment2.end());
        alignments.push_back(alignment1);
        alignments.push_back(alignment2);
        return;
    }

    if (i > 0 && j > 0 && score[i][j] == score[i - 1][j - 1] + (sequence1[i - 1] == sequence2[j - 1] ? matchScore : mismatchScore)) {
        backtrack(score, sequence1, sequence2, i - 1, j - 1, alignment1 + sequence1[i - 1], alignment2 + sequence2[j - 1], alignments);
    }

    if (i > 0 && score[i][j] == score[i - 1][j] + gapScore) {
        backtrack(score, sequence1, sequence2, i - 1, j, alignment1 + sequence1[i - 1], alignment2 + '-', alignments);
    }

    if (j > 0 && score[i][j] == score[i][j - 1] + gapScore) {
        backtrack(score, sequence1, sequence2, i, j - 1, alignment1 + '-', alignment2 + sequence2[j - 1], alignments);
    }
}
