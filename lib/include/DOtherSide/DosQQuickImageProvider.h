#pragma once

// std
#include <iostream>

// Qt
#include <QtGui/QPixmap>
#include <QtQuick/QQuickImageProvider>

#include "DOtherSideTypes.h"

class DosImageProvider : public QQuickImageProvider
{
public:
    DosImageProvider(RequestPixmapCallback callback);

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

private:
    RequestPixmapCallback m_pixmap_callback;
};
