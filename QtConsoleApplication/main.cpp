#include <QtCore/QCoreApplication>
#include <iostream>
#include <thread> 
#include "toml11-master/toml.hpp"
#include <codecvt>
#include <windows.h>

using namespace std;
using namespace chrono;

#define locale

template<typename T>
using deleted_unique_ptr = unique_ptr<T, function<void(T*)>>;


string to_string(wstring wstr)
{
	return wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(wstr);
}

wstring to_wstring(string str)
{
	return wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str);
}

void readFromFileUsingWinAPI(string raw_str) {

	wstring str = to_wstring(raw_str);

	auto start = steady_clock::now();

	OVERLAPPED ovr;

	memset(&ovr, 0, sizeof(ovr));

	deleted_unique_ptr<HANDLE> hEndRead((HANDLE*)CreateEvent(NULL, FALSE, FALSE, NULL), [](HANDLE hadle)
	{
		CloseHandle(hadle);
	});

	if (hEndRead.get() == NULL)
	{
		cout << GetLastError();
	}

	ovr.hEvent = hEndRead.get();

	deleted_unique_ptr<HANDLE> port((HANDLE*)CreateFile(str.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL), [](HANDLE handle) 
	{
		CloseHandle(handle);
	});

	if (port.get() == INVALID_HANDLE_VALUE)
	{
		cout << "Create file " << to_string(str) << " is failed." << endl << "The last error code: " << GetLastError() << endl;
		cout << "Time is " << (duration_cast<seconds>(steady_clock::now() - start)).count() << " seconds" << endl;
		return;
	}

	while (true) {
		DWORD R;
		DWORD  dwError;
		char Line[1000000];

		auto bResult = ReadFile(port.get(), Line, sizeof(Line), &R, &ovr);

		for (int i = 0; i < 5; i++) {
			this_thread::sleep_for(milliseconds(100));
			cout << "#";
		}
		
		cout << endl;
		cout << "Useful work here" << endl;

		if (!bResult)
		{
			switch (dwError = GetLastError())
			{
			case ERROR_HANDLE_EOF: {
				cout << "End of file" << endl;
				cout << "Time is " << (duration_cast<seconds>(steady_clock::now() - start)).count() << " seconds" << endl;
				return;
			}
			case ERROR_IO_PENDING: {
				cout << " In process " << endl;
				break;
			}
			default: {
				cout << "Read file " << to_string(str) << " is failed." << endl << "The last error code: " << dwError << endl;
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
				cout << "Time is " << (duration_cast<seconds>(steady_clock::now() - start)).count() << " seconds" << endl;
				return;
			}
		}

		cout << this_thread::get_id() << endl;
		cout << Line << " " << endl;

		ovr.Offset += sizeof(Line);

	}
}

void readFromFileUsingSTD(const char str[]) {

	/*deleted_unique_ptr<const char> str(raw_str.c_str(), [](const char* str) 
	{
		delete str;
	});*/

	/*SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	auto numCPU = sysinfo.dwNumberOfProcessors;*/

	deleted_unique_ptr<FILE> file(fopen(str, "rt"), [](FILE* file) 
	{
		fclose(file);
	});

	if (file.get() == NULL)
	{
		fputs("Ошибка файла", stderr);
		exit(1);
	}


	fseek(file.get(), 0, SEEK_END);
	long lSize = ftell(file.get());
	rewind(file.get());

	deleted_unique_ptr<char> buffer((char*)calloc(sizeof(char), lSize), [](char* buffer) 
	{
		free(buffer);
		//buffer = nullptr;
	});

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
		string str1 = toml::find<toml::string>(data, "pathToFile", 0);
		string str2 = toml::find<toml::string>(data, "pathToFile", 1);

		//thread t(readFromFileUsingSTD, str1);

		readFromFileUsingWinAPI(str1);
		//readFromFileUsingSTD(str1.c_str());

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

	return a.exec();
}
