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

    QString source();
public slots:
    void setSource(QString path);
signals:
    void confetti();
    void sourceChanged(QString );
private:
    Ui::PlayerWinsWidget *ui;
    QString m_qmlToLoad;
};

#endif // PLAYERWINSWIDGET_H
