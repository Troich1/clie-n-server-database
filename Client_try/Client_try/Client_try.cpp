// Client_try.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//



#include <stdio.h>
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <winsock2.h>


#pragma comment(lib, "ws2_32.lib")

using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);


	WSADATA wsaData;
	int result;
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		cout << "Ошибка WSAStartup: " << result << endl;
		return 1;
	}

	sockaddr_in stSockAddr;
	SOCKET sock_disp = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock_disp == -1)
	{
		perror("Ошибка: невозможно создать сокет");
		return EXIT_FAILURE;
	}

	memset(&stSockAddr, 0, sizeof(stSockAddr));

	stSockAddr.sin_family = PF_INET;
	stSockAddr.sin_port = htons(1100);
	stSockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);


	if (connect(sock_disp, (struct sockaddr*) & stSockAddr, sizeof(stSockAddr)) == -1)
	{
		perror("Ошибка: соединения");
		closesocket(sock_disp);
		return EXIT_FAILURE;
	}


	#define bufsize 2048
	char buf[bufsize];

	string str;
	int r;
	int res;

	for (;;)
	{
		cout << endl;

		cout << "Выберите действие" << endl;
		cout << "Показать список (1)" << endl; cout << "Добавить элемент в список(2)" << endl; cout << "Удалить элемент из списка(3)" << endl;
		cout << "Сортировать по типу (кино или музыка) (4) " << endl; cout << "Сортировать по жанру (5)" << endl; cout << "Искать по названию (6)" << endl;

		int mes;
		cin >> mes;

		str += to_string(mes);
		send(sock_disp, str.c_str(), sizeof(str.c_str()), 0);
		str.clear();

		switch (mes)
		{
		case 1:
		{


			r = recv(sock_disp, buf, bufsize, 0);
			if (r > 0)
			{
				cout << buf;
			}
			else if (r == 0)
				std::cout << "Соединение разорвано" << std::endl;
			else
				std::cout << "Ошибка в recv(): " << WSAGetLastError() << std::endl;

			break;
		}

		case 2:
		{



			string name, genre, author, tmp;
			int type, length, data;

			cout << "Кино(0) или музыка(1) " << endl;
			cin >> type;
			cout << endl;
			str += to_string(type); 
			send(sock_disp, str.c_str(), bufsize, 0);
			str.clear();

			cout << "Название " << endl;
			cin >>name;
			getline(cin, tmp);
			name+= tmp;
			cout << endl;
			str += name;
			send(sock_disp, str.c_str(), bufsize, 0);
			str.clear();
			tmp.clear();

			cout << "Жанр " << endl;
			cin >> genre;
			getline(cin, tmp);
			genre+= tmp;
			cout << endl;
			str += genre; 
			send(sock_disp, str.c_str(), bufsize, 0);
			str.clear();

			cout << "Автор " << endl;
			cin >> author;
			getline(cin, tmp);
			author+= tmp;
			cout << endl;
			str += author; 
			send(sock_disp, str.c_str(), bufsize, 0);
			str.clear();

			cout << "Продолжительность (мин) " << endl;
			cin >> length;
			cout << endl;
			str += to_string(length); 
			send(sock_disp, str.c_str(), bufsize, 0);
			str.clear();

			cout << "Дата выхода (год) " << endl;
			cin >> data;
			cout << endl;
			str += to_string(data); 
			send(sock_disp, str.c_str(), bufsize, 0);
			str.clear();

			break;
		}

		case 3:
		{
			int type;


			
			cout << "Выберите способ удаления" << endl;
			cout << "1 - удалить начало списка 2 - удалить конец списка 3 - удалить по номеру 4 - удалить по имени " << endl;
			cin >> type;
			cout << endl;
			str += to_string(type);
			send(sock_disp, str.c_str(), sizeof(str.c_str()), 0);
			str.clear();

			if (type == 3) 
			{
			
				int n;
				cout << endl;
				cout << "Ведите номер элемента " << endl;
				cin >> n;
				n -= 1;
				str += to_string(n);
				send(sock_disp, str.c_str(), bufsize, 0);
				str.clear();

			
			}

			if (type == 4)
			{
				cout << endl;
				cout << "Ведите название " << endl;
				cin >> str;
				string tmp;
				getline(cin, tmp);
				str += tmp;
				send(sock_disp, str.c_str(), bufsize, 0);
				str.clear();
			}

			break;
		}

		case 4:
		{
			int type;

			cout << "Выберите тип сортировки" << endl;
			cout << "0 - кино 1 - музыка " << endl;
			cin >> type;
			cout << endl;
			str += to_string(type);
			send(sock_disp, str.c_str(), bufsize, 0);
			str.clear();
			recv(sock_disp, buf, bufsize, 0);
			cout << buf;
			
			break;
		}

		case 5:
		{
			string genre,tmp;
			cout << "Выберите жанр и введите его" << endl;
			cin >> genre;
			getline(cin, tmp);
			genre+= tmp;
			cout << endl;
			send(sock_disp, genre.c_str(), bufsize, 0);
			recv(sock_disp, buf, bufsize, 0);
			cout << buf;

			break;
		}


		case 6:
		{
			string name, tmp;
			cout << "Введите название " << endl;
			cin >> name;
			getline(cin, tmp);
			name += tmp;
			cout << endl;
			send(sock_disp, name.c_str(), bufsize, 0);
			recv(sock_disp, buf, bufsize, 0);
			cout << buf;
		
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
