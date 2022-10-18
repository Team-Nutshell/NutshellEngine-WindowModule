#include "qtwindow.h"
#include "../external/Common/ntsh_engine_defines.h"

QtWindow::QtWindow(QWidget* parent) : QWidget(parent) {
}

bool QtWindow::shouldClose() {
	return m_shouldClose;
}

void QtWindow::closeEvent(QCloseEvent* event) {
	m_shouldClose = true;
	event->ignore();
}
