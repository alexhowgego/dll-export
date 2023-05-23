// UnmanagedConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"

struct DummyStruct
{
	short a;
	DWORD64 b;
	byte c;
	double d;
};

typedef LPTSTR(__stdcall* HelloFunc)(LPTSTR name);
typedef int(__stdcall* AddFunc)(int values[], int count);
typedef DummyStruct(__stdcall* StructFunc)(void);
typedef void(__stdcall* StructRefFunc)(DummyStruct& dummyStruct);
typedef void(__stdcall* StructPtrFunc)(DummyStruct* dummyStruct);

int main()
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
	int values[] = { 1, 2, 3, 4, 5 };
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

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
