#include <string>
#include <iostream>
#include <fstream>
#include "List.h"

using namespace std;

//#pragma warning(disable : 4996)
#pragma once



//конструктор и деструктор структуры


List::ListElement::ListElement(media* element)
{
	this->element = element;
	this->next = NULL;
	this->previous = NULL;
}

List::ListElement:: ~ListElement()
{
	delete element;
}


//конструктор и деструктор класса

List::List()
{
	head = nullptr;
	tail = nullptr;
}

//конструктор копирования	
List::List(const List& other)
{

	head = nullptr;
	tail = nullptr;

	ListElement* current_element = other.head;
	while (current_element)
	{
		this->addTail((current_element->element));
		current_element = current_element->next;
	}
}

List :: ~List()
{
	ListElement* current_element = head;
	while (current_element)
	{
		ListElement* temp = current_element;
		current_element = current_element->next;
		delete temp;
	}


}


// методы

// инициализируем

void List::initList()
{
	List();
}

void List::initElement(media* gov)
{

	int type;
	cout << "Тип продукта (0-фильм, 1-музыка) " << endl;
	cin >> type;
	gov->Settype(type);
	cout << endl;

	string name;
	cout << "Название " << endl;
	cin >> name;
	gov->Setname(name);
	cout << endl;

	string genre;
	cout << "Жанр " << endl;
	cin >> genre;
	gov->Setgenre(genre);
	cout << endl;

	string author;
	cout << "Автор " << endl;
	cin >> author;
	gov->Setauthor(author);
	cout << endl;

	int length;
	cout << "Продолжительность " << endl;
	cin >> length;
	gov->Setlength(length);
	cout << endl;

	int data;
	cout << "Дата выхода " << endl;
	cin >> data;
	gov->Setdata(data);
	cout << endl;

}


// добавляем элементы

void List::addHead(media* element)
{
	ListElement* temp = new ListElement(element);

	if (!head)
	{
		head = temp;
		tail = temp;
	}

	else
	{
		head->previous = temp;
		temp->next = head;
		head = temp;
	}
}

void List::addTail(media* element)
{
	ListElement* temp = new ListElement(element);

	if (!head)
	{
		head = temp;
		tail = temp;
	}

	else
	{
		if (head == tail)
		{

			tail = temp;
			tail->previous = head;
			head->next = temp;
		}
		else
		{
			tail->next = temp;
			temp->previous = tail;
			tail = temp;
			tail->next = nullptr;
		}

	}
}

void List::Insert(media* element)
{
	if (!head)
	{
		addHead(element);
	}
	else
	{
		addTail(element);
	}

}


//удаляем элементы

void List::removeHead()
{
	if (!head)
	{
		cout << "лул очередь пуста";
	}

	else if (head == tail)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}

	else
	{
		ListElement* temp = head;
		head = temp->next;
		delete temp;
		head->previous = nullptr;
	}
}

void List::removeTail()
{
	if (!head)
	{
		cout << "лул очередь пуста";
	}

	else if (head == tail)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}

	else
	{
		ListElement* current_element = head;

		while (current_element->next != tail)
		{
			current_element = current_element->next;
		}

		tail = current_element;
		delete current_element->next;
		current_element->next = nullptr;
	}

}

void List::removeElem(int n)
{
	if (n == 0)
	{
		this->removeHead();
		return;
	}

	int current_idx = 0;
	ListElement* current_element = head;
	ListElement* prev_element = nullptr;

	while (current_idx < n && current_element)
	{
		current_idx++;
		prev_element = current_element;
		current_element = current_element->next;
	}


	if (current_element == tail)
	{
		tail = prev_element;
		prev_element->next = nullptr;
		delete current_element;
	}
	else
	{
		prev_element->next = current_element->next;
		delete current_element;
	}


}

void List::remove()
{

	int place;
	string name;
	cout << "1 - удалить начало списка, 2 - удалить конец списка, 3 - удалить произвольный элемент (введите номер элемента)" << "4 - удалить по имени" << endl;
	cin >> place;
	cout << endl;

	switch (place)
	{

	case 1:
	{
		removeHead();
		break;
	}


	case 2:
	{
		removeTail();
		break;
	}

	case 3:
	{
		removeElem(place);
		break;
	}

	case 4:
	{

		cout << "Введите название для удаления " << endl;
		cin >> name;
		cout << endl;
		remove(name);
	}

	default:
	{
		break;
	}

	}
}

void List::remove(string name)
{



	ListElement* current_element = head;
	ListElement* prev_element=nullptr;
	ListElement* temp= nullptr;

	while (current_element)
	{
		if ( name == current_element->element->Getname() )
	{

			if (current_element == tail)
			{
				tail = prev_element;
				prev_element->next = nullptr;
				delete current_element;
				break;
			}
			else if (current_element == head)
			{
				removeHead();
				break;
			}

			else
			{
				temp = current_element;
				prev_element->next = current_element->next;
				current_element = temp->next;
				delete temp;
				break;
			}

	}
		prev_element = current_element;
		current_element = current_element->next;
	}

	}





// работаем с файлом

void List::print()

{
	ListElement* current_element;
	int i = 1;
	current_element = head;
	while (current_element)
	{
		cout << "Element #" << i << ":" << endl;
		current_element->element->print();
		cout << endl;
		current_element = current_element->next;
		i++;
	}
}

void List::save(const char* filename)
{

	ofstream file(filename);
	ListElement* current_element = head;

	if (file.is_open())
	{
		while (current_element)
		{

			if (current_element==tail)
			{
				file << current_element->element->Gettype() << " | " <<
					current_element->element->Getname() << " | " <<
					current_element->element->Getgenre() << " | " <<
					current_element->element->Getauthor() << " | " <<
					current_element->element->Getlength() << " | " <<
					current_element->element->Getdata();
				return;
			}


			file << current_element->element->Gettype() << " | " <<
				current_element->element->Getname() << " | " <<
				current_element->element->Getgenre() << " | " <<
				current_element->element->Getauthor() << " | " <<
				current_element->element->Getlength() << " | " <<
				current_element->element->Getdata() << endl;

			current_element = current_element->next;

		}
	}
	file.close();

}

void List::load(const char* filename)
{
	char read[32];
	int n = 0;
	ifstream file(filename);


	while (!file.eof())
	{
		string name, genre, author, temp;
		int type, length, data;
		file >> type >> temp;
		for (file >> temp; temp != "|"; file >> temp) name += temp += " ";
		for (file >> temp; temp != "|"; file >> temp) genre += temp += " ";
		for (file >> temp; temp != "|"; file >> temp) author += temp += " ";
		file >> length >> temp >> data;
		this->addTail(new media(type, name, genre, author, length, data));
	}
	file.close();
}


//поиск и фильтр

void List::search(string name, List *newl)
{
	
	ListElement* current_element = head;

	while (current_element)
	{
		if ((current_element->element->Getname()) == name)
		{
			newl->addTail((current_element->element));
		}
		current_element = current_element->next;
	}

}

void List::typefilter(int type, List *newl)
{
	ListElement* tmp = head;

	//List* newL = new List();

	//ListElement* newgov = newL->head;

	while (tmp)
	{
		if (type == tmp->element->Gettype())
		{

			newl->Insert(tmp->element);

		}

		tmp = tmp->next;

	}

	//newL->print();

}

void List::genrefilter(string genre, List *newl)
{
	ListElement* tmp = head;

	//List* newL = new List();

	//ListElement* newgov = newL->head;

	while (tmp != NULL)
	{
		if (tmp->element->Getgenre() == genre)
		{

			newl->Insert(tmp->element);

		}

		tmp = tmp->next;

	}

	//newL->print();

}



string List::to_str()
{
	string str;
	
	for (ListElement* current_element = head; current_element != nullptr; current_element = current_element->next) {
		str += current_element->element->Getname(); str += " ";
		str += current_element->element->Getgenre(); str += " ";
		str += current_element->element->Getauthor(); str += " ";
		str += to_string(current_element->element->Getlength()); str += " ";
		str += to_string(current_element->element->Getdata()); str += "\n";
	}
	return str;
}