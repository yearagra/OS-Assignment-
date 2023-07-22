#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <libgen.h> 
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <dirent.h>


int main(){
	int Max_Size = 100;
	
	char line[Max_Size];
	int ctr=0;

	char Root_Folder[100];
	getcwd(Root_Folder,sizeof(Root_Folder));

	while (1){
		printf("My Shell");
		fgets(line,Max_Size,stdin);
		

		if(line==NULL){
			break;
		}

		char *history[100];
		history[ctr]=strdup(line);
		
		ctr++;
		

		char root[100];
		strcpy(root,Root_Folder);
		char *final=line;
		char *inCmd[5];
		inCmd[0]="exit";
        inCmd[1]="echo";
		inCmd[2]="cd";
		inCmd[3]="pwd";
		inCmd[4]="history";

		int command_check=0;

		char *present_dir;
		char curr_path[100];
		char buff[1000];

		char *tkn=NULL;
		tkn=strtok(line," ");
		
		char *exec[100];
		int i=0;
		
		while(tkn !=NULL){
			exec[i] = (char *) malloc(strlen(tkn)+1);
			strcpy(exec[i],tkn);
			tkn=strtok(NULL," ");
			i++;
		}
		
		exec[i]=NULL;

		if(strcmp(exec[0],inCmd[0])==0){
			break;
		}
		else if(strcmp(exec[0],inCmd[1])==0){
			command_check=1;
			if(exec[1]==NULL){
				chdir("/home/verma");
			}
			else{
				int check=chdir(exec[1]);
				present_dir=getcwd(buff,sizeof(buff));
				if(check==-1){
					printf("Invalid path\n");
				}
			}
		}
		else if(strcmp(exec[0],inCmd[2])==0){
			command_check=1;
			getcwd(curr_path,sizeof(curr_path));
			printf("current working directory : %s\n", curr_path);
			printf("pwd cmd\n" );
		}
		else if(strcmp(exec[0],inCmd[3])==0){
			command_check=1;			
			for (int x = ctr-1;x>=0;--x){
				printf("print %s\n", history[x]);
			}
			int j=ctr-1;
			int ct=0;
			while(history[j]!= NULL && ct<10){
				printf("%s \n",history[j] );
				j--;
				ct++;
			}
		}
		else if(strcmp(exec[0],inCmd[4])==0){
			command_check=1;
			if(exec[1]==NULL){
				printf("\n");
			}
			else if(strcmp(exec[1],"-n")==0){
			}
			else{
				i=1;				
				while(exec[i]!= NULL){
					printf("%s",exec[i] );
					i++;
				}
				printf("\n");				
			}			
		}
		
		if(fork()==0){			
			if(strcmp(exec[0],"ls")==0){				
					strcat(root,"/ls");
					execv(root,exec);				
			}
			else if(strcmp(exec[0],"cat")==0){
				
					strcat(root,"/catto");
					execv(root,exec);										
			}
			else if(strcmp(exec[0],"rm")==0){
				if(exec[1]==NULL){
					printf("Enter a name\n");
				}
				else{
					strcat(root,"/rem");
					execv(root,exec);				
				}
			}
			else if(strcmp(exec[0],"date")==0){			
				strcat(root,"/dato");
				execv(root,exec);				
			}
			else if(strcmp(exec[0],"mkdir")==0){				
				strcat(root,"/mak");
				execv(root,exec);
			}
			else {
				if(command_check==0)
					printf("Command not found\n");
			}
			exit(0);
		}
		else{
			wait(NULL);
		}
	}
	return 0;
}