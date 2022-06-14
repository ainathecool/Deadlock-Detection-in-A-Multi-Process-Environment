#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdbool.h>

void task5(char const* const fileN);
void task134(char const* const fileN);
void task2(char const* const fileN);

int main(int argc, char* argv[])
{
	
	char const* const fileN = argv[2];
	if((strcmp(argv[1], "-f") == 0) && (strcmp(argv[3], "d") == 0)) 
	{
		task134(fileN);
	}
	
	if((strcmp(argv[3], "-e") == 0) && (strcmp(argv[1], "-f") == 0))
	{
		task2(fileN);
	}
	
	if((strcmp(argv[3], "-c") == 0) && (strcmp(argv[1], "-f") == 0))
	{
		task5(fileN);
	}
	
	
	
	return 0;	
}

void task134(char const* const fileN)
{
	printf("\nin task 134");
	
	//task1 -for total no of processes
	
	FILE *countP;
	countP = fopen(fileN, "r");
	if(countP == NULL)
	{
		puts("Error: Unable to open file.");
		exit(0);
	}
	
	int c=0, fNum =0, dup =0;
	int fID = 0, lf =0, wlf =0; //file id, locked file, waiting for lock file
	char ch;
	char lockedF[10];
	char waitLockF[10];
	char fileIDs[10];
	char totalF[30];
	int deadlock =0;
	int terminate = 0;
	int numF[30];
	int num[10][10];
	
	
	for(ch = getc(countP); ch!= EOF; ch = getc(countP))
	{
		if(ch=='\n')
			c++;
			
	}

	fclose(countP);
	
	printf("\nProcesses: %d", c);

	FILE *deadlockP;
	deadlockP = fopen(fileN, "r");
	
	if(deadlockP == NULL)
	{
		puts("Error: Unable to open file.");
		exit(0);
	}
	
	for(int i =0; i<c ;i++)
	{
		(fscanf(deadlockP, "%d%d%d", &fID, &lf, &wlf));
		fileIDs[i] = fID;
		lockedF[i] = lf;
		waitLockF[i] = wlf;
		num[i][1]= lf;
		num[i][2] = wlf;
		printf("\n%d %d %d", fID, lf, wlf);
		
	}
	
	int s = 0, found = 0;
	bool matched = false;
	
	for(int i =0;i<c;i++)
	{
		for(int j =0;j<3;j++)
		{
			if(j==1 || j==2)
			{
				matched = false;
				found = 0;
				for(int k =i;k<c;k++)
				{
					for(int l=1;l<3;l++)
					{
						if(num[i][j] == num[k][l])
						{
							found++;
							if(found==2)
							{
								matched = true;
								break;
							}
						}
					}
					if(matched)  break;
				}
					if(!matched)
					{
						fNum++;
					}
			}
		}
	}
	
	printf("\nFiles: %d", fNum);
	
	for(int i =0; lockedF[i] != '\0'; i++)
	{
	if((lockedF[i] == waitLockF[i+1] && lockedF[i+1] == waitLockF[i]))
		{	deadlock = 1; 
				
			if(fileIDs[i] < fileIDs[i+1])
				{ terminate = 1;
					printf("\nTerminate: ");
					if( terminate == 0)
						printf(" %d", fileIDs[i+1]);
					else
						printf(" %d", fileIDs[i]);
				}	
		}
		else
		{
			if(deadlock != 1)
			{
				deadlock = 0;
				terminate = 0;
			}	
		}
		
		
		if((lockedF[i] == fileIDs[i+1] && waitLockF[i] == lockedF[i+1]) && (deadlock == 0))
		{	deadlock = 1; 
				
			
			
			if(fileIDs[i] < fileIDs[i+1])
				{ terminate = 1;
					printf("\nTerminate: ");
					if( terminate == 0)
						printf(" %d", fileIDs[i+1]);
					else
						printf(" %d", fileIDs[i]);
				}	
			
		}
		else
		{
			if(deadlock != 1)
			{
				deadlock = 0;
				terminate = 0;
			}			
		}
	}
	
	fclose(deadlockP);
	
	if(deadlock == 1)
	{
		printf("\nDeadlock detected.");
		
	}
		
	else
		{printf("\nNo Deadlock.");}
	

}

void task2(char const* const fileN)
{
	printf("\non task 2");
	
	FILE *countP;
	countP = fopen(fileN, "r");
	if(countP == NULL)
	{
		puts("Error: Unable to open file.");
		exit(0);
	}
	
	int c=0, fNum =0, dup =0;
	int fID = 0, lf =0, wlf =0; //file id, locked file, waiting for lock file
	char ch;
	char lockedF[10];
	char waitLockF[10];
	char fileIDs[10];
	char totalF[30];
	int deadlock =0;
	int terminate = 0;
	int numF[30];
	int num[10][10];
	
	
	for(ch = getc(countP); ch!= EOF; ch = getc(countP))
	{
		if(ch=='\n')
			c++;
			
	}

	fclose(countP);
	
	printf("\nProcesses: %d", c);

	FILE *deadlockP;
	deadlockP = fopen(fileN, "r");
	
	if(deadlockP == NULL)
	{
		puts("Error: Unable to open file.");
		exit(0);
	}
	
	for(int i =0; i<c ;i++)
	{
		(fscanf(deadlockP, "%d%d%d", &fID, &lf, &wlf));
		fileIDs[i] = fID;
		lockedF[i] = lf;
		waitLockF[i] = wlf;
		num[i][1]= lf;
		num[i][2] = wlf;
		printf("\n%d %d %d", fID, lf, wlf);
		
	}
	
	int s = 0, found = 0, repeat = 0, distinct = 0, total = 0;;
	bool matched = false;
	
	for(int i =0;i<c;i++)
	{
		for(int j =0;j<3;j++)
		{
			if(j==1 || j==2) //checking for locked and requested files both sly using 1 and 2
			{
				matched = false;
				found = 0;
				for(int k =i;k<c;k++)
				{
					for(int l=1;l<3;l++) 
					{
						if(num[i][j] == num[k][l])
						{
							found++;// if duplicate file found and when it's true then repeat files ++
							if(found==2)
							{
								matched = true;
								repeat++;
								break;
							}
						}
					}
					if(matched)  break;
				}
					if(!matched)
					{
						fNum++;
						distinct++;
					}
			}
		}
	}
	
	printf("\nFiles: %d", fNum);
	
	for(int i =0; lockedF[i] != '\0'; i++)
	{
	if((lockedF[i] == waitLockF[i+1] && lockedF[i+1] == waitLockF[i]))
		{	deadlock = 1; 
				
			if(fileIDs[i] < fileIDs[i+1])
				{ terminate = 1;
					printf("\nTerminate: ");
					if( terminate == 0)
						printf(" %d", fileIDs[i+1]);
					else
						printf(" %d", fileIDs[i]);
				}	
		}
		else
		{
			if(deadlock != 1)
			{
				deadlock = 0;
				terminate = 0;
			}	
		}
		
		
		if((lockedF[i] == fileIDs[i+1] && waitLockF[i] == lockedF[i+1]) && (deadlock == 0))
		{	deadlock = 1; 
				
			
		}
		else
		{
			if(deadlock != 1)
			{
				deadlock = 0;
				terminate = 0;
			}			
		}
	}
	
	fclose(deadlockP);
	
	if(deadlock == 1)
	{
		printf("\nDeadlock detected. No minimum time execution.");
		
	}
		
	else
		{printf("\nNo Deadlock. ");
			
				
				
				bool matchedFile = false;
				int matchedIndex = 0;
				int matchedFiles[c];
				
				for(int i =0;i<c;i++)
				{
					for(int j =0;j<3;j++)
					{
						if(j==2) //2 bcs we are only checking req files rn
						{
							matchedFile = false; //if stil no match
							
							for(int k =0;k<c;k++)
							{
								if(num[i][j] == 0) break;
								
								if(num[i][j] == matchedFiles[k])
								{
									matchedFile = true;
								}
							}
							if(!matchedFile)
							{
								matchedIndex++;
								matchedFiles[matchedIndex] = num[i][j]; //uss index pa apna mathced betha dou
							}
						}
					}
					
					
				}
				
				distinct = 0;
					for(int l =0; l<matchedIndex+1;l++)
					{
						repeat = 0;
						for(int j =0;j<c;j++)
						{
							if(matchedFiles[l] == num[j][2])
							{
								repeat++; //jitni times repeat hoga utna time lagay ga
							}
						}
						if(repeat>distinct)
						{
							distinct = repeat; 
						}
					}
					
					total = distinct +1; //bcs started w 0 and takes 1 unit time for distincr files
				
				printf("\n Minimum Execution Time: %d", distinct);
		}
	
	
	
	
}

void task5(char const* const fileN)
{
	printf("\nin task 5");
	
	FILE *countP;
	countP = fopen(fileN, "r");
	if(countP == NULL)
	{
		puts("Error: Unable to open file.");
		exit(0);
	}
	
	int c=0, fNum =0, dup =0;
	
	int fID = 0, lf =0, wlf =0; //file id, locked file, waiting for lock file
	char lockedF[10], waitLockF[10], fileIDs[10], totalF[30], temp, ch, i1[20], i2[20], i3[20];
	int deadlock =0, terminate = 0, exist=0, allocated[30];
	
	
	for(ch = getc(countP); ch!= EOF; ch = getc(countP))
	{
		if(ch=='\n')
			c++;
			
	}

	fclose(countP);
	
	
	FILE *deadlockP;
	deadlockP = fopen(fileN, "r");
	
	if(deadlockP == NULL)
	{
		puts("Error: Unable to open file.");
		exit(0);
	}
	
	
	int size = c+2;
	int process[size];
	
	for(int i =0; i<c ;i++)
	{
		(fscanf(deadlockP, "%d %d %d", &fID, &lf, &wlf));
		fileIDs[i] = fID;
		lockedF[i] = lf;
		waitLockF[i] = wlf;
	
		sprintf(i1, "%d", fID);
		sprintf(i2, "%d", lf);
		sprintf(i3, "%d", wlf);
		strcat(i1,i2);
		strcat(i1,i3);
		
		int c = atoi(i1);
		
		//printf("\n process concat: %d",c);
		process[i] = c;
		
		//printf("\n process sa%d", process[i]);
		//printf("%d%d%d", fID, lf, wlf);*/
		
	}
	
	//printf("\nFiles: %d", fNum);
	
	int counter = 0; 
	int j =0;
	for(int i =0; lockedF[i] != '\0'; i++)
      {
	if(lockedF[i] == waitLockF[i+1] && lockedF[i+1] == waitLockF[i] || (lockedF[i] == fileIDs[i+1] && waitLockF[i] == lockedF[i+1]))
		{	deadlock = 1; 
			
			if(c/2 != counter)
			{
				temp = process[i];
				process[i] = process[i+3];
				process[i+3] = temp;
				counter++;
				allocated[j] = process[i];
				j++;
				i++;
			}
	
			

		}
		else
		{
			if(deadlock != 1)
			{
				deadlock = 0;
				
			}
				
		}
	
	}
	fclose(deadlockP);
	
	int time = 0; 
	if(deadlock == 1)
	{
		time = 0;
		counter=0;
		printf("\nReallocation of process in deadlock free manner:");
		for(int i =0 ;i<c;i++)
		{
			counter++;
			printf("\n %d  %d", time, process[i]);
			if(counter == c/2)
				time++;
		}
		
		printf("\nsimulation time: %d", time+1);
	}
	else
		printf("\nNo Reallocation since no deadlock.");
		
	

}





