#pragma once
#include <Windows.h>

class Window {

public:
	Window();

	// initialize window
	bool init();
	bool broadcast();
	bool isRun();
	bool release();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	// EVENTS
	virtual void onCreate()=0;
	virtual void onUpdate()=0;
	virtual void onDestroy();

	~Window();

protected:
	HWND m_hwnd;
	bool m_is_run;

};

