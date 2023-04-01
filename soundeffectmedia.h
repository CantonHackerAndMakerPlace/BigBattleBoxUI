#ifndef SOUNDEFFECTMEDIA_H
#define SOUNDEFFECTMEDIA_H

#include <QObject>
#include <QAudioDecoder>

class QSoundEffect;
class QAudioOutput;

class SoundEffectMedia : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(float volume READ volume WRITE setVolume NOTIFY volumeChanged)
public:
    explicit SoundEffectMedia(QAudioOutput *out, QObject *parent = nullptr);
    void play();
    qint64 duration() const;
    QString path() const;
    float volume() const { return m_volume; }
public slots:
    void setPath(QString path);
    void setVolume(float vol) {
        if (m_volume != vol) {
            m_volume = vol;
            emit volumeChanged(m_volume);
        }
    }
signals:
    void pathChanged(QString arg);
    void volumeChanged(float);
    void ready(qint64 duration);

    void decodeError(QAudioDecoder::Error error);
private:
    QString m_path;
    float m_volume;
    QSoundEffect *m_effect;
    QAudioDecoder *m_decoder;
};

#endif // SOUNDEFFECTMEDIA_H
