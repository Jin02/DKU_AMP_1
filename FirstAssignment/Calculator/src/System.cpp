#include "System.h"
#include <memory.h>
#include <fstream>

#include "Transmit.h"
#include "Arithmetic.h"

#include "DumpLogManager.h"

System* System::_instance = nullptr;

System::System()
{
}

System::~System()
{
   	ClearAllDataRegisters();
    ClearAllInstruction();
    ClearAllInstructionStr();
}

System* System::GetInstance()
{
	if(_instance == nullptr)
		_instance = new System;

	return _instance;
}

void System::Destory()
{
	SAFE_DELETE(_instance);
}

void System::ClearAllDataRegisters()
{
    std::fill(_dataRegisters.begin(), _dataRegisters.end(), 0);
}

void System::ClearRegister(unsigned int index)
{
    _dataRegisters[index] = 0;
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
    

    std::string buff = "";
    while (std::getline(file, buff))
    {
        _inst_reg_string.push_back(buff);

        // \t, '  ' 를 ' '로 통일. 속도는 신경 쓰지 않음 ㅋ
        {
            Replace(buff, buff, "\t", " ");
            
            while (1)
            {
                size_t pos = buff.find("  ");
                if(pos != std::string::npos)    buff.replace(pos, 2, " ");
                else                            break;
            }
        }
        
        {
            std::vector<std::string> tokens;
            Tokenize(tokens, buff, " ");
            
            std::vector<Operand> operands;
            for(int i=1; i<tokens.size(); ++i)
            {
                const std::string& operandStr = tokens[i];
                
                try
                {
                    unsigned long hexValue = std::stoul(operandStr, nullptr, 16);
                    Operand operand(Operand::Type::Value);
                    operand.SetData((unsigned int)hexValue);
                    
                    operands.push_back(operand);
                }
                catch(...) // maybe.. register
                {
                    ASSERT_COND_MSG(operandStr[0] == 'R', "Error, strange text");
                    
                    Operand operand(Operand::Type::Register);
                    unsigned int value = (unsigned int)std::stoul(operandStr.c_str()+1, nullptr, 16);
                    operand.SetData(value);
                    
                    operands.push_back(operand);
                }
            }
            
            const std::string& opCode = tokens[0];
            if(opCode == "+")
                _instructions.push_back( new Add(operands) );
            else if(opCode == "-")
                _instructions.push_back( new Sub(operands) );
            else if(opCode == "/")
                _instructions.push_back( new Div(operands) );
            else if(opCode == "*")
                _instructions.push_back( new Mul(operands) );
            else if(opCode == "M")
                _instructions.push_back( new Move(operands) );
        }
    }
    
    file.close();
}

void System::ClearAllInstruction()
{
    for(auto elem : _instructions)
        SAFE_DELETE(elem);
}

void System::ClearInstruction(unsigned int index)
{
    SAFE_DELETE( _instructions[index] );
    _instructions.erase(_instructions.begin() + index);
}

void System::ClearAllInstructionStr()
{
    _inst_reg_string.clear();
}

void System::ClearInstructionStr(unsigned int index)
{
    _inst_reg_string.erase(_inst_reg_string.begin() + index);
}

void System::Run(unsigned int start)
{
#ifdef USE_OUTPUT_DUMP_LOG
    DumpLogManager::GetInstance()->AddLog("\tInput\t\t\tOutput\n");
#endif
    
    for(unsigned int i = start; i < _instructions.size(); ++i)
    {
#ifdef USE_OUTPUT_DUMP_LOG
    DumpLogManager::GetInstance()->AddLog(_inst_reg_string[i] + "\t\t");
#endif
        _instructions[i]->Work();
    }
    
#ifdef USE_OUTPUT_DUMP_LOG
    DumpLogManager::GetInstance()->Print();
#endif
}