#ifndef GFF_ENTRY_HPP
#define GFF_ENTRY_HPP

#include <cstdint>

#include <map>
#include <string>

struct GFFEntry {
	std::string seqid;
	std::string source;
	std::string type;
	uint64_t start;
	uint64_t end;
	float score;
	char strand;
	uint8_t phase;
	std::map<std::string, std::string> tags;
};

#endif // GFF_ENTRY_HPP
