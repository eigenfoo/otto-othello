# Othello/Reversi Artificial Intelligence

An Othello/Reversi game with an AI that searches the game tree using a minimax
search with alpha-beta pruning.

## Requirements
* A terminal with 
  - Unicode support
  - xterm-256-color code support

## Installation and Usage
Using git:

```
$ git clone https://github.com/eigenfoo/othello.git
$ cd othello
$ make
$ make run
```

Alternatively, you can download the .zip file from
[my GitHub repository](https://github.com/eigenfoo/othello) and compile it
manually using your preferred C++ compiler.

Note that the included Makefile makes use of the `-03` and `-march=native`
flags. This has not caused problems. However, if you experience any bugs, please
remove these flags from line 4 of the Makefile, then `make clean`, `make` and
re-`make run`.

## Details

### Save Files
You can load a saved board at the start of a game. The first 8 rows of the save
file represent the state of the board. The spacing _is_ important: each line
must begin with a space, each number must be separated by a single space, and
there must not be a trailing space. 0, 1, and 2 represent an emtpy square, a
black disc, and a white disc, respectively. The numbers in the final two rows
represent whose turn it is (black or white), and the time limit (for any turn
played by the computer). Two example board text files are included under the
`test/` directory.
