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
    int test = -1234;
    unsigned int test2 = test;
    int test3 = test2;
    
    
	System::GetInstance()->Load("input2.bin");
    return 0;
}
