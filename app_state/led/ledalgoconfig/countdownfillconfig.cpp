#include "countdownfillconfig.h"

CountDownFillConfig::CountDownFillConfig(QString const& keyPrefix, QObject *parent)
    : QObject{parent}
    , m_settingsPrefix(keyPrefix)
    , m_duration(3000, m_settingsPrefix + "/countdown/duration")
    , m_unificationKind(UnificationKindObject::Style::BothSame, m_settingsPrefix + "/countdown/unificationKind")
    , m_p1Brightness(100, m_settingsPrefix + "/countdown/p1/brightness")
    , m_curve(Interpolation::Curve::Linear, m_settingsPrefix + "/countdown/p1/curve")
    , m_curveAmplitude(1.0, m_settingsPrefix + "/countdown/p1/amplitude")
    , m_p1ConsumedColor(Qt::white, m_settingsPrefix + "/countdown/p1/consumedColor")
    , m_p1CountColor(Qt::yellow, m_settingsPrefix + "/countdown/p1/countDownColor")
    , m_p1FinalColor(Qt::white, m_settingsPrefix + "/countdown/p1/finalColor")
    , m_p1FinalColorBrightness(100, m_settingsPrefix + "/countdown/p1/finalBrightness")
    , m_p2Brightness(100, m_settingsPrefix + "/countdown/p2/brightness")
    , m_p2ConsumedColor(Qt::white, m_settingsPrefix + "/countdown/p2/consumedColor")
    , m_p2CountColor(Qt::yellow, m_settingsPrefix + "/countdown/p2/countDownColor")
    , m_p2FinalColor(Qt::white, m_settingsPrefix + "/countdown/p2/finalColor")
    , m_p2FinalColorBrightness(100, m_settingsPrefix + "/countdown/p2/finalBrightness")
{
    qDebug() << "Constructing CountDownFillConfig";
}

IntegerObject &CountDownFillConfig::duration(){
    return m_duration;
}

UnificationKindObject &CountDownFillConfig::unificationKind() {
    return m_unificationKind;
}

IntegerObject &CountDownFillConfig::p1Brightness() {
    return m_p1Brightness;
}

InterpolationCurveObject &CountDownFillConfig::curve() {
    return m_curve;
}

QRealObject &CountDownFillConfig::curveAmplitude() {
    return m_curveAmplitude;
}

ColorObject &CountDownFillConfig::p1ConsumedColor() {
    return m_p1ConsumedColor;
}

ColorObject &CountDownFillConfig::p1CountColor() {
    return m_p1CountColor;
}

ColorObject &CountDownFillConfig::p1FinalColor() {
    return m_p1FinalColor;
}

IntegerObject &CountDownFillConfig::p1FinalColorBrightness() {
    return m_p1FinalColorBrightness;
}

IntegerObject &CountDownFillConfig::p2Brightness() {
    return m_p2Brightness;
}

ColorObject &CountDownFillConfig::p2ConsumedColor() {
    return m_p2ConsumedColor;
}

ColorObject &CountDownFillConfig::p2CountColor() {
    return m_p2CountColor;
}

ColorObject &CountDownFillConfig::p2FinalColor() {
    return m_p2FinalColor;
}

IntegerObject &CountDownFillConfig::p2FinalColorBrightness() {
    return m_p2FinalColorBrightness;
}


void CountDownFillConfig::init(QSettings *settings) {
    assert(settings);
    qDebug() << "Attaching settings BreathConfig";
    m_duration.attachSettings(settings);
    m_unificationKind.attachSettings(settings);
    m_p1Brightness.attachSettings(settings);
    m_curve.attachSettings(settings);
    m_curveAmplitude.attachSettings(settings);
    m_p1ConsumedColor.attachSettings(settings);
    m_p1CountColor.attachSettings(settings);
    m_p1FinalColor.attachSettings(settings);
    m_p1FinalColorBrightness.attachSettings(settings);
    m_p2Brightness.attachSettings(settings);
    m_p2ConsumedColor.attachSettings(settings);
    m_p2CountColor.attachSettings(settings);
    m_p2FinalColor.attachSettings(settings);
    m_p2FinalColorBrightness.attachSettings(settings);
}

void CountDownFillConfig::setLEDController(LEDController *controller) {
    auto curve = Interpolation(m_curve, m_curveAmplitude);
    controller->countDownFill(
        m_duration,
        m_p1Brightness,
        curve.easingCurve(),
        m_p1ConsumedColor,
        m_p1CountColor,
        m_p1FinalColor,
        m_p1FinalColorBrightness,
        m_p2Brightness,
        m_p2ConsumedColor,
        m_p2CountColor,
        m_p2FinalColor,
        m_p2FinalColorBrightness,
        m_unificationKind);
}
