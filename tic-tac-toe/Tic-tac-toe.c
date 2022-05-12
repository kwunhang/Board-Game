/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name  :Lau Kwun Hang
 * Student ID    :1155158471
 * Class/Section :ENGG1110
 * Date          :20/11/2020
 */

#include <stdio.h>
/* NO other header files are allowed */

/* NO global variables are allowed */

/* Macros used to represent the state of each square */
#define EMPTY 0
#define CIRCLE 1
#define CROSS 2

/* Initialize the game board by setting all nine squares to EMPTY */
void initGameBoard(int gameBoard[3][3]) {
  gameBoard[0][0]=EMPTY;
  gameBoard[0][1]=EMPTY;
  gameBoard[0][2]=EMPTY;
  gameBoard[1][0]=EMPTY;
  gameBoard[1][1]=EMPTY;
  gameBoard[1][2]=EMPTY;
  gameBoard[2][0]=EMPTY;
  gameBoard[2][1]=EMPTY;
  gameBoard[2][2]=EMPTY;
    // TODO: Complete this part

}



// Display the game board on the screen

void printGameBoard(int gameBoard[3][3]){
  int i,j,k=7;
  int printBoard[3][3];
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      if(gameBoard[i][j]==EMPTY){
        printBoard[i][j]=k;
        }
      k++;
    }
    k-=6;
  }
  printf("=========\n");
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      if (gameBoard[i][j]==EMPTY) printf("|%d|",printBoard[i][j]);
      else if(gameBoard[i][j]==CIRCLE)printf("|O|");
      else printf("|X|");
    }
    printf("\n");
  }
    printf("=========\n");
}



// Ask the human player to place the mark.

void placeMarkByHumanPlayer(int gameBoard[3][3], int mark) {
  int i,j,k=0,x,y;
  char input[100]={0};
  while(1){
    while(1){
      fgets(input,100,stdin);
      if((input[0]>='1'&&input[0]<='9')&&input[1]==10){
        i=input[0]-48;
        break;
      }else{
        printf("Your input is invalid.Please only input an valid integer between 1-9.\n");
      }
    }
    i=9-i;
    x=i/3;
      for(j=2;j>=0;j--){
        if(i%3==j) y=k;
        k++;
      }
      if(gameBoard[x][y]==EMPTY){
        gameBoard[x][y]=mark;
        printGameBoard(gameBoard);
        break;
      }else printf("Your input is invalid.Please only input an valid integer between 1-9 which does not repeat.\n");
      k=0;
    }

}


/* Return 1 if there is a winner in the game, otherwise return 0 */

// used this program when larger gameboard size, size n*n
/*
int straight(int **gameBoard,int n){
  int i,j,check;
  for(i=0;i<n;i++){
    check = gameBoard[i][i];
    for(j=0;j<n;j++){
      if(check!=gameBoard[i][j])  break;
    }
    if(j==n)  return 1;
    for(j=0;j<n;j++){
      if(check!=gameBoard[j][i])  break;
    }
    if(j==n)  return 1;

  }
  return 0;
}
*/



//with 3x3 gameBoard size, it is easier to read and implement
int hasWinner(int gameBoard[3][3]) {
  if(
    (gameBoard[0][0]==gameBoard[0][1]&&gameBoard[0][1]==gameBoard[0][2]&&!(gameBoard[0][0]==EMPTY))||
    (gameBoard[1][0]==gameBoard[1][1]&&gameBoard[1][1]==gameBoard[1][2]&&!(gameBoard[1][0]==EMPTY))||
    (gameBoard[2][0]==gameBoard[2][1]&&gameBoard[2][1]==gameBoard[2][2]&&!(gameBoard[2][0]==EMPTY))||
    (gameBoard[0][0]==gameBoard[1][0]&&gameBoard[1][0]==gameBoard[2][0]&&!(gameBoard[2][0]==EMPTY))||
    (gameBoard[0][1]==gameBoard[1][1]&&gameBoard[1][1]==gameBoard[2][1]&&!(gameBoard[2][1]==EMPTY))||
    (gameBoard[0][2]==gameBoard[1][2]&&gameBoard[1][2]==gameBoard[2][2]&&!(gameBoard[2][2]==EMPTY))||
    (gameBoard[0][0]==gameBoard[1][1]&&gameBoard[1][1]==gameBoard[2][2]&&!(gameBoard[2][2]==EMPTY))||
    (gameBoard[0][2]==gameBoard[1][1]&&gameBoard[1][1]==gameBoard[2][0]&&!(gameBoard[2][0]==EMPTY))
  ) return 1;
    else return 0;


}



/* Return 1 if the game board is full, otherwise return 0 */

int isFull(int gameBoard[3][3]){
  int i,j;
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      if(gameBoard[i][j]==EMPTY) return 0;
    }
  }
  return 1;
}



// Determine the next move of the computer player.



int winPredictAndPlace(int gameBoard[3][3],int mark,int computermark){
  int i,j;
  for(i=0;i<=2;i++){
    for(j=0;j<=2;j++){
      if(gameBoard[i][j]==EMPTY){
        gameBoard[i][j]=mark;
        if(hasWinner(gameBoard)){
          gameBoard[i][j]=computermark;
          return 1;
        }
        gameBoard[i][j]=EMPTY;
      }
    }
  }
  return 0;
}

int twoHeadedSnakePrevent(int gameBoard[3][3],int mark){
  int x,y,kx,ky,corner=0,side=0,counterx=0,countery=0;
  for(x=0;x<=2;x++){
    for(y=0;y<=2;y++){
      if(gameBoard[x][y]==CIRCLE){
        if((x+y)%2==0){
          corner++;
          kx=x;
          ky=y;
          }
        else{
          side++;
          counterx+=x;
          countery+=y;
        }
      }
    }
  }
  if(side==2){
    if (counterx==2) return 0; //opposite side condition,which can use normal method
    gameBoard[counterx-1][countery-1]=mark;
    return 1;
  }if(corner==2){
    gameBoard[0][1]=mark;
    return 1; 
  }if(counterx%2==0){//this condition is 1side 1corner
    gameBoard[counterx][ky]=mark;
  }else gameBoard[kx][countery]=mark;
  return 1;
}

void placeMarkByComputerPlayer(int gameBoard[3][3],int mark,int turn){
  int i,j;
  if(winPredictAndPlace(gameBoard,CROSS,mark)) return;
  if(winPredictAndPlace(gameBoard,CIRCLE,mark)) return;
  if (gameBoard[1][1]==EMPTY){
    gameBoard[1][1]=mark;
    return;
    }
    if((turn==2)&&gameBoard[1][1]==CROSS){
      if(twoHeadedSnakePrevent(gameBoard,mark)){
        return;
      }
    }
  for(i=0;i<=1;i++){
    for(j=0;j<=1;j++){
      if(gameBoard[i*2][j*2]==EMPTY){
        gameBoard[i*2][j*2]=mark;
        return;
        }
    }
  }
  for(i=0;i<=2;i++){
    for(j=(i+1)%2;j<=2;j+=2){
      if(gameBoard[i][j]==EMPTY){
        gameBoard[i][j]=mark;
        return;
      }
    }
  }

}



/* The main function */
int main() {
    /* Local variables */
    int gameBoard[3][3];    // Each element stores 0 (EMPTY), 1 (CIRCLE), or 2 (CROSS)
    int currentPlayer;      // 1: Player 1 (Human)   2: Player 2 (Human) or Computer Player
    int gameEnds;           // 0: The game continues   1: The game ends
    char numOfHumanPlayers[100]={0};  // 1 or 2 
    int turn=1;

    /* Initialize the local variables by invoking a function, using assignment statements, and reading the user input */
    initGameBoard(gameBoard);
    currentPlayer = 1;
    gameEnds = 0;
    while(1){
      printf("How many human players [1-2]?\n");
      fgets(numOfHumanPlayers,100,stdin);    // In Part 1, you can assume that the user input must be valid
      if((numOfHumanPlayers[0]=='1'||numOfHumanPlayers[0]=='2')&&numOfHumanPlayers[1]==10) break;
      else printf("Your input is invalid.Please input the digit 1 or 2.\n");
    } 


    printGameBoard(gameBoard);
    while(numOfHumanPlayers[0]=='2'){///
    printf("Player 1, please place your mark [1-9]:\n");
    placeMarkByHumanPlayer(gameBoard, CIRCLE);
    gameEnds=hasWinner(gameBoard);
    if(gameEnds==1) {
      printf("Player 1 wins! Congratultions!");
      return 0;
    }
    gameEnds=isFull(gameBoard);
    if(gameEnds==1) {
      printf("Draw game!");
      return 0;
    }
    printf("Player 2, please place your mark [1-9]:\n");
    placeMarkByHumanPlayer(gameBoard, CROSS);
    gameEnds=hasWinner(gameBoard);
    if(gameEnds==1) {
      printf("Player 2 wins! Congratultions!");
      return 0;
    }
  }
  while(numOfHumanPlayers[0]=='1'){///
    printf("Player 1, please place your mark [1-9]:\n");
    placeMarkByHumanPlayer(gameBoard, CIRCLE);
    gameEnds=hasWinner(gameBoard);
    if(gameEnds==1) {
      printf("Player 1 wins! Congratultions!");
      return 0;
    }
    gameEnds=isFull(gameBoard);
    if(gameEnds==1) {
      printf("Draw game!");
      return 0;
    }
    printf("Computer places type mark:\n");
    placeMarkByComputerPlayer(gameBoard, CROSS,turn);
    printGameBoard(gameBoard);
    gameEnds=hasWinner(gameBoard);
    if(gameEnds==1) {
      printf("Computer wins!");
      return 0;
    }
    turn++;
  }

  return 0;
}