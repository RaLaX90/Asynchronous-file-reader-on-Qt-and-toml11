#include <QtCore/QCoreApplication>
#include <iostream>
//#include <QDebug>
#include "toml11-master/toml.hpp"

//#include <chrono>

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

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

//1
HANDLE hEvent;
DWORD sizeOfBuf = 33554432;
BYTE *ReadBuffer = new BYTE[sizeOfBuf];

void ReadFromFile(int index) 
{
	SYSTEM_INFO SysInfo;  // system information; used to get granularity
	DWORD dwSysGran;      // system allocation granularity
	GetSystemInfo(&SysInfo);
	dwSysGran = SysInfo.dwAllocationGranularity;

	int iEvent = 0;

	DWORD dw = WaitForSingleObject(hEvent, INFINITE);

	HANDLE hFileForRead = CreateFile(L"D:time.txt",		// file to open
		GENERIC_READ,          // open for reading
		FILE_SHARE_READ,       // share for reading
		NULL,                  // default security
		OPEN_EXISTING,         // existing file only
		FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED,	// no buffering | asynchronous mode
		NULL);                 // no attr. template


	if (hFileForRead == INVALID_HANDLE_VALUE)
	{
		cout << "\nError of opening file!";
		return;
	}

	OVERLAPPED lpOverlapped;	// структура для задания режима асинхронного чтения
	lpOverlapped.hEvent = hEvent;
	lpOverlapped.Offset = 0;
	lpOverlapped.OffsetHigh = 0;
	DWORD  dwBytesRead = 0;

	DWORD  numberOfBytesTrasferred = 0;
	//DWORD  numberOfBytesToRead = 33554432; // читать блоками, кратными размеру сектора (c флешки) (асинхр.)
	DWORD  numberOfBytesToRead = 1048576; // c FLOPPY

	bool readFlag = ReadFile(hFileForRead, ReadBuffer, numberOfBytesToRead, &dwBytesRead, &lpOverlapped);
	bool flag = GetOverlappedResult(hFileForRead, &lpOverlapped, &numberOfBytesTrasferred, FALSE);
	if (flag) {
		cout << "\nReadFile(" << index << ") finished" << endl; // ГФО закончилась
	}
	else {
		cout << "\nReadFile(" << index << ") in processing" << endl; // ГФО выполняется
	}

	//CloseHandle(hFileForRead);
}

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


//###########################################################################################################

	//HANDLE  hFile;     // дескриптор файла
	//HANDLE  hEndRead;  // дескриптор события
	//OVERLAPPED  ovl;   // структура управления асинхронным доступом к файлу

	//// создаем события с автоматическим сбросом
	//hEndRead = CreateEvent(NULL, FALSE, FALSE, NULL);
	//if (hEndRead == NULL)
	//	return GetLastError();

	//// инициализируем структуру OVERLAPPED
	//ovl.Offset = 0;         // младшая часть смещения равна 0
	//ovl.OffsetHigh = 0;      // старшая часть смещения равна 0
	//ovl.hEvent = hEndRead;   // событие для оповещения завершения чтения

	//// открываем файл для чтения
	//hFile = CreateFile(
	//	L"time.txt",   // имя файла
	//	GENERIC_READ,          // чтение из файла
	//	FILE_SHARE_READ,       // совместный доступ к файлу
	//	NULL,                  // защиты нет
	//	OPEN_EXISTING,         // открываем существующий файл
	//	FILE_FLAG_OVERLAPPED,  // асинхронный ввод
	//	NULL                   // шаблона нет
	//);
	//// проверяем на успешное открытие
	//if (hFile == INVALID_HANDLE_VALUE)
	//{
	//	cerr << "Create file failed." << endl
	//		<< "The last error code: " << GetLastError() << endl;

	//	CloseHandle(hEndRead);

	//	cout << "Press any key to finish.";
	//	cin.get();

	//	return 0;
	//}
	//// читаем данные из файла
	//for (;;)
	//{
	//	DWORD  dwBytesRead;
	//	DWORD  dwRet;
	//	int    n;

	//	// читаем одну запись
	//	if (!ReadFile(
	//		hFile,           // дескриптор файла
	//		&n,              // адрес буфера, куда читаем данные
	//		sizeof(n),       // количество читаемых байтов
	//		&dwBytesRead,    // количество прочитанных байтов
	//		&ovl             // чтение асинхронное
	//	))
	//	{
	//		switch (dwRet = GetLastError())
	//		{
	//		case ERROR_IO_PENDING:
	//			cout << "Read file pending." << endl;
	//			break;
	//		case ERROR_HANDLE_EOF:
	//			cout << endl << "End of the file." << endl;
	//			cout << "The file is read." << endl;

	//			// закрываем дескрипторы
	//			CloseHandle(hFile);
	//			CloseHandle(hEndRead);

	//			return 1;
	//		default:
	//			cout << "Read file failed." << endl
	//				<< "The last error code: " << dwRet << endl;

	//			// закрываем дескрипторы
	//			CloseHandle(hFile);
	//			CloseHandle(hEndRead);

	//			return 0;
	//		}
	//	}
	//	// ждем, пока завершится асинхронная операция чтения
	//	WaitForSingleObject(hEndRead, INFINITE);
	//	// печатаем число
	//	cout << n << ' ';
	//	// увеличивает смещение в файле
	//	ovl.Offset += sizeof(n);
	//}

//####################################################################################################################

//#define UNICODE 
//#define _UNICODE 
//#include "stdafx.h" 
//#include "windows.h" 
//
//	HANDLE file;
//	file = CreateFile(L"D:time.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//	TCHAR Dannie[12] = TEXT("12345");
//	WriteFile(file, Dannie, 20, NULL, NULL);
//	return 0;
//	LPDWORD buf;
//	file = CreateFile(stdPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, NULL);
//	CHAR Dannie2[20];
//	BOOL read;
//	read = ReadFile(file, Dannie2, 20, buf, NULL);
//	printf(Dannie2);
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

//####################################################################################################################  1

hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
for (int i = 0; i < 10; ++i)
{
	ReadFromFile(i); 

}
cout << endl << "Press any key to exit...";
Sleep(2000);

//####################################################################################################################  2
	/*auto start = chrono::steady_clock::now();
	cout << ReadFromFile();
	auto end = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start);
	cout << "Time is " << end.count() << endl;*/

	return a.exec();
}
