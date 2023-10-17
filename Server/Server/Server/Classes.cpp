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
	cout << "��� ������(0), ��� ������(1)\n ";
	cin >> type;

	cout << "��������\n ";
	cin >> name;

	cout << "�����\n> ";
	cin >> author;

	cout << "����\n> ";
	cin >> genre;

	cout << "�����������������\n> ";
	cin >> length;

	cout << "���� ������\n> ";
	cin >> data;

}

void media::print()

{
	cout << "��������: " << this->name << endl;
	cout << "�����: " << this->author << endl;
	cout << "����: " << this->genre << endl;
	cout << "�����������������: " << this->length << endl;
	cout << "���� ������: " << this->data << endl;

}
