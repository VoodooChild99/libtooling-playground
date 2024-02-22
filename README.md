# LibTooling Playground

Ready-to-use environment that makes it easy to develop LibTooling-based tools, inspired by [clang-tutor](https://github.com/banach-space/clang-tutor).

## How to use

- Add new tools to [src](./src) and modify `CMakeFiles.txt` accordingly.

- To build tools, run `cmake-config.sh` first, then `cd build && make`. `CMAKE_BUILD_TYPE` is set to `RelWithDebInfo` by default.

- To use different LLVM/Clang versions, set the env var `LLVM_CONFIG` before you run `cmake-config.sh`,
e.g., `LLVM_CONFIG=llvm-config-15 ./cmake-config.sh` if you want to use LLVM-15/clang-15. By default,
`llvm-config` is used.

- It is recommended to install the tools with `sudo make install`, so that the tools can find builtin headers (see [this](https://clang.llvm.org/docs/LibTooling.html#builtin-includes)). Tools are installed to the LLVM binary directory by default (`$LLVM_CONFIG --bindir`). Symbolic links to the installed tools will be created under `build/scripts`, so that you can easily use the tools. You can run `sudo make uninstall` later to uninstall these tools and remove the symbolic links.