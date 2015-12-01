#include "Console.h"
#include <iostream>
#include <string>
#include "GlobalSystem.h"

DWORD WINAPI ConsoleListeningThread(void* arguments)
{
	
	float a = 0.f;
	while (true)
	{
		a = 0;
		std::string line;
		std::getline(std::cin, line);
		std::string cvar = line.substr(0, line.find(' '));
		std::string val = line.substr(line.find(' ') + 1);

		for (SCommandRegParams& c : gSys->pConsole->getCommands())
		{
			if (cvar == c.keyWord)
			{
				if (val != cvar && val != "")
				{
					try
					{
						gSys->pConsole->crossThreadValue = atof(val.c_str());
						c.shouldUpdate = true;
						c.get = false;
					}
					catch (const std::exception&)
					{
						throw "Elejiglle";
					}
				}
				else
				{
					c.get = true;
					c.shouldUpdate = true;
				}
			}
			else gSys->log("Unknown variable");
		}
	}
}

CConsole::CConsole()
{
	m_thread = CreateThread(nullptr, 0, ConsoleListeningThread, 0, 0, nullptr);
}

CConsole::~CConsole()
{
	CloseHandle(m_thread);
}

void CConsole::registerCVar(string keyWord, float* a)
{
	for (SCommandRegParams c : m_commands)
		if (c.keyWord == keyWord)
			return;
	SCommandRegParams params;
	params.keyWord = keyWord;
	params.var = a;
	params.shouldUpdate = false;
	m_commands.push_back(params);
}

void CConsole::update()
{
	for (int i = 0; i < m_commands.size(); i++)
	{
		SCommandRegParams& p = m_commands[i];
		if (p.shouldUpdate)
		{
			if(p.get)
			{ 
				gSys->log(std::to_string(*p.var));
				p.shouldUpdate = false;
			}
			else
			{
				*p.var = crossThreadValue;
				gSys->log("SET TO :"+std::to_string(*p.var));
				p.shouldUpdate = false;
			}
		}
	}
}
