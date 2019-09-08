#include <iostream>

void crashStack(int num) {
	if (num == 0) {
	return;
}
	 else {
		 crashStack(++num);
	 }
}

char *reverseString(const char *input_string) {
	if (input_string == NULL) {
		return NULL;
	}
	int length = strlen(input_string);
	
	char *newString = new char[length + 1];
	
	int j = length - 1;
	for (int i = 0; i < length; i++) {
		newString[i] = input_string[j];
		j--;
	}
	newString[length] = '\0';

	return newString;
}

int main() {

	//crashStack(2);

	char *result = reverseString("Hello World");

	if (result != NULL) {
	for (int i = 0; i < strlen(result); i++) {
		std::cout << *(result + i);
	}
	delete result;
}
	

	return 0;
}

