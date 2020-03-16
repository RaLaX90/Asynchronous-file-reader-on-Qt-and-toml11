#include <QtCore/QCoreApplication>
//#include <QTextCodec>
#include <iostream>
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

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

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

	//####################################################################################################################


	//####################################################################################################################

	//#define UNICODE 
	//#define _UNICODE 
	////#include "stdafx.h" 
	//#include "windows.h" 
	//
	//	HANDLE file;
	//	/*file = CreateFile(L"D:time.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//	TCHAR Dannie[12] = TEXT("12345");
	//	WriteFile(file, Dannie, 20, NULL, NULL);
	//	return 0;*/
	//	LPDWORD buf;
	//	file = CreateFile(L"D:time.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, NULL);
	//	CHAR Dannie2[20];
	//	BOOL read;
	//	read = ReadFile(file, Dannie2, 20, buf, NULL);
	//cout << Dannie2 << endl;
	//	CloseHandle(file);
	//	Sleep(5000);


	//####################################################################################################################

		//ifstream infile("D:time.txt", ios::in | ios::binary | ios::ate);
		//if (infile.is_open()) {
		//	size_t in_file_size = static_cast<size_t>(infile.tellg());
		//	cout << "file: " << "D:time.txt" << " - is opened, size = " << in_file_size << " \n";
		//	vector<char> data_array(in_file_size);
		//	infile.seekg(0, ios::beg);
		//	atomic<size_t> read_pos(0);
		//	size_t const read_by_size = 1024 * 1024;	// 1 MB
		//	condition_variable cv_read;
		//	mutex mtx_read;
		//	thread t_read_file([&]() {
		//		while (read_pos < in_file_size) {
		//			size_t current_read_bytes = min(read_by_size, (size_t)in_file_size - read_pos);
		//			infile.read(data_array.data(), current_read_bytes);
		//			read_pos += current_read_bytes;
		//			cv_read.notify_all();
		//		}
		//		cout << "thread read ended \n";
		//	});
		//	size_t current_pos;
		//	for (current_pos = 0; current_pos < in_file_size;) {
		//		size_t tmp_read_pos = read_pos;
		//		if (tmp_read_pos > current_pos) {
		//			for (size_t i = current_pos; i < tmp_read_pos; ++i) {
		//				data_array[i] = data_array[i] * 2;	// process data
		//			}
		//		}
		//		else {
		//			for (unique_lock<mutex> lock(mtx_read); read_pos <= current_pos; cv_read.wait(lock));
		//		}
		//		current_pos = tmp_read_pos;
		//	}
		//	t_read_file.join();
		//	cout << "current_pos = " << current_pos << " \n";
		//	cout << "read_pos = " << read_pos << " \n";
		//}

		//cout << "OK \n";
		//getchar();

//#################################################################################################################### 2

		/*auto start = chrono::steady_clock::now();
		cout << ReadFromFile();
		auto end = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start);
		cout << "Time is " << end.count() << endl;*/


		//####################################################################################################################

	HANDLE port;
	HANDLE  hEndRead;  // дескриптор события
	OVERLAPPED ovr;

	port = CreateFile(L"time.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (port == INVALID_HANDLE_VALUE)
	{
		cout << "Create file failed." << endl << "The last error code: " << GetLastError() << endl;

		CloseHandle(port);
		CloseHandle(hEndRead);

		cout << "Press any key to finish.";
		cin.get();
		return 0;
	}

	memset(&ovr, 0, sizeof(ovr));

	ovr.hEvent = hEndRead;

	hEndRead = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hEndRead == NULL) {
		cout << GetLastError();
	}

	

	while (true) {
		DWORD R;
		DWORD  dwError;
		char Line[256];

		auto bResult = ReadFile(port, Line, sizeof(Line), &R, &ovr);

		cout << "Useful work here" << endl;

		if (!bResult)
		{
			switch (dwError = GetLastError())
			{
			case ERROR_HANDLE_EOF: {
				cout << "End of file" << endl;
				CloseHandle(port);
				CloseHandle(hEndRead);
				cout << "Press any key to finish.";
				cin.get();
				return 0;
			}
			case ERROR_IO_PENDING: {
				cout << " In process ";
				break;
			}
			default: {
				cout << "Read file failed." << endl << "The last error code: " << dwError << endl;
				
				// закрываем дескрипторы
				CloseHandle(port);
				CloseHandle(hEndRead);

				cin.get();
				return 0;
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
				cout << "Press any key to finish.";
				cin.get();
				return 0;
			}
		}
		/*else {
			cout << "End of file" << endl;
			CloseHandle(port);
			CloseHandle(hEndRead);
			cout << "Press any key to finish.";
			cin.get();
			return 0;
		}*/

		//WaitForSingleObject(hEndRead, INFINITE);
		// печатаем число
		cout << Line << " " << endl;
		// увеличивает смещение в файле
		ovr.Offset += sizeof(Line);

	}

	//char* buf;
	/*DWORD bc;*/
	//DWORD  buf_size = 1048576;

	//for (;;){
	//	DWORD  dwBytesRead;
	//	DWORD  dwRet;
	//	//int    n;
	//
	//	/*char* buf;*/
	//	char Line[256];
	//
	//	DWORD R;
	//	DWORD Size;
	//	Size = GetFileSize(port, &Size);
	//
	//	// читаем одну запись
	//	if (!ReadFile(port, Line, buf_size, &dwBytesRead, &ovr))
	//	{
	//		switch (dwRet = GetLastError())
	//		{
	//		case ERROR_IO_PENDING:
	//			cout << "Read file pending." << endl;
	//			break;
	//		case ERROR_HANDLE_EOF:
	//			cout << endl << "End of the file." << endl;
	//			cout << "The file is read." << endl;
	//
	//			// закрываем дескрипторы
	//			CloseHandle(port);
	//			CloseHandle(hEndRead);
	//
	//			return 1;
	//		default:
	//			cout << "Read file failed." << endl
	//				<< "The last error code: " << dwRet << endl;
	//
	//			// закрываем дескрипторы
	//			CloseHandle(port);
	//			CloseHandle(hEndRead);
	//
	//			return 0;
	//		}
	//	}
	//	// ждем, пока завершится асинхронная операция чтения
	//	WaitForSingleObject(hEndRead, INFINITE);
	//	// печатаем число
	//	cout << Line << ' ';
	//	// увеличивает смещение в файле
	//	ovr.Offset += sizeof(Line);
	//}

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

	/*CloseHandle(port);
	CloseHandle(ovr.hEvent);*/

	return a.exec();
}
