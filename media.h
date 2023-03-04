#ifndef MEDIA_H
#define MEDIA_H

#include <QObject>
class QMovie;
class QLabel;
class QPixmap;
class Media : public QObject
{
    Q_OBJECT
public:
    explicit Media(QObject *parent = nullptr);

    Q_PROPERTY(QString m_name READ name WRITE setName NOTIFY notifyNameChanged)

    QString name() const;

    virtual void updateLabel(QLabel *label) = 0;
    virtual bool mediaIsValid() = 0;
    virtual void start();
    virtual void pause();
    virtual void stop();
public slots:
    void setName(QString other);

signals:
    void notifyNameChanged(QString arg);

private:
    QString m_name;
};

class VideoMedia : public Media
{
    Q_OBJECT
public:
    explicit VideoMedia(QString path, QObject *parent = nullptr);

    virtual void updateLabel(QLabel *label);
    virtual bool mediaIsValid();
    virtual void start();
    virtual void pause();
    virtual void stop();
private:
    QMovie *m_movie;
};

class ImageMedia : public Media
{
    Q_OBJECT
public:
    explicit ImageMedia(QString path, QObject *parent = nullptr);

    virtual void updateLabel(QLabel *label);
    virtual bool mediaIsValid();
private:
    QPixmap *m_image;
};



#endif // MEDIA_H
