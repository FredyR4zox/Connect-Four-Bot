# IA-Project-2
Second project of the subject Artificial Inteligence, which consisted in developing a bot to play the Connect Four Game using adversarial search.
Our implementation was in C++.


### Search functions implemented
* Minimax
* Alpha-Beta prunning


### Compilation
``` bash
$ g++ -O3 main.cpp -o main
```

### Usage
The usage of this project is intuitive. It's instructions appear when the program is executed.


### Files
* main.cpp - Requests input and calls the search functions
* Node.h - Implementation of the graph node's
* Config.h 	- Implementation of the game board and functions to work with the board
* Minimax.h - Implementation of the Minimax algorithm
* Alphabeta.h - Implementation of the Alpha-Beta Pruning algorithm


### Change the maximum depth
The maximum depth that the search functions DFS, BFS, A* and Greedy have is 80 by default.
To change this value go to the file "SearchMethods.h" and change the value of the constant MAX_DEPTH on the beginning of the file.


### Authors
* Ana Rita Santos Lopes da Costa - up201605706 - [ritasantos11](https://www.github.com/ritasantos11)
* Frederico Emanuel Almeida Lopes - up201604674 - [FredyR4zox](https://www.github.com/FredyR4zox)
* João Lucas Faria de Pires - up201606617 - [iSynthx](https://www.github.com/iSynthx)
