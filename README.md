# Learning CPP

## Resources

- https://www.learncpp.com

## Setup

- This repo contains an example of how to set up your environment
- Install CMake, Ninja and LLVM:

  ```bash
  brew install cmake ninja llvm
  ```

- Ensure the `clangd` LSP is installed via Mason
- Ensure `cpp` is added to Neovim Treesitter `ensure_installed` table

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
