#include "System.h"
#include <memory.h>
#include <fstream>

#include "Transmit.h"
#include "Arithmetic.h"

#include "DumpLogManager.h"

System::System()
{
}

System::~System()
{
   	ClearAllDataRegisters();
}

void System::ClearAllDataRegisters()
{
    std::fill(_registers.begin(), _registers.end(), 0);
}

void System::ClearRegister(int index)
{
    _registers[index] = 0;
}

void System::ParseAssemblyDumpFile(const std::string& dumpFileFullPath)
{
    std::ifstream file(dumpFileFullPath);
    ASSERT_COND_MSG(file.is_open() && file.good(), "Error, strange file");
    
    auto Tokenize = [](std::vector<std::string>& outTokens, const std::string& str, const std::string& delimiters)
    {
        std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
        std::string::size_type pos     = str.find_first_of(delimiters, lastPos);
        
        while (std::string::npos != pos || std::string::npos != lastPos)
        {
            outTokens.push_back(str.substr(lastPos, pos - lastPos));
            lastPos = str.find_first_not_of(delimiters, pos);
            pos = str.find_first_of(delimiters, lastPos);
        }
    };
    
    auto Replace = [](std::string& outString, const std::string& targetStr, const std::string& from, const std::string& to)
    {
        outString = targetStr;
        
        for(size_t pos = 0;
            ( pos = targetStr.find(from, pos) ) != std::string::npos;
            pos += to.length())
        {
            outString.replace(pos, from.length(), to);
        }
    };
    


    std::string lineBuff = "";
    while (std::getline(file, lineBuff))
    {
        //먼저 '.' 이 있는지 체크, '.'이 있는 줄은 처리 안해도 되는듯 함
        if( lineBuff.find('.') != std::string::npos )
            continue;
        
        if( lineBuff[ lineBuff.length() - 1 ] == ':' )
        {
            std::string temp = lineBuff.substr(0, lineBuff.length() - 1);
            _jumpAddrs.insert( std::make_pair(temp, _instructions.size() + 1) ); // Next Line
            continue;
        }
        
        // 문자열 정리 - 1
        // \t, '  ' 를 ' '로 통일. 속도는 신경 쓰지 않음 ㅋ
        {
            Replace(lineBuff, lineBuff, "\t", " ");
            
            while (1)
            {
                size_t pos = lineBuff.find("  ");
                if(pos != std::string::npos)    lineBuff.replace(pos, 2, " ");
                else                            break;
            }
        }
        
    }
    
    file.close();
}

void System::Run(int start)
{
    
}