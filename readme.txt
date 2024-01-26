Tic-Tac-Toe

About: A terminal-based Tic-Tac-Toe game with a roughly made AI opponent. No
special algorithms were used for making the AI. Instead, the whole project 
was an attempt at finding my own algorithms and gaining experience in C++.
Of course, this didn't lead to the most efficient code but it was a great
exercise in problem-solving and code reusability

How the AI works: It checks the board to decide its next move, based on the
following conditions (in this order): 
1)if it can win in one move
2)if the player is about to win and how to prevent it
3)if it can win in two moves, choose one of the two randomly
4)if none of the above applies, play a random move
These are checked by manually iterating through each line, column and diagonal,
to know what moves are already made on them

