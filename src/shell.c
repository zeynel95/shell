/*
 * Copyright (C) 2002, Simon Nieuviarts
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readcmd.h"
#include "csapp.h"

void interprete(cmdline* l){
	int i = 0;
	if(!strcmp(l->seq[0][0], "quit")){
		exit(0);
	}
	else{
		if(Fork() == 0)
		{
			int Tact[2];
			int Tprec[2];

			if (l->in)
			{
				int fd1 = Open(l->in, O_RDONLY, 0);
				Dup2(fd1, 0);
				Close(fd1);
			}

			if (l->out){
				int fd2 = Open(l->out, O_WRONLY | O_CREAT, 0);
				Dup2(fd2,1);
				Close(fd2);
			}
			
			for (i=0; l->seq[i]!=0; i++){
				// cas particulier
				if(l->seq[i+1]!=0)	
					pipe(Tact);

				if (Fork() == 0)
				{
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
					waitpid(-1, NULL, 0);
					close(Tact[1]);
					Tprec[0] = Tact[0];
				} 

			}
		}
		waitpid(-1, NULL, 0);
	}
}


int main()
{
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
		interprete(l);
	}
}
