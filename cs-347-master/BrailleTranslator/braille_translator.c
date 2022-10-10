/**
 * Name:Andrew Murphy
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAR (30)

FILE* in_file;
FILE* out_file;

/*This method will write the Braille letters either horizontally or vertically
 to the output_file.

 @param braille_line: an array of int arrays(Braille letters).
 @param length: length of braille_line, number of Braille letters in line.

 @return 1 on success, -1 if an error occurs*/
int write_braille_to_file(int **braille_line, int length){
	char str[(sizeof(char)*13*length)];
	int index = 0;
	for (int i = 0; i < length; i++){
		if (*braille_line != NULL){
			int * braille_letter = *braille_line;
			str[index] = braille_letter[0];
			index++;
			str[index] = ' ';
			index++;
			str[index] = braille_letter[3];
			index++;
			str[index] = '\n';
			index++;
			str[index] = braille_letter[1];
			index++;
			str[index] = ' ';
			index++;
			str[index] = braille_letter[4];
			index++;
			str[index] = '\n';
			index++;
			str[index] = braille_letter[2];
			index++;
			str[index] = ' ';
			index++;
			str[index] = braille_letter[5];
			index++;
			str[index] = '\n';
			index++;
			str[index] = '\n';
			index++;
			str[index] = '\n';
		}
		braille_line++;
	}
	index++;
	str[index] = '\0';
	fseek(out_file, 0, SEEK_END);
	if (fwrite(str, sizeof(char), sizeof(str)/sizeof(char), out_file) != sizeof(str)){
		return -1;
	}
	return 1;
}

/*This method translates an ASCII char to an array of 6 ints(a Brailler letter):
 0 3
 1 4
 2 5

 @param letter: the ASCII char to be translated.

 @return an int* that represents a Braille char, or NULL if that char is invalid.*/
int *ASCII_to_braille(char letter){
	//I used 48 and 49 as my ints since that will correlate to 0's and 1's when they are printed as chars
	//initialize all 'dots' to 0
	int* braille = malloc(6*sizeof(int));
	for (int i = 0; i < 6; i++){
		braille[i] = 48;
	}
	//treat space as a special case
	if (letter == ' ' || letter == '.' || letter == ',' || letter == '"' || letter == 39){
		return braille;
	}
	//converts numbers to letter 1->a
	if (letter > '/' && letter < ':'){
		letter += 49;
	}
	//if the letter is uppercase, then make it lowercase
	if (letter > '@' && letter < '['){
		letter += 32;
	}
	//treat w as a special case
	if (letter == 'w'){
		braille[1] = 49;
		braille[3] = 49;
		braille[4] = 49;
		braille[5] = 49;
		return braille;
	}
	//for all letters besides w
	if (letter > '`' && letter < '{' && letter != 'w'){
		int decade = (letter - 'a') / 10;
		int modulus = (letter - 'a') % 10;
		//setup 'decade dots'
		if (decade == 1){
			braille[2] = 49;
		}
		else if (decade == 2){
			braille[2] = 49;
			braille[5] = 49;
		}
		//now we go through the modulus's to setup the 0, 1, 3 and 4 dots
		//0 dot
		if (modulus != 8 && modulus != 9){
			braille[0] = 49;
		}
		//1 dot
		if (modulus > 4 || modulus == 1){
			braille[1] = 49;
		}
		//3 dot
		if (modulus == 2 || modulus == 3 || modulus == 5 || modulus == 6 || modulus == 9){
			braille[3] = 49;
		}
		//4 dot
		if (modulus == 3 || modulus == 4 || modulus == 6 || modulus == 7 || modulus == 9){
			braille[4] = 49;
		}
		return braille;
	}
	return NULL;
}

/*This method reads from in_file up to MAX_CHAR per call to fread(), then builds an
 array of Braille letters by calling ASCII_to_braille(). It will write the Braille
 to out_file by calling write_braille_to_file().

 @return 1 on success, and -1 if an error occurs.*/
int translate_to_braille(){
	char ascii[MAX_CHAR];
	int amtRead = 1;
	while (amtRead){
		amtRead = fread(ascii, sizeof(char), MAX_CHAR, in_file);
		if (ferror(in_file)){
			return -1;
		}
		int* braille[amtRead];
		for (int i = 0; i < amtRead; i++){
			if (!ASCII_to_braille(ascii[i])){
				amtRead--;
			}
			braille[i] = ASCII_to_braille(ascii[i]);
		}
		write_braille_to_file(braille, amtRead);
	}
	return 1;
}

/*The program should validate that only one argument was supplied, and that it opens
 a valid file. The in_file will be translated from ASCII to Braille. It will create
 the output file, and call translate_to_braille().

 The program should output the translation to a file named in_file.txt.output.
 e.g.: in_file: some_text.txt
       out_file: some_text.txt.output

 @return 0 on success, and a 1 on error, exiting.*/
//original int main(int argc, char** argv[]){
int main(int argc, char** argv){
	if (argc != 2){
		printf("Usage:\n./braille <src_file_name>\n");
		return 1;
	}
	in_file = fopen(argv[1], "r");
	if (in_file){
		out_file = fopen(strcat(argv[1], ".output"), "w");
		translate_to_braille();
		fclose(out_file);
		fclose(in_file);
		return 0;
	}
	else {
		printf("Invalid filename\n");
		fclose(in_file);
		return 1;
	}
}
