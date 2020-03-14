#include <QtCore/QCoreApplication>

#include "toml11-master/toml.hpp"

#include <windows.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
//#include <conio.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	HANDLE hFile;
	const auto lul = CreateFile();

	return a.exec();
}
