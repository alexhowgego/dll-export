// DummyLibraryUsage.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

struct DummyStruct
{
    short a;
	DWORD64 b;
    byte c;
	double d;
};

typedef LPTSTR (__stdcall *HelloFunc)(LPTSTR name);
typedef int (__stdcall *AddFunc)(int values[], int count);
typedef DummyStruct (__stdcall *StructFunc)(void);
typedef void (__stdcall *StructRefFunc)(DummyStruct& dummyStruct);
typedef void (__stdcall *StructPtrFunc)(DummyStruct* dummyStruct);
typedef void (__stdcall *Callback)(LPTSTR name);
typedef void (__stdcall *CallbackFunc)(Callback callback);
typedef void (__stdcall *RainbowFunc)(void);

void __stdcall MyCallback(LPTSTR name)
{
	wprintf(L"Hello from unmanaged code, %s!\n", name);
}

int _tmain(int argc, _TCHAR* argv[])
{
	HMODULE hDll = LoadLibrary(L"DummyLibrary.dll");
	if (!hDll)
		return GetLastError();

	HelloFunc helloFunc = (HelloFunc)GetProcAddress(hDll, "SayHello");
	if (!helloFunc)
		return GetLastError();
	wprintf(L"%s\n", helloFunc(L"unmanaged code"));

	AddFunc addFunc = (AddFunc)GetProcAddress(hDll, "Add");
	if (!addFunc)
		return GetLastError();
	int values[] = {1, 2, 3, 4, 5 };
	wprintf(L"Sum of integers from 1 to 5 is: %d\n", addFunc(values, sizeof(values) / sizeof(int)));

	StructFunc structFunc = (StructFunc)GetProcAddress(hDll, "TestStruct");
	if (!structFunc)
		return GetLastError();
	DummyStruct dummyStruct = structFunc();
	wprintf(L"Struct fields are: %d, %llu, %hhu, %g\n", dummyStruct.a, dummyStruct.b, dummyStruct.c, dummyStruct.d);

	StructRefFunc structRefFunc = (StructRefFunc)GetProcAddress(hDll, "TestStructRef");
	if (!structRefFunc)
		return GetLastError();
	structRefFunc(dummyStruct);
	wprintf(L"Another struct fields are: %d, %llu, %hhu, %g\n", dummyStruct.a, dummyStruct.b, dummyStruct.c, dummyStruct.d);

	StructPtrFunc structPtrFunc = (StructPtrFunc)GetProcAddress(hDll, "TestStructRef");
	if (!structPtrFunc)
		return GetLastError();
	structPtrFunc(&dummyStruct);
	wprintf(L"Yet another struct fields are: %d, %llu, %hhu, %g\n", dummyStruct.a, dummyStruct.b, dummyStruct.c, dummyStruct.d);

	//CallbackFunc callbackFunc = (CallbackFunc)GetProcAddress(hDll, "DoCallback");
	//if (!callbackFunc)
	//	return GetLastError();
	//callbackFunc(&MyCallback);

	//RainbowFunc rainbowFunc = (RainbowFunc)GetProcAddress(hDll, "Rainbow");
	//if (!rainbowFunc)
	//	return GetLastError();
	//rainbowFunc();

	return 0;
}
