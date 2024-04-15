#include <iostream>
#include <vector>

int main() {
  std::vector<int> v;
  v.reserve(50);

  for (auto i = 0; i < 50; ++i) {
    v.push_back(i);
  }

  for (int i = v.size() - 1; i >= 0; --i) {
    std::cout << i << ": " << v[i] << std::endl;
  }
  return 0;
}

// Explanation
/* used an integer index to iterate through 
the vector, ensuring that the indices 
remain valid. this ensures that the 
correct elements are accessed and printed. */
