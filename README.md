209294768 sagitmalk10@gmail.com
# K-ary Tree

This project is an implementation of a container representing a k-ary tree. The tree is generic, such that it contains keys of any type (e.g numbers, strings and classes). The dipole state of the tree is a binary tree (i.e k=2).
## Features

- **Iterators**:
  - In-order
  - Post-Order
  - Pre-Order
  - MyHeap
  - BFS scan
  - DFS scan



## Usage
### Crate a binary- tree of ints
```ruby
Tree<int> tree;
```
### Crate a 3-ary- tree of ints
```ruby
Tree<int, 3> tree;
```

### Printing all traversals
```ruby
std::cout << tree << std::endl;
```
### Heapfy tree
```ruby
tree.myHeap();
```
![p](https://github.com/SagitMalka/KaryTree/assets/118733667/cd950530-44bd-4f2e-aa74-173ed42199da)


## License
MIT
## Acknowledgements
- [Doctest](https://github.com/doctest/doctest) for unit testing.
