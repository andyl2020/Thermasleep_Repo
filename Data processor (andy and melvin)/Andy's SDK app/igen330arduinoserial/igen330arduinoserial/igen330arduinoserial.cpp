// igen330arduinoserial.cpp : main project file.

//#define MY_TIMER_ID (WM_USER + 200)

#include <tchar.h>
#include <stdlib.h>
#using <mscorlib.dll>
#using<system.dll> 
#include <windows.h>

#include "stdafx.h"

using namespace System;

//import 'ports' class from the serial IO class
using namespace System::IO;
using namespace System::IO::Ports;
using namespace std;


int main(array<System::String ^> ^args)
{
    //create a serial port object, call it port (activate with port name and speed)
	SerialPort port("COM10", 9600);
	//open port 

	//AS (anything with AS is stuff that's commented out for read/write testing)
	//AS (anything with AS is stuff that's commented out NOT for read/write testing but the stuff after(RW /w arduino))

	//as
	port.Open();

	//create inf loop that asks user for a number, if correct send an A to the arduino

	while (1)
	{
		

		//String^ fileName = "textfile.txt";
		//holy this works:
		String^ fileName = "C:\\Users\\Andy L\\Desktop\\Thermasleep_Repo\\Data processor (andy and melvin)\\Andy's SDK app\\ZIPPED - Microsoft Band Sensors\\C#\\BandSensors\\bin\\x86\\Debug\\AppX\\andytest1.txt";
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

				//printing the temp -> convert str to int
				//use to compare and send A if too hot/cold
				//AS2
				int input = int::Parse(str);
				//AS2
				if (input == 33)
					//AS2
					port.Write("A");
				//AS2
				else
					port.Write("b");

			}



		}
		catch (Exception^ e)
		{
			if (dynamic_cast<FileNotFoundException^>(e))
				Console::WriteLine("file '{0}' not found", fileName);
			else
				Console::WriteLine("problem reading file '{0}'", fileName);
		}







		//AS
		//int input = Convert::ToInt32(Console::ReadLine());



		//AS
		/*
		if (input == 1) {
		port.Write("A");
		}

		else {
		port.Write("b");
		}
		*/



		//https://support.microsoft.com/en-ca/help/816148/how-to-read-from-and-write-to-a-text-file-by-using-visual-c-net-or-vis
		//https://msdn.microsoft.com/en-us/library/y52yxde8.aspx
		//timer options:
		//https://social.msdn.microsoft.com/Forums/en-US/66b430af-de06-4729-92c1-75084ad53f7d/how-can-i-make-a-delay-in-vissual-studio-2010-c?forum=vcmfcatl




			
	}

	//Console::WriteLine(L"Hello World");
	return 0;

}

