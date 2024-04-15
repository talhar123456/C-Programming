#include <string>

struct FASTAentry {
  FASTAentry() : header(), sequence(){};
  FASTAentry(std::string hdr, std::string seq) {
    header = hdr;
    sequence = seq;
  }

  std::string header;
  std::string sequence;
};
