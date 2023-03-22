#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
int main (int argc, char* argv[]){
	if(argc<2){
		printf("Specifica il file!\n");
		return 1;
	}
	char file[20];
	strcpy(file, argv[1]);
	file[strlen(file)-1]='e';
	strcat(file, "xe");
	pid_t pid = fork();
	if(pid<0){
		printf("Errore nella fork!\n");
		return 1;
	}
	if (pid==0){
		execlp("/bin/gcc", "gcc", argv[1], "-o", file, NULL);
		printf("Errore nell'esecuzione del comando!\n");
		return 1;
	}
	wait(NULL);
	FILE *fp = popen("/bin/pwd", "r");
	  if (fp == NULL) {
	    printf("Comando fallito!\n" );
	    return 1;
	}
  	char path[100];
	fgets(path, sizeof(path), fp);
	pclose(fp);
	path[strlen(path)-1]='/';
	strcat(path, file);

	if(argc>2) {
		char** args = (char**) malloc((argc)*sizeof(char*));
		args[0] = (char*) malloc(sizeof(file));
		strcpy(args[0], file);
		for(int i=0; i<argc-2; i++){
			args[i+1] = (char*) malloc(sizeof(argv[i+2]));
			strcpy(args[i+1], argv[i+2]);
			//fprintf(stdout, "%d: %s\n", i+1, args[i]);
		}
		args[argc-1] = NULL;
		//fprintf(stdout, "str: %s\n", args[2]);
		execvp(path, args);
		printf("Errore nell'esecuzione 1!\n");
		return 1;
	}
	execlp(path, file, NULL);
	printf("Errore nell'esecuzione 2!\n");
	return 1;
}
