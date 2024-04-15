#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "bad_read_collapser.hpp"

// clang-format off
// This programm expects a fasta file as input containing small NGS reads (first argument). The second argument is the name of the output fasta file.
// Since many reads occur multiple times, this programm "collapses" the reads, such that downstream tools can work with a much smaller fasta file.
// Collapsing means: if the exact same sequence occurs Z times in the fasta file, we generate a new fasta header for this sequence by adding the
// number of occurrences like this: >seq_12345_xZ
// The new unique sequences can be just given incremental numbers in the header, e.g. seq_1, seq_2, .... to be uniquely identifiable
// The output is the new collapsed fasta file with reads sorted according to their frequency (highest frequencies first), length, and last alphabetically.
// The collapser should also be able to work with already (partially) collapsed input files, meaning we have to check if the fasta header ends with _xZ, and then
// handle this accordingly.
// clang-format on

bool sort_by_length_frequency(const std::pair<std::string, std::size_t>,
                              const std::pair<std::string, std::size_t>);

std::map<std::string, std::size_t>& parse_fasta_file(std::ifstream& infile,
                                                     std::size_t reads);

int main(int argc, char* argv[]) {
  std::ofstream output_file;
  std::ifstream input_file;

  if (argc == 3) {
    output_file.open(argv[2]);
    if (!output_file) {
      std::cerr << "cannot open output file: " << argv[2] << std::endl;
      return 1;
    }
    input_file.open(argv[1]);
    if (!input_file) {
      std::cerr << "cannot open input file: " << argv[1] << std::endl;
      return 1;
    }
  } else {
    std::cerr << "\nusage: " << argv[0] << "  <read_file> <output_file>\n"
              << std::endl;
    return 1;
  }

  std::size_t total_reads = 0;
  // parse input fasta file
  auto read2freq = parse_fasta_file(input_file, total_reads);

  // sort reads by frequency
  std::vector<std::pair<std::string, std::size_t>> freq2read;
  for (auto it = read2freq.begin(); it != read2freq.end(); ++it) {
    auto entry = std::make_pair(it->first, it->second);
    freq2read.push_back(entry);
  }
  std::sort(freq2read.begin(), freq2read.end(), sort_by_length_frequency);

  // output result
  int counter = 1;
  for (auto it = freq2read.begin(); it != freq2read.end(); ++it) {
    output_file << ">seq_" << counter << "_x" << it->second << "\n"
                << it->first << "\n";
    ++counter;
  }

  std::cout << "Total reads parsed: " << total_reads << std::endl;
  std::cout << "Number of different collapsed reads: " << read2freq.size()
            << std::endl;

  return 0;
}

// sort by frequency, then length, then alphabetically
bool sort_by_length_frequency(
    const std::pair<std::string, std::size_t> sequence1,
    const std::pair<std::string, std::size_t> sequence2) {
  if (sequence1.second != sequence2.second) {
    return sequence1.second > sequence2.second;
  } else {
    if (sequence1.first.length() != sequence2.first.length()) {
      return sequence1.first.length() > sequence2.first.length();
    } else {
      return sequence1.first > sequence2.first;
    }
  }
}

std::map<std::string, std::size_t>& parse_fasta_file(std::ifstream& infile,
                                                     std::size_t total_reads) {
  std::map<std::string, std::size_t> read2freq;
  std::string current, header, sequence;

  while (std::getline(infile, current)) {
    if (current.find(">") != std::string::npos)  // new header
    {
      if (header != "" && sequence != "")  // save previous entry
      {
        FASTAentry fa(header, sequence);

        if (fa.header.find("_x") !=
            std::string::npos)  // we have a collapsed read
        {
          // get the frequency
          int freq = std::stoi(
              fa.header.substr(fa.header.find("_x") + 2, std::string::npos));

          read2freq[fa.sequence] += freq;
          total_reads += freq;
        } else {
          ++read2freq[fa.sequence];
          ++total_reads;
        }
      }
      // ready for next entry
      header = current;
      sequence = "";
    } else {
      sequence += current;
    }
  }
  // handle last entry
  if (header != "" && sequence != "") {
    FASTAentry fa(header, sequence);
    if (fa.header.find("_x") != std::string::npos)  // we have a collapsed read
    {
      // get the frequency
      int freq = std::stoi(
          fa.header.substr(fa.header.find("_x") + 2, std::string::npos));

      read2freq[fa.sequence] += freq;
      total_reads += freq;
    } else {
      ++read2freq[fa.sequence];
      ++total_reads;
    }
  }

  return read2freq;
}
