# Shells
This is my attempt at learning some systems level programming.

Essentially, I'll be creating UNIX shells in 3 languages:
- C
- Ruby
- Rust

While my gaol is to get some low-level code going, I'm also trying to add some additional functionality.


## C

### Running shell in C
- `cd cshell`
- Compiling
  - `make`
    - This uses a `Makefile` to compile all `.c` files in the directory and create an executable named `shell` 
  - Alternatively you can complile the files yourself with `gcc *.c -o shell`
    - This command compiles all `.c` files in the directory and creates an executable file: `shell`
- `./shell`
  - This command runs the executable file (`shell`) created in the previous command
