//
//  main.cpp
//  Calculator
//
//  Created by Jin on 2015. 3. 11..
//  Copyright (c) 2015년 __Jin__. All rights reserved.
//

#pragma warning(disable : 4996)

#include <stdio.h>
#include <string>
#include "System.h"
#include "DumpLogManager.h"

int main(int argc, const char * argv[])
{
    uint arr[100] = {0, };
    
    for(uint i = 0; i < 100; ++i)
        arr[i] = 100 + i + 1;
    
    NSetCache test(256, 16, 2, arr);
    test.FetchData(0);
    test.InputData(4, 1);
    test.FetchData(8);
    test.FetchData(4);
    test.InputData(16, 2);
    test.FetchData(20);
    test.FetchData(16);
    test.InputData(32, 2);
    test.FetchData(32);
    test.FetchData(0);
    
    GlobalDumpManagerAddLogNewLine("--------- Init ---------");
    System* system = System::GetInstance();

    const std::string fileName = "/Users/jin/Project/MipsEmulator/Calculator/Calculator/input2.bin";
	GlobalDumpManagerAddLogNewLine("Load .bin file : " + fileName);
	system->Load(fileName);
	GlobalDumpManagerAddLogNewLine("--------- Done ---------\n\n");

	GlobalDumpManagerAddLogNewLine("--------- System Start ---------");
	system->Run();
	GlobalDumpManagerAddLogNewLine("--------- System End ---------");

	GlobalDumpLogManager->WriteFile("/Users/jin/Project/MipsEmulator/Calculator/Calculator/out.txt");
    

    return 0;
}
