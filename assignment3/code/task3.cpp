#include "cxxopts.hpp"

int main(int argc, char* argv[]) {
  cxxopts::Options options("MyProgram", "One line description of MyProgram");
  options.add_options()
  ("i", "case insensitive", cxxopts::value<bool>())
  ("input", "input files", cxxopts::value<std::vector<std::string>>());

  options.parse_positional({"input"});
  auto result = options.parse(argc, argv);

  if(result["i"].as<bool>()){
    std::cout << "case insensitive" << std::endl;
  }

  for(auto& e : result["input"].as<std::vector<std::string>>()){
    std::cout << e << ' ';
  }
  std::cout << std::endl;
  return 0;
}
