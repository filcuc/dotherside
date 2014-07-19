#pragma once

#include <QObject>

class MockPrinter : public QObject
{
    Q_OBJECT
public:
    explicit MockPrinter(QObject *parent = 0);

public slots:
    void print(const QVariant& message);

signals:
    void printed(const QVariant& message);

};

