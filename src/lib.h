#ifndef __LIB_H__
#define __LIB_H__

#include <stdio.h>

enum err_type
{
	instructure_too_long,
	invalid_char,
	undefined_label,
	error_label_syntax
};

typedef struct {
	char name[32];
	long long int address;
} Label;


class List
{
public:
	typedef struct _Node
	{
		Label* item;
		_Node* next;
	} Node;
private:
	long long int lenth;
	Node* head;

public:
	List(void);
	List(Label* _item);

	~List(void);

	void append(Label* _item);
	void show(void);
	Label* read(long long int _index);
	Label* find(const char* _name);
	
};


extern List* list;



long long int pre_process(FILE* _out, FILE* _in);
void error(long long int _line, enum err_type _type);






#endif // !__LIB_H__
