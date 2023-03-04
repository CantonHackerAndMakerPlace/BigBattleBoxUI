#include "media.h"
#include <QLabel>
#include <QMovie>
#include <QPixmap>

Media::Media(QObject *parent)
    : QObject{parent}
{ }

QString Media::name() const {
    return m_name;
}

void Media::setName(QString other) {
    if (m_name != other) {
        m_name = other;
        emit notifyNameChanged(m_name);
    }
}

void Media::start() { }
void Media::pause() { }
void Media::stop() { }


// --------------------------------------------------
//              VideoMedia
// --------------------------------------------------
VideoMedia::VideoMedia(QString path, QObject *parent)
    :Media(parent)
    , m_movie(new QMovie(path, QByteArray(), this))
{

}

void VideoMedia::updateLabel(QLabel *label) {
    label->setMovie(m_movie);

}
bool VideoMedia::mediaIsValid(){
    return m_movie->isValid();
}

void VideoMedia::start() {
    m_movie->start();
}

void VideoMedia::pause() {
    m_movie->setPaused(true);
}

void VideoMedia::stop() {
    m_movie->stop();
}

// --------------------------------------------------
//              ImageMedia
// --------------------------------------------------
ImageMedia:: ImageMedia(QString path, QObject *parent)
    :Media(parent)
    , m_image(new QPixmap(path))
{

}

void ImageMedia::updateLabel(QLabel *label) {
    label->setPixmap(*m_image);
}

bool ImageMedia::mediaIsValid() {
    return !m_image->isNull();
}
