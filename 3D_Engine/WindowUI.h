#ifndef __WindowUI_H__
#define __WindowUI_H__

class WindowUI
{
public:
	WindowUI(char*title);
	virtual ~WindowUI();


public:

	virtual bool Display() = 0;
	virtual inline bool isActive()const			{ return active; };
	virtual inline void SetState(bool state)	{ active = state; }
	virtual inline void ChangeState()			{ active = !active; }
	virtual inline char*GetNameWin()const		{ return name_win; }

protected:

	bool  active = false;
	char* name_win = nullptr;

};

#endif