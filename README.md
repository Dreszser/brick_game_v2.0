# Brick Game v2.0

Educational project, interactive version of Tetris in C language and Snake in C++, supports Qt desktop interface and Ncurses command-line interface.

## Installation

- MacOS is supported, did not test on other platforms

You will need ncurses library, and Qt libraries installed to run the game, to install on MacOS using ```brew```:
```Shell
brew install ncurses
```
Qt can be installed from the official website or you can use Qt Creator:
```https://doc.qt.io/qt-6/macos.html```

For full installation run ```make install```, four executable files will be located in the Brick_Game folder outside of ```src```.

If you want partial installation, you can run one of the following make targets:
- ```make tetric_cli``` will create executable only for cli version of tetris(requires ncurses)
- ```make snake_cli``` will create executable only for cli version of snake(requires ncurses)

## Controls

- Arrow keys(left, right, down, up) to control the tetrominoe or snake
- Spacebar to rotate(tetris) or speed up(snake)
- 'P' or 'p' button to pause and unpause
- Enter to start the game and restart after gameover
- Escape to close the game

## Uninstall
- To uninstall game and clean all the unneccessary files
  ```Shell
  make uninstall
  ```
- To remove high score file
  ```Shell
  make clean_record
  ```
