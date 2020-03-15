#include <QtCore/QCoreApplication>
#include <iostream>
//#include <QDebug>
#include "toml11-master/toml.hpp"

#include <windows.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
//#include <conio.h>

using namespace std;

LPCSTR ReadFromFile() {
	HANDLE FileHandle;
	DWORD R;
	DWORD Size;
	static char Line[256];
	FileHandle = CreateFileA("time.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	Size = GetFileSize(FileHandle, &Size);
	ReadFile(FileHandle, Line, Size, &R, NULL);
	return Line;
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//const auto data = toml::parse("Example.toml");

	//toml::table tab = toml::get<toml::table>(data);

	////const auto data2 = toml::parse(tab["pathToFile"][0].as_string());

	//cout << "the title is " << tab["pathToFile"][0].as_string() << endl;

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

	//LPDWORD buf;
	//string stdPath = "D:\time.txt";
	//hFile = CreateFileA("D:\time.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//CHAR Dannie2[20];
	//BOOL read;
	//read = ReadFile(hFile, Dannie2, 20, buf, NULL);
	////printf(Dannie2);
	//cout << Dannie2 << endl;
	//CloseHandle(hFile);
	//Sleep(5000);

//####################################################################################################################

	/*HANDLE file;
	TCHAR stdPath[30] = TEXT("F:\КОЛЛЕДЖ\Операционные системы\С++ Визуал Студия 2 семестр\TXT.txt");
	TCHAR Dannie[12] = TEXT("12345");*/

//####################################################################################################################


	cout << ReadFromFile();


	return a.exec();
}
