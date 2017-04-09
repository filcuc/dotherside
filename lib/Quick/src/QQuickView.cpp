#include "DOtherSide/Quick/Quick.h"

#include <QQuickView>

::DosQQuickView *dos_qquickview_create()
{
    return new QQuickView();
}

void dos_qquickview_show(::DosQQuickView *vptr)
{
    auto view = static_cast<QQuickView *>(vptr);
    view->show();
}

void dos_qquickview_delete(::DosQQuickView *vptr)
{
    auto view = static_cast<QQuickView *>(vptr);
    delete view;
}

char *dos_qquickview_source(const ::DosQQuickView *vptr)
{
    auto view = static_cast<const QQuickView *>(vptr);
    QUrl url = view->source();
    return convert_to_cstring(url.toString());
}

void dos_qquickview_set_source(::DosQQuickView *vptr, const char *filename)
{
    auto view = static_cast<QQuickView *>(vptr);
    view->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + QDir::separator() + QString(filename)));
}

void dos_qquickview_set_source_url(::DosQQuickView *vptr, ::DosQUrl *url)
{
    auto view = static_cast<QQuickView *>(vptr);
    auto _url = static_cast<QUrl *>(url);
    view->setSource(*_url);
}

void dos_qquickview_set_resize_mode(::DosQQuickView *vptr, int resizeMode)
{
    auto view = static_cast<QQuickView *>(vptr);
    view->setResizeMode((QQuickView::ResizeMode) resizeMode);
}

::DosQQmlContext *dos_qquickview_rootContext(::DosQQuickView *vptr)
{
    auto view = static_cast<QQuickView *>(vptr);
    return view->rootContext();
}
