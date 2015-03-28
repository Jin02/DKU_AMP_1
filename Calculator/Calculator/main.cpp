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

int main(int argc, const char * argv[])
{
    System* system = System::GetInstance();
    system->Load("input2.bin");
    system->Run();
    
    return 0;
}
