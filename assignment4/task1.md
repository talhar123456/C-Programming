1. Why is it dangerous to return a reference when you must return an object?

Ans. because the local variable is destroyed after the function returns, leaving the reference dangling and causing undefined beahaviour.

2. What is an implicit interface in the context of compile-time polymorphism?

Ans. An implicit interface refers to the set of methods that a class must support based on how it's used in code, promoting flexibility in polymorphic behavior without explicit declarations.

3. Why should you prefer range member functions to their single-element counterparts? 

Ans. Range member functions, like std::for_each and std::transform, offer a concise and expressive way to apply operations to entire ranges, enhancing code readability and reducing boilerplate.

4. Why should you avoid in-place modification of keys in a set?

Ans. In-place modification of keys in a set can break the set's ordering, leading to incorrect sorting and compromising the integrity of the data structure.

5. Why should predicate functions be pure? 

Ans. Pure predicate functions, devoid of side effects, enhance the predictability of algorithms, making them more reliable.

6. Why should you avoid the default capture modes of lamdbas? 

Ans. Default capture modes in lambdas might unintentionally capture variables by reference, potentially causing issues. Explicitly specifying captures improves clarity and avoids unintended behavior.

7. What do std::move and std::forward do? 

Ans. std::move converts an object into an rvalue, facilitating efficient transfer of resources, while std::forward is used in template functions to maintain the original value category (lvalue or rvalue) of forwarded arguments.

8. How are the strings of a std::set<std::string*> sorted? How you would make them sorted lexicographically? Provide the necessary code. 

Ans. Strings in std::set<std::string*> are sorted based on the pointers' addresses, not the lexicographical order of the strings themselves. To sort them lexicographically, we can use a custom comparator that compares the strings like this:

#include <set>
#include <string>
struct CompareStrings {
    bool operator()(const std::string* a, const std::string* b) const {
        return *a < *b;
    }
};
int main() {
    std::set<std::string*, CompareStrings> mySet;
    // Add strings to the set
    return 0;
}
