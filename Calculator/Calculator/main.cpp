//
//  main.cpp
//  Calculator
//
//  Created by Jin on 2015. 3. 11..
//  Copyright (c) 2015년 __Jin__. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "System.h"
#include "DumpLogManager.h"

int main(int argc, const char * argv[])
{
	GlobalDumpManagerAddLogNewLine("--------- Init ---------");
    System* system = System::GetInstance();

	const std::string fileName = "input2.bin";
	GlobalDumpManagerAddLogNewLine("Load .bin file : " + fileName);
	system->Load(fileName);
	GlobalDumpManagerAddLogNewLine("--------- Done ---------\n\n");

	GlobalDumpManagerAddLogNewLine("--------- System Start ---------");
	system->Run();
	GlobalDumpManagerAddLogNewLine("--------- System End ---------");

	GlobalDumpLogManager->WriteFile("out.txt");

    return 0;
}
