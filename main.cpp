#include <stdio.h>
#include <stdlib.h>

void greeting();
void display();
void screenClear();

void takeIns();
int execution();

int instruct[100];
int memory[100];

int accumulator;
int insCounter = 0, insRegister = 0;
int operation, operand;

int main(){
	greeting();
	screenClear();
	
	greeting();
	display();
	takeIns();
}

void greeting(){
	printf("\n\t---------------------------------------------------------------------------------------------------");
	printf("\n\t|| \t\t\t\t\t\t\t || \t\t\t\t\t\t ||");
	printf("\n\t|| \t\t Welcome to Simpletron!\t\t\t ||    READ        10 | WRITE      11  \t ||");
	printf("\n\t|| \tPlease enter your program one instruction\t ||    LOAD        20 | STORE      21  \t ||");
	printf("\n\t|| \t(or data word) at a time. I will type the\t ||    ADD         30 | SUBTRACT   31  \t ||");
	printf("\n\t|| \tlocation number and a question mark (?).\t ||    DIVIDE      32 | MULTIPLY   33  \t ||");
	printf("\n\t|| \tYou then type the word for that location.\t ||    BRANCH      40 | BRANCHNEG  41  \t ||");
	printf("\n\t|| \tType the sentinel -99999 to stop entering\t ||    BRANCHZERO  42 | HALT       43  \t ||");
	printf("\n\t|| \t\t     your program.\t\t\t || \tEDIT PREVIOUS INSTRUCTION -1 \t ||");
	printf("\n\t---------------------------------------------------------------------------------------------------");
}

void screenClear(){
	printf("\n\n\tPress enter key to continue.");
	getchar();
	system("CLS");
}

void display(){
	int x, y, i = 0;
	
	printf("\n\n\tREGISTERS:");
	if(accumulator < 0)
		printf("\n\taccumulator \t\t%.4d", accumulator);
	else
		printf("\n\taccumulator \t\t %.4d", accumulator);
	printf("\n\tinstructionCounter \t   %.2d", insCounter);
	printf("\n\tinstructionRegister \t+%.4d", insRegister);
	printf("\n\toperationCode \t\t   %.2d", operation);
	printf("\n\toperand \t\t   %.2d", operand);
	printf("\n\n\tMEMORY:");
	printf("\n\t");
	
	for(x = 0; x < 10; x++){ //printing of first line in memory display 0 1 2 etc...
		printf("\t%d", x);
	}
	
	for(y = 0; y < 100; y += 10){
		printf("\n\t%d", y);
		for(x = 0; x < 10; x++){
			if(memory[i] < 0)
				printf("\t%.4d", memory[i]);
			else
				printf("\t+%.4d", memory[i]);
			i++;
		}
	}
}

void takeIns(){
	printf("\n\n\tInput instructions: \n");

	int flag = 1, flag2 = 1;
	int insNo = 0;
	while(flag){ //take in instructions until user input states "stop"s
		printf("\t%.2d ? ", insNo);
		scanf("%d", &instruct[insNo]); //take instruction
		
		while(flag2){
			if(instruct[insNo] == -1){
				insNo -= 2; //edit previous instruction
			} else if(instruct[insNo] == -99999 ){ //stop taking of instruction
				insCounter -= 2; //-99999 not included in counting
				flag2 = 0;
				flag = 0;
		//allowed ranges for instruction
			} else if(instruct[insNo] > 1000 && instruct[insNo] < 1199){
				flag2 = 0;
			} else if(instruct[insNo] > 2000 && instruct[insNo] < 2199){
				flag2 = 0;
			} else if(instruct[insNo] > 3000 && instruct[insNo] < 3399){
				flag2 = 0;
			} else if(instruct[insNo] > 4000 && instruct[insNo] < 4399){
				flag2 = 0;
			} else {
		//numbers outside of range
				printf("\tInvalid input. Please enter again: ");
				scanf("%d", &instruct[insNo]); //take instruction
			}
		}
		flag2 = 1; //to stop the taking of input
		
		insNo++;
		insCounter++;		
	}
	screenClear();
	printf("\n\t*** Program loading completed ***");
	screenClear();
	printf("\n\t*** Program execution begins ***");
	
	screenClear();
	execution();
}

int execution(){
	int flag = 1, flag2 = 1;
	int insNo = 0;
	
	display ();
	while(flag){
		if(instruct[insNo] == 4300){
			flag = 0;
		} else {
			operand = instruct[insNo] % 100;  //get the latter 2 digits
			operation = instruct[insNo] / 100;  //get the former digits
					
			printf("\n\n\t%.2d ? ", insNo);
			
			switch(operation){ //perform instruction
			//read and write
				case 10:
					printf("Reading Input: ");
					scanf("%d", &memory[operand]);
					while(flag2){
						if(memory[operand] > 9999 || memory[operand] <= -10000){
							printf("\tValue out of range(max: 9999, min: -9999).\n\tInput again: ");
							scanf("%d", &memory[operand]);
						} else
							flag2 = 0;
					}
					break;
				case 11:
					printf("The final value is: %.4d", accumulator);
					break;
			//load and store
				case 20:
					printf("Load value of slot %d to accumulator.", operand);
					accumulator = memory[operand];
					break;
				case 21:
					printf("Store value of accumulator to slot %d.", operand);
					memory[operand] = accumulator;
					break;
			//arithmetic operations
				case 30: //add
					printf("%d (accumulator) added with %d from slot %d", accumulator, memory[operand], operand);
					accumulator += memory[operand];
					break;
				case 31: //subtract
				printf("%d (accumulator) subtracted with %d from slot %d", accumulator, memory[operand], operand);
					accumulator -= memory[operand];
					break;
				case 32: //divide
					if(memory[operand] != 0){
						printf("%d (accumulator) divided with %d from slot %d", accumulator, memory[operand], operand);
						accumulator /= memory[operand];
					} else {
						printf("Undefined value.");
					}
					break;
				case 33: //multiply
					printf("%d (accumulator) multiplied with %d from slot %d", accumulator, memory[operand], operand);
					accumulator *= memory[operand];
					break;
			//branching
				case 40: //branch
					if(accumulator > 0){
						printf("Branching to instruction %.2d", operand);
						insNo = operand - 1;
					}
					break;
				case 41: //negbranch
					if(accumulator < 0){
						printf("Branching to instruction %.2d", operand);
						insNo = operand - 1;
					}
					break;
				case 42: //zerobranch
					if(accumulator == 0){
						printf("Branching to instruction %.2d", operand);
						insNo = operand - 1;
					}
					break;
					
			}
			
			if(accumulator > 9999 || accumulator < -9999){
				accumulator = 0;
				printf("\n\n*** Error. Values are out of range. ***");
				return 0;
			}
			
			insCounter--; //less count per performed instruction
			insRegister = instruct[insNo]; //instruction performed
			
			screenClear();
			display();
			
			insNo++;
		}
	}
	
	printf("\n\n\t*** Program terminated ***");
	return 0;
}
