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
    int test   = -1234;
    int ee     = 1234;
    
    bool t = test > ee;
    
    int test3 = ee - test;
    
    
	System::GetInstance()->Load("input2.bin");
    return 0;
}
