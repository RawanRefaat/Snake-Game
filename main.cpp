#include <iostream>
#include <conio.h>
#include <stdlib.h>

#define UPARROW 72
#define DOWNARROW 80
#define LEFTARROW 75
#define RIGHTARROW 77
#define MAXIMUMSIZE 100

using namespace std;

//contains all the snake variables
struct snakeType{
bool gameOver;
int x,y,fruitX,fruitY;
int score;
enum direction {start=0, up , down , left , right};
direction dir;
int tailX[MAXIMUMSIZE],tailY[MAXIMUMSIZE],length;
};

snakeType snake1;
const int borderWidth=50,borderHeight=20;

//functions prototypes
void initializeGame();
void drawBorder();
void checkDirection();
void moveSnake();

//sets up the game to start
void initializeGame(){
    snake1.gameOver = false;
    snake1.x = 5;
    snake1.y = 5;
    snake1.dir = snakeType::start;
    snake1.fruitX = rand() % borderWidth;
    snake1.fruitY = rand() % borderHeight;
    snake1.score = 0;
}

//takes input from user for directions through the arrow keys
void checkDirection(){
int key;
if (kbhit()) {
    key=getch();
    if (key == 224) {
        do{
           key=getch();
        }while(key==224);
        switch (key) {
            case UPARROW:
                snake1.dir = snakeType::up;
                break;
            case DOWNARROW:
                snake1.dir = snakeType::down;
                break;
            case LEFTARROW:
                snake1.dir = snakeType::left;
                break;
            case RIGHTARROW:
                snake1.dir = snakeType::right;
                break;
        }
    }
}}

void drawBorder(){
    system("cls"); //system("clear");
    cout << "Press the arrow keys on the keyboard to move the snake!" << endl;
	for (int i = 0; i < borderWidth+2; i++)
		 cout << "*";
	cout << endl;
	for (int i = 0; i < borderHeight; i++){
            for (int j = 0; j < borderWidth; j++){
                if (j == 0)
				   cout << "*";
               if(i==snake1.y && j==snake1.x){//to print the snake head if the cursor is at the snake position
                  cout << "0";}
               else if (i== snake1.fruitY && j==snake1.fruitX){
                       cout << "#";}
               else {
                    bool tail=false;
                    for (int t=0; t < snake1.length; t++){
                        if (snake1.tailX[t]==j && snake1.tailY[t]==i){
                                cout << "o";
                                tail = true;}}
                        if (tail==false)
                            cout << " ";
                    }
			   if (j == borderWidth - 1)
				  cout << "*";
           }
		   cout << endl;
	}
	for (int i = 0; i < borderWidth+2; i++)
		cout << "*";
	cout << endl;
	cout << "Score: " << snake1.score << endl;
}


void moveSnake(){
   int previousX= snake1.tailX[0],tempX;
   int previousY= snake1.tailY[0],tempY;
   snake1.tailX[0] = snake1.x;
   snake1.tailY[0] = snake1.y;

   if (snake1.dir == snakeType::up)
            {snake1.y--;}
   else if (snake1.dir == snakeType::down)
            {snake1.y++;}
    else if (snake1.dir == snakeType::left)
            {snake1.x--;}
    else if (snake1.dir == snakeType::right)
             {snake1.x++;}

    //to prevent the snake from going through the wall
    //if it does, the program terminates
    if (snake1.x > borderWidth || snake1.y > borderHeight || snake1.x < 0 || snake1.y < 0){
        snake1.gameOver = true;}
    for (int t=0; t<snake1.length; t++){
            if (snake1.tailX[t]==snake1.x && snake1.tailY[t]==snake1.y){
                snake1.gameOver = true;
            }
    }
    if (snake1.x == 0){
        cout << "You last score: " << snake1.score;
    }

    //if the snake eats the fruit
    if (snake1.x==snake1.fruitX && snake1.y==snake1.fruitY)
        { ++snake1.score;
          ++snake1.length;
          snake1.fruitX = rand() % borderWidth;
          snake1.fruitY = rand() % borderHeight;
        }
    for (int k=1; k<snake1.length;k++){
        tempX = snake1.tailX[k];
        tempY = snake1.tailY[k];
        snake1.tailX[k] = previousX;
        snake1.tailY[k] = previousY;
        previousX = tempX;
        previousY = tempY;
   }
}




int main()
{   initializeGame();
    while (snake1.gameOver == false){
        drawBorder();
        checkDirection();
        moveSnake();
    }
    return 0;
}
