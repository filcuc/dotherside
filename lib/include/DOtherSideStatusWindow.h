#ifndef STATUSWINDOW_H
#define STATUSWINDOW_H

#include <QQuickWindow>

class StatusWindow: public QQuickWindow
{
    Q_OBJECT

public:
    explicit StatusWindow(QWindow *parent = nullptr);

private:
    void removeTitleBar(WId wid);
};

#endif // STATUSWINDOW_H
