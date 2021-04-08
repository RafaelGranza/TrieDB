# TrieDB
NoSQL Trie Based Data Base that stores entities in json format.

It keeps the data in some hiden folder **.TrieDB**.

## Complexity:
As a Trie-based system, the number of items in the database does not interfere with complexity. 
The complexity is always related to the size of the item identifier (**|S|**), usually less than **O(log (n))**.
* Remove: **O( |S| )**
* Insert: **O( |S| )**
* Update: **O( |S| )**
* Get: **O( |S| )**

### To compile the Data Base:
```sh
$ make
```

###### *main.cpp and view.cpp are only for tests*
#### To run the example test:
```sh
$ make
$ g++ popular.cpp -o  popular -O2
$ ./popular
$ g++ view.cpp -o view -O2
$ ./view
```


