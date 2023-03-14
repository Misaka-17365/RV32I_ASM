#include "lib.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

List::List(void)
{
	this->lenth = 0;
	this->head = (Node*)malloc(sizeof(Node));
	this->head->item = nullptr;
	this->head->next = nullptr;
}

List::List(Label* _item)
{
	this->lenth = 1;
	this->head = (Node*)malloc(sizeof(Node));
	this->head->item = nullptr;
	this->head->next = (Node*)malloc(sizeof(Node));
	this->head->next->item = _item;
	this->head->next->next = nullptr;
}

void List::append(Label* _item)
{
	Node* temp = this->head;
	for (int i = 0; i < this->lenth; i++) {
		temp = temp->next;
	}
	temp->next = (Node*)malloc(sizeof(Node));
	if (!temp->next) {
		printf_s("kong");
	}
	temp->next->item = _item;
	temp->next->next = nullptr;
	this->lenth++;
}

Label* List::read(long long int _index)
{
	if (_index + 1 > this->lenth) {
		return nullptr;
	}
	Node* temp = this->head;
	for (int i = 0; i < _index + 1; i++) {
		temp = temp->next;
	}
	return temp->item;
}

Label* List::find(const char* _name)
{
	Node* temp = this->head;
	for (int i = 0; i < this->lenth; i++) {
		if (!strcmp(_name, temp->item->name)) {
			return temp->item;
		}
	}
	return nullptr;
}

void List::show(void)
{
	Node* temp = this->head;
	for (int i = 0; i < this->lenth; i++) {
		temp = temp->next;
		printf("[%d]%s\t:%lld\n", i, temp->item->name, temp->item->address);
	}
}