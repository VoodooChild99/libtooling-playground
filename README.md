# LibTooling Playground

Ready-to-use environment that makes it easy to develop LibTooling-based tools, inspired by [clang-tutor](https://github.com/banach-space/clang-tutor).

## How to use

- Add new tools to [src](./src) and modify `CMakeFiles.txt` accordingly.

- To build tools, run `cmake-config.sh` first, then `cd build && make`. `CMAKE_BUILD_TYPE` is set to `RelWithDebInfo` by default.

- To use different LLVM/Clang versions, set the env var `LLVM_CONFIG` before you run `cmake-config.sh`,
e.g., `LLVM_CONFIG=llvm-config-15 ./cmake-config.sh` if you want to use LLVM-15/clang-15. By default,
`llvm-config` is used.
