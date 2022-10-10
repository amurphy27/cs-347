#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	//Check for the correctness of the entered command. If it is incorrect, display a usage message
	if (argc != 3 || argv[2] == NULL || strcmp(argv[1], "-e") != 0 || strcmp(argv[1], "-d") != 0){
		printf("Usage:\n./filesec -e|-d [filename]");
	}

	char outputFile[128];
	char* command = argv[1];
	char* file = argv[2];

	if (strcmp(argv[1], "-e") == 0){
		int pFile = open(file, O_RDONLY);
		strcpy(outputFile, file);
		strtok(outputFile, ".");
		strcat(outputFile, "_enc.txt");

		//encrypt the contents of the input file and save the results in the output file. Do not forget to create the output file
		//create file for output
		int newFile = open(outputFile, O_RDWR | O_APPEND | O_CREAT, 0644);
		//read file the encrypt it into new file
		int size;
		char ch[0];
		while((size = read(pFile, ch, 1)) > 0){
			ch[0]+=100;
			write(newFile, ch, size);
		}
		//close the files
		close(pFile);
		close(newFile);
		return 0;
	}

	if (strcmp(argv[1], "-d") == 0){
		int pFile = open(file, O_RDONLY);
		//create and open the output file
		strcpy(outputFile, file);
		strtok(outputFile, ".");
		strcat(outputFile, "_dec.txt");
		int newFile = open(outputFile, O_RDWR | O_APPEND | O_CREAT, 0644);
		//decrypt the contents of the input file and save the results in the output file
		int size;
		char ch[0];
		while((size = read(pFile, ch, 1)) > 0){
			ch[0]-=100;
			write(newFile, ch, size);
		}
		//close the files
		close(pFile);
		close(newFile);
		return 0;
	}

}

