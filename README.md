In this repo you'll find two data structures, a **hash table** and a **linked list**.
# Tests and makefiles
The following files can be created using make

| Command          | Outfile          | Description                                                                                                                 |
| ---------------- | ---------------- | --------------------------------------------------------------------------------------------------------------------------- |
| make ht_coverage | ht_coverage.html | Compiles hash_table.c with its tests and runs gcovr on it. This produces a html coverage report.                            |
| make ll_coverage | ll_coverage.html | Compiles linked_list.c with its tests and runs gcovr on it. This produces a html coverage report.                           |
| make freq        | freq             | Compiles an example program that uses the hash table to count the frequency of words in text files. Usage: freq file1 file2 |
| make clean       | n/a              | cleans the directory from coverage files.                                                                                   |
# Hash Table
Generic hash table implementation in C using a union datatype *elem_t* as keys and values. The hashtable supports different types of values and keys using user supplied hash and equality functions. 

The implementation uses a linked list to handle collisions and provides an iterator for traversing stored entries.
### Features
- Generic keys and values using *elem_t*
- User supplied hash functions
- User supplied equality functions
- Linked list for collision handling
- Insert, lookup, remove, and key existence operations
- Hash table size
- Empty queries
- Iterator
- Built in hash functions for integers and strings.
- Built in equality functions for integers, strings, booleans and floats
### Datatypes
The hash table uses the following `elem_t` union to store keys and values:

```
union elem
{
    int i;
    unsigned int u;
    bool b;
    float f;
    void *p;
    char *s;
};
```

The following helper macros can be used to create elem_t objects:

```
int_elem(x)
bool_elem(x)
ptr_elem(x)
string_elem(x)
```

###### Example:

`ioopm_hash_table_insert(ht, string_elem("hello"), int_elem(42));`

The hash table itself does not know what type an elem_t contains. The appropriate hash and equality functions must be supplied by the user when the table is created.

### Creating a hash table and basic operations

Use the following function to create a hash table: 

`ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn);

This will return a pointer to the hash table. As previously mentioned the user has to provide appropriate hash and equality functions. There are however some built in provided for your convenience. 

**The hash_table.h file contains definitions and documentation for the rest of the functions.**

There is also an iterator provdid which can traverse the table and return current key and value. You create the iterator using:

`ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht);`

which will return a pointer to an iterator.

**The hash_table_iterator.h file contains definitions and documentation for the rest of the iterator functions**
### Built in hash and equality funtions
###### Integer hashing
`size_t ioopm_hash_int(elem_t key)`
Hashes the integer stored in key.i.

###### String hashing
`size_t ioopm_hash_string(elem_t key)`
Hashes the string stored in key.s

###### Equality functions
```
bool ioopm_int_comp(elem_t a, elem_t b);  
bool ioopm_string_comp(elem_t a, elem_t b); 
bool ioopm_bool_comp(elem_t a, elem_t b);  
bool ioopm_float_comp(elem_t a, elem_t b);
```

### Error handling and undefined behaviour

There is no error handling.
However there is some undefiend behaviour and restrictions: 

- Advancing the iterator past the end of the hash table will result in a segmentation fault (instead of staying at the last element)
- You may **NOT** change the hash_table while iterating over it. This will break the iterator. You will need to create a new iterator for each unique hash table. So if you insert a new key, value pair you will need to create a new iterator.
- `ioopm_hash_table_print()` is specialized for string keys and integer values.
- Pointer and string memory referenced by `elem_t` is not automatically freed by the hash table.
- Inserting a new key, value pair into the hash table where the key already exists it will replace the value of that key instead of inserting a new one. 
### Memory handling

Each inserted entry is dynamically allocated using `calloc()`.

Destroying the hash table frees:

1. Every dynamically allocated entry.
2. The hash table itself.

The hash table stores `elem_t` values directly. It does **not** make copies of memory referenced by pointers such as `char *s` or `void *p`.

This means that the caller is responsible for both maintaining the pointers and also freeing their memory. 

# Linked List
Generic linked list implementation in c. This data structure also uses the union datatype elem_t in order to support using different types of elements. Using different types of elements in the same list at the same time is also supported. 

### Features
- Insert, lookup and remove, operations in O(n) time
- Append, prepend, head and last operations in O(1) time
- Iterator that supports modifying the underlying list whilst iterating using iterator insert and remove operations in O(1) time.


### Datatypes
The linked list uses the following `elem_t` union to store keys and values:

```
union elem
{
    int i;
    unsigned int u;
    bool b;
    float f;
    void *p;
    char *s;
};
```

The following helper macros can be used to create elem_t objects:

```
int_elem(x)
bool_elem(x)
ptr_elem(x)
string_elem(x)
```

### Creating a linked list and basic operations

To create a linked list:
`ioopm_list_t *ioopm_list_create(void);` 
which returns a pointer to an empty list. 

**The rest of the function definitions and documentation is proivded in the linked_list.h file.**

### Error handling and undefined behaviour
There is almost no error handling with one exception:
- If you try to remove anything from an empty list, the function will print out a string saying that the list is empty and return the value -99.

Other considerations:
- Advancing the iterator beyond the end of the list will result in a segmentation fault.
- The list does not save copies of pointers or strings but stores the pointers directly. The user is responsible for maintaining and freeing heap allocated memory.

### Memory handling
Similarly to the hash table:

Each inserted entry is dynamically allocated using `calloc()`.

Destroying the linked list frees:

1. Every dynamically allocated entry.
2. The hash table itself.

The linkes list stores `elem_t` values directly. It does **not** make copies of memory referenced by pointers such as `char *s` or `void *p`.

This means that the caller is responsible for both maintaining the pointers and also freeing their memory. 
