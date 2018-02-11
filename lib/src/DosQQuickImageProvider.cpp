#include "DOtherSide/DosQQuickImageProvider.h"

DosImageProvider::DosImageProvider() : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

QPixmap DosImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    auto pixmap = m_pixmap_callback(id.toLatin1().data(), &size->rwidth(), &size->rheight(), size->width(), size->height());
    auto pixmap_copy = *(static_cast<QPixmap*>(pixmap));
    delete (static_cast<QPixmap*>(pixmap));
    return pixmap_copy;
}

void DosImageProvider::setPixmapCallback(PixmapCallback callback) {
    m_pixmap_callback = callback;
}
