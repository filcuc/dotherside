#include "DOtherSide/DOtherSideStatusWindow.h"

StatusWindow::StatusWindow(QWindow *parent)
: QQuickWindow(parent)
{
    removeTitleBar(winId());
}
