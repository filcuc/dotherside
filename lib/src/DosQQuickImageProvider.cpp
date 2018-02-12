#include "DOtherSide/DosQQuickImageProvider.h"

DosImageProvider::DosImageProvider(PixmapCallback callback) : QQuickImageProvider(QQuickImageProvider::Pixmap),
                                                              m_pixmap_callback(callback)
{
}

QPixmap DosImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    auto pixmap = m_pixmap_callback(id.toLatin1().data(), &size->rwidth(), &size->rheight(), size->width(), size->height());
    auto pixmap_copy = *(static_cast<QPixmap*>(pixmap));
    delete (static_cast<QPixmap*>(pixmap));
    return pixmap_copy;
}
