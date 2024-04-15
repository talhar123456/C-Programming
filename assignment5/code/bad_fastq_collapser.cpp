#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "bad_fastq_collapser.hpp"

// clang-format off
// This program gets a FASTQ file as input and will output a collapsed FASTQ file.
// Collapsing is done similar to the collapsing for fasta files: 1. find equal sequences, 2. count them, 3. new header: @seq_number_xZ for Z occurrences
// of the sequence, 4. compute the mean of the probability that a base call is wrong for each position for the sequences that are collapsed into one and map them back to a base quality.
// The base quality is in Sanger format that can encode a Phred quality score from 0 to 93 using ASCII 33 to 126
// The probability p that a base call is wrong can be derived from the Phred quality score Q: Q=-10*log10(p)
// The output should be addionally sorted by frequency and then by the sum of the probabilities of a sequence (lowest first).
// clang-format on

bool sort_by_freq_quality(std::pair<FASTQentry, int> fq1,
                          std::pair<FASTQentry, int> fq2);
std::vector<double> qualities_to_probabilities(const std::string& quals);
std::string probabilities_to_qualities(const std::vector<double>& probas);
std::map<std::string, std::vector<FASTQentry>> parse_fastq_file(
    std::ifstream& infile, std::size_t& total_reads);
std::vector<std::pair<FASTQentry, int>> count_frequencies_and_merge_qualities(
    std::map<std::string, std::vector<FASTQentry>> read2fqs);

int main(int argc, char* argv[]) {
  std::ifstream input_file;
  std::ofstream output_file;

  if (argc == 3) {
    input_file.open(argv[1]);
    if (!input_file) {
      std::cerr << "cannot open input file: " << argv[1] << std::endl;
      return 1;
    }
    output_file.open(argv[2]);
    if (!output_file) {
      std::cerr << "cannot open output file: " << argv[2] << std::endl;
      return 1;
    }
  } else {
    std::cerr << "\nusage: " << argv[0] << "  <read_file> <output_file>\n"
              << std::endl;
    return 1;
  }

  std::size_t total_reads = 0;

  // parse input fastq file
  auto read2fqs = parse_fastq_file(input_file, total_reads);

  auto newfqs = count_frequencies_and_merge_qualities(read2fqs);
  sort(newfqs.begin(), newfqs.end(), sort_by_freq_quality);

  for (auto& out_entry : newfqs) {
    output_file << out_entry.first;
  }

  std::cout << "Total reads parsed: " << total_reads << std::endl;
  std::cout << "Number of different collapsed reads: " << read2fqs.size()
            << std::endl;

  return 0;
}

// first sort by frequency, then by cumulative quality and finally by sequence
bool sort_by_freq_quality(std::pair<FASTQentry, int> fq1,
                          std::pair<FASTQentry, int> fq2) {
  if (fq1.second != fq2.second) {
    return fq1.second > fq2.second;
  } else {
    // cumulative sum of quality
    auto s1 = 0.;
    auto s2 = 0.;
    for (auto i = 0ul; i < fq1.first.probas.size(); ++i) {
      s1 += fq1.first.probas[i];
    }
    for (auto i = 0ul; i < fq2.first.probas.size(); ++i) {
      s2 += fq2.first.probas[i];
    }
    if (s1 != s2){
      return s1 > s2;
    }
    return fq1.first.sequence > fq2.first.sequence;
  }
}

std::vector<double> qualities_to_probabilities(const std::string& quals) {
  std::vector<double> result;
  result.reserve(quals.size());
  for (auto& q : quals) {
    result.push_back(std::pow(10, (q - 33) / -10));
  }
  return result;
}

std::string probabilities_to_qualities(const std::vector<double>& probas) {
  std::string result;
  result.reserve(probas.size());
  for (auto& p : probas) {
    result.push_back(-10 * std::log10(p) + 33);
  }
  return result;
}

std::istream& operator>>(std::istream& is, FASTQentry& fq_entry) {
  std::string quals;
  is >> fq_entry.header >> fq_entry.sequence >> fq_entry.plus >> quals;
  fq_entry.probas = qualities_to_probabilities(quals);
  return is;
}

std::ostream& operator<<(std::ostream& o, const FASTQentry& fq_entry) {
  o << fq_entry.header << std::endl;
  o << fq_entry.sequence << std::endl;
  o << fq_entry.plus << std::endl;
  auto quals = probabilities_to_qualities(fq_entry.probas);
  o << quals << std::endl;
  return o;
}

std::map<std::string, std::vector<FASTQentry>> parse_fastq_file(
    std::ifstream& infile, std::size_t& total_reads) {
  std::map<std::string, std::vector<FASTQentry>> read2fqs;

  while (!infile.eof()) {
    FASTQentry fq;
    infile >> fq;
    read2fqs[fq.sequence].push_back(fq);
    ++total_reads;
  }
  return read2fqs;
}

std::vector<std::pair<FASTQentry, int>> count_frequencies_and_merge_qualities(
    std::map<std::string, std::vector<FASTQentry>> read2fqs) {
  std::vector<std::pair<FASTQentry, int>> newfqs;

  int counter = 1;
  // iterate over same reads
  for (auto it = read2fqs.begin(); it != read2fqs.end(); ++it) {
    FASTQentry newfq;
    auto freq = it->second.size();
    newfq.header =
        "@seq_" + std::to_string(counter) + "_x" + std::to_string(freq);
    newfq.plus = "+";
    newfq.sequence = it->first;
    std::vector<double> mean_probas(it->first.length(), 0);

    // iterate over entries belonging to the same sequence
    for (auto& fq_entry : it->second) {
      // sum up qualities at same positions
      for (std::size_t c = 0; c < mean_probas.size(); ++c) {
        mean_probas[c] += fq_entry.probas[c];
      }
    }

    // compute mean of qualities
    for (auto c = 0ul; c < mean_probas.size(); ++c) {
      mean_probas[c] /= freq;
    }

    newfq.probas = mean_probas;
    newfqs.emplace_back(newfq, freq);
    ++counter;
  }

  return newfqs;
}
