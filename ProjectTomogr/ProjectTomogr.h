
// ProjectTomogr.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CProjectTomogrApp:
// Сведения о реализации этого класса: ProjectTomogr.cpp
//

class CProjectTomogrApp : public CWinApp
{
public:
	CProjectTomogrApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CProjectTomogrApp theApp;
