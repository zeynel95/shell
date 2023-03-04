/*
 * Copyright (C) 2002, Simon Nieuviarts
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readcmd.h"
#include "csapp.h"

int Tpid[50];

void ajouter(int p){
	int  i = 0;
	while (Tpid[i] != -1)
	{
		i++;
	}
	Tpid[i] = p;
}

void supprimmer(int p){
	for (int i = 0; i < 50; i++)
	{
		if(Tpid[i] == p)
		{
			Tpid[i] = -1;
			return ;
		}
	}
	
}

void init(){
	for (int i = 0; i < 50; i++)
	{
		Tpid[i] = -1;
	}
}

int est_vide(){
	for (int i = 0; i < 50; i++)
	{
		if (Tpid[i] != -1)
			return 0;		
	}
	return 1;
}

void interprete(cmdline* l){
	int pid;
	int i = 0;
	if(l->seq[0] == NULL) return;
	if(!strcmp(l->seq[0][0], "quit")){
		exit(0);
	}
	else{
			int Tact[2];
			int Tprec[2];

			// int saved_stdin;
			// int saved_stdout;

			// if (l->in)
			// {
			// 	// saved_stdin = dup(STDIN_FILENO);
			// 	int fd1 = Open(l->in, O_RDONLY, 0);
			// 	Dup2(fd1, 0);
			// 	Close(fd1);
			// }

			// if (l->out){
			// 	// saved_stdout = dup(STDOUT_FILENO);
			// 	int fd2 = Open(l->out, O_WRONLY | O_CREAT, 0);
			// 	Dup2(fd2,1);
			// 	Close(fd2);
			// }
			
			for (i=0; l->seq[i]!=0; i++){
				// cas particulier
				if(l->seq[i+1]!=0)	
					pipe(Tact);

				if ((pid = Fork()) == 0)
				{
					
					if (l->in)
					{
						// saved_stdin = dup(STDIN_FILENO);
						int fd1 = Open(l->in, O_RDONLY, 0);
						Dup2(fd1, 0);
						Close(fd1);
					}

					if (l->out){
						// saved_stdout = dup(STDOUT_FILENO);
						int fd2 = Open(l->out, O_WRONLY | O_CREAT, 0);
						Dup2(fd2,1);
						Close(fd2);
					}

					if(l->seq[i+1]!=0){
						close(Tact[0]);
						dup2(Tact[1], 1);
						close(Tact[1]);
					}

					if(i>0){
						dup2(Tprec[0], 0);
						close(Tprec[0]);
					}

					if(execvp(l->seq[i][0], l->seq[i]) == -1){
						printf("Erreur commande !!!\nCode erreur %d\n", errno);
						exit(-1);
					}
				}
				else{
					ajouter(pid);
					close(Tact[1]);
					Tprec[0] = Tact[0];
				} 
			}
			if(l->bg == 1){
				while(waitpid(-1, NULL, WNOHANG)>0);
				init();
			}
			else{
				while(!est_vide()){
					pid = waitpid(-1, NULL, 0);
					supprimmer(pid);
				}
			}
			// if (l->in)
			// {
			// 	dup2(saved_stdin, STDIN_FILENO);
			// }

			// if (l->out){
			// 	dup2(saved_stdout, STDOUT_FILENO);
			// }
		}
}
void child_handler(int sig) {
    int pid;
	while((pid = waitpid(-1, NULL, WNOHANG))>0){
		supprimmer(pid);
	}
}

// void int_handler(int sig){
// 	// for(int i = 0; i < 50; i++){
// 	// 	if(Tpid[i] != -1)
// 	// 		Kill(Tpid[i],SIGKILL);
// 	// }
// 	printf("\nshell> ");
// }


int main()
{
	// on initialise Tpid
	init();
	

	Signal(SIGCHLD, child_handler);
	// Signal(SIGINT, int_handler);
	while (1) {
		cmdline *l;
		// int i, j;

		printf("shell> ");
		l = readcmd();

		/* If input stream closed, normal termination */
		if (!l) {
			printf("exit\n");
			exit(0);
		}

		if (l->err) {
			/* Syntax error, read another command */
			printf("error: %s\n", l->err);
			continue;
		}

		// if (l->in) printf("in: %s\n", l->in);
		// if (l->out) printf("out: %s\n", l->out);

		/* Display each command of the pipe */
		// for (i=0; l->seq[i]!=0; i++) {
		// 	char **cmd = l->seq[i];
		// 	printf("seq[%d]: ", i);
		// 	for (j=0; cmd[j]!=0; j++) {
		// 		printf("%s ", cmd[j]);
		// 	}
		// 	printf("\n");
		// }
		// printf("  (bg) = %d\n", l->bg);

		interprete(l);
	}
}
