//�� ������������, �������� ������ � ���������������


//// ���������� ��� ����� �������, � ������� �� ����� �������� 16 �����������.
//#define MAX_THREADS	32
//#define BUFFER_SIZE (64*1024)
//DWORD dwNumProcessors;
//
//// ���������� �������������� ������������� �����
//HANDLE hSourceFile = NULL;
//
//// ���������� ����� ���������� �����-������ ������ (I/O)
//HANDLE hIOCompletionPort = NULL;
//
//// ������� ������
//ULARGE_INTEGER readPointer;
//
//// ����������� ������
//CRITICAL_SECTION critSec;
//
//// ������� ThreadProc
//DWORD WINAPI readAndAnalyzeChunk(LPVOID lpParam);
//
//// ����, ������� ��������� ���������� ������ ������.
//#define KICKOFFKEY  99  // ������ ������ � ������� �����
//#define KEY          1  // ������ ��������� ������ ����� � ������ ��
//#define EXITKEY     86  // ����� �� ������(���� ��� �������� � ���������������)
//
//// ���������, ������������� ��������� ��������� �������� I/O
//typedef struct _CHUNK {
//	OVERLAPPED overlapped;
//	LPVOID buffer;
//} CHUNK, *PCHUNK;
//



//DWORD WINAPI readAndAnalyzeChunk(LPVOID lpParam)
//{
//	BOOL   bSuccess, bMoreToRead;
//	DWORD  dwNumBytes, dwKey, dwSuccess, i, repeatCnt, dwThreadId;
//	LPOVERLAPPED completedOverlapped;
//	PCHUNK completedChunk;
//	CHUNK  chunk;
//
//	printf("����� (%d) �������\n", dwThreadId = GetCurrentThreadId());
//
//	chunk.buffer = VirtualAlloc(NULL, BUFFER_SIZE, MEM_COMMIT, PAGE_READWRITE);
//
//	if (chunk.buffer == NULL)
//	{
//		fprintf(stderr, "������� VirtualAlloc ����������� ������� (������ %d)\n", GetLastError());
//		exit(1);
//	}
//
//	// ������ ������������ ������. ���� ���������� ������, ����� ������ ������.
//	while (1) {
//		bSuccess = GetQueuedCompletionStatus(hIOCompletionPort,
//			&dwNumBytes,
//			&dwKey,
//			&completedOverlapped,
//			INFINITE);
//		if (!bSuccess && (completedOverlapped == NULL))
//		{
//			fprintf(stderr, "GetQueuedCompletionStatus ����������� ������� (������ %d)\n", GetLastError());
//			exit(1);
//		}
//		if (dwKey == EXITKEY)
//		{
//			VirtualFree((LPVOID)chunk.buffer,
//				0,
//				MEM_RELEASE);
//			ExitThread(0);
//		}
//		if (!bSuccess)
//		{
//			fprintf(stderr, "GetQueuedCompletionStatus ����������� ����������� ����� I/O (������ %d)\n", GetLastError());
//			// �� ������ �� ��, ��� �� ������ ����� ��������� ������
//			// �� ������ ���� ������ ������������.
//		}
//
//		if (dwKey != KICKOFFKEY)
//		{
//			// ����������� ������. ������ � ���� ������� �������� ����������
//			// ��� ���������������� ������, ������� �������� ����� ���� �����.
//			printf("���������������� %d ����� ������\n", dwNumBytes);
//			completedChunk = (PCHUNK)completedOverlapped;
//			repeatCnt = 0;
//			for (i = 1; i < dwNumBytes; i++)
//				if ((((PBYTE)completedChunk->buffer)[i - 1] ^
//					((PBYTE)completedChunk->buffer)[i]) == 0)
//					repeatCnt++;
//			printf("������� �������� %d (����� #%d)\n", repeatCnt, dwThreadId);
//
//			// ���� ����� ������������ ������ ������, ��� BUFFER_SIZE, 
//			// ������� ���� ��������� ��������� ���. ����� ������ �� ���������.
//			if (dwNumBytes < BUFFER_SIZE)
//				ExitThread(0);
//		}
//		// �������� ��������� OVERLAPPED ��� ������������ ������.
//		EnterCriticalSection(&critSec);
//
//		if (readPointer.QuadPart < ((ULARGE_INTEGER *)lpParam)->QuadPart)
//		{
//			bMoreToRead = TRUE;
//			chunk.overlapped.Offset = readPointer.LowPart;
//			chunk.overlapped.OffsetHigh = readPointer.HighPart;
//			chunk.overlapped.hEvent = NULL;     // �� �����
//
//			// ��������� ��������� ������� � ����� ��� ���������� ������
//			readPointer.QuadPart += BUFFER_SIZE;
//		}
//		else bMoreToRead = FALSE;
//
//		LeaveCriticalSection(&critSec);
//
//		// ���������� ����������� ������.
//
//		if (bMoreToRead)
//		{
//			dwSuccess = ReadFile(hSourceFile,
//				chunk.buffer,
//				BUFFER_SIZE,
//				&dwNumBytes,
//				&chunk.overlapped);
//			if (!dwSuccess && (GetLastError() == ERROR_HANDLE_EOF))
//				printf("����� �����\n");
//			if (!dwSuccess && (GetLastError() != ERROR_IO_PENDING))
//				fprintf(stderr, "ReadFile ��� %lx ����������� ������� (������ %d)\n",
//					chunk.overlapped.Offset,
//					GetLastError());
//		}
//	} // ���� �����
//}
//



//	HANDLE hThread[MAX_THREADS];
//	DWORD  dwThreadId,
//		dwStatus,
//		dwStartTime,
//		dwEndTime,
//		dwExitStatus = ERROR_SUCCESS;
//	ULARGE_INTEGER fileSize,
//		readPointer;
//	SYSTEM_INFO systemInfo;
//	UINT i;
//	BOOL bInit = FALSE;
//	OVERLAPPED  kickoffOverlapped,
//		dieOverlapped;
//
//	// ��������, ��� ������������ ���� ������������ � ��������� ������.
//
//	if (argc != 2)
//	{
//		fprintf(stderr, "������������: %s <source file>\n", argv[0]);
//		dwExitStatus = 1;
//		goto EXIT;
//	}
//
//	// ������� ����� ����������� � �������.
//
//	GetSystemInfo(&systemInfo);
//	dwNumProcessors = systemInfo.dwNumberOfProcessors;
//
//	// ������� ������������ ����.
//
//	hSourceFile = CreateFile(L"time.txt",
//		GENERIC_READ,
//		FILE_SHARE_READ,
//		NULL,
//		OPEN_EXISTING,
//		FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED,
//		NULL);
//	if (hSourceFile == INVALID_HANDLE_VALUE)
//	{
//		fprintf(stderr, "%s: ������� �� ������� %s, ������ %d\n",
//			argv[0],
//			argv[1],
//			dwExitStatus = GetLastError());
//		goto EXIT;
//	}
//	fileSize.LowPart = GetFileSize(hSourceFile, &fileSize.HighPart);
//
//	if ((fileSize.LowPart == 0xffffffff) && (GetLastError() != NO_ERROR))
//	{
//		fprintf(stderr, "%s: GetFileSize ����������� �������, ������ %d\n", "time.txt", dwExitStatus = GetLastError());
//		goto EXIT;
//	}
//
//	// ���������� ����������� ������, ����� ������������� � ����������������
//	// ����� ������ � ���������� �������.
//	InitializeCriticalSection(&critSec);
//	bInit = TRUE;
//
//	// ������� ���� ���������� I/O. 
//	hIOCompletionPort = CreateIoCompletionPort(hSourceFile,
//		NULL,  // ��� ������������ ������ ���������� I/O
//		KEY,   // ����������� ��� � ������ ���������� I/O
//		dwNumProcessors); // �������� ������� �������
//
//	if (hIOCompletionPort == NULL)
//	{
//		fprintf(stderr,
//			"%s: ���� ����������� I/O ������� �� ������� (������ %d)\n", "time.txt", dwExitStatus = GetLastError());
//		goto EXIT;
//	}
//
//	// �������������� ��������� ����� �� ����������� ���������
//	readPointer.LowPart = readPointer.HighPart = 0;
//
//	dwStartTime = GetTickCount();
//
//	// ��������� ������� ������.
//	for (i = 0; i < 2 * dwNumProcessors; i++)
//	{
//		hThread[i] = CreateThread(NULL,
//			0,  // ������ ����� �� ���������
//			(LPTHREAD_START_ROUTINE)readAndAnalyzeChunk,
//			(LPVOID)&fileSize,
//			0,  // ���������� ����������
//			&dwThreadId);
//		if (hThread[i] == NULL)
//		{
//			fprintf(stderr, "%s: ����� ������� �� ������� #%d (������ %d)\n", "time.txt", i, dwExitStatus = GetLastError());
//			goto EXIT;
//		}
//	}
//	// �������� � ������� ��������� �������.
//	PostQueuedCompletionStatus(hIOCompletionPort,
//		0,
//		KICKOFFKEY,
//		&kickoffOverlapped);
//
//	// ����, ����� ������� ����� �������� ������.
//	dwStatus = WaitForMultipleObjects(2 * dwNumProcessors,
//		hThread,
//		FALSE,
//		INFINITE);
//	if (dwStatus == WAIT_FAILED)
//	{
//		fprintf(stderr, "%s: �������� �������� (������ %d)\n", "time.txt", dwExitStatus = GetLastError());
//		goto EXIT;
//	}
//	// ������� ����� ��������� ��������; �������� ���������,
//	// ����� ����� ����� �� ���������.
//	for (i = 0; i < 2 * dwNumProcessors - 1; i++)
//	{
//		PostQueuedCompletionStatus(hIOCompletionPort,
//			0,
//			EXITKEY,
//			&dieOverlapped);
//	}
//	// ����, ����� ����� �������� ���� ������ � �������� ������ ������������.
//	dwStatus = WaitForMultipleObjects(2 * dwNumProcessors,
//		hThread,
//		TRUE,
//		INFINITE);
//
//	if (dwStatus == WAIT_FAILED)
//	{
//		fprintf(stderr, "%s: �������� �������� (������ %d)\n", "time.txt", dwExitStatus = GetLastError());
//		goto EXIT;
//	}
//	dwEndTime = GetTickCount();
//	printf("\n\n%d ������ ���������������� �� %.3f ������\n", fileSize.LowPart,
//		(float)(dwEndTime - dwStartTime) / 1000.0);
//	printf("%.2f M�/���\n",
//		((LONGLONG)fileSize.QuadPart / (1024.0*1024.0)) /
//		(((float)(dwEndTime - dwStartTime)) / 1000.0));
//
//EXIT:
//	(void)_getch();
//	if (bInit)
//		DeleteCriticalSection(&critSec);
//	if (hThread[i])
//		CloseHandle(hThread[i]);
//	if (hIOCompletionPort)
//		CloseHandle(hIOCompletionPort);
//	if (hSourceFile)
//		CloseHandle(hSourceFile);
//
//	exit(dwExitStatus);