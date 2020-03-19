#include <QtCore/QCoreApplication>
//#include <QTextCodec>
#include <iostream>
#include <thread> 
//#include <QDebug>
#include "toml11-master/toml.hpp"
#include <codecvt>

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

#define locale;

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

string to_string(wstring wstr)
{
	return wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(wstr);
}

wstring to_wstring(string str)
{
	return wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str);
}

void readFromFileUsingWinAPI(wstring str) {

	auto start = steady_clock::now();

	using UniqueHandle = unique_ptr<remove_pointer<HANDLE>::type, integral_constant<decltype(&CloseHandle), &CloseHandle>>;

	OVERLAPPED ovr;

	memset(&ovr, 0, sizeof(ovr));

	UniqueHandle hEndRead(CreateEvent(NULL, FALSE, FALSE, NULL));
	if (hEndRead.get() == NULL) 
	{
		cout << GetLastError();
	}

	ovr.hEvent = hEndRead.get();

	UniqueHandle port(CreateFile(str.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL));
	if (port.get() == INVALID_HANDLE_VALUE)
	{
		cout << "Create file " << to_string(str) << " is failed." << endl << "The last error code: " << GetLastError() << endl;
		//CloseHandle(port);
		//CloseHandle(hEndRead);
		cout << "Time is " << (duration_cast<seconds>(steady_clock::now() - start)).count() << " seconds" << endl;
		return;
	}

	while (true) {
		DWORD R;
		DWORD  dwError;
		char Line[100000];

		auto bResult = ReadFile(port.get(), Line, sizeof(Line), &R, &ovr);

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				this_thread::sleep_for(milliseconds(100));
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
				//CloseHandle(port);
				//CloseHandle(hEndRead);
				cout << "Time is " << (duration_cast<seconds>(steady_clock::now() - start)).count() << " seconds" << endl;
				return;
			}
			case ERROR_IO_PENDING: {
				cout << " In process " << endl;
				break;
			}
			default: {
				cout << "Read file " << to_string(str) << " is failed." << endl << "The last error code: " << dwError << endl;
				//CloseHandle(port);
				//CloseHandle(hEndRead);
				cout << "Time is " << (duration_cast<seconds>(steady_clock::now() - start)).count() << " seconds" << endl;
				return;
			}

			}
		}

		bResult = GetOverlappedResult(port.get(), &ovr, &R, TRUE);

		if (!bResult)
		{
			switch (dwError = GetLastError())
			{
			case ERROR_HANDLE_EOF:
				cout << "End of file" << endl;
				//CloseHandle(port.get());
				//CloseHandle(hEndRead);
				cout << "Time is " << (duration_cast<seconds>(steady_clock::now() - start)).count() << " seconds" << endl;
				return;
			}
		}

		//WaitForSingleObject(hEndRead, INFINITE);

		cout << this_thread::get_id() << endl;
		cout << Line << " " << endl;

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

void readFromFileUsingSTD(const char str[]) {

	using UniqueFile = unique_ptr<remove_pointer<FILE>::type, integral_constant<decltype(&fclose), &fclose>>;

	UniqueFile file(fopen(str, "rt"));
	//unique_ptr<FILE, int(*)(FILE*)> file(fopen(str, "rt"), fclose);

	if (file.get() == NULL)
	{
		fputs("Ошибка файла", stderr);
		exit(1);
	}


	fseek(file.get(), 0, SEEK_END);
	long lSize = ftell(file.get());
	rewind(file.get());

	using UniqueBuffer = unique_ptr<remove_pointer<char>::type, integral_constant<decltype(&free), &free>>;

	UniqueBuffer buffer((char*)calloc(sizeof(char), lSize));

	if (buffer.get() == NULL)
	{
		fputs("Ошибка памяти", stderr);
		exit(2);
	}

	size_t result = fread(buffer.get(), 1, lSize, file.get());

	if (result != lSize)
	{
		if (!feof(file.get())) { // !
			fputs("Ошибка чтения", stderr);
			exit(3);
		}
	}

	cout << buffer.get();

	//file.get_deleter();
	//fclose(file.get());
	//free(buffer.get());
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	setlocale(LC_ALL, "ru");

#ifdef locale
	auto oldin = GetConsoleCP();
	auto oldout = GetConsoleOutputCP();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif

	try
	{
		const auto data = toml::parse("Example.toml");
		//toml::table path = toml::get<toml::table>(data);
		string str1 = toml::find<toml::string>(data, "pathToFile", 0);
		string str2 = toml::find<toml::string>(data, "pathToFile", 1);
		//cout << "The path 1 is " << path["pathToFile"][0] << " and the path 2 is " << path["pathToFile"][1] << endl;

		//thread t(readFromFileUsingSTD, to_wstring(path["pathToFile"][0].as_string()));

		//readFromFileUsingWinAPI(to_wstring(str1));
		readFromFileUsingSTD(str2.c_str());

		//t.join();
	}
	catch (const exception& ex)
	{
		cout << ex.what();
	}

#ifdef locale
	SetConsoleCP(oldin);
	SetConsoleOutputCP(oldout);
#endif

	//#################################################################################################################### 2

			/*auto start = steady_clock::now();
			cout << ReadFromFile();
			auto end = duration_cast<milliseconds>(steady_clock::now() - start);
			cout << "Time is " << end.count() << endl;*/


			//####################################################################################################################


	return a.exec();
}
