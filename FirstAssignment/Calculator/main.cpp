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
    System::GetInstance()->ParseAssemblyDumpFile("/Users/jin/Desktop/test.txt");
    System::GetInstance()->Run(0);
    DumpLogManager::GetInstance()->WriteFile("/Users/jin/Desktop/yo.txt");
    
	System::GetInstance()->Destory();
	DumpLogManager::GetInstance()->Destory();

    return 0;
}
