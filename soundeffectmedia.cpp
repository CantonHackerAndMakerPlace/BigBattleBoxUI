#include "soundeffectmedia.h"
#include "qaudiodevice.h"
#include <QAudioOutput>
#include <QAudioDevice>
#include <QSoundEffect>

SoundEffectMedia::SoundEffectMedia(QAudioOutput *out, QObject *parent)
    : QObject{parent}
    , m_volume(1.0f)
    , m_effect(new QSoundEffect(out->device(), this))
    , m_decoder(new QAudioDecoder(this))
{
    connect(this, &SoundEffectMedia::volumeChanged,
            m_effect, &QSoundEffect::setVolume);
    m_effect->setLoopCount(1);
    m_effect->setVolume(1.0f);

    // Fire any pending play request once the sound finishes loading.
    connect(m_effect, &QSoundEffect::statusChanged, this, [this]() {
        if (m_effect->status() == QSoundEffect::Ready && m_pendingPlay) {
            m_pendingPlay = false;
            m_effect->play();
        }
    });

    // Connecting the audio decoder signals/slots
    using MFP = void(QAudioDecoder::*)(QAudioDecoder::Error);
    connect(m_decoder, MFP(&QAudioDecoder::error),
            [=](QAudioDecoder::Error error) {
        qDebug() << "Received error " << error<< m_decoder->errorString() << "for path:" << this->resourcePath();
        emit decodeError(error);
        // Emit ready(0) so callers can still build animation groups even when
        // the decoder fails; sound will fire without an intentional delay.
        emit ready(0);
    });
    connect(m_decoder, &QAudioDecoder::durationChanged,
            this, &SoundEffectMedia::ready);
}

void SoundEffectMedia::play() {
    if (m_effect->status() == QSoundEffect::Ready) {
        m_effect->play();
    } else {
        // Sound hasn't finished loading yet; fire it once it becomes ready.
        m_pendingPlay = true;
    }
}

qint64 SoundEffectMedia::duration() const {
    return m_decoder->duration();
}

QString SoundEffectMedia::resourcePath() const {
    return m_effect->source().toString();
}

QString SoundEffectMedia::localPath() const {
    return m_decoder->source().toString();
}

void SoundEffectMedia::initialize(QString fsPath, QString resourcePath) {
    m_effect->setSource(QUrl(resourcePath));
    assert(!m_effect->isLoaded());
    assert(!m_effect->isMuted());
    m_decoder->setSource(QUrl::fromLocalFile(fsPath));
    QAudioFormat format;
    format.setSampleRate(48000);
    format.setChannelCount(1);
    m_decoder->setAudioFormat(format);
    m_decoder->start();
}
