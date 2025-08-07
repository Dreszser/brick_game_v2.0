# Brick Game v2.0

Educational project: an interactive version of Tetris (in C) and Snake (in C++), supporting both a Qt desktop interface and an Ncurses command-line interface.

## About

This project consists of four separate modules and broadly follows the MVC pattern. Two modules serve as backend game libraries(one in C, the other in C++), and two as frontends(one in C using Ncurses, the other in C++ using Qt). The `lib_specification.h` file acts as a thin controller for Snake and a thick controller for Tetris. Both interfaces interact exclusively with this file and its defined functions and structures. No other backend components are directly accessed from the frontend.

You can observe the architectural progress made since the Tetris implementation. While not much was changed structurally, the project is now significantly more organized. For example, both interfaces now share a single `main` file - a much cleaner approach compared to the original vision where each game variant had its own `main`.

## Installation

**Note:** Only macOS is officially supported (other platforms untested).

You'll need the Ncurses and Qt libraries. To install dependencies on macOS using Homebrew:

```bash
brew install ncurses
```
Qt can be installed from the official website or you can use Qt Creator:

```https://doc.qt.io/qt-6/macos.html```

Qt part of the project is bult using CMake:

```brew install cmake```

To build the full project: 
- ```make install```

Four executables will be placed in the Brick_Game folder (outside of the src directory).

For partial builds, you can use one of the following targets:
- ```make tetric_cli``` builds only the CLI version of Tetris (requires Ncurses)
- ```make snake_cli``` builds only the CLI version of Snake (requires Ncurses)

## Controls

- `Arrow keys` - to control the tetrominoe or snake
- `Spacebar` to rotate(tetris) or speed up(snake)
- `P` or `p` button to pause and unpause
- `Enter` to start the game and restart after gameover
- `Escape` to close the game

## Tests

Both games have unit-tests and coverage reports. Only backend libraries are covered by this tests.
To build and run tests:
- ```make test```
- ```make run_tests```

## Documentation

Project supports `Doxygen` documentation.
To create html documentation:
- ```make dvi```

On MacOS it opens automatically, on other platforms open file `docs/html/index.html`

## Uninstall
- To uninstall game and clean all the unneccessary files
  ```Shell
  make uninstall
  ```
- To remove high score file
  ```Shell
  make clean_record
  ```
