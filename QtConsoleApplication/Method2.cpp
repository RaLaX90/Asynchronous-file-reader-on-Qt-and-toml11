//Работает, но выдаёт просто цифры

//HANDLE hEvent;
//DWORD sizeOfBuf = 33554432;
//BYTE *ReadBuffer = new BYTE[sizeOfBuf];
//
//
//void ReadFromFile(int index)
//{
//	SYSTEM_INFO SysInfo;  // system information; used to get granularity
//	DWORD dwSysGran;      // system allocation granularity
//	GetSystemInfo(&SysInfo);
//	dwSysGran = SysInfo.dwAllocationGranularity;
//
//	int iEvent = 0;
//
//	DWORD dw = WaitForSingleObject(hEvent, INFINITE);
//
//	HANDLE hFileForRead = CreateFile(L"D:time.txt",		// file to open
//		GENERIC_READ,          // open for reading
//		FILE_SHARE_READ,       // share for reading
//		NULL,                  // default security
//		OPEN_EXISTING,         // existing file only
//		FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED,	// no buffering | asynchronous mode
//		NULL);                 // no attr. template
//
//
//	if (hFileForRead == INVALID_HANDLE_VALUE)
//	{
//		cout << "\nError of opening file!";
//		return;
//	}
//
//	OVERLAPPED lpOverlapped;	// структура для задания режима асинхронного чтения
//	lpOverlapped.hEvent = hEvent;
//	lpOverlapped.Offset = 0;
//	lpOverlapped.OffsetHigh = 0;
//	DWORD  dwBytesRead = 0;
//
//	DWORD  numberOfBytesTrasferred = 0;
//	//DWORD  numberOfBytesToRead = 33554432; // читать блоками, кратными размеру сектора (c флешки) (асинхр.)
//	DWORD  numberOfBytesToRead = 1048576; // c FLOPPY
//
//	bool readFlag = ReadFile(hFileForRead, ReadBuffer, numberOfBytesToRead, &dwBytesRead, &lpOverlapped);
//	bool flag = GetOverlappedResult(hFileForRead, &lpOverlapped, &numberOfBytesTrasferred, FALSE);
//	if (flag) {
//		cout << "\nReadFile(" << index << ") finished" << endl; // ГФО закончилась
//	}
//	else {
//		cout << "\nReadFile(" << index << ") in processing" << endl; // ГФО выполняется
//	}
//
//	//CloseHandle(hFileForRead);
//}
//
//




//	hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
//	for (int i = 0; i < 10; ++i)
//	{
//		ReadFromFile(i);
//
//	}
//	cout << endl << "Press any key to exit...";
//	Sleep(2000);
