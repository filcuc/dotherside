#pragma once

// std
#include <iostream>

// Qt
#include <QPixmap>
#include <QQuickImageProvider>

#include "DOtherSideTypes.h"

class DosImageProvider : public QQuickImageProvider
{
public:
    DosImageProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    void setPixmapCallback(pixmap_cb fn);

private:
    pixmap_cb _pixmap_callback;
};
