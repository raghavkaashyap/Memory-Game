//SE 185: Final Project - Memory Game//
/////////////////////////



#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <unistd.h> //lets you make second intervals easier
#include <string.h>

/////////////////////////////////////
//User Defined Functions Prototype//
//List prototypes here and define//
//tehm below the main function////
/////////////////////////////////

void drawShape(int random);
int printTable();
void addHighScore();
int score = 0;
int main() {
  char flag = 'f';
  int play = 1;
  int numTurns = 1;
  int arrCount = 0;
  char userInput = 'i';
  char * outputs = (char * ) malloc((arrCount + 1) * sizeof(char));
  srand(time(NULL));

  printf("Welcome to the memory game.\n");
  printf("To start the game enter \"g\" \n");
  printf("In the game various shapes will appear with a circle around it\n");
  printf("You must remember the shapes that are circled and repeat the order\n");
  printf("Use W for up, S for down, D for right, A for left\n\n");

  int lowestScore = printTable();
  //if leaderboard is empty
  if (lowestScore == -1) {
    printf("\n");
  }

  printf("What would you like to do?\n");
  while (flag != 'g') {
    printf("Enter \"g\" to start: ");
    scanf(" %c", &flag);
  }

  //main game loop
  while (play == 1) {
    printf("Get ready for the round!\n");
    int count = 3;
    //counts down from 3
    while (count > 0) {
      printf("%d...\n", count);
      sleep(1);
      count--;
    }
    int random = rand() % 4;
    //RK: Choose a random shape and store it in the array
    switch (random) {
    case 0:
      *
      (outputs + arrCount) = 'w';
      break;
    case 1:
      *
      (outputs + arrCount) = 'a';
      break;
    case 2:
      *
      (outputs + arrCount) = 's';
      break;
    case 3:
      *
      (outputs + arrCount) = 'd';
      break;
    }
    //draw the board and circle the random symbol
    drawShape(random);

    printf("Okay, what was the order? (Use w,a,s,d)\n");

    //quiz the player on their knowledge and compare it to the past rounds
    for (int i = 0; i < numTurns; i++) {
      printf("%d time: ", i + 1);
      scanf(" %c", & userInput);
      //check against the previous random chars
      if (userInput == * (outputs + i)) {
        score++;
        printf("Score: %d\n", score);
      } else {
        play = -1;
        printf("Sorry, you lose, at least you got to turn %d.\n", numTurns);
        printf("Your final score was %d, try again and get an even higher score!\n\n", score);
        break;
      }
    }
    //if they got all of the turns right
    if (play == 1) {
      numTurns++;
      arrCount++;
    }
  }
  free(outputs); // memory freed

  //if on the highscore board, update and print it
  if (score >= lowestScore) {
    addHighScore();
    printf("\n");
    printTable();
  }

  return 0;
}

///////////////////////////////////////
//User Defined Functions' Definition//
/////////////////////////////////////

//prints out the highscore table stored in highscores.txt
int printTable() {
  FILE * f = fopen("highscore.txt", "r");
  //maximum row length for chars is 9, for this method of searching
  char arr[9][6];
  int row = 0;
  int col = 0;
  char * lowest = (char * ) malloc(2 * sizeof(char));

  if (f == NULL) {
    printf("Error: Could not find \"highscore.txt\"");
    exit(0);
  }

  printf("Highscore Table: \nRank Score  Name\n");

  //checks if the file is empty, if so, return -1
  fseek(f, 0, SEEK_END);
  if (ftell(f) == 0) {
    return -1;
  }

  rewind(f);
  //reads the file and stores its input in a 2d char array
  while (!feof(f)) {
    char current;
    //add current char to array
    fscanf(f, "%c ", & current);
    //if the column reached the end reset and increment row
    if (col == 5) {
      arr[row][col] = current;
      row++;
      col = 0;
    } else {
      arr[row][col] = current;
      col++;
    }
  }
  fclose(f);

  //traverses the 2d array and prints out the highscores with proper spacing
  for (int r = 0; r < row; r++) {
    for (int c = 0; c < 6; c++) {
      switch (c) {
      case 0:
        printf("%c     ", arr[r][c]);
        break;
      case 1:
      case 3:
      case 4:
      case 5:
        printf("%c ", arr[r][c]);
        break;
      case 2:
        printf("%c   ", arr[r][c]);
        break;
      default:
        printf("%c ", arr[r][c]);
      }
    }
    printf("\n");
  }

  //gets the lowest score on the leaderboard and returns it as an int
  *(lowest) = arr[row][1];
  *(lowest + 1) = arr[row][2];
  return atoi(lowest);
}

//draws out the 4 symbols,
//circling one of them based on the given random
void drawShape(int random) {

  if (random == 0) {
    printf(" - - - - - -\n");
  }
    
  //drawing triangle
  int mySpace = 20;
  int rowLength = 4;
  for (int i = 1; i <= rowLength; i++) {
    if (random == 0) {
      printf("|");
    }

    for (int j = i; j < rowLength; j++) {
      printf(" ");

    }

    if (i > 0)
    {
      printf(" ");
      printf(" ");
    }

    for (int j = 1; j <= (2 * i - 1); j++) {
      printf("^");
    }

    if (random == 0) {

      for (int z = i; z < rowLength; z++) {
        printf(" ");
      }
      printf("  |");
    }
    printf("\n");

  }

  if (random == 0) {
    printf(" - - - - - -\n");

  }
  printf("\n");
  if (random == 3) {
    printf("         - - - - -");
  }

  //drawing square
  int hLength = 5;
  int rLength = 2;
  int sideLength = 3;
  int heightL = 3;
  int rowL = 0;
  printf("\n");

  if (random == 1) {
    printf(" - - - - - ");
    printf("\n");
   
  }

  for (int l = 1; l < rLength; l++) {
    for (int h = 1; h <= hLength; h++) {
      if (h == 1)
      {
          if (random == 1){
            printf("|");
            }
          if (l > 0){
            printf(" ");
          }
        printf(" ");
          
      }
      printf("H");
      if (h == 5) {
        printf(" ");
      }
    }
  }

  //drawing diamond
  for (int k = 1; k <= sideLength; k++) {
      if (random == 1 || random == 3){
          printf("|");
      }
    for (int m = k; m <= sideLength; m++) {
      printf(" ");
    }

    for (int m = 1; m <= (2 * k - 1); m++) {
      printf("0");
      if (m >= (2 * k - 1)) {
          if (random == 3 && m == 1){
              printf("    |");
          }
          if (random == 3 && m == 3){
              printf("   |");
          }
          if (random == 3 && m == 5){
              printf("  |");
          }
        printf("\n");
        for (int h = 1; h <= hLength; h++) {
          if (h == 1)
          {
              if (random == 1){
                printf("|");
              }
              printf(" ");
              printf(" ");
          }
          printf("H");
          if (h == 5) {
            printf(" ");
          }
        }
      }
    }
      if (random == 1 || random == 3) {
        for (int z = k; z >= sideLength; z--) {
          printf("|");
        }
      }
  }

  for (int l = 2; l >= rowL; l--) {
    for (int h = l; h <= heightL; h++) {
      printf(" ");
    }
    for (int h = 3; h <= (2 * l + 1); h++) {
      printf("0");
      if (h > (4)) {
          if (random == 3){
              printf("   |");
          }
        printf("\n");
        for (int h = 1; h <= hLength; h++) {
          if (h == 1) {
              if (random == 1){
                  printf("|");
              }
            printf(" ");
            printf(" ");
          }
          printf("H");
          if (h >= 5) {
            printf(" ");
              if (random == 1 || random == 3){
                  printf("|");
              }
          }
        }
      }
      }
      if (random == 3 && l == 0){
        printf("|");
        }
    }
  printf(" \n");
  if (random == 1) {
    printf(" - - - - - ");
  }

  if (random == 3) {
    printf("         - - - - -");
  }

  if (random == 2) {
    printf(" - - - - -");
  }

  //drawing X
  printf("\n");
  int t, r;
  int size = 5;

  for (t = 1; t <= size; t++) {
    if (random == 2) {
      printf("|");
    }
    for (r = 1; r <= size; r++) {
      if (r == 1)
      {
        printf(" ");
        printf(" ");
      }
      if (r == t || (r == size - t + 1)) {
        printf("X");
      } else {
        printf(" ");
      }
    }
    if (random == 2) {
         for (int z = t; z > size; z++) {
           printf(" ");
         }
         printf("  |");
       }
      
    printf("\n");
   
  }
    
  if (random == 2)
    printf(" - - - - -\n");
}

//takes the players score and name
//then inserts it into the correct position and
//moves the rest of the leaderboard into its new order
void addHighScore() {
  //max score is 99
  if (score > 99) {
    score = 99;
  }
  
  FILE * f = fopen("highscore.txt", "r");
  char arr[9][6];
  char name[3];
  int row = 0;
  int col = 0;
  char * currentValue = (char * ) malloc(2 * sizeof(char));
  int replacementRow = 0;

  //checks if the file is empty, if so, set replacementRow to 0
  fseek(f, 0, SEEK_END);
  if (ftell(f) == 0) {
    replacementRow = 0;
  }
  rewind(f);

  //scan current highscore table into 2d char array
  while (!feof(f)) {
    char current;
    //add current char to array
    fscanf(f, "%c ", & current);
    //if the column reached the end reset and increment row
    if (col == 5) {
      arr[row][col] = current;
      row++;
      col = 0;
    } else {
      arr[row][col] = current;
      col++;
    }
  }
  fclose(f);

  //find row to put new highscore in
  //by comparing this players score vs the leaderboards
  for (int r = 0; r < row; r++) {
    *(currentValue) = arr[r][1];
    *(currentValue + 1) = arr[r][2];
    *(currentValue + 2) = '\0';
    if (score >= atoi(currentValue)) {
      replacementRow = r;
      printf("Congratulations, you made it on the highscore table!\n"); 
      printf("Please enter your name (only 3 capital letters): "); 
      scanf("%s", name);
      break;
    }
  }

  char newArr[9][6];

  // RK: moves the lowest score to the bottom of the highscore table
  if (replacementRow != 0) { 
    for (int r = 0; r < row; r++) {
      if (r == replacementRow) {
        newArr[replacementRow][0] = '0' + (replacementRow + 1);
        newArr[replacementRow][1] = '0' + (score / 10) % 10;
        newArr[replacementRow][2] = '0' + score % 10;
        newArr[replacementRow][3] = name[0];
        newArr[replacementRow][4] = name[1];
        newArr[replacementRow][5] = name[2];
      }
      for (int c = 0; c < 6; c++) { 
        if (r < replacementRow) {
          newArr[r][c] = arr[r][c];
        } else if (r > replacementRow) {
          if (c == 0) {
            int orig = arr[r - 1][c] - '0';
            orig++;
            newArr[r][c] = orig + '0';
          } else {
            newArr[r][c] = arr[r - 1][c];
          }
        }
      }
    }
  } else {
    newArr[replacementRow][0] = '0' + (replacementRow + 1);
    newArr[replacementRow][1] = '0' + (score / 10) % 10;
    newArr[replacementRow][2] = '0' + score % 10;
    newArr[replacementRow][3] = name[0];
    newArr[replacementRow][4] = name[1];
    newArr[replacementRow][5] = name[2];
    for (int r = 1; r <= row; r++) {
      for (int c = 0; c < 6; c++) {
        if (c == 0) {
          int orig = arr[r - 1][c] - '0';
          orig++;
          newArr[r][c] = orig + '0';
        } else {
          newArr[r][c] = arr[r - 1][c];
        }
      }
    }
  }

  //AT: rewrites new leaderboard to the text file highscore.txt
  f = fopen("highscore.txt", "w");
  for (int r = 0; r < row; r++) {
    for (int c = 0; c < 6; c++) {
      fprintf(f, "%c ", newArr[r][c]);
    }
    if (row > 1) {
      fprintf(f, "\n");
    }
  }
  fclose(f);
}
