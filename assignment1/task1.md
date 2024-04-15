1. List 8 built-in types provided by C++.
A. int, double, char, bool, float, long, short, unsigned int.

2. What is the difference between an expression and a statement? Provide an example for each.
A. expression return a value while statement does not return a value. Eg. int sum = a + b; this is an expression it returns the sum. while int a = 5; this is a statement it declares that x is a integer with value 5.

3. What is type safety and why is it important?
A. a property that ensures that operations performed on data of the correct types. compiler can catch type related errors at compile time.

4. When would a programmer prefer a switch-statement over an if-statement?
A. when there are too many cases so it makes sense to use switch-case as compare to if-statement. furthermore if-statement might be suitable to deal with complex logical conditions.

5. What is a common problem with switch statements? Provide an example.
A. a common problem with switch case is lack of flexibility in hadling complex conditions. this limitation can lead to code duplication.

6. Name one operation available for strings but not for integers and one operation available for integers but not for strings.
A. operation for string is cincatenation and operation for integer is division.

7. Explain what are references and pointers. Provide examples for each. 
A. a reference is an alternative name for an existing variable. it provides a directi connection to variable's location and allows direct modification of original value. 
Eg. 
int num = 10;
int& ref = num;
ref = 90; //modifying num

 a pointer is a variable that stores the memery address of another variable. it points to the location where actual data is stored.
 Eg. 
 int num = 10;
 int* p = &num; //pointer to num

 Arithmetic operations like addition and subtraction can be performed on pointer values, while references do not support arithmetic operations.

8. Explain the relationship between pointers and arrays (and C-strings). Provide examples.
A. pointes and arrays are closely related data structures that provide indirect access to memory locations.

Arrays: a collection of the same data type stored in contiguous memory locations. each element has a index starting from zero. arrays are declared using [].

pointers: A pointer is a variable that stores the memory address of another variable. It points to the location where the actual data is stored. Pointers are declared using the asterisk '*'.

9. Explain the pass by value and pass by reference concepts. Provide examples.
A. Pass by value: a copy of the actual value of the arguement is created and passed to the function. any modifications made to the parameter within the function do not affect the original value.
Eg.
void swap(int a, int b) {
  int temp = a;
  a = b;
  b = temp;
}

int main() {
  int x = 1, y = 2;
  swap(x, y); // Passing values by copy
  std::cout << "x: " << x << ", y: " << y << std::endl; // Output: x: 1, y: 2
}

Pass be reference: a reference to the actual memory location of the argument is passed to the function. Any modifications made to the parameter within the function directly affect the original value in the calling function. 
Eg. 
void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int main() {
  int x = 1, y = 2;
  swap(x, y); // Passing references
  std::cout << "x: " << x << ", y: " << y << std::endl; // Output: x: 2, y: 1
}

10. Explain the terms declaration and definition.
A. declaration: to declare a variable means to give it's data type and name but it does not allocate memory.

definition: provides an implementaion for an identifier declared earlier. it allocates memory for the identifier and assigns an initial value.

11. What is a namespace and what is its typical use?
A.  a method used for organizing code and preventing naming conflicts.

12. Why should you avoid using directives in a header? 
A. it can lead to naming conflicts when the header is included in multiple files. this is because the contents of the header are essentially copied into each  source file that includes it, causes clshes resulting in unexpected behaviour.

13. List four kinds of errors and provide an example for each.
A. Syntax error:
Eg.
int x = 10
logic error
Eg.
int sum(int a, int b) {
    return a - b;
    // Incorrect subtraction instead of addition
}
runtime error:
Eg.
int arr[5];
cout << arr[10];
// Accessing an element outside the bounds of the array
Semantic errors
Eg.
double calculateArea(double radius) {
    return 3.14 * radius * radius * radius;
    // Incorrect formula for calculating the area of a circle
}

14. What is the free store and for what reasons might one use it?
A. free store is a memory region that is managed dynamically by the program. it is used to allocate memory for objects that are created during the execution of the program. also known as heap.

15. How do you allocate memory and about what do you need to be careful? Provide an example.
A. a process of requesting and obtaining memory from the operating system for use by a program. it's crucial to manage memory properly to avoid memory leaks and undefined behaviour. smart pointers are smart choice.
Eg. 
int *dynamicInt = new int;

16. How do you safely allocate/manage memory?
A. safely allocating memory involves understanding memory allocation mechanisms, allocating sufficient memory, deallocating unused memory, using appropiate memory management techniques, avoiding memory overwrites, validating memory pointers and etc.

17. What is RAII? 
A. a programming technique that ensures resources are properly accquired and released thriughout object's lifetime. simplify resource management and prevents leaks.
