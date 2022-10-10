#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 32               /* Size of buffer */

#define FILE_NAME_LEN 200         /* Maximum length of file name */



int main(int argc, char *argv[]){
	if (argc < 2){//Checks for correct input
		printf("Expecting 1 filename.\n");
	}
	char output[BUF_SIZE];//output char array of length BUF_SIZE since we will never encounter anything longer in 1 iteration
	for (int i = 1; i < argc; i++){
		if (strlen(argv[i]) > FILE_NAME_LEN){//checks to make sure the length of the filename is below the max, if it is skip that file
			continue;
		}
		int inFile = open(argv[i], O_RDONLY);//opens input file
		if (inFile == -1){//error handling for open
			perror("Error opening the file for reading.\n");
			continue;
		}
		int amtRead;//holder for the amount read by read so we can check for errors later
		while ((amtRead = read(inFile, output, BUF_SIZE)) > 0){//while there is stuff to read write into stdout
			if(write(1, output, amtRead) == -1){//error handling for writing
				perror("Error while writing to standard output.\n");
				continue;
			}
		}
		if (amtRead == -1){//error handling for reading goes here since if an error occurs the while loop won't run
			perror("Error while reading the file.\n");
			continue;
		}
		close(inFile);//close input file
	}
	return 0;
}

