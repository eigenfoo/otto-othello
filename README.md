# Othello/Reversi Artificial Intelligence

An Othello/Reversi game with an AI that searches the game tree using a minimax
search with alpha-beta pruning.

## Requirements
* A terminal that supports
  - Unicode
  - xterm-256-color
* g++ or another C++ compiler
* UNIX `make` utility (recommended, but not required)

## Installation and Usage
Using git:

```
$ git clone https://github.com/eigenfoo/othello.git
$ cd othello
$ make
$ make run
```

Alternatively, you can download the `.zip` file from
[my GitHub repository](https://github.com/eigenfoo/othello) and compile it
manually using your preferred C++ compiler.

## Details

### Save Files
  - There is the option to load a saved board at the start of a game.
  - The first 8 rows of the save file represent the state of the board.
    - _Spacing is important_: each line must begin with a space, each
    number must be separated by a single space, and there must not be any
    trailing spaces.
  - 0, 1, and 2 represent an emtpy square, a black disc, and a white disc,
  respectively.
  - The numbers in the final two rows represent whose turn it is (black or white),
  and the time limit (for any turn played by the computer).
  - Two example board text files are included under the `test/` directory.
