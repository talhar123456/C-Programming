#include <iostream>
#include <vector>

unsigned int get_max(unsigned int a, unsigned int b) {
  return a > b ? a : b;
}

int main() {
  std::vector<unsigned int> v(10000, 0);
  v[9999] = 1000u;

  auto max = 0u;
  for(auto e : v){
    max = get_max(max, e);
  }
  std::cout << "Maximum: " << max << std::endl;
  return 0;
}

// Explanation
/* In this code get_max function returns a reference 
to a local variable 'c', which is problem because 
it goes out of scope when the function is returned. */