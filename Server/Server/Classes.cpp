#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <iomanip>
#include "Classes.h"

using namespace std;

#pragma warning(disable : 4996)
#pragma once


media::media(int type, string name, string genre, string author, int length, int data)
{
	this->type = type;
	this->name = name;
	this->genre = genre;
	this->author = author;
	this->length = length;
	this->data = data;
}
media::media()
{


	this->type = 0;
	this->name = "None";
	this->genre = "None";
	this->author = "None";
	this->length = 0;
	this->data = 0;
}




string media::Getname() { return name; }
void media::Setname(string name) { this->name = name; }

string media::Getgenre() { return genre; }
void media::Setgenre(string genre) { this->genre = genre; }

string media::Getauthor() { return author; }
void media::Setauthor(string author) { this->author = author; }

int media::Getlength() { return length; }
void media::Setlength(int length) { this->length = length; }

int media::Getdata() { return data; }
void media::Setdata(int data) { this->data = data; }

int media::Gettype() { return type; }
void media::Settype(int type) { this->type = type; }


void media::read()

{
	cout << "Для фильма(0), для музыки(1)\n ";
	cin >> type;

	cout << "Название\n ";
	cin >> name;

	cout << "Автор\n> ";
	cin >> author;

	cout << "Жанр\n> ";
	cin >> genre;

	cout << "Продолжительность\n> ";
	cin >> length;

	cout << "Дата выхода\n> ";
	cin >> data;

}

void media::print()

{
	cout << "Название: " << this->name << endl;
	cout << "Автор: " << this->author << endl;
	cout << "Жанр: " << this->genre << endl;
	cout << "Продолжительность: " << this->length << endl;
	cout << "Дата выхода: " << this->data << endl;

}
