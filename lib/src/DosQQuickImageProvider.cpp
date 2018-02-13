#include "DOtherSide/DosQQuickImageProvider.h"

DosImageProvider::DosImageProvider(RequestPixmapCallback callback) : QQuickImageProvider(QQuickImageProvider::Pixmap),
                                                              m_pixmap_callback(callback)
{
}

QPixmap DosImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QPixmap result;
    m_pixmap_callback(id.toLatin1().data(), &size->rwidth(), &size->rheight(), size->width(), size->height(), &result);
    return result;
}
