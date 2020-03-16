#include <QtCore/QCoreApplication>
//#include <QTextCodec>
#include <iostream>
#include <thread> 
//#include <QDebug>
#include "toml11-master/toml.hpp"

//#include <chrono>

#include <windows.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
//#include <conio.h>

//#include <fstream>
//#include <string>
//#include <vector>
//#include <thread>
//#include <atomic>
//#include <condition_variable>
//#include <algorithm>

using namespace std;
using namespace chrono;

//2
//LPCSTR ReadFromFile() {
//	HANDLE FileHandle;
//	DWORD R;
//	DWORD Size;
//	static char Line[256];
//	FileHandle = CreateFile(L"D:time.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//	Size = GetFileSize(FileHandle, &Size);
//	ReadFile(FileHandle, Line, Size, &R, NULL);
//	return Line;
//}

void readFromFile(wstring str) {

	auto start = steady_clock::now();

	HANDLE port;
	HANDLE  hEndRead;  // дескриптор события
	OVERLAPPED ovr;

	memset(&ovr, 0, sizeof(ovr));

	hEndRead = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hEndRead == NULL) {
		cout << GetLastError();
	}

	ovr.hEvent = hEndRead;

	port = CreateFile(str.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (port == INVALID_HANDLE_VALUE)
	{
		cout << "Create file failed." << endl << "The last error code: " << GetLastError() << endl;
		CloseHandle(port);
		CloseHandle(hEndRead);
		cout << "Time is " << (duration_cast<seconds>(steady_clock::now() - start)).count() << " seconds" << endl;
		return;
	}

	while (true) {
		DWORD R;
		DWORD  dwError;
		char Line[100];

		auto bResult = ReadFile(port, Line, sizeof(Line), &R, &ovr);

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				Sleep(100);
				cout << "#";
			}
			cout << endl;
		}

		cout << "Useful work here" << endl;

		if (!bResult)
		{
			switch (dwError = GetLastError())
			{
			case ERROR_HANDLE_EOF: {
				cout << "End of file" << endl;
				CloseHandle(port);
				CloseHandle(hEndRead);
				cout << "Time is " << (duration_cast<seconds>(steady_clock::now() - start)).count() << " seconds" << endl;
				return;
			}
			case ERROR_IO_PENDING: {
				cout << " In process " << endl;
				break;
			}
			default: {
				cout << "Read file failed." << endl << "The last error code: " << dwError << endl;
				// закрываем дескрипторы
				CloseHandle(port);
				CloseHandle(hEndRead);
				cout << "Time is " << (duration_cast<seconds>(steady_clock::now() - start)).count() << " seconds" << endl;
				return;
			}

			}
		}

		bResult = GetOverlappedResult(port, &ovr, &R, TRUE);

		if (!bResult)
		{
			switch (dwError = GetLastError())
			{
			case ERROR_HANDLE_EOF:
				cout << "End of file" << endl;
				CloseHandle(port);
				CloseHandle(hEndRead);
				cout << "Time is " << (duration_cast<seconds>(steady_clock::now() - start)).count() << " seconds" << endl;
				return;
			}
		}
		/*else {
			cout << "End of file" << endl;
			CloseHandle(port);
			CloseHandle(hEndRead);
			cout << "Time is " << (duration_cast<seconds>(steady_clock::now() - start)).count() << "seconds" << endl;
			return;
		}*/

		//WaitForSingleObject(hEndRead, INFINITE);
		// печатаем число
		cout << Line << " " << endl;
		// увеличивает смещение в файле
		ovr.Offset += sizeof(Line);

	}

	/* Выполняем некую полезную работу */
	//auto err = WaitForSingleObject(ovr.hEvent, 3000);

	//if (err == WAIT_OBJECT_0) {
	//	GetOverlappedResult(port, &ovr, &bc, FALSE);
	//	cout << "Count of bites = " << bc << endl;
	//}
	//else {

	//	cout << "Error" << endl;
	//	/* Обработка ошибки */

	//}

}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	setlocale(LC_ALL, "ru");

	/*auto oldin = GetConsoleCP();
	auto oldout = GetConsoleOutputCP();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);*/
	//SetConsoleCP(oldin);
	//SetConsoleOutputCP(oldout);


	/*try
	{
		const auto data = toml::parse("Example.toml");
		toml::table path = toml::get<toml::table>(data);
		cout << "The path 1 is " << path["pathToFile"][0] << " and the path 2 is " << path["pathToFile"][1] << endl;
	}
	catch (const exception& ex)
	{
		cout << ex.what();
	}*/



	//#################################################################################################################### 2

			/*auto start = steady_clock::now();
			cout << ReadFromFile();
			auto end = duration_cast<milliseconds>(steady_clock::now() - start);
			cout << "Time is " << end.count() << endl;*/


			//####################################################################################################################

	thread t(readFromFile, L"Беляев-Наум.-Генри-Форд-royallib.com.txt");
	readFromFile(L"time.txt");
	t.join();
	//readFromFile(L"Беляев-Наум.-Генри-Форд-royallib.com.txt");


	return a.exec();
}
