#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char grid[20][20];
char newGrid[20][20];

void initialGrid() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            grid[i][j] = (rand() % 4 == 0) ? '0' : '.'; // '0' for live virus, '.' for dead
        }
    }
}

void printGrid() {
    printf("Dead Virus: [.]        Live Virus: [0]\n"); //shows what part is dead or alive 
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");  // print the grid
    }
}

int countLiveNeighbors(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) ; // Skip 
            int p = x + i;
            int q = y + j; // Neighbor coordinates
            if (p >= 0 && p < 20 && q >= 0 && q < 20 && grid[p][q] == '0') {
                count++;
            }
        }
    }
    return count;
}

void updateGrid() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            int liveNeighbors = countLiveNeighbors(i, j);
            if (grid[i][j] == '0') {
                newGrid[i][j] = (liveNeighbors < 2 || liveNeighbors > 3) ? '.' : '0'; // Uncrowded or Overcrowded 
            } else {
                newGrid[i][j] = (liveNeighbors == 3) ? '0' : '.'; // Spread or Reproduce 
            }
        }
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            grid[i][j] = newGrid[i][j]; // Copy the new grid into the original grid
        }
    }
}

int main() {
    initialGrid();
    
    while (1) {
        printGrid();
        updateGrid();
        sleep(1); // Delay in showing output 
        system("clear"); // Clear the existing output for the new output 
    }
    return 0;
}
    
