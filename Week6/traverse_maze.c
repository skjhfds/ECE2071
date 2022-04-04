#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
The program should display the maze after each move so the user can
watch as the maze is solved. As the program runs, it should place an
"x" on each location it has traversed, and an "o" at the current location.
The program should write its output to command window. The output should
be a picture of the maze for each move in the traversal of the maze.
*/
/*
Compile with:
gcc -std=c17 -pedantic -Werror traverse_maze.c -o traverse_maze -lm
*/
#define SIZE 12 // We assume a square maze.
// Function prototypes:

void traverse_maze(char maze[SIZE][SIZE], int x, int y);
void printMaze(char maze[SIZE][SIZE]);

void clrscr()
{
    system("clear");
}
void wait_for(unsigned int secs) {
    unsigned int return_time = time(0) + secs;
    while (time(0) < return_time);
}

int main(void)
{
    // Simple maze
    // char maze[SIZE][SIZE] = {
    //     {'#','#','#','.','#','#','#','#','#','#','#','#'},
    //     {'#','.','.','.','#','.','.','.','.','.','.','#'},
    //     {'.','.','#','.','#','.','#','#','#','#','.','#'},
    //     {'#','#','#','.','#','.','.','.','.','#','.','#'},
    //     {'#','.','.','.','.','#','#','#','.','#','.','#'},
    //     {'#','#','#','#','.','#','.','#','.','#','.','#'},
    //     {'#','.','.','#','.','#','.','#','.','#','.','#'},
    //     {'#','#','.','#','.','#','.','#','.','#','.','#'},
    //     {'#','.','.','.','.','.','.','.','.','#','.','#'},
    //     {'#','#','#','#','#','#','.','#','#','#','.','#'},
    //     {'#','.','.','.','.','.','.','#','.','.','.','#'},
    //     {'#','#','#','#','#','#','#','#','#','#','#','#'}
    // };
    // Complex maze
    char maze[SIZE][SIZE] = {
    {'#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#','.','.','.','#','.','.','.','.','.','.','#'},
    {'.','.','#','.','#','.','#','#','#','#','.','#'},
    {'#','#','#','.','#','.','.','.','.','#','.','#'},
    {'#','.','.','.','.','#','#','#','.','#','.','.'},
    {'#','#','#','#','.','#','.','#','.','#','.','#'},
    {'#','.','.','#','.','#','.','#','.','#','.','#'},
    {'#','#','.','#','.','#','.','#','.','#','.','#'},
    {'#','.','.','.','.','.','.','.','.','#','.','#'},
    {'#','#','#','#','#','#','.','#','#','#','.','#'},
    {'#','.','.','.','.','.','.','#','.','.','.','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#'}
    };

    
    /*
    Write your function that will traverse the maze
    recursively. Each call should only make one cell move. The
    recursive calls will end when an exit is found. This means that
    the current position should be passed as an argument to the
    function.

    Note that you can assume that the maze has a path between the
    entry and exit (otherwise the program will keep wandering in
    the maze desperately looking for an exit).
    Also note that, the use of global variables is not allowed.
    */
    maze[2][0] = 'x';
    traverse_maze(maze,2,0);
    return 0;

}

void traverse_maze(char maze[SIZE][SIZE], int x, int y){    
    if (x == 0 || y == 0 || x == SIZE || y == SIZE){
        if (maze[x][y]=='.'){
            maze[x][y] = 'o';
            printMaze(maze);
            return;
        }
    }

    maze[x][y] = 'o';
    printMaze(maze);
    maze[x][y] = 'x';

    float r = (float) rand()/RAND_MAX;
    if (r>.75 && x < SIZE-1 && maze[x+1][y]!='#')     x = x+1;
    else if (r>.5 && x > 0 && maze[x-1][y]!='#')      x = x-1;
    else if (r>.25 && y < SIZE-1 && maze[x][y+1]!='#')y = y+1;
    else if (y > 0 && maze[x][y-1]!='#')              y = y-1;

    //wait_for(1);
    traverse_maze(maze, x, y);
}

void printMaze(char maze[SIZE][SIZE]){
    //clrscr();
    for (int x = 0; x < SIZE; x++){
        for (int y = 0; y < SIZE; y++){
            printf("%c   ", maze[x][y]);
        }
        puts("\n");
    }
    puts("\n");
}