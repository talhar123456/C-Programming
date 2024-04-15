#include <istream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

class FASTQentry {
 public:
  FASTQentry() = default;
  FASTQentry(const std::string& hdr, const std::string& seq,
             const std::string& plus, const std::vector<double>& probs) {
    header = hdr;
    sequence = seq;
    this->plus = plus;
    probas = probs;
  }

  std::string header;
  std::string sequence;
  std::string plus;
  std::vector<double> probas;

  friend std::ostream& operator<<(std::ostream& o, const FASTQentry& fq_entry);
  friend std::istream& operator>>(std::istream& is, FASTQentry& fq_entry);
};
