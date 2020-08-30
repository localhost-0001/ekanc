//known_bugs: snake_tp, snake_input
//stupidly overengineered

#include<stdio.h>
#include<ncurses.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

const int HeaderTest = 1;
enum DIRECTION  { UP , DOWN , LEFT , RIGHT };

void moveSnake(enum DIRECTION CurrentDirection, int **snek);
void generateFood(int *a, int my, int mx);

int main(){
	initscr();	
	nodelay(stdscr, 1);	
	curs_set(FALSE);
	keypad(stdscr, 1);
	refresh();
	sleep(1);

	bool active = 1;
	bool FoodEaten = 0;

	int food[] = {0, 0};	
	int SnakeArraySize = 10;
	int SnakeLength = 4;
	int len = sizeof(int*) * SnakeArraySize + sizeof(int[2]) * SnakeArraySize;
	int **snake = (int **)malloc(len);
	int *SnakePTR = (int *)(snake + SnakeArraySize);

	enum DIRECTION CurrentDirection = RIGHT;

	for(int i = 0; i < SnakeArraySize; i++){
		snake[i] = (SnakePTR + 2 * i);
	}

	snake[0][0] = 1;
	snake[0][1] = 11;
	snake[1][0] = 1;
	snake[1][1] = 10;
	snake[2][0] = 1;
	snake[2][1] = 9;
	snake[3][0] = 1;
	snake[3][1] = 8;

	noecho();
	int my, mx;
	while(active){
		//figure out screen size
		getmaxyx(stdscr, my, mx);
		clear();
		int ch = wgetch(stdscr);
		for(int i = 0; i <= SnakeLength; i++){

			int sy = snake[i][0];
			int sx = snake[i][1];
			mvprintw(sy, sx, "X"); 
		}
		//precheck if player ded
		int sneky = snake[0][0];
		int snekx = snake[0][1];
		if (sneky == my || snekx == mx || snekx < 0 || sneky < 0){
			active = 0;	exit(12);	/*return 0;*/}
		if((sneky == food[0] && snekx == food[1]) || !food[0]){
		//yey, food eaten
			generateFood(food, my, mx);
			FoodEaten = 1;
			SnakeLength++;
		}	

		if((ch == KEY_UP || ch == 'k') && CurrentDirection != DOWN){
			CurrentDirection = UP;	
		} else if((ch == KEY_DOWN || ch == 'j') && CurrentDirection != UP){
			CurrentDirection = DOWN;
		} else if ((ch == KEY_LEFT || ch == 'h') && CurrentDirection != RIGHT){
			CurrentDirection = LEFT;
		} else if ((ch == KEY_RIGHT || ch == 'l') && CurrentDirection != LEFT){
			CurrentDirection = RIGHT;
		}

		if(SnakeArraySize <= SnakeLength - 2){
			SnakeArraySize = SnakeArraySize + 8;
			int newlen = sizeof(int*) * (SnakeArraySize) + sizeof(int[2]) * (SnakeArraySize);
			int **NewArray = realloc(snake, newlen);
			if(NewArray){
				SnakePTR = (int *)(NewArray + SnakeArraySize);

			for(int i = 0; i < SnakeArraySize; i++){
				NewArray[i] = (SnakePTR + 2 * i);
			}
			snake = NewArray;
		} else {exit(19);}
		//free(NewArray);
		} 	
		for (int i = SnakeLength - 2; i > 0; i--){
			snake[i][0] = snake[i - 1][0];
			snake[i][1] = snake[i - 1][1];
	}
		FoodEaten = 0;
		moveSnake(CurrentDirection, snake);
		for (int i=3;i <= SnakeLength - 2; i++){
			if(snake[i][0] == snake[0][0] && snake[i][1] == snake[0][1]){
				exit(121);
			}
		}
		mvprintw(--my, --mx, "m");	
		mvprintw(food[0], food[1], "%c", ACS_PI);
		refresh(); 
		usleep(100000);

	}
	usleep(1410065407);
	return 0;
}

void generateFood(int *a, int my, int mx){
	srand(time(NULL));	
	a[1] = (rand() % mx) + 1;
	a[0] = (rand() % my) + 1;
	return;
}

void moveSnake(enum DIRECTION CurrentDirection, int **snek){
	snek[0][0] = snek[1][0];
	snek[0][1] = snek[1][1];
	switch(CurrentDirection){
		case UP:
			//snek[0][0]--;
			snek[0][0] = snek[0][0] - 1;
			break;
		case DOWN:
			//snek[0][0]++;
			snek[0][0] = snek[0][0] + 1;
			break;
		case LEFT:
			//snek[0][1]--;
			snek[0][1] = snek[0][1] - 1;
			break;
		case RIGHT:
			//snek[0][1]++;
			snek[0][1] = snek[0][1] + 1;
			break;
	}
}
