#pragma once
#include "GlobalSystem.h"
#include <functional>


struct SCommandRegParams
{
	string keyWord;
	float* var;
	bool shouldUpdate;
	bool get;
};


class CConsole
{
public:
	CConsole();
	~CConsole();
	
	void registerCVar(string keyWord, float* a);
	void update();
	std::vector<SCommandRegParams>& getCommands() { return m_commands; }
	float crossThreadValue;


private:
	std::vector<SCommandRegParams> m_commands;
	HANDLE m_thread;

};
