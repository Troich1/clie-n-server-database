
// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include <windows.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <WS2tcpip.h>
#include <winsock2.h>
#include "Classes.h"
#include "List.h"

#pragma comment(lib, "ws2_32.lib")

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	List* lst = new List();

	//lst->print();

	FILE* file; char fname[] = "List.txt";
	//lst->save("List.txt");
	lst->load("List.txt");
	//lst->load("genreList.txt");
	//lst->load("nameList.txt");
	//lst->load("TypeList0.txt");
	//lst->load("TypeList1.txt");
	//cout << "вывыодим" << endl;
	//lst->print();//*/
	string str;

	WSADATA wsaData;
	int result;
	result = WSAStartup(MAKEWORD(2, 2), &wsaData); 
	if (result != 0)
	{
		cout << "Ошибка WSAStartup: " << result << endl;
		return 1;
	}

	struct sockaddr_in stSockAddr;
	SOCKET sock_disp = socket(PF_INET, SOCK_STREAM, 0); //создаем сокет
	 /*1 аргумент — обозначает семейство адресов, или протокол;
	 2 аргумент - указывает тип взаимодействия: ориентированное на установку соединения, или потоковое(SOCK_STREAM)
	 3 аргумент - если аргумент 1 установлен равным AF_INET или PF_INET используеться значение 0.
	 В случае неудачного завершения функция socket возвращает значение INVALID_SOCKET.*/
	if (sock_disp == INVALID_SOCKET)
	{
		perror("ошибка при создании сокета");
		exit(EXIT_FAILURE);
	}

	memset(&stSockAddr, 0, sizeof(stSockAddr));
	
	// тип адреса (TCP/IP)
	stSockAddr.sin_family = PF_INET;
	// Порт. Используем функцию htons для перевода номера порта из обычного в //TCP/IP представление.
	stSockAddr.sin_port = htons(1100); 
	// адрес. для локального соединения подойдет параметр INADDR_ANY
	stSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock_disp, (sockaddr*)&stSockAddr, sizeof(stSockAddr)) == -1) //связываем сокет с адресом
	
	/*1 аргумент - ранее созданный и не связанный с адресом сокет
	2 аргумент - структура в которой хранятся протокол адрес и порт*/
	{
		perror("Ошибка: связывания");

		closesocket(sock_disp);
		exit(EXIT_FAILURE);
	}

	if (listen(sock_disp, 1) == -1) //готовим сокет к получению данных
	/*1 агрмуент - наш связанный с адресом и портом сокет
	2 аргумент - число запросов для соединения*/

	{
		perror("Ошибка: прослушивания");

		closesocket(sock_disp);
		exit(EXIT_FAILURE);
	}

	cout << "ждем соединения" << endl;


	SOCKET i32ConnectFD = accept(sock_disp, 0, 0);

	if (i32ConnectFD < 0)
	{
		perror("Ошибка: принятия");
		//closesocket(sock_disp);
		exit(EXIT_FAILURE);
	}

	cout << "соединились" << endl;

	#define bufsize 2048
	char buf[bufsize];
	int r;



	for (;;)
	{

		r = recv(i32ConnectFD, buf, bufsize, 0);

		int mes = atoi(buf);
		
		cout << mes << endl;

		switch (mes)
		{
		case 1:
		{

			str = lst->to_str();

			
			r = send(i32ConnectFD, str.c_str(), bufsize, 0);
			str.clear();
			break;
		}

		case 2:
		{

			string name, genre, author, strbuff;
			int type, length, data;
			
			recv(i32ConnectFD, buf, bufsize, 0);
			cout << buf << endl;
			strbuff += buf;
			type = atoi(buf);
			strbuff.clear();

			recv(i32ConnectFD, buf, bufsize, 0);
			cout << buf << endl;
			name += buf;

			recv(i32ConnectFD, buf, bufsize, 0);
			cout << buf << endl;
			genre += buf;

			recv(i32ConnectFD, buf, bufsize, 0);
			cout << buf << endl;
			author += buf;

			recv(i32ConnectFD, buf, bufsize, 0);
			cout << buf << endl;
			strbuff += buf;
			length = atoi(buf);
			strbuff.clear();

			recv(i32ConnectFD, buf, bufsize, 0);
			cout << buf << endl;
			strbuff += buf;
			data = atoi(buf);
			strbuff.clear();

			media* gov = new media(type, name, genre, author, length, data);
		
			lst->Insert(gov);

	
			break;
		}

		case 3:
		{
			
			recv(i32ConnectFD, buf, bufsize, 0);
			int rem = atoi(buf);
			cout << rem << endl;

			switch (rem)

			{
			case 1:
			{
				lst->removeHead();
				break;
			}

			case 2:
			{
				lst->removeTail();
				break;
			}

			case 3:
			{

				recv(i32ConnectFD, buf, bufsize, 0);
				int n = atoi(buf);
				cout << n << endl;
				lst->removeElem(n);

				break;
			}

			case 4:
			{
				recv(i32ConnectFD, buf, bufsize, 0);
				string name(buf); name += " ";
				cout << name;
				lst->remove(name);

				break;
			}

			default:
			{
				break;
			}

			}

			break;
		}

		case 4:
		{
			recv(i32ConnectFD, buf, bufsize, 0);
			int type = atoi(buf);
			cout << type << endl;

			if (type == 0)
			{
			
				FILE* file; char fname[] = "TypeList0.txt";
				List* typeList = new List();
				lst->typefilter(type, typeList);
				typeList->save("TypeList0.txt");
				str = typeList->to_str();
				cout << str << endl;
				send(i32ConnectFD, str.c_str(), bufsize, 0);
				str.clear();
			}

			if (type == 1)
			{
	
				FILE* file; char fname[] = "TypeList1.txt";
				List* typeList = new List();
				lst->typefilter(type, typeList);
				typeList->save("TypeList1.txt");
				str = typeList->to_str();
				cout << str << endl;
				send(i32ConnectFD, str.c_str(), bufsize, 0);
				str.clear();

			}

			break;
		}

		case 5:
		{
		
			recv(i32ConnectFD, buf, bufsize, 0);
			cout << buf << endl;
			string name(buf); name += ' ';
			FILE* file; char fname[] = "genreList.txt";
			List* typeList = new List();
			lst->genrefilter(name, typeList);
			typeList->save("genreList.txt");
			str = typeList->to_str();
			cout << str << endl;
			send(i32ConnectFD, str.c_str(), bufsize, 0);
			str.clear();

			break;
		}

		case 6:
		{
		
			recv(i32ConnectFD, buf, bufsize, 0);
			cout << buf << endl;
			string name(buf); name += " ";
			FILE* file; char fname[] = "nameList.txt";
			List* typeList = new List();
			lst->search(name, typeList);
			typeList->save("nameList.txt");
			str = typeList->to_str();
			cout << str << endl;
			send(i32ConnectFD, str.c_str(), bufsize, 0);
			str.clear();

			break;
		}

		default:
		{
			break;
		}

		}
	}


	shutdown(sock_disp, 2);

	closesocket(sock_disp);
}
