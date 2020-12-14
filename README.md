# Shells
This is my attempt at learning some systems level programming.

Essentially, I'll be creating UNIX shells in 3 languages:
- C++
- Ruby
- Rust

While my gaol is to get some low-level code going, I'm also trying to add some additional functionality.


## C++

### Running shell in C++
- `cd cshell`
- Compiling
  - `make clean`
    - This ensures that we don't have any stray executable files (beware of the `-rf` flag)
  - `make`
    - This uses the Makefile to compile our lex file, Bison file and run the g++ C++ compiler and creating the executable (called `shell`)
  - `./shell`
  - This command runs the executable file (`shell`) created in the previous command
