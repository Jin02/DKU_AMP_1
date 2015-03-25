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
	System::GetInstance()->Load("input2.bin");
	System::GetInstance()->Decode(0x27bdffd8);
    return 0;
}
