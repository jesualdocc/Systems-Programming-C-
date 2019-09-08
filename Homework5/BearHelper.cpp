#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <unordered_map>
#include <fstream>
#include "BearHelper.h"

#include "ExpandableArray.h"

//This method constructs BearHelper object by reading the file f into the dictionary string
BearHelper::BearHelper(const char *f)
{
  
  //Open the file for reading

	FILE *inFile;

	inFile = fopen(f, "r");
	if (inFile == NULL) {
		std::cout << "Error Opening File\n";
		return ;
	}

  //Determine the number of characters in file.  Hint: you can use fseek and ftell.
	
	fseek(inFile, 0, SEEK_END);
	
	size = (int) ftell(inFile);
  //Allocate a string large enough for the entire dictionary.

	theDictionary = new char[size];

  //Read the entire file into the string allocated
	fseek(inFile, 0, SEEK_SET); //Set pointer back to start of file
	fread(theDictionary, sizeof(char), size, inFile); //Read all characters at once
  
  //Replace every \n character with a null character.

	for (int i = 0; i < size; i++) {
		//Look for every new line character in the string
		if (theDictionary[i] == '\n') {
			//Replace it with null character
			theDictionary[i] = '\0';
		}
	}
	fclose(inFile);

}


//Destructor for the BearHelper to free the memory used by dictionary
BearHelper::~BearHelper()
{
  //Destroy any memory allocated on heap and set pointer to null
	delete[] theDictionary;
	theDictionary = NULL;
}

/*
 * Returns true if all letters in "letters" are in group of letters "group" (duplicates should be accounted for)
 * therefore the letters: "ee" are in group "tree" but not in group "tea"
 *
 * parameter: letters - list of letters, group - a collection of letter
 * return: true of all letters are in set
 */
bool BearHelper::AllLettersInSet(const char *letters, const char *set)
{
	int l[26];
	int s[26];
	for (int x = 0; x < 26; x++)
		l[x] = s[x] = 0;
	
	for (const char *t = letters; *t; t++)
	{
		l[tolower(*t)-97]++;
	}
	for (const char *t = set; *t; t++)
	{
		s[tolower(*t)-97]++;
	}
	for (int x = 0; x < 26; x++)
		if (l[x] > s[x])
			return false;
	return true;
 
}


//Print all words that satisfy the condition: All characters in required must be in word and all letters in word must be in available
//The words are printed in order of length from longest to shortest.  
void BearHelper::GetAllWords(const char* required, const char* available)
{
	int numWords = 0;

	//Gets Number of words in the dictionary
	for (int i = 0; i < size; i++) {
		if (theDictionary[i] == '\0') {
			numWords++;
		}
	}

  //Go in order through the dictionary.
  
  //Check if each word matches.

  //If it does, add it to the expandable set.

	ExpandableArray arr;
	char *tmp = theDictionary;

	for (int i = 0; i < numWords; i++) {

		//All characters in required must be in word and all letters in word must be in available
		if (AllLettersInSet(required, tmp) && AllLettersInSet(tmp, available)) { // 

				arr.Append(tmp);
		}

		tmp += strlen(tmp) + 1; // Move to next word in the dictionary
	}
  
  //Sort the expandable set.

	arr.Sort();
  
  //Print the expandable set.

	for (int i = 0; i < arr.length(); i++) {
		std::cout << arr.get(i) << "\n";
	}
}


