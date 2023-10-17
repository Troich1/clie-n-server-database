#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#pragma warning(disable : 4996)
#pragma once



class media
{
private:

	int type;
	string name;
	string genre;
	string author;
	int length;
	int data;
	
public:

	media(int type, string name, string genre, string author, int lenght, int data);

	media();

	string Getname();
	void Setname(string name);

	string Getgenre();
	void Setgenre(string genre);

	string Getauthor();
	void Setauthor(string author);

	int Getlength();
	void Setlength(int length);

	int Getdata();
	void Setdata(int data);

	int Gettype();
	void Settype(int type);


	void read();
	void print();

};


