// igen330arduinoserial.cpp : main project file.

#include "stdafx.h"

using namespace System;

//import 'ports' class from the serial IO class
using namespace System::IO::Ports;

int main(array<System::String ^> ^args)
{
    //create a serial port object, call it port (activate with port name and speed)
	SerialPort port("COM10", 9600);
	//open port 
	port.Open();

	//create inf loop that asks user for a number, if correct send an A to the arduino
	while (1)
	{
		int input = Convert::ToInt32(Console::ReadLine());
		//port.Write("A");

		if (input == 1) {
			port.Write("A");
		}

		else {
			port.Write("b");
		}
	}


	//Console::WriteLine(L"Hello World");
    return 0;
}
