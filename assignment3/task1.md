1. What is the difference between the keywords typedef and using? Also, state
one usage example for both. 

Ans. typedef is a keyword for creating type aliases in c++, while using is more versatile and can also be used for defining aliases, especially for function pointers and template aliases. eg. typedef int IntAlias; vs. using IntAlias = int;

2. What are iterators? Name at least 3 different types of iterators and explain
their functionalities.

Ans. iterators are objects that allow the traversal of containers. Three types are: 
input iterators: Read and process values once.
forward iterators: Move forward in a sequence.
random-access iterators: Support accessing elements in any order.
 

3. What is a crucial difference between an input and a forward iterator?

Ans. an input iterator can only be dereferenced once, and the result is undefined if you attempt to use it again, whereas a forward iterator allows multiple dereferencings.

4. Why are iterators to a std::vector invalided by insert, push_back or erase?

Ans. cause these operations may reallocate memory, causing iterators to be invalidated.

5. Which container would you choose and why if
a) you need to do sorted traversal and no duplicates are allowed
b) the order is not important and no duplicates are allowed 
c) you only need to add elements at the end and want fast traversal
d) you need to provide a dictionary that can associate multiple values with
the same key 

Ans. 
a. std::set: Sorted traversal, no duplicates.
a. std::unordered_set: No order requirement, no duplicates.
a. std::vector: Adding elements at the end, fast traversal.
a. std::multimap: Associates multiple values with the same key.

6. How does an STL algorithm usually indicate "not found" or "failure"? 

Ans. stl algorithms typically use a return value or an iterator equal to the end iterator to indicate "not found" or "failure."

7. What does std::sort(b,e) use as its sorting criterion?

Ans. it uses the less-than (operator<) criterion for sorting.

8. Why is the STL container set missing a [] (subscript) operator? 

Ans. lacks a [] operator because it ensures unique keys, and using [] could violate that uniqueness constraint.

9. Why does std::map require its key_type to be copy-constructible and its
mapped_type to be default constructible? 

Ans. std::map requires its key type to be copy-constructible for sorting, and mapped type to be default constructible for creating default values.

10. Why is std::forward_list missing a size member function and why is the
empty member-function still implemented if it is typically equal to container.size() == 0?

Ans. std::forward_list lacks a size member function for efficiency reasons, and the empty function is still implemented for consistency, even though it's equivalent to container.size() == 0.