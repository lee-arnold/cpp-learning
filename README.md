# Learning CPP

## Resources

- https://www.learncpp.com

## Setup

Have Homebrew and Git installed.
This project requires CMake 3.28 or newer and a C++23-capable compiler and standard
library. Install CMake, Ninja and LLVM (including Clang and clang-tidy):

```bash
brew install cmake ninja llvm
```

### macOS

Install Apple's CLI Tools if they are not already installed:

```bash
xcode-select --install
```

Put Homebrew LLVM on your PATH:

```fish
fish_add_path (brew --prefix llvm)/bin
```

### Ubuntu / WSL

Install the native development packages needed by SFML's graphics and window
modules:

```bash
sudo apt update
sudo apt install libx11-dev libxrandr-dev libxcursor-dev libxi-dev \
    libudev-dev libgl1-mesa-dev libegl1-mesa-dev \
    libfreetype-dev libharfbuzz-dev
```

Running a graphical window under WSL requires a working graphical environment,
such as WSLg.

### Optional Neovim setup

These editor settings are not required to build or run the application:

- Install the `clangd` LSP via Mason.
- Add `cpp` to Neovim Treesitter's `ensure_installed` table.

## Running

Configure the project after cloning it:

```bash
cmake --preset dev
```

Then build and run the application:

```bash
./run
```

After the initial configuration, `./run` will rebuild the executable using
CMake and automatically run it.
