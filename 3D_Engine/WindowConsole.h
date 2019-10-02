#ifndef __WINDOWCONSOLE_H__
#define __WINDOWCONSOLE_H__

#include<string>
#include"imgui/imgui.h"
#include"Application.h"
#include <list>


class WindowConsole: public WindowUI
{
public:

	WindoeConsole();
	~WindowConsole();

	void addLog(int* log) const;
	bool Cleanup();

private:

	std::list<int*> logList;

}




#endif //__WINDOWCONSOLE_H_