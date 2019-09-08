#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <unordered_map>
#include <fstream>
#include "bearHelper.h"

/*
 * Counts the number of words in a file named f
 * parameter: file name
 * return: number of words in file
 */
int GetNumEntriesInFile(const char *f)
{
  //1. Open the file for reading
	FILE *inFile;

	inFile = fopen(f, "r");
	if (inFile == NULL) {
		std::cout << "Error Opening File\n";
		return 0;
	}
	
  //2. Count the number of words in file.  Hint: You can count the number of '\n' characters in file. Use fgetc to read one character at a time.

	int count = 0;

	do {
		char c = fgetc(inFile);
		if (c == '\n') {
			count++;
		}
	} while (!feof(inFile)); //EOF is return when end of file is reached

//3. close file

	fclose(inFile);
  
  //4.return count
	return count;
}


/*
 * Creates an array of strings of size count and populates it with words in file named f
 * parameter: f - file name, cout - number of words in file
 * return: An array of c-strings
 */
char **ReadWords(const char *f, int count)
{
	//1. Open file for reading
	FILE *inFile;

	inFile = fopen(f, "r");
	if (inFile == NULL) {
		std::cout << "Error Opening File\n";
		return 0;
	}

	//2. Allocate the array of c-strings

	char **array; // since length of words is unknown at this point
	array = new char*[count];

	//3. For each word in the file
	int offset = 0;
	for (int i = 0; i < count; i++) {
		int length = 0;
		int temp = ftell(inFile);

		while (fgetc(inFile) != '\n') {
			length++;
		}
		
	//3.a Determine the length of word
	//   (hint: use ftell to determine the location of the pointer in file before you start counting the letters, use fgetc to read a single character, then fseek to the location of the start of the word and read it).
		
		offset = (ftell(inFile) - temp) * (-1);

		fseek(inFile, offset, SEEK_CUR); // Moves pointer back to the beginning of the word (offset is negative)

	//3.b Allocate a string long enough to store word

		array[i] = new char[length + 1]; // An extra byte for the null character

	//3.c store word in array of words
		
		fread(array[i], length, 1, inFile);
		array[i][length] = '\0';
		fseek(inFile, 2, SEEK_CUR); //Skip both the null and new line characters
}
  //4. close file
	fclose(inFile);

  //5. return array of words
	return array;
}


/*
 * Returns true if all letters in "letters" are in group of letters "group" (duplicates should be accounted for)
 * therefore the letters: "ee" are in group "tree" but not in group "tea"
 *
 * parameter: letters - list of letters, group - a collection of letter
 * return: true of all letters are in set
 */
bool AllLettersInSet(const char *letters, const char *group)
{
	
	bool check = false;

	int count = 0;
	int lengthOfGroup = strlen(group);
	int lengthOfLetters = strlen(letters);

	bool *letterUsed = new bool[lengthOfGroup]; //To keep track of duplicates

	for (int i = 0; i < lengthOfGroup; i++) {
		letterUsed[i] = false; 
	}
	
		for (int i = 0; i < lengthOfLetters; i++) {
			for (int j = 0; j < lengthOfGroup; j++) {

				if (letterUsed[j]) {
						//is letter has already been matched, checks the next one
						//Each index/character from group is only compared once
				}
				else {
					if (letters[i] == group[j]) {
						count++;
						letterUsed[j] = true; //Checks that specific charcter from group has been used for comparison
						break; //Breaks so that same char from letter is not compared multiple times after a match is found
					}
				}
			
		}
	}

		if (count == lengthOfLetters) { //All letters matched 
			check = true;
	}

	return check;
}

