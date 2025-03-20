#include<stdio.h>//

#include <stdlib.h>//

#include <unistd.h>//

#include <time.h>//

#include <string.h>//

#define MAX_SCORES 10

typedef struct {
    int rank;
    int score;
    char name[4];
} Highscore;

void start();
void drawBoard(int random);
int printHighscore();
void countDown();
void addHighscore(int score);

int main() {
  char check = 'f';
  int stillPlaying = 1;
  int score = 0;
  int turns = 1;
  int arrCount = 0;
  char input = 'z';
  char * outputs = (char * ) malloc((arrCount + 1) * sizeof(char));
  srand(time(NULL));

  start();
  int lowestHS = printHighscore();
  //if leaderboard is empty
  if (lowestHS == -1) {
    printf("\n");
  }

  printf("What would you like to do?\n");
  while (check != 'g') {
    printf("Enter \"g\" to start: ");
    scanf(" %c", & check);
  }

  //main game loop
  while (stillPlaying == 1) {
    printf("Get ready for the round!\n");
    countDown();
    int random = rand() % 4;
    //Choose random answer and store it in the array
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
    drawBoard(random);
    //printf("%c\n", *(outputs + arrCount));

    printf("Okay, what was the order? (Use w,a,s,d)\n");
    //quiz the player on their knowledge and compare it to the past rounds
    for (int i = 0; i < turns; i++) {
      printf("%d time: ", i + 1);
      scanf(" %c", & input);
      //check against the previous random chars
      if (input == * (outputs + i)) {
        score++;
        printf("Score: %d\n", score);
      } else {
        stillPlaying = -1;
        printf("Sorry, you lose, at least you got to turn %d.\n", turns);
        printf("Your final score was %d, try again and get an even higher score!\n\n", score);
        break;
      }
    }
    //if they got all of the turns right
    if (stillPlaying == 1) {
      turns++;
      arrCount++;
    }
  }
  free(outputs);

  //if they got on the highscore board, update and print it
  if (score >= lowestHS) {
    addHighscore(score);
    printf("\n");
    printHighscore();
  }

  return 0;
}

//Prints out the start messages and waits for user input
void start() {
  char check = 'f';
  printf("Welcome to the memory game.\n");
  while (check != 'g') {
    printf("Enter \"g\" to start: ");
    scanf(" %c", & check);
  }
  printf("In the game various shapes will appear with a circle around it\n");
  printf("You must remember the shapes that are circled and repeat the order\n");
  printf("Use W for up, S for down, D for right, A for left\n\n");
}

//prints out the highscore table stored in highscores.txt,
//with proper spacing
int printHighscore() {
    FILE *f = fopen("highscores.txt", "r");
    if (f == NULL) {
        printf("Error: Could not open \"highscores.txt\"\n");
        return -1;
    }

    char line[20]; 
    int lowestScore = 100;
    int count = 0;

    printf("Highscore Table:\nRank  Score  Name\n");

    while (fgets(line, sizeof(line), f) != NULL) {
        int rank, score;
        char name[4];

        if (sscanf(line, "%d %d %s", &rank, &score, name) == 3) {
            printf("%d     %d     %s\n", rank, score, name);
            
            if (score < lowestScore) {
                lowestScore = score;
            }
            count++;
        }
    }

    fclose(f);
    return (count > 0) ? lowestScore : -1;
}


//counts down from 3
void countDown() {
  int count = 3;
  while (count > 0) {
    printf("%d...\n", count);
    sleep(1);
    count--;
  }
}

//draws out the 4 symbols,
//circling one of them based on the given random
void drawBoard(int random) {

  if (random == 0) {
    printf(" - - - - - -\n");

  }
    
  //drawing triangle
  int spaceOut = 20;
  int rowLength = 4;
  for (int i = 1; i <= rowLength; i++) {
    if (random == 0) {
      printf("|");
    }

    for (int j = i; j < rowLength; j++) {
      printf(" ");

    }

    if (i > 0) //spacing for the triangle, keeps it away from the edge of the screen.
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
      if (h == 1) //spacing for the top line of the square.
      {
          if (random == 1){
                       printf("|");
                   }
          if (l > 0) {
                  printf(" ");
                }
        printf(" ");
          
      }
      printf("@");
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
      printf("^");
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
          if (h == 1) //this is spacing before the shape is printed. For the 3 middle parts of the sqare
          {
              if (random == 1){
                           printf("|");
                       }
            printf(" ");
            printf(" ");
          }
          printf("@");
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
      printf("^");
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
          printf("@");
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
      if (r == 1) //spacing for the x, to keep away from edge of screen.
      {
        printf(" ");
        printf(" ");
      }
      if (r == t || (r == size - t + 1)) {
        printf("*");
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
    
  if (random == 2) {
    printf(" - - - - -\n");
  }

}

//takes the players score and name
//then inserts it into the correct position and
//moves the rest of the leaderboard into its new order

void addHighscore(int score) {
    Highscore scores[MAX_SCORES];
    int count = 0;

    FILE *f = fopen("highscores.txt", "r");
    
    if (f != NULL) {
        while (fscanf(f, "%d %d %s", &scores[count].rank, &scores[count].score, scores[count].name) == 3) {
            count++;
            if (count >= MAX_SCORES) break;
        }
        fclose(f);
    }

    char name[4];
    printf("Enter your name (3 letters): ");
    scanf("%3s", name);

    int insertPos = count;
    for (int i = 0; i < count; i++) {
        if (score >= scores[i].score) {
            insertPos = i;
            break;
        }
    }
    for (int i = MAX_SCORES - 1; i > insertPos; i--) {
        scores[i] = scores[i - 1];
    }

    // Insert the new score
    scores[insertPos].rank = insertPos + 1;
    scores[insertPos].score = score;
    strcpy(scores[insertPos].name, name);

    for (int i = 0; i < MAX_SCORES && i < count + 1; i++) {
        scores[i].rank = i + 1;
    }

    // Write scores back to the file
    f = fopen("highscores.txt", "w");
    for (int i = 0; i < MAX_SCORES && i < count + 1; i++) {
        fprintf(f, "%d %d %s\n", scores[i].rank, scores[i].score, scores[i].name);
    }
    fclose(f);

    printf("Highscore saved successfully!\n");
}
