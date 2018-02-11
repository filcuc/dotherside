#include "DOtherSide/DosQQuickImageProvider.h"

DosImageProvider::DosImageProvider() : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

QPixmap DosImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    pixmap_request request {
        id.toLatin1().data(), &size->rwidth(), &size->rheight(), size->width(), size->height() };                
    auto pixmap = m_pixmap_callback(request);
    auto pixmap_copy = *(static_cast<QPixmap*>(pixmap));
    delete (static_cast<QPixmap*>(pixmap));
    return pixmap_copy;
}

void DosImageProvider::setPixmapCallback(PixmapCallback fn) {
    m_pixmap_callback = fn;
}
