#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
extern int menu();
extern int checkName();
extern void saveName(char name[100]);
extern void game(char map[8][8]);
extern int readScore();
extern int search(int n);
extern void tutorial();
extern void cls();

int main(int argc, char *argv[]) {
	char buttonPress='0';
	int gameLive=0;
	char name[100];
	char map[8][8];
	
	checkName();
	
	if(checkName()==0){
		puts("Insert your username:");
		scanf("%[^\n]",&name);
		getchar();
		if(name!="\0"){
			gameLive=1;
		}
		saveName(name);
	}
	else{
		FILE* fp=fopen("user.txt","r");
		fscanf(fp,"%[^\n]",&name);
		fclose(fp);
		gameLive=1;
	}
	
	while(gameLive==1){
		int input;
		
		mainMenu:
			cls();
			printf("Welcome to The Gold Mine, %s!	\n",name);
			input=menu();
	
		switch(input){
			case 1:{
				int x,y;
				for(x=0;x<8;x++){
					for(y=0;y<8;y++){
						map[x][y]=220;
					}
				}
				game(map);
				goto mainMenu;
				break;
			}
			case 2:{
				cls();
				readScore();
            	printf("\nTo continue, press button: \n");
            	printf("f: Search for your previous run.\nx: Return to main menu.\n");
				while(buttonPress!='x' && buttonPress!='X' && buttonPress!='f' && buttonPress!='F'){
					scanf("%c",&buttonPress);
				}
				if(buttonPress=='x' || buttonPress=='X'){
					goto mainMenu;
				}
				else{
					cls();
					int key;
					printf("The n-th run you want to search: ");
					scanf("%d",&key);
					float x=search(key);
					if(x!=-1){
						printf("Result:\n");
						printf("Run: %d    Score: %.0f\n",key,x);
					}
					else{
						printf("Item not found.\n");
					}
					printf("\nPress x to go back.\n");
					while(buttonPress!='x'&&buttonPress!='X'){
						scanf("%c",&buttonPress);
					}
					goto mainMenu;
				}
				break;
			}
			case 3:{
				cls();
				tutorial();
				printf("\nPress x to go back.\n");
				while(buttonPress!='x'&&buttonPress!='X'){
					scanf("%c",&buttonPress);
				}
				goto mainMenu;
				break;
			}
			case 4:{
				cls();
				char name[100];
				FILE* file=fopen("user.txt","w");
				printf("Insert new username: ");
				getchar();
				scanf("%[^\n]",&name);
				getchar();
				fprintf(file,"%s",name);
				fclose(file);
				printf("Username changed. Restart the game.");
				printf("\nPress x to go back.\n");
				while(buttonPress!='x'&&buttonPress!='X'){
					scanf("%c",&buttonPress);
				}
				goto mainMenu;
				break;
			}
			case 5:{
				cls();
				gameLive=0;
				break;
			}
			default:{
				cls();
				goto mainMenu;
				break;
			}
		}
	}
	
	return 0;
}
