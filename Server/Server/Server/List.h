#include <string>
#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Classes.h"

using namespace std;

#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")
#pragma once

class List
{
	friend string std::to_string(int);

	struct ListElement
	{
		media* element;
		ListElement* next;
		ListElement* previous;

		//конструктор и деструктор структуры

		ListElement(media*);

		~ListElement();

	};

	ListElement* head;
	ListElement* tail;

public:

	//конструктор и деструктор класса

	List();
	List(const List& other); //конструктор коипрования


	~List();


	//методы


	void initElement(media* gov);
	void initList();

	// добавление элемента в очередь
	void Insert(media* element);
	void addHead(media* element);
	void addTail(media* element);
	//void addTail(media element);


	

	//удаление элемента
	void removeHead();
	void removeTail();
	void removeElem(int name);
	void remove();
	void remove(string name);

	//работа с файлом
	void print();
	void load(const char* filename);
	void save(const char* filename);

	//фильтр и поиск
	//ListElement* 
	void search(string name, List *newl);
	void typefilter(int lang, List *newl);
	void genrefilter(string genre, List *newl);


	string to_str();

	
};
