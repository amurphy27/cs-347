#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define FALSE (0)
#define TRUE  (1)

int main() {
	int tot_chars = 0 ;	/* total characters */
	int tot_lines = 0 ;	/* total lines */
	int tot_words = 0 ;	/* total words */
	//char for the current character we are looking at and the previous one
	char ch = getchar();
	char prevch = ' ';
	//while loop that goes till the end of input, checks for newline character to add to line counter,
	//then checks if the current character is a blank space and the previous character was not a blank
	//space which would indicate that we should add to the word counter, and lastly add to character
	//counter every loop and iterate by making prevch the current and the current ch look at the next
	//character for the next loop. Then print out the totals.
	while (ch != -1){
		if (ch == '\n'){
			tot_lines++;
		}
		if (isspace(ch) && !isspace(prevch)){
			tot_words++;
		}
		tot_chars++;
		prevch = ch;
		ch = getchar();
	}
	printf("%d %d %d\n", tot_lines, tot_words, tot_chars);
	return 0 ;
}

