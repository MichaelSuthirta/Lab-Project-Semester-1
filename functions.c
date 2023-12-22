#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int menu(){
	int choice;
	printf("Welcome to The Gold Mine!		\n");
	printf("  1. Play the game			\n");
	printf("  2. View Highscore			\n");
	printf("  3. How to Play?   		\n");
	printf("  4. Exit the game			\n");
	printf("Insert your choice: ");
	scanf("%d",&choice);
	return choice;
}

void tutorial(){
	printf("\tWelcome to The Gold Mine. In this game, you'll work as a miner in an abandoned gold mine that has just been reopened. ");
	printf("Your task is to gather as many gold ores as possible."
	" However, there are bombs in the mine, left by the previous workers in the mine. ");
	printf("You must avoid the bombs. However, you aren't provided with safety measures and can only rely on leftover safety kit."
	" You can dig at ");
	printf("any coordinate among the provided 8x8 field. When digging, there's a chance one of the following items will appear:\n");
	printf("1. Gold. It adds to your score.\n2. Bomb. It decreases your lifepoint.\n");
	printf("3. Empty.\n4. Safety kit. It restores your lifepoint.\nEnjoy the game!");
}

void cls(){
	system("cls");
}

void display(){
	char map[8][8];
	int x,y;
	
	for(x=0;x<8;x++){
		for(y=0;y<8;y++){
			map[x][y]=220;
		}
	}
	
	for(x=0;x<8;x++){
		for(y=0;y<8;y++){
			printf("%c ",map[x][y]);
		}
		printf("\n");
	}
}

int gameStats(int x,int y){
	int mapVal[8][8];
	
	for(x=0;x<8;x++){
		for(y=0;y<8;y++){
			mapVal[x][y]=1;
		}
	}
}

void showLife(int *hp){
	int i;
	int x=*hp;
	printf("Life: ");
	for(i=1;i<=x;i++){
		printf("o ");
	}
	printf("\n");
}

void showGold(int *gold){
	printf("Gold: %d\n",*gold);
}

void game(){
	cls();
	int hp=3, safe=2, gold=0;
	int x,y;
	int *life=&hp;
	int *score=&gold;
	int res=0;
	int prevRes=0, goldCount=0, emptyCount=0;
	while(hp!=0){
		showLife(life);
		showGold(score);
		display();
		printf("\nDigging coordinate (x y):\n");
		scanf("%d %d",&x,&y);
		if(x>8 || y>8){
			printf("Please dig between the 8x8 field.\n");
			continue;
		}
		srand(time(0));
		if(safe>0){
			res=(rand()%4)+1;
		}
		else{
			res=(rand()%(3))+1;
		}
		if(res==3 && res==prevRes){
			res=(rand()%(3))+1;
		}
		if(goldCount==4 && res==1){
			res+=((rand()%2)+1);
			goldCount=0;
		}
		if(emptyCount==5 && res==2){
			if(gold>8){
				res++;
			}
			else if(gold<3){
				res--;
			}
			else{
				while(res==2){
					res=(rand()%(3))+1;
				}
			}
			emptyCount=0;
		}
		switch(res){
			case 1:{
				printf("Gold.\n");
				gold++;
				goldCount++;
				break;
			}
			case 2:{
				printf("Nothing here.\n");
				emptyCount++;
				break;
			}
			case 3:{
				printf("A bomb!\n");
				hp--;
				prevRes=res;
				break;
			}
			case 4:{
				printf("You found a safety kit.\n");
				hp++;
				safe--;
				break;
			}
			default:{
				break;
			}
		}
		cls();
	}
	if(*life==0){
		char input;
		cls();
		printf("Game Over!\n");
		printf("High Score: %d\n",gold);
		printf("Press x to return.\n");
		while(input!='x' && input !='X'){
			scanf("%c",&input);
		}
	}
}
