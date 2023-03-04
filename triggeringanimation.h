#ifndef TRIGGERINGANIMATION_H
#define TRIGGERINGANIMATION_H

#include <QAbstractAnimation>

class TriggeringAnimation : public QAbstractAnimation
{
    Q_OBJECT
public:
    explicit TriggeringAnimation(QObject *parent = nullptr);

    virtual int duration() const override;
public slots:
    void setDuration(int time);

protected:
    virtual bool event(QEvent *event) override;
    virtual void updateCurrentTime(int currentTime) override;
private:
    int m_duration = 0;
};

#endif // TRIGGERINGANIMATION_H
