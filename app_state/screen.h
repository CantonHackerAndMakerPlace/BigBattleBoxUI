#ifndef SCREEN_H
#define SCREEN_H

#include <QObject>

class Screen : public QObject
{
    Q_OBJECT
public:
    explicit Screen(QObject *parent = nullptr);

signals:

};

#endif // SCREEN_H
