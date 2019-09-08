#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>

struct Student {
	int studentId;
	int assignmentGrades[4];
};

void readInReverse(const char *s) {
	
	Student inputStruct;
	FILE *file;
	file = fopen(s , "rb+");

	if (file == NULL) {
		std::cout << "Error!! File Not Found\n";
		exit(1);
	}
	
	for (int i = -1; i >= -5; i--) {
		//Negative offset takes the pointer backwards x bytes (x = i * sizeof(struct Student) )

		int returnValueSeek = fseek(file, ( i * sizeof(struct Student)), SEEK_END);

		if (returnValueSeek != 0) {
			std::cout << "Error Seeking in the File\n";
			exit(1);
		}

		int returnValueRead = fread(&inputStruct, sizeof(struct Student), 1, file);

		if (returnValueRead != 1) { // 1 is count value
			std::cout << "Error Writing File!! \n";
			exit(1);
		}
		
		std::cout << "StudentID = " << inputStruct.studentId << "\nGrades = ";
		
		for (int j = 0; j < 4; j++) {
			std::cout << inputStruct.assignmentGrades[j] << " ";
		}
		std::cout << "\n\n";
	}

	fclose(file);

}

int main() {

	FILE * outFile;
	outFile = fopen("myfile.bin", "wb+");
	
	Student students[5];
	
	for (int i = 0; i < 5; i++) {
		students[i].studentId = i;
		std::cout << "Enter Grades for Student " << i << "\n";
		
		for (int j = 0; j < 4; j++) {
			std::cin >> students[i].assignmentGrades[j];
		}

	}

	for (int i = 0; i < 5; i++) {

		//Since I am inserting one struct in the array at a time, the count number is set to 1

		int returnValue = fwrite(&students[i], sizeof(students[i]), 1, outFile);

		if (returnValue != 1) { // 1 is count value
			std::cout << "Error Writing File!! \n";
		}
		
	}

	fclose(outFile);
	/*
	
	//If I wanted  to put the entire array of structs all at once

	fwrite(students, sizeof(struct Student), (sizeof(students) / sizeof(students[0])), outFile);

	*/
	
	
	std::cout << "\n";
	// 1st Call
	readInReverse("myfile.bin");

	outFile = fopen("myfile.bin", "wb+");

	for (int i = 0; i < 5; i++) {
		students[i].studentId = i;
		std::cout << "Enter Grades for Student " << i << "\n";

		for (int j = 0; j < 4; j++) {
			std::cin >> students[i].assignmentGrades[j];
		}

	}

	for (int i = 0; i < 5; i++) {

		//Since I am inserting one struct in the array at a time, the count number is set to 1

		int returnValue = fwrite(&students[i], sizeof(students[i]), 1, outFile);

		if (returnValue != 1) { // 1 is count value
			std::cout << "Error Writing File!! \n";
		}

	}

	fclose(outFile);

	std::cout << "\n";
	// 2nd Call
	readInReverse("myfile.bin");

	return 0;
}