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

	//HANDLE  hFile;     // ���������� �����
	//HANDLE  hEndRead;  // ���������� �������
	//OVERLAPPED  ovl;   // ��������� ���������� ����������� �������� � �����

	//// ������� ������� � �������������� �������
	//hEndRead = CreateEvent(NULL, FALSE, FALSE, NULL);
	//if (hEndRead == NULL)
	//	return GetLastError();

	//// �������������� ��������� OVERLAPPED
	//ovl.Offset = 0;         // ������� ����� �������� ����� 0
	//ovl.OffsetHigh = 0;      // ������� ����� �������� ����� 0
	//ovl.hEvent = hEndRead;   // ������� ��� ���������� ���������� ������

	//// ��������� ���� ��� ������
	//hFile = CreateFile(
	//	L"time.txt",   // ��� �����
	//	GENERIC_READ,          // ������ �� �����
	//	FILE_SHARE_READ,       // ���������� ������ � �����
	//	NULL,                  // ������ ���
	//	OPEN_EXISTING,         // ��������� ������������ ����
	//	FILE_FLAG_OVERLAPPED,  // ����������� ����
	//	NULL                   // ������� ���
	//);
	//// ��������� �� �������� ��������
	//if (hFile == INVALID_HANDLE_VALUE)
	//{
	//	cerr << "Create file failed." << endl
	//		<< "The last error code: " << GetLastError() << endl;

	//	CloseHandle(hEndRead);

	//	cout << "Press any key to finish.";
	//	cin.get();

	//	return 0;
	//}
	//// ������ ������ �� �����
	//for (;;)
	//{
	//	DWORD  dwBytesRead;
	//	DWORD  dwRet;
	//	int    n;

	//	// ������ ���� ������
	//	if (!ReadFile(
	//		hFile,           // ���������� �����
	//		&n,              // ����� ������, ���� ������ ������
	//		sizeof(n),       // ���������� �������� ������
	//		&dwBytesRead,    // ���������� ����������� ������
	//		&ovl             // ������ �����������
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

	//			// ��������� �����������
	//			CloseHandle(hFile);
	//			CloseHandle(hEndRead);

	//			return 1;
	//		default:
	//			cout << "Read file failed." << endl
	//				<< "The last error code: " << dwRet << endl;

	//			// ��������� �����������
	//			CloseHandle(hFile);
	//			CloseHandle(hEndRead);

	//			return 0;
	//		}
	//	}
	//	// ����, ���� ���������� ����������� �������� ������
	//	WaitForSingleObject(hEndRead, INFINITE);
	//	// �������� �����
	//	cout << n << ' ';
	//	// ����������� �������� � �����
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
	TCHAR stdPath[30] = TEXT("F:\�������\������������ �������\�++ ������ ������ 2 �������\TXT.txt");
	TCHAR Dannie[12] = TEXT("12345");*/

//####################################################################################################################


	cout << ReadFromFile();


	return a.exec();
}
