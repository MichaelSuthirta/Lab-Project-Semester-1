#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
extern int menu();
extern void game();
extern void tutorial();
extern void cls();

int main(int argc, char *argv[]) {
	char buttonPress='0';
	int gameLive=1;
	
	while(gameLive==1){
		int input;
		
		mainMenu:
			cls();
			input=menu();
	
		switch(input){
			case 1:{
				game();
				break;
			}
			case 2:{
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
				gameLive=0;
				break;
			}
			default:{
				cls();
				menu();
				break;
			}
		}
	}
	
	return 0;
}
