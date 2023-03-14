#include <iostream>
#include "lib.h"

using std::cerr;
using std::endl;

char input_file_name[32];
char output_file_name[32];

const char temp_file_name[] = "temp.txt";

int main(int argc, const char* argv[])
{
	// Terminal arguments chack
	if (argc == 2) {
		if (strlen(argv[1]) > 31) {
			cerr << "File name is too long...31 at most." << endl;
			return -1;
		}
		strcpy_s(output_file_name, "a.out");
		strcpy_s(input_file_name, argv[1]);
	}
	else if (argc == 3) {
		if (strlen(argv[1]) > 31 || strlen(argv[2]) > 31) {
			cerr << "File name is too long...31 at most." << endl;
			return -1;
		}
		strcpy_s(input_file_name, argv[1]);
		strcpy_s(output_file_name, argv[2]);
	}
	else {
		cerr << "Incorrect parameter list..." << endl;
		return -1;
	}

	// open files 
	FILE* in, * out, * temp;
	in = fopen(input_file_name, "r");
	out = fopen(output_file_name, "w");
	temp = fopen(temp_file_name, "w");

	if (!(in && out && temp)) {
		cerr << "Open files failed...check the input file." << endl;
		return -1;
	}

	pre_process(temp, in);
	
	list->show();

	return 0;
}