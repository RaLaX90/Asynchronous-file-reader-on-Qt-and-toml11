//Не запускаеться, странная ошибка с преобразованием


//// Назначения для этого примера, в который мы имеем максимум 16 процессоров.
//#define MAX_THREADS	32
//#define BUFFER_SIZE (64*1024)
//DWORD dwNumProcessors;
//
//// Дескриптор анализируемого источникового файла
//HANDLE hSourceFile = NULL;
//
//// Дескриптор порта завершения ввода-вывода данных (I/O)
//HANDLE hIOCompletionPort = NULL;
//
//// Позиция чтения
//ULARGE_INTEGER readPointer;
//
//// Критическая секция
//CRITICAL_SECTION critSec;
//
//// Функция ThreadProc
//DWORD WINAPI readAndAnalyzeChunk(LPVOID lpParam);
//
//// Коды, которые управляют характером работы потока.
//#define KICKOFFKEY  99  // Начало чтения и анализа файла
//#define KEY          1  // Чтение следующей порции файла и анализ ее
//#define EXITKEY     86  // Выход из работы(файл был прочитан и проанализирован)
//
//// Структурв, отслеживающая ожидающие обработки операции I/O
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
//	printf("Поток (%d) запущен\n", dwThreadId = GetCurrentThreadId());
//
//	chunk.buffer = VirtualAlloc(NULL, BUFFER_SIZE, MEM_COMMIT, PAGE_READWRITE);
//
//	if (chunk.buffer == NULL)
//	{
//		fprintf(stderr, "Функция VirtualAlloc завершилась ошибкой (ошибка %d)\n", GetLastError());
//		exit(1);
//	}
//
//	// Начало асинхронного чтения. Ждем завершения чтения, затем читаем дальше.
//	while (1) {
//		bSuccess = GetQueuedCompletionStatus(hIOCompletionPort,
//			&dwNumBytes,
//			&dwKey,
//			&completedOverlapped,
//			INFINITE);
//		if (!bSuccess && (completedOverlapped == NULL))
//		{
//			fprintf(stderr, "GetQueuedCompletionStatus завершилась ошибкой (ошибка %d)\n", GetLastError());
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
//			fprintf(stderr, "GetQueuedCompletionStatus переместила испорченный пакет I/O (ошибка %d)\n", GetLastError());
//			// Не смотря на то, что вы можете здесь завершить работу
//			// по ошибке этот пример продолжается.
//		}
//
//		if (dwKey != KICKOFFKEY)
//		{
//			// Анализируем данные. Анализ в этом примере выявляет количество
//			// пар последовательных байтов, которые являются равны друг другу.
//			printf("Проанализирована %d часть байтов\n", dwNumBytes);
//			completedChunk = (PCHUNK)completedOverlapped;
//			repeatCnt = 0;
//			for (i = 1; i < dwNumBytes; i++)
//				if ((((PBYTE)completedChunk->buffer)[i - 1] ^
//					((PBYTE)completedChunk->buffer)[i]) == 0)
//					repeatCnt++;
//			printf("Подсчет повторов %d (поток #%d)\n", repeatCnt, dwThreadId);
//
//			// Если число возвращенных байтов меньше, чем BUFFER_SIZE, 
//			// которое было прочитано последний раз. Выход потока из программы.
//			if (dwNumBytes < BUFFER_SIZE)
//				ExitThread(0);
//		}
//		// Настроим структуру OVERLAPPED для последующего чтения.
//		EnterCriticalSection(&critSec);
//
//		if (readPointer.QuadPart < ((ULARGE_INTEGER *)lpParam)->QuadPart)
//		{
//			bMoreToRead = TRUE;
//			chunk.overlapped.Offset = readPointer.LowPart;
//			chunk.overlapped.OffsetHigh = readPointer.HighPart;
//			chunk.overlapped.hEvent = NULL;     // не нужен
//
//			// Установим указатель позиции в файле для следующего чтения
//			readPointer.QuadPart += BUFFER_SIZE;
//		}
//		else bMoreToRead = FALSE;
//
//		LeaveCriticalSection(&critSec);
//
//		// Происходит последующее чтение.
//
//		if (bMoreToRead)
//		{
//			dwSuccess = ReadFile(hSourceFile,
//				chunk.buffer,
//				BUFFER_SIZE,
//				&dwNumBytes,
//				&chunk.overlapped);
//			if (!dwSuccess && (GetLastError() == ERROR_HANDLE_EOF))
//				printf("Конец файла\n");
//			if (!dwSuccess && (GetLastError() != ERROR_IO_PENDING))
//				fprintf(stderr, "ReadFile при %lx завершилась ошибкой (ошибка %d)\n",
//					chunk.overlapped.Offset,
//					GetLastError());
//		}
//	} // пока конец
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
//	// Убедимся, что источниковый файл определяется в командной строке.
//
//	if (argc != 2)
//	{
//		fprintf(stderr, "Используется: %s <source file>\n", argv[0]);
//		dwExitStatus = 1;
//		goto EXIT;
//	}
//
//	// Получим число процессоров в системе.
//
//	GetSystemInfo(&systemInfo);
//	dwNumProcessors = systemInfo.dwNumberOfProcessors;
//
//	// Откроем источниковый файл.
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
//		fprintf(stderr, "%s: Открыть не удалось %s, ошибка %d\n",
//			argv[0],
//			argv[1],
//			dwExitStatus = GetLastError());
//		goto EXIT;
//	}
//	fileSize.LowPart = GetFileSize(hSourceFile, &fileSize.HighPart);
//
//	if ((fileSize.LowPart == 0xffffffff) && (GetLastError() != NO_ERROR))
//	{
//		fprintf(stderr, "%s: GetFileSize завершилась ошибкой, ошибка %d\n", "time.txt", dwExitStatus = GetLastError());
//		goto EXIT;
//	}
//
//	// Используем критическую секцию, чтобы преобразовать в последовательную
//	// форму доступ к нескольким потокам.
//	InitializeCriticalSection(&critSec);
//	bInit = TRUE;
//
//	// Создаем порт завершения I/O. 
//	hIOCompletionPort = CreateIoCompletionPort(hSourceFile,
//		NULL,  // нет существующих портов завершения I/O
//		KEY,   // принимаемый код в пакете завершения I/O
//		dwNumProcessors); // максимум рабочих потоков
//
//	if (hIOCompletionPort == NULL)
//	{
//		fprintf(stderr,
//			"%s: Порт заверешения I/O создать не удалось (ошибка %d)\n", "time.txt", dwExitStatus = GetLastError());
//		goto EXIT;
//	}
//
//	// Инициализируем указатель файла на асинхронную структуру
//	readPointer.LowPart = readPointer.HighPart = 0;
//
//	dwStartTime = GetTickCount();
//
//	// Запускаем рабочие потоки.
//	for (i = 0; i < 2 * dwNumProcessors; i++)
//	{
//		hThread[i] = CreateThread(NULL,
//			0,  // размер стека по умолчанию
//			(LPTHREAD_START_ROUTINE)readAndAnalyzeChunk,
//			(LPVOID)&fileSize,
//			0,  // выполнение немедленно
//			&dwThreadId);
//		if (hThread[i] == NULL)
//		{
//			fprintf(stderr, "%s: Поток создать не удалось #%d (ошибка %d)\n", "time.txt", i, dwExitStatus = GetLastError());
//			goto EXIT;
//		}
//	}
//	// Помещаем в очередь начальное событие.
//	PostQueuedCompletionStatus(hIOCompletionPort,
//		0,
//		KICKOFFKEY,
//		&kickoffOverlapped);
//
//	// Ждем, когда рабочий поток завершит работу.
//	dwStatus = WaitForMultipleObjects(2 * dwNumProcessors,
//		hThread,
//		FALSE,
//		INFINITE);
//	if (dwStatus == WAIT_FAILED)
//	{
//		fprintf(stderr, "%s: Ожидание прервано (ошибка %d)\n", "time.txt", dwExitStatus = GetLastError());
//		goto EXIT;
//	}
//	// Рабочий поток возвратил значение; отправим сообщение,
//	// чтобы поток вышел из программы.
//	for (i = 0; i < 2 * dwNumProcessors - 1; i++)
//	{
//		PostQueuedCompletionStatus(hIOCompletionPort,
//			0,
//			EXITKEY,
//			&dieOverlapped);
//	}
//	// Ждем, когда поток закончит свою работу и завершит всякую деятельность.
//	dwStatus = WaitForMultipleObjects(2 * dwNumProcessors,
//		hThread,
//		TRUE,
//		INFINITE);
//
//	if (dwStatus == WAIT_FAILED)
//	{
//		fprintf(stderr, "%s: Ожидание прервано (ошибка %d)\n", "time.txt", dwExitStatus = GetLastError());
//		goto EXIT;
//	}
//	dwEndTime = GetTickCount();
//	printf("\n\n%d байтов проанализировано за %.3f секунд\n", fileSize.LowPart,
//		(float)(dwEndTime - dwStartTime) / 1000.0);
//	printf("%.2f Mб/сек\n",
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