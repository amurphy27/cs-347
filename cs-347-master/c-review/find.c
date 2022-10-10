/*
 * Implementation of functions that find values in strings.
 *****
 * YOU MAY NOT USE ANY FUNCTIONS FROM <string.h>
 *****
 */

#include <stdlib.h>
#include <stdbool.h>
#include "find.h"

#define NOT_FOUND (-1)	// integer indicator for not found.

/*
 * Return the index of the first occurrence of <ch> in <string>,
 * or (-1) if the <ch> is not in <string>.
 */
int find_ch_index(char string[], char ch) {
	int i = 0;
	while (string[i]){
		if (string[i] == ch){
			return i;
		}
		else {
			i++;
		}
	}
	return -1;
}

/*
 * Return a pointer to the first occurrence of <ch> in <string>,
 * or NULL if the <ch> is not in <string>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_ch_ptr(char *string, char ch) {
	while (*string){
		if (*string == ch){
			return string;
		}
		else {
			string++;
		}
	}
	return NULL;
}

/*
 * Return the index of the first occurrence of any character in <stop>
 * in the given <string>, or (-1) if the <string> contains no character
 * in <stop>.
 */
int find_any_index(char string[], char stop[]) {
	int i = 0;
	while (string[i]){
		int j = 0;
		while (stop[j]){
			if (string[i] == stop[j]){
				return i;
			}
			else {
				j++;
			}
		}
		i++;
	}
	return -1;
}

/*
 * Return a pointer to the first occurrence of any character in <stop>
 * in the given <string> or NULL if the <string> contains no characters
 * in <stop>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_any_ptr(char *string, char* stop) {
	char* temp;
	while (*string){
		temp = stop;
		while (*temp){
			if (*string == *temp){
				return string;
			}
			else {
				temp++;
			}
		}
		string++;
	}
	return NULL;
}

/*
 * Return a pointer to the first character of the first occurrence of
 * <substr> in the given <string> or NULL if <substr> is not a substring
 * of <string>.
 * Note: An empty <substr> ("") matches *any* <string> at the <string>'s
 * start.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_substr(char *string, char* substr) {
	if (*substr == NULL){
		return string;
	}

	while (*string){
		char* tempSub = substr;
		char* tempStr = string;
		while (*tempStr == *tempSub){
			tempStr++;
			tempSub++;
			if (*tempSub == NULL){
				return string;
			}
		}
		string++;
	}

	return NULL;
}
