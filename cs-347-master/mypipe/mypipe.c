/*****************************************************************************
*Write a program that executes two commands using a pipe*
*The two commands should be entered by the user as arguments enclosed by " " and separated by |, e.g. ./mypipe "command1 | command2"
*If no arguments are entered by the user, the program will assume command 1 is ls -l and command 2 is sort.
*The correctness of both commands is totally at the discretion of the user                           *
*The program should execute  the commands in pipe and show the output (if any)
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>               /* strsep, etc. */

#define MAX_NUM_ARGS 20           /* Maximum number of arguments allowed */
#define MAX_STR_LEN 200           /* Maximum string length */



int main(int argc, char * argv[])
{
       int fd[2];                 /* Two ends of the pipe */
       char * lhs = NULL;         /* Left hand side command of the pipe */
       char * rhs = NULL;          /* Right hand side command of the pipe */
       char * lhscommand = "ls";  /* Default command name on left hand side of pipe */
       char * rhscommand = "sort"; /* Default command name on right hand side of pipe */
       char * lhsargs[MAX_NUM_ARGS] = { "ls", "-l", NULL };   /* Default LHS args */
       char * rhsargs[MAX_NUM_ARGS] = { "sort", NULL };       /* Default RHS args */

       /*Parse the user input to extract the commands and their arguments*/
       /*Hint: read about strsep(3) */
	if (argc == 2){
		lhs = strsep(&argv[1], "|");
		rhs = strsep(&argv[1], "|");
		char * tmp;
		if (lhs != NULL){
			*lhsargs = NULL;
		}
		if (rhs != NULL){
			*rhsargs = NULL;
		}
		for (int i = 0; i < MAX_NUM_ARGS; i++){
			if ((tmp = strsep(&lhs, " ")) == NULL){
				lhsargs[i] = NULL;
				break;
			}
			if (tmp[0] == '\0'){
				i--;
				continue;
			}
			lhsargs[i] = tmp;
		}
		for (int i = 0; i < MAX_NUM_ARGS; i++){
			if ((tmp = strsep(&rhs, " ")) == NULL){
				break;
			}
			if (tmp[0] == '\0'){
				i--;
				continue;
			}
			rhsargs[i] = tmp;
		}
		lhscommand = lhsargs[0];
		rhscommand = rhsargs[0];
	}
	else if (argc > 2){
		printf("Usage:\n./mypipe [\"<LHS-command>|<RHS-command>\"]");
		return 0;
	}
       /* Create the pipe */
       pipe(fd);     /* fd[0] is read end, fd[1] is write end */

       /* Do the forking */
       switch ( fork() )
       {
		case -1:
			perror("Error with fork.\n");
			break;
		//child
		case 0 :
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
			if (execvp(lhscommand, lhsargs)){
				printf("Usage:\n./mypipe [\"<LHS-command>|<RHS-command>\"]\n");
			}
			break;
		//parent
		default :
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (execvp(rhscommand, rhsargs) == -1){
				printf("Usage:\n./mypipe [\"<LHS-command>|<RHS-command>\"]\n");
			}
			break;
	}
}
