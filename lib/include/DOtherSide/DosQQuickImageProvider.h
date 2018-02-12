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
    DosImageProvider(PixmapCallback);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private:
    PixmapCallback m_pixmap_callback;
};
