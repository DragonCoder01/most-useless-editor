# The most feature-rich, most useless Editor...

... is still under development. duh.

# User interface

You only need two keys: `1` and `0`. You'll need to enter the ASCII representation of the character. To quit the editor, we took inspiration from `vim`. You just need to type: `ESC:qw`. Good luck exiting the program.

# Contributing

To contribute to this amazing project, please follow the following rules:
 - If the feature introduces "usefullness", please consider rewriting it so it isn't usefull anymore.
 - Please create your own branch.
 - Please commit before 1AM.

# Building

This project uses `C++`. We use `cmake` to compile it. Here is an example how compiling the program would look like:

```
mkdir build
cd build
cmake ..
cmake --build .
```

The resulting binary is located in the `bin` folder.