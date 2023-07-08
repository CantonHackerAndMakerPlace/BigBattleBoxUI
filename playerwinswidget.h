#ifndef PLAYERWINSWIDGET_H
#define PLAYERWINSWIDGET_H

#include <QWidget>

namespace Ui {
class PlayerWinsWidget;
}

class PlayerWinsWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
public:
    explicit PlayerWinsWidget(QWidget *parent = nullptr);
    ~PlayerWinsWidget();
    QString winner();
    QString source();
public slots:
    void setSource(QString path);
    void setWinner(QString name);

    void startCelibration();
signals:
    void confetti();
    void restartConfetti();
    void sourceChanged(QString );
    void winnerChanged(QString);
private:
    Ui::PlayerWinsWidget *ui;
    QString m_qmlToLoad;
    QString m_winner;
};

#endif // PLAYERWINSWIDGET_H
