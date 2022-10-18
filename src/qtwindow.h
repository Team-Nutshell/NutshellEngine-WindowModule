#pragma once
#include "qwidget.h"
#include <QCloseEvent>

class QtWindow : public QWidget {
public:
	QtWindow(QWidget* parent = nullptr);

	bool shouldClose();

protected:
	void closeEvent(QCloseEvent* event);

private:
	bool m_shouldClose = false;
};