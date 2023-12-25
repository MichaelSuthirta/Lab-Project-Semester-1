#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int checkName(){
	FILE* fp=fopen("user.txt","r");
	fseek(fp,0,SEEK_END);
	int size=ftell(fp);
	if(size==0){
		return 0;
	}
	else return 1;
}

void saveName(char name[100]){
	FILE* fp=fopen("user.txt","w");
	fprintf(fp,"%s",name);
	fclose(fp);
}

int menu(){
	int choice;
	printf("  1. Play the game			\n");
	printf("  2. View Highscore			\n");
	printf("  3. How to Play?   		\n");
	printf("  4. Change Username			\n");
	printf("  5. Exit the game			\n");
	printf("Insert your choice: ");
	scanf("%d",&choice);
	return choice;
}

int findRunAmt(){
	int run=0;
	int score=0;
	FILE* fp=fopen("score.txt","r");
	while(!feof(fp)) {
		fscanf(fp,"%d|%d",&run,&score);
	}
	fclose(fp);
	return run;
}

void saveScore(int run,int score){
    FILE *fscore = fopen("score.txt", "a+");
    fprintf(fscore, "%d|%d\n", run, score);
    fclose(fscore);
}

void sort(int arr1[],float arr2[],int size){
	int m,n;
	
	for(m=1;m<size;m++){
		float temp=arr2[m];
		int t=arr1[m];
		n=m-1;
		while(n>=0 && arr2[n]<temp){
			arr2[n+1]=arr2[n];
			arr1[n+1]=arr1[n];
			n--;
		}
		arr2[n+1]=temp;
		arr1[n+1]=t;
	}
}

int readScore(){
    FILE *fscore = fopen("score.txt", "r");
    int i=0;
    int run[100000];
    float scoreList[100000];
    float totalScore=0;
    while(!feof(fscore)){
		fscanf(fscore, "%d|%f", &run[i],&scoreList[i]);
		i++;
	}
    fclose(fscore);
	int size=i;
	sort(run,scoreList,size);
	puts("Top 3 Runs with Highest Score:");
	for(i=0;i<3;i++){
		printf("Run %d: %.0f\n",run[i],scoreList[i]);
		totalScore=totalScore+scoreList[i];
	}
	float avg=totalScore/3;
	printf("Average of the top 3: %.2f\n",avg);
}

int binSearch(int arr1[],float arr2[],int key,int left, int right){
	if(left>right){
		return -1;
	}
	int r;
	float s;
	int mid=(left+right)/2;
	if(key==arr1[mid]){
		return mid;
	}
	else if(key<arr1[mid]){
		return binSearch(arr1,arr2,key,left, mid-1);
	}
	else{
		return binSearch(arr1,arr2,key,mid+1,right);
	}
}

int search(int n){
	int run[100000];
	float score[100000];
	int i=0;
	FILE* fp=fopen("score.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%d|%f",&run[i],&score[i]);
		i++;
	}
	fclose(fp);
	int index=binSearch(run,score,n,0,i-1);
	if(index==-1){
		return -1;
	}
	else return score[index];
}

void tutorial(){
	printf("\tWelcome to The Gold Mine. In this game, you'll work as a miner in an abandoned gold mine that has just been reopened. ");
	printf("Your task is to gather as many gold ores as possible."
	" However, there are bombs in the mine, left by the previous workers in the mine. ");
	printf("You must avoid the bombs. However, you aren't provided with safety measures and can only rely on leftover safety kit."
	" You can dig at ");
	printf("any coordinate among the provided 8x8 field. When digging, there's a chance one of the following items will appear:\n\n");
	printf("1. Gold. It adds to your score.\n2. Bomb. It decreases your lifepoint.\n");
	printf("3. Empty.\n4. Safety kit. It restores your lifepoint.\n\nEnjoy the game!");
}

void cls(){
	system("cls");
}

void display(char map[8][8]){
	int x,y;

	for(y=0;y<8;y++){
		for(x=0;x<8;x++){
			printf("%c ",map[x][y]);
		}
		printf("\n");
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

void game(char map[8][8]){
	cls();
	int hp=3, safe=2, gold=0;
	int x,y;
	int run=0;
	int *life=&hp;
	int *score=&gold;
	int res=0;
	int prevRes=0, goldCount=0, emptyCount=0;
	while(hp!=0){
		run=findRunAmt();
		showLife(life);
		showGold(score);
		display(map);
		printf("\nDigging coordinate (x y): (Coordinate starts from (1 1) to (8 8))\n");
		scanf("%d %d",&x,&y);
		if(x>8 || y>8 || x<1 || y<1){
			printf("Please dig between the 8x8 field.\n");
			sleep(1);
			cls();
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
		if(goldCount==3 && res==1){
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
		map[x-1][y-1]='X';
		cls();
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
		sleep(1);
		cls();
	}
	if(*life==0){
		run++;
		saveScore(run,gold);
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
