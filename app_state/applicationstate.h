#ifndef APPLICATIONSTATE_H
#define APPLICATIONSTATE_H

#include <QObject>

class ApplicationState : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationState(QObject *parent = nullptr);

signals:

};

#endif // APPLICATIONSTATE_H
