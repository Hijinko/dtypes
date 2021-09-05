[![version](https://img.shields.io/badge/version-1.2-yellow.svg)](https://semver.org)

# dtypes
A repository of different data types that are not standard in the C library i.e. Lists, Trees, Graphs etc.

## Implemented Data Types
- [x] list
- [x] stack
- [x] queu
- [x] set
- [ ] tree
- [ ] trie
- [ ] hashtble
- [ ] graph
- [ ] heap

## Make Commands
### Run Unit Tests
```
make check
```
### Run Unit Tests and Check for Memory Leaks
```
make valgrind
```
### Create the Library to Link to
```
make
```
### Compile With Debug Symbols
```
make debug
```
### Delete All the Object Files in the Repository
```
make clean
```

## Usage
First compile the library using the make command above. Then link your program with the bin/libtype.a file.
