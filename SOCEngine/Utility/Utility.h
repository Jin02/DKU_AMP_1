#pragma once

#include <string>
#include <vector>
#include <stdio.h>

class Utility
{
public:
	//http://www.joinc.co.kr/modules/moniwiki/wiki.php/Site/C++/Documents/C++ProgramingHowToPerPage/standardstring.html
	static void Tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ")
	{
		// �� ù ���ڰ� �������� ��� ����
		std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
		// �����ڰ� �ƴ� ù ���ڸ� ã�´�
		std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

		while (std::string::npos != pos || std::string::npos != lastPos)
		{
			// token�� ã������ vector�� �߰��Ѵ�
			tokens.push_back(str.substr(lastPos, pos - lastPos));
			// �����ڸ� �پ�Ѵ´�.  "not_of"�� �����϶�
			lastPos = str.find_first_not_of(delimiters, pos);
			// ���� �����ڰ� �ƴ� ���ڸ� ã�´�
			pos = str.find_first_of(delimiters, lastPos);
		}
	}

	static std::string WinCmd(const std::string& cmd)
	{
		FILE* fp = _popen(cmd.c_str(), "r");
		if( fp == nullptr )
			return "ERROR";

		char buffer[128];
		std::string result = "";
		while(!feof(fp))
		{
			if(fgets(buffer, 128, fp) != nullptr)
				result += buffer;
		}
		_pclose(fp);
		return result;
	}
};