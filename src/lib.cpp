#include "lib.h"
#include <stdlib.h>
#include <iostream>

using std::cerr;
using std::endl;

#define IS_VALID(x) ( (x) >= '0' && (x) <= '9' || (x) >= 'a' && (x) <= 'z' || (x) >= 'A' && (x) <= 'Z' || (x) == '_' )
#define IS_BLANK(x)  ( (x) == '\t' || (x) == ' ' || (x) == ',' )
#define IS_END(x) ( (x) ==  '\n' || (x) == ';' || (x) == 0 )

List *list = new List();

long long int pre_process(FILE* _out, FILE* _in)
{
	char buffer[128];
	char result[128];
	long long int lineCounter = 1;

	rewind(_in);
	rewind(_out);

	// loop for each statement(one line)
	while (!feof(_in)) {
		int cursor;

		if (!fgets(buffer, 128, _in)) {
			buffer[0] = 0;
		}

		if (strlen(buffer) == 127 && buffer[126] != '\n') {
			error(lineCounter, instructure_too_long);
		}

		for (int i = 0; buffer[i] != 0; i++) {
			if (buffer[i] == ':') {
				goto TYPE_LABEL;
			}
		}

		if (0) {
		TYPE_LABEL:

			int i = 0;
			while (IS_BLANK(buffer[i])) {
				i++;
			}
			while (IS_VALID(buffer[i])) {
				i++;
			}
			if (buffer[i] != ':') {
				error(lineCounter, error_label_syntax);
			}
			else {
				int i = 0, j = 0;
				Label* label = new Label;

				while (IS_BLANK(buffer[i])) {
					i++;
				}
				while (buffer[i] != ':') {
					label->name[j] = buffer[i];
					i++;
					j++;
				}
				label->name[j] = 0;
				label->address = 4 * lineCounter - 4;

				//cerr << "Label:" << label->name << " is " << label->address << endl;
				
				list->append(label);
				continue;
			}
		}

		if (IS_END(buffer[0])) {
			continue;
		}

		cursor = 0;
		result[0] = 0;

		for (int i = 0; (buffer[i] != 0);) {
			if (IS_BLANK(buffer[i])) {
				while (IS_BLANK(buffer[i])) {
					i++;
				}
				continue;
			}
			else if (IS_VALID(buffer[i])) {
				while (IS_VALID(buffer[i])) {
					result[cursor] = buffer[i];
					cursor++;
					i++;
				}
				result[cursor] = ' ';
				cursor++;
				continue;
			}
			if (IS_END(buffer[i])) {
				result[cursor] = 0;
				break;
			}
			else{
				error(lineCounter, invalid_char);
			}
		}
		fputs(result, _out);
		fputc('\n', _out);

		lineCounter++;
	}
	return lineCounter;
}






void error(long long int _line, enum err_type _type)
{
	switch (_type)
	{
	case instructure_too_long:
		cerr << "Error in line: " << _line << " , too many characters in one line." << endl;
		break;

	case invalid_char:
		cerr << "Error in line: " << _line << " , invalid characters exist. Only 0~9 , a~z and A~Z are valid." << endl;

		break;
	case undefined_label:
		cerr << "Error in line: " << _line << " , the label is used, but never defined." << endl;
		break;

	case error_label_syntax:
		cerr << "Error in line: " << _line << " , the syntax of label defination is wrong." << endl;
		break;

	default:
		cerr << "Error in line: " << _line << " , unkonwn errer type." << endl;
		break;
	}
	exit(-1);
}