#include "Window.h"
#include <iostream>

Window* window = nullptr;

Window::Window() {

}

void Window::onDestroy() {
	m_is_run = false;
}

Window::~Window() {

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	switch (msg) {
	case WM_CREATE:
		if (window) window->onCreate();
		break;

	case WM_DESTROY:
		if (window) window->onDestroy();
		::PostQuitMessage(0);
		break;

	default:
		return ::DefWindowProcW(hwnd, msg, wparam, lparam);
	}

	return 0;

}


bool Window::init()
{
	WNDCLASSEX wc = {};
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc)) {
		std::cerr << "RegisterClassEx failed. Error: " << GetLastError() << std::endl;
		return false;
	}


	if (!window)
		window = this;

	// creation of window
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"3D Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, GetModuleHandle(NULL), NULL);

	// if creation fails, return false
	if (!m_hwnd) {
		std::cerr << "CreateWindowEx failed. Error: " << GetLastError() << std::endl;
		return false;
	}

	// show up the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	// set flag to indicate that the window is initialized and running
	m_is_run = true;

	return true;
}

bool Window::broadcast()
{
	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	window->onUpdate();

	Sleep(0);

	return true;
}

bool Window::isRun()
{
	return m_is_run;
}

bool Window::release()
{
	if (!::DestroyWindow(m_hwnd))
		return false;

	return true;
}
