#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#define RIGHT 77
//M  
#define LEFT 75
//K
#define UP 72
//H
#define DOWN 80
//P

void Print();
void load();
void gotoxy();
void createFood();

struct coordinate{
	int x;
	int y;
	int direction;
}head, food, body[50];

int inl=5;
int score=0;
int length;

border(){
	int i;
	for(i=0; i<80; i++){
		printf("*");
	}
	gotoxy(0,24);
	for(i=0; i<80; i++){
		printf("*");
	}
	gotoxy(0,0);
	for(i=0;i<24;i++){
		printf("*\n");
	}
	for(i=0;i<24;i++){
		gotoxy(79,i);
		printf("*");
	}
}
printBody(){
	int i;
	for(i=0; i<length;i++){
		gotoxy(body[i].x,body[i].y);
		printf("*");
	}
	gotoxy(body[length].x,body[length].y);
	printf("@");
}

initialBody(){
	int i;
	for(i=0; i<inl; i++){
		body[i].x=10 + i;
		body[i].y=10;
		Sleep(100);
	}
	length=i;
	head.x=10+i;
	head.y=10;
	head.direction = RIGHT;
	body[length]=head;
	printBody();
}
moveSnakeX(){
	int i;
	if(body[length].direction==LEFT){
			return;
	}else{
		body[length].direction = RIGHT;
	}
	gotoxy(body[0].x,body[0].y);
	printf(" ");
	for(i=1; i<=length;i++){
		body[i-1].x=body[i].x;
		body[i-1].y=body[i].y;
	}
	body[length].x+=1;
	printBody();
}
moveSnakeY(){
	int i;
	if(body[length].direction==DOWN){
			return;
	}else{
		body[length].direction = UP;
	}
	gotoxy(body[0].x,body[0].y);
	printf(" ");
	for(i=1; i<=length;i++){
		body[i-1].x=body[i].x;
		body[i-1].y=body[i].y;
	}
	body[length].y+=1;
	printBody();
}
moveSnakeMX(){
	int i;
	if(body[length].direction==RIGHT){
			return;
	}else{
		body[length].direction = LEFT;
	}
	gotoxy(body[0].x,body[0].y);
	printf(" ");
	for(i=1; i<=length;i++){
		body[i-1].x=body[i].x;
		body[i-1].y=body[i].y;
	}
	body[length].x-=1;
	printBody();
}
moveSnakeMY(){
	int i;
	if(body[length].direction==UP){
			return;
	}else{
		body[length].direction = DOWN;
	}
	gotoxy(body[0].x,body[0].y);
	printf(" ");
	for(i=1; i<=length;i++){
		body[i-1].x=body[i].x;
		body[i-1].y=body[i].y;
	}
	body[length].y-=1;
	printBody();
}
void myscore(){
	printf("Your Score:%d\n",score);
}
void saveScore(){
//	char name[20];
//	System("cls");
//	printf("Enter Your Name:\n");
//	FILE *info;
//	info = fopen("record.txt","a+");
//	scanf("%[^\n]",name);
}
void gameOver(){
	system("cls");
	gotoxy(33,12);
	myscore();
	gotoxy(31,13);
	printf("----Game Over----\n");
	getch();
	main();
	saveScore();
}

void checkEat(){
	if( body[length].x == food.x && body[length].y == food.y ){
		length+=1;
		body[length].x=food.x;
		body[length].y=food.y;
		body[length].direction = body[length-1].direction;
		score+=1;
		createFood();
	}
}

void checkHit(){
	int i;
	if( body[length].x == 0 || body[length].x == 80 || body[length].y == 0 || body[length].y == 24 ){ //hit with wall
		gameOver();
	}else{
		for(i=0; i<length; i++){
			if( body[length].x == body[i].x && body[length].y == body[i].y ){ //hit with itself body
				gameOver();
			}
		}
	}
	checkEat();
}


void createFood(){
	int x,y;
	srand(time(NULL));
	x=rand()%80;
	y=rand()%24;
	food.x=x;
	food.y=y;
	gotoxy(food.x,food.y);
	printf("#");
}

move(){
	int i;
	char ch;
	if(kbhit()){
		ch=getch();
		if(ch == 77){
			moveSnakeX();//Right
		}else if(ch == 75){
			moveSnakeMX();//Left
		}else if(ch == 80){
			moveSnakeY();//Up
		}else if(ch == 72){
			moveSnakeMY();//Down
		}
	}else{
		if(body[length].direction==RIGHT){
			moveSnakeX();
			Sleep(100);
			checkHit();
		}if(body[length].direction==LEFT){
			moveSnakeMX();
			Sleep(100);
			checkHit();
		}if(body[length].direction==UP){
			moveSnakeY();
			Sleep(100);
			checkHit();
		}if(body[length].direction==DOWN){
			moveSnakeMY();
			Sleep(100);
			checkHit();
		}
	}
	move();
}
int main(){
	int i;
//	gotoxy(10,10);
//	Print();
	system("cls");
	border();
	initialBody();
	createFood();
	move();
	getch();
//	printf("%d",head.x);
	
//	load();
//	head.direction = RIGHT;
	
	
	
}
void load(){
	int i,j;
	gotoxy(34,14);
	printf("loading...");
	gotoxy(28,15);
	for(i=0; i < 20; i++){
		for(j=0; j<=100000000; j++);
		printf("%c",177);
	}
	system("cls");
}

void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void Print(){
	printf("Welcome to Snake Game.(Press any key to continue)");
	getch();
	system("cls");
	printf("* Use Arrow key to move ..\n");
	printf("* You Will be provide a food item, you have to pick it \n");
	printf("* If you picked length of snake increase by 1\n");
	printf("* If you hit by wall then game will start again\n");
	printf("* You have 3 lives to play. Hit maximum score you can\n");	
	printf("* To Pause press any key. To continue again press any key\n");
	printf("* To exit from game press esc\n");
	if(getch() == 27)
	{
		exit(0);
	}
} 
