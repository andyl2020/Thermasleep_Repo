// igen330arduinoserial.cpp : main project file.

//#include <tchar.h>
//#using <mscorlib.dll>
#using<system.dll> 

#include "stdafx.h"

using namespace System;

//import 'ports' class from the serial IO class
using namespace System::IO;
using namespace System::IO::Ports;

int main(array<System::String ^> ^args)
{
    //create a serial port object, call it port (activate with port name and speed)
	SerialPort port("COM11", 9600);
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


		String^ fileName = "textfile.txt";
		try
		{
			Console::WriteLine("trying to open file {0}...", fileName);
			StreamReader^ din = File::OpenText(fileName);

			String^ str;
			int count = 0;
			while ((str = din->ReadLine()) != nullptr)
			{
				count++;
				Console::WriteLine("line {0}: {1}", count, str);
			}
		}
		catch (Exception^ e)
		{
			if (dynamic_cast<FileNotFoundException^>(e))
				Console::WriteLine("file '{0}' not found", fileName);
			else
				Console::WriteLine("problem reading file '{0}'", fileName);
		}






		//https://support.microsoft.com/en-ca/help/816148/how-to-read-from-and-write-to-a-text-file-by-using-visual-c-net-or-vis
		//https://msdn.microsoft.com/en-us/library/y52yxde8.aspx



	}

	//Console::WriteLine(L"Hello World");
	return 0;

}

