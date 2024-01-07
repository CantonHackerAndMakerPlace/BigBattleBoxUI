#ifndef ARDUINOCLIENT_H
#define ARDUINOCLIENT_H

#include <QObject>

class GeneralLEDConfiguration;
class ArduinoMessanger;

/// This class is a simplifying translation layer made to handle
/// exactly how we translate from the normal world to the world
/// that's oriented in terms of the physical orientation of
/// things.
///
/// Basically this handles translating turn this light on, make it this
/// color at this index etc... and translates that into the physical
/// LED lights that we actually have and their relative orientation.
///
///
class ArduinoClient : public QObject
{
    Q_OBJECT
public:
    explicit ArduinoClient(
        GeneralLEDConfiguration *generalLEDConfig,
        ArduinoMessanger *messanger,
        QObject *parent = nullptr);

    GeneralLEDConfiguration *generalLEDConfig() const;
    ArduinoMessanger *messanger() const;


    /// Functions for treating the entire set of pixels as a single strand
    void contigiousSetPixel(QColor color, int index, bool show = false);
    void contigiousFill(QColor color, int index, int count, bool show = false);
    void contigiousFill(QColor color, int index, qreal percentOfLights, bool show = false);

    /// Sets both strips the same way.
    void mirroredSetPixel(QColor color, int index, bool show = false);
    void mirroredFill(QColor color, int index, int count, bool show = false);
    void mirroredFill(QColor color, int index, qreal percentage, bool show = false);

    /// Functions that can be used by both the global and mirrored
    /// and contiguous.
    void setGlobalColor(QColor color, bool show = false);
    void setAllBrightness(int brightness, bool show = false);

    /// Player 1 specific led comands
    void p1SetBrightness(int brightness, bool show = false);
    void p1Fill(QColor color, int index, int count, bool show = false);
    void p1SetPixel(QColor color, int index, bool show = false);
    void p1SetColor(QColor color, bool show = false);

    /// Player 2 specific led commands.
    void p2SetBrightness(int brightness, bool show = false);
    void p2Fill(QColor color, int index, int count, bool show = false);
    void p2SetPixel(QColor color, int index, bool show = false);
    void p2SetColor(QColor color, bool show = false);

    void setSpotLights(bool p1, bool p2);
    void setP1SpotLight(bool v);
    void setP2SpotLight(bool v);

    void ledShowAll();
private:
    /// Figure out based on the LED light orientation the index inside of the LED
    /// strand that corresponds to a zero relative index.
    int computePlayerOneIndex(int providedIndex);

    /// Figure out based on the LED light orientation the index inside of the LED
    /// strand that corresponds to a zero relative index.
    int computePlayerTwoIndex(int providedIndex);

    struct FillInfo {
        int index;
        int count;
    };
    FillInfo computePlayerOneFill(int providedIndex, int providedCount);
    FillInfo computePlayerTwoFill(int providedIndex, int providedCount);

public slots:
    void onConnected();
signals:
    /// Emitted when the messanger is able to send messages.
    void connected();

    /// Emittted when the arduino becomse disconnected.
    void disconnected();

private:
    GeneralLEDConfiguration *m_config;
    ArduinoMessanger *m_messanger;
};

#endif // ARDUINOCLIENT_H
