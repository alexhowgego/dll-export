#include "pch.h"
#include <iostream>
using namespace DummyLibrary;

int main()
{
	System::Console::WriteLine(DummyClass::Hello("Howge"));
	System::Console::WriteLine(DummyClass::CreateJSON("CLR runtime"));

	return 0;
}
