#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])

{
	if (argc < 2){
		printf("Need a filename.");
		return 1;
	}
	mode_t file_perm;          /* File permissions */
	struct stat file_details;  /* Detailed file info */


	/* Retrieve the file details */
	struct stat data;
	if (lstat(argv[1], &data) != 0){
		printf("Oh no! BAD NIGHTMARE!");
		return 1;
	}
	/* Get the file type */
	char* fileType;
	if (S_ISREG(data.st_mode)){
		printf("Output sample for the file %s\nFile Type : Regular\n", argv[1]);
	}
	else {
		printf("Output sample for a Directory\nFile Type : Directory\n");
	}
	/* Get the time of last access of the file */
	time_t date = data.st_atime;
	printf("Time of last access : %s", ctime(&date));
	/* Get the file permissions */
	printf("File Permissions:\n");
	printf("User : ");
	if (!(data.st_mode & S_IRUSR)){
		printf("Not ");
	}
	printf("Readable, ");
	if (!(data.st_mode & S_IWUSR)){
		printf("Not ");
	}
	printf("Writable, ");
	if (!(data.st_mode & S_IXUSR)){
		printf("Not ");
	}
	printf("Executable\nGroup : ");
	if (!data.st_mode & S_IRGRP){
		printf("Not ");
	}
	printf("Readable, ");
	if (!(data.st_mode & S_IWGRP)){
		printf("Not ");
	}
	printf("Writable, ");
	if (!(data.st_mode & S_IXGRP)){
		printf("Not ");
	}
	printf("Executable\nOthers : ");
	if (!(data.st_mode & S_IROTH)){
		printf("Not ");
	}
	printf("Readable, ");
	if (!(data.st_mode & S_IWOTH)){
		printf("Not ");
	}
	printf("Writable, ");
	if (!(data.st_mode & S_IXOTH)){
		printf("Not ");
	}
	printf("Executable\n");
}
