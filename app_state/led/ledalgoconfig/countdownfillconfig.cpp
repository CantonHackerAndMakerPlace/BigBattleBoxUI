#include "countdownfillconfig.h"

CountDownFillConfig::CountDownFillConfig(QString const& keyPrefix, QObject *parent)
    : QObject{parent}
    , m_settingsPrefix(keyPrefix)
    , m_duration(3000, m_settingsPrefix + "/countdown/duration")
    , m_unificationKind(UnificationKindObject::Kind::BothSame, m_settingsPrefix + "/countdown/unificationKind")
    , m_loop(true, m_settingsPrefix + "/countdown/loop" )
    , m_timeBetweenCycles(1000, m_settingsPrefix + "/countdown/timeBetweenCycles")
    , m_p1Brightness(100, m_settingsPrefix + "/countdown/p1/brightness")
    , m_p1Curve(Interpolation::Curve::Linear, m_settingsPrefix + "/countdown/p1/curve")
    , m_p1CurveAmplitude(1.0, m_settingsPrefix + "/countdown/p1/amplitude")
    , m_p1ConsumedColor(Qt::white, m_settingsPrefix + "/countdown/p1/consumedColor")
    , m_p1CountColor(Qt::yellow, m_settingsPrefix + "/countdown/p1/initialColor")
    , m_p1FinalColor(Qt::white, m_settingsPrefix + "/countdown/p1/finalColor")
    , m_p1FinalColorBrightness(100, m_settingsPrefix + "/countdown/p1/finalBrightness")
    , m_p2Curve(Interpolation::Curve::Linear, m_settingsPrefix + "/countdown/p2/curve")
    , m_p2CurveAmplitude(1.0, m_settingsPrefix + "/countdown/p2/amplitude")
    , m_p2Brightness(100, m_settingsPrefix + "/countdown/p2/brightness")
    , m_p2ConsumedColor(Qt::white, m_settingsPrefix + "/countdown/p2/consumedColor")
    , m_p2CountColor(Qt::yellow, m_settingsPrefix + "/countdown/p2/initialColor")
    , m_p2FinalColor(Qt::white, m_settingsPrefix + "/countdown/p2/finalColor")
    , m_p2FinalColorBrightness(100, m_settingsPrefix + "/countdown/p2/finalBrightness")
{ }

IntegerObject &CountDownFillConfig::duration(){
    return m_duration;
}

UnificationKindObject &CountDownFillConfig::unificationKind() {
    return m_unificationKind;
}

BooleanObject &CountDownFillConfig::loop() {
    return m_loop;
}

IntegerObject &CountDownFillConfig::timeBetweenCycles() {
    return m_timeBetweenCycles;
}

IntegerObject &CountDownFillConfig::p1Brightness() {
    return m_p1Brightness;
}

InterpolationCurveObject &CountDownFillConfig::p1Curve() {
    return m_p1Curve;
}

QRealObject &CountDownFillConfig::p1CurveAmplitude() {
    return m_p1CurveAmplitude;
}

ColorObject &CountDownFillConfig::p1ConsumingColor() {
    return m_p1ConsumedColor;
}

ColorObject &CountDownFillConfig::p1InitialColor() {
    return m_p1CountColor;
}

ColorObject &CountDownFillConfig::p1FinalColor() {
    return m_p1FinalColor;
}

IntegerObject &CountDownFillConfig::p1FinalColorBrightness() {
    return m_p1FinalColorBrightness;
}

InterpolationCurveObject &CountDownFillConfig::p2Curve() {
    return m_p2Curve;
}

QRealObject &CountDownFillConfig::p2CurveAmplitude() {
    return m_p2CurveAmplitude;
}

IntegerObject &CountDownFillConfig::p2Brightness() {
    return m_p2Brightness;
}

ColorObject &CountDownFillConfig::p2ConsumingColor() {
    return m_p2ConsumedColor;
}

ColorObject &CountDownFillConfig::p2InitialColor() {
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
    m_duration.attachSettings(settings);
    m_unificationKind.attachSettings(settings);
    m_p1Brightness.attachSettings(settings);
    m_p1Curve.attachSettings(settings);
    m_p1CurveAmplitude.attachSettings(settings);
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
    auto p1Curve = Interpolation(m_p1Curve, m_p1CurveAmplitude);
    auto p2Curve = Interpolation(m_p2Curve, m_p2CurveAmplitude);
    controller->countDownFill(
        m_duration,
        m_loop,
        m_timeBetweenCycles,
        p1Curve.easingCurve(),
        m_p1Brightness,
        m_p1ConsumedColor,
        m_p1CountColor,
        m_p1FinalColor,
        m_p1FinalColorBrightness,
        p2Curve.easingCurve(),
        m_p2Brightness,
        m_p2ConsumedColor,
        m_p2CountColor,
        m_p2FinalColor,
        m_p2FinalColorBrightness,
        m_unificationKind);
}
