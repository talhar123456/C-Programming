1. What is the difference between a struct and a class?
Ans. struct members have default access level of public and class lies in the default access level to private. This means that in a struct, members are acceessible by default.

2. Why should the public interface to a class be as small as possible?
Ans. a minimal interface enhances encapsulation and reduces dependencies. limiting the public interface sheilds the internal implementaion details, promoting easier maintenance, and minimizing the risk of unintended misuse or changes by other part of the program.

3. What is the difference between const and static? Ans. const is a keyword which is used to specify that a variable's value cannot be changed after initialization. on the other hand static can be applied to variables or functions and has diffferent implications.

4. Why should you distinguish between functions that modify objects and those
that do not?
Ans. it is important for clarity and avoiding unexpected side effects. clearly identifying funcitons that modify objects helps in understanding the behaviour of code and prevents unintentional changes to the program called on const objects. it enhances code readbility.

5. What is the concept and effect of inline functions? When would you prefer
inline functions over function calls?
Ans. inline functions are expanded in place during compilation, reducing and overhead of funciton calls. they are preferred in cases where function is short and frequntly called, as this can potentially improve performance by eleiminating the function call overhead.

6. What is a destructor and when is it called? What is the typical consequence
of its usage?
Ans. a destructor is a special member function in c++ that is called when an object goes out of scope or is explicitly deleted. it is responsible for freeing resources, such as memory oe handles, accquired during the object's lifetime.

7. In which context are virtual functions used?
Ans. virtual functions are used in the context of polymorphism and inheritance. they enable dynamic dispatch, allowing the selection of the appropiate function implementaiton at runtime based on the actual type of the object.

8. What is the semantic result of combining the keywords friend and virtual
for a class function? Explain and state reasons for your observations. 
Ans. combining friend and virtual for a class function implies that the function is not a member of the class but has the access to its private members and can be overridden in desired classes. this provides a mechanism for external entities to extend the functionality of a class without being part of it's hierarchy.

9. When would you make a virtual member function pure? 
Ans. a virtual member function is made pure when the base class does not provide a meaningful implementaion, and it is intended to be overridden by desired clsses.

10. What are pitfalls of multiple inheritance?
Ans. multiple inheritance introduces challenges such as the diamond problem, where class inherits from two clsses that have a common ancestor. this can lead to ambiguity in the resolution of inherited members.

11. What is the difference between a concrete class and an interface? 
Ans. a concrete class is a class that provides a complete implementaion for all of it's member functions, while an interface is a class with only pure virtual functions, intended to be implemented by derived classes.
