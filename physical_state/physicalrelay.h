#ifndef PHYSICALRELAY_H
#define PHYSICALRELAY_H

#include <QObject>

class PhysicalRelay : public QObject
{
    Q_OBJECT
public:
    explicit PhysicalRelay(QObject *parent = nullptr);

    bool state() const;

public slots:
    void setState(bool arg);
signals:
    void stateChanged(bool v);
private:
    bool m_state = false;
};

#endif // RELAYSTATE_H
