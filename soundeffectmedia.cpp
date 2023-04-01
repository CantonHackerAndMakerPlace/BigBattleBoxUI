#include "soundeffectmedia.h"
#include "qaudiodevice.h"
#include <QAudioOutput>
#include <QAudioDevice>
#include <QSoundEffect>

SoundEffectMedia::SoundEffectMedia(QAudioOutput *out, QObject *parent)
    : QObject{parent}
    , m_path()
    , m_volume(100.0)
    , m_effect(new QSoundEffect(out->device(), this))
    , m_decoder(new QAudioDecoder(this))
{
    connect(this, &SoundEffectMedia::volumeChanged,
            m_effect, &QSoundEffect::setVolume);
    m_effect->setLoopCount(1);
    m_effect->setVolume(1.0f);

    // Connecting the audio decoder signals/slots
    using MFP = void(QAudioDecoder::*)(QAudioDecoder::Error);
    connect(m_decoder, MFP(&QAudioDecoder::error),
            [=](QAudioDecoder::Error error) {
        qDebug() << "Received error " << error<< m_decoder->errorString()<<"for path:" << this->path();
        emit decodeError(error);
    });
    connect(m_decoder, &QAudioDecoder::durationChanged,
            this, &SoundEffectMedia::ready);
}

void SoundEffectMedia::play() {
    m_effect->play();
}

qint64 SoundEffectMedia::duration() const {
    return m_decoder->duration();
}

QString SoundEffectMedia::path() const {
    return m_effect->source().toString();
}

void SoundEffectMedia::setPath(QString path) {
    m_effect->setSource(QUrl(path));
    assert(!m_effect->isLoaded());
    assert(!m_effect->isMuted());
    m_decoder->setSource(QUrl::fromLocalFile(path));
    QAudioFormat format;
    format.setSampleRate(48000);
    format.setChannelCount(1);
    m_decoder->setAudioFormat(format);
    m_decoder->start();
}
