#include "interpolation.h"
#include <QDebug>

constexpr const char* CurveLinear = "Linear";
constexpr const char* CurveInQuad = "InQuad";
constexpr const char* CurveOutQuad = "OutQuad";
constexpr const char* CurveInOutQuad = "InOutQuad";
constexpr const char* CurveOutInQuad = "OutInQuad";
constexpr const char* CurveInCubic = "InCubic";
constexpr const char* CurveOutCubic = "OutCubic";
constexpr const char* CurveInOutCubic = "InOutCubic";
constexpr const char* CurveOutInCubic = "OutInCubic";
constexpr const char* CurveInQuart = "InQuart";
constexpr const char* CurveOutQuart = "OutQuart";
constexpr const char* CurveInOutQuart = "InOutQuart";
constexpr const char* CurveOutInQuart = "OutInQuart";
constexpr const char* CurveInQuint = "InQuint";
constexpr const char* CurveOutQuint = "OutQuint";
constexpr const char* CurveInOutQuint = "InOutQuint";
constexpr const char* CurveOutInQuint = "OutInQuint";
constexpr const char* CurveInSine = "InSine";
constexpr const char* CurveOutSine = "OutSine";
constexpr const char* CurveInOutSine = "InOutSine";
constexpr const char* CurveOutInSine = "OutInSine";
constexpr const char* CurveInExpo = "InExpo";
constexpr const char* CurveOutExpo = "OutExpo";
constexpr const char* CurveInOutExpo = "InOutExpo";
constexpr const char* CurveOutInExpo = "OutInExpo";
constexpr const char* CurveInCirc = "InCirc";
constexpr const char* CurveOutCirc = "OutCirc";
constexpr const char* CurveInOutCirc = "InOutCirc";
constexpr const char* CurveOutInCirc = "OutInCirc";
constexpr const char* CurveInElastic = "InElastic";
constexpr const char* CurveOutElastic = "OutElastic";
constexpr const char* CurveInOutElastic = "InOutElastic";
constexpr const char* CurveOutInElastic = "OutInElastic";
constexpr const char* CurveInBack = "InBack";
constexpr const char* CurveOutBack = "OutBack";
constexpr const char* CurveInOutBack = "InOutBack";
constexpr const char* CurveOutInBack = "OutInBack";
constexpr const char* CurveInBounce = "InBounce";
constexpr const char* CurveOutBounce = "OutBounce";
constexpr const char* CurveInOutBounce = "InOutBounce";
constexpr const char* CurveOutInBounce = "OutInBounce";

constexpr const char* DescriptionLinear = "Easing curve for a linear (t) function: velocity is constant.";
constexpr const char* DescriptionInQuad = "Easing curve for a quadratic (t^2) function: accelerating from zero velocity.";
constexpr const char* DescriptionOutQuad = "Easing curve for a quadratic (t^2) function: decelerating to zero velocity.";
constexpr const char* DescriptionInOutQuad = "Easing curve for a quadratic (t^2) function: acceleration until halfway, then deceleration.";
constexpr const char* DescriptionOutInQuad = "Easing curve for a quadratic (t^2) function: deceleration until halfway, then acceleration.";
constexpr const char* DescriptionInCubic = "Easing curve for a cubic (t^3) function: accelerating from zero velocity.";
constexpr const char* DescriptionOutCubic = "Easing curve for a cubic (t^3) function: decelerating to zero velocity.";
constexpr const char* DescriptionInOutCubic = "Easing curve for a cubic (t^3) function: acceleration until halfway, then deceleration.";
constexpr const char* DescriptionOutInCubic = "Easing curve for a cubic (t^3) function: deceleration until halfway, then acceleration.";
constexpr const char* DescriptionInQuart = "Easing curve for a quartic (t^4) function: accelerating from zero velocity.";
constexpr const char* DescriptionOutQuart = "Easing curve for a quartic (t^4) function: decelerating to zero velocity.";
constexpr const char* DescriptionInOutQuart = "Easing curve for a quartic (t^4) function: acceleration until halfway, then deceleration.";
constexpr const char* DescriptionOutInQuart = "Easing curve for a quartic (t^4) function: deceleration until halfway, then acceleration.";
constexpr const char* DescriptionInQuint = "Easing curve for a quintic (t^5) easing in: accelerating from zero velocity.";
constexpr const char* DescriptionOutQuint = "Easing curve for a quintic (t^5) function: decelerating to zero velocity.";
constexpr const char* DescriptionInOutQuint = "Easing curve for a quintic (t^5) function: acceleration until halfway, then deceleration.";
constexpr const char* DescriptionOutInQuint = "Easing curve for a quintic (t^5) function: deceleration until halfway, then acceleration.";
constexpr const char* DescriptionInSine = "Easing curve for a sinusoidal (sin(t)) function: accelerating from zero velocity.";
constexpr const char* DescriptionOutSine = "Easing curve for a sinusoidal (sin(t)) function: decelerating to zero velocity.";
constexpr const char* DescriptionInOutSine = "Easing curve for a sinusoidal (sin(t)) function: acceleration until halfway, then deceleration.";
constexpr const char* DescriptionOutInSine = "Easing curve for a sinusoidal (sin(t)) function: deceleration until halfway, then acceleration.";
constexpr const char* DescriptionInExpo = "Easing curve for an exponential (2^t) function: accelerating from zero velocity.";
constexpr const char* DescriptionOutExpo = "Easing curve for an exponential (2^t) function: decelerating to zero velocity.";
constexpr const char* DescriptionInOutExpo = "Easing curve for an exponential (2^t) function: acceleration until halfway, then deceleration.";
constexpr const char* DescriptionOutInExpo = "Easing curve for an exponential (2^t) function: deceleration until halfway, then acceleration.";
constexpr const char* DescriptionInCirc = "Easing curve for a circular (sqrt(1-t^2)) function: accelerating from zero velocity.";
constexpr const char* DescriptionOutCirc = "Easing curve for a circular (sqrt(1-t^2)) function: decelerating to zero velocity.";
constexpr const char* DescriptionInOutCirc = "Easing curve for a circular (sqrt(1-t^2)) function: acceleration until halfway, then deceleration.";
constexpr const char* DescriptionOutInCirc = "Easing curve for a circular (sqrt(1-t^2)) function: deceleration until halfway, then acceleration.";
constexpr const char* DescriptionInElastic = "Easing curve for an elastic (exponentially decaying sine wave) function: accelerating from zero velocity. The peak amplitude can be set with the amplitude parameter, and the period of decay by the period parameter.";
constexpr const char* DescriptionOutElastic = "Easing curve for an elastic (exponentially decaying sine wave) function: decelerating to zero velocity. The peak amplitude can be set with the amplitude parameter, and the period of decay by the period parameter.";
constexpr const char* DescriptionInOutElastic = "Easing curve for an elastic (exponentially decaying sine wave) function: acceleration until halfway, then deceleration.";
constexpr const char* DescriptionOutInElastic = "Easing curve for an elastic (exponentially decaying sine wave) function: deceleration until halfway, then acceleration.";
constexpr const char* DescriptionInBack = "Easing curve for a back (overshooting cubic function: (s+1)*t^3 - s*t^2) easing in: accelerating from zero velocity.";
constexpr const char* DescriptionOutBack = "Easing curve for a back (overshooting cubic function: (s+1)*t^3 - s*t^2) easing out: decelerating to zero velocity.";
constexpr const char* DescriptionInOutBack = "Easing curve for a back (overshooting cubic function: (s+1)*t^3 - s*t^2) easing in/out: acceleration until halfway, then deceleration.";
constexpr const char* DescriptionOutInBack = "Easing curve for a back (overshooting cubic easing: (s+1)*t^3 - s*t^2) easing out/in: deceleration until halfway, then acceleration.";
constexpr const char* DescriptionInBounce = "Easing curve for a bounce (exponentially decaying parabolic bounce) function: accelerating from zero velocity.";
constexpr const char* DescriptionOutBounce = "Easing curve for a bounce (exponentially decaying parabolic bounce) function: decelerating from zero velocity.";
constexpr const char* DescriptionInOutBounce = "Easing curve for a bounce (exponentially decaying parabolic bounce) function easing in/out: acceleration until halfway, then deceleration.";
constexpr const char* DescriptionOutInBounce = "Easing curve for a bounce (exponentially decaying parabolic bounce) function easing out/in: deceleration until halfway, then acceleration.";

constexpr const char* ImageUriLinear = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-linear.png";
constexpr const char* ImageUriInQuad = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inquad.png";
constexpr const char* ImageUriOutQuad = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outquad.png";
constexpr const char* ImageUriInOutQuad = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inoutquad.png";
constexpr const char* ImageUriOutInQuad = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outinquad.png";
constexpr const char* ImageUriInCubic = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-incubic.png";
constexpr const char* ImageUriOutCubic = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outcubic.png";
constexpr const char* ImageUriInOutCubic = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inoutcubic.png";
constexpr const char* ImageUriOutInCubic = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outincubic.png";
constexpr const char* ImageUriInQuart = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inquart.png";
constexpr const char* ImageUriOutQuart = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outquart.png";
constexpr const char* ImageUriInOutQuart = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inoutquart.png";
constexpr const char* ImageUriOutInQuart = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outinquart.png";
constexpr const char* ImageUriInQuint = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inquint.png";
constexpr const char* ImageUriOutQuint = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outquint.png";
constexpr const char* ImageUriInOutQuint = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inoutquint.png";
constexpr const char* ImageUriOutInQuint = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outinquint.png";
constexpr const char* ImageUriInSine = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-insine.png";
constexpr const char* ImageUriOutSine = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outsine.png";
constexpr const char* ImageUriInOutSine = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inoutsine.png";
constexpr const char* ImageUriOutInSine = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outinsine.png";
constexpr const char* ImageUriInExpo = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inexpo.png";
constexpr const char* ImageUriOutExpo = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outexpo.png";
constexpr const char* ImageUriInOutExpo = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inoutexpo.png";
constexpr const char* ImageUriOutInExpo = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outinexpo.png";
constexpr const char* ImageUriInCirc = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-incirc.png";
constexpr const char* ImageUriOutCirc = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outcirc.png";
constexpr const char* ImageUriInOutCirc = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inoutcirc.png";
constexpr const char* ImageUriOutInCirc = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outincirc.png";
constexpr const char* ImageUriInElastic = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inelastic.png";
constexpr const char* ImageUriOutElastic = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outelastic.png";
constexpr const char* ImageUriInOutElastic = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inoutelastic.png";
constexpr const char* ImageUriOutInElastic = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outinelastic.png";
constexpr const char* ImageUriInBack = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inback.png";
constexpr const char* ImageUriOutBack = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outback.png";
constexpr const char* ImageUriInOutBack = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inoutback.png";
constexpr const char* ImageUriOutInBack = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outinback.png";
constexpr const char* ImageUriInBounce = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inbounce.png";
constexpr const char* ImageUriOutBounce = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outbounce.png";
constexpr const char* ImageUriInOutBounce = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-inoutbounce.png";
constexpr const char* ImageUriOutInBounce = ":/battlebox/LEDInterpolation/resources/LEDInterpolation/qeasingcurve-outinbounce.png";


Interpolation::Interpolation(Curve data, qreal ampliatude,QObject *parent)
    :QObject(parent)
    , m_data(data)
    , m_ampliatude(ampliatude)
{ }

QVector<Interpolation::CurveInfo> Interpolation::buildCurveData() {
    return {
        { Curve::Linear, getName(Curve::Linear), getDescription(Curve::Linear), getResourceImage(Curve::Linear)},
        { Curve::InQuad, getName(Curve::InQuad), getDescription(Curve::InQuad), getResourceImage(Curve::InQuad)},
        { Curve::OutQuad, getName(Curve::OutQuad), getDescription(Curve::OutQuad), getResourceImage(Curve::OutQuad)},
        { Curve::InOutQuad, getName(Curve::InOutQuad), getDescription(Curve::InOutQuad), getResourceImage(Curve::InOutQuad)},
        { Curve::OutInQuad, getName(Curve::OutInQuad), getDescription(Curve::OutInQuad), getResourceImage(Curve::OutInQuad)},
        { Curve::InCubic, getName(Curve::InCubic), getDescription(Curve::InCubic), getResourceImage(Curve::InCubic)},
        { Curve::OutCubic, getName(Curve::OutCubic), getDescription(Curve::OutCubic), getResourceImage(Curve::OutCubic)},
        { Curve::InOutCubic, getName(Curve::InOutCubic), getDescription(Curve::InOutCubic), getResourceImage(Curve::InOutCubic)},
        { Curve::OutInCubic, getName(Curve::OutInCubic), getDescription(Curve::OutInCubic), getResourceImage(Curve::OutInCubic)},
        { Curve::InQuart, getName(Curve::InQuart), getDescription(Curve::InQuart), getResourceImage(Curve::InQuart)},
        { Curve::OutQuart, getName(Curve::OutQuart), getDescription(Curve::OutQuart), getResourceImage(Curve::OutQuart)},
        { Curve::InOutQuart, getName(Curve::InOutQuart), getDescription(Curve::InOutQuart), getResourceImage(Curve::InOutQuart)},
        { Curve::OutInQuart, getName(Curve::OutInQuart), getDescription(Curve::OutInQuart), getResourceImage(Curve::OutInQuart)},
        { Curve::InQuint, getName(Curve::InQuint), getDescription(Curve::InQuint), getResourceImage(Curve::InQuint)},
        { Curve::OutQuint, getName(Curve::OutQuint), getDescription(Curve::OutQuint), getResourceImage(Curve::OutQuint)},
        { Curve::InOutQuint, getName(Curve::InOutQuint), getDescription(Curve::InOutQuint), getResourceImage(Curve::InOutQuint)},
        { Curve::OutInQuint, getName(Curve::OutInQuint), getDescription(Curve::OutInQuint), getResourceImage(Curve::OutInQuint)},
        { Curve::InSine, getName(Curve::InSine), getDescription(Curve::InSine), getResourceImage(Curve::InSine)},
        { Curve::OutSine, getName(Curve::OutSine), getDescription(Curve::OutSine), getResourceImage(Curve::OutSine)},
        { Curve::InOutSine, getName(Curve::InOutSine), getDescription(Curve::InOutSine), getResourceImage(Curve::InOutSine)},
        { Curve::OutInSine, getName(Curve::OutInSine), getDescription(Curve::OutInSine), getResourceImage(Curve::OutInSine)},
        { Curve::InExpo, getName(Curve::InExpo), getDescription(Curve::InExpo), getResourceImage(Curve::InExpo)},
        { Curve::OutExpo, getName(Curve::OutExpo), getDescription(Curve::OutExpo), getResourceImage(Curve::OutExpo)},
        { Curve::InOutExpo, getName(Curve::InOutExpo), getDescription(Curve::InOutExpo), getResourceImage(Curve::InOutExpo)},
        { Curve::OutInExpo, getName(Curve::OutInExpo), getDescription(Curve::OutInExpo), getResourceImage(Curve::OutInExpo)},
        { Curve::InCirc, getName(Curve::InCirc), getDescription(Curve::InCirc), getResourceImage(Curve::InCirc)},
        { Curve::OutCirc, getName(Curve::OutCirc), getDescription(Curve::OutCirc), getResourceImage(Curve::OutCirc)},
        { Curve::InOutCirc, getName(Curve::InOutCirc), getDescription(Curve::InOutCirc), getResourceImage(Curve::InOutCirc)},
        { Curve::OutInCirc, getName(Curve::OutInCirc), getDescription(Curve::OutInCirc), getResourceImage(Curve::OutInCirc)},
        { Curve::InElastic, getName(Curve::InElastic), getDescription(Curve::InElastic), getResourceImage(Curve::InElastic)},
        { Curve::OutElastic, getName(Curve::OutElastic), getDescription(Curve::OutElastic), getResourceImage(Curve::OutElastic)},
        { Curve::InOutElastic, getName(Curve::InOutElastic), getDescription(Curve::InOutElastic), getResourceImage(Curve::InOutElastic)},
        { Curve::OutInElastic, getName(Curve::OutInElastic), getDescription(Curve::OutInElastic), getResourceImage(Curve::OutInElastic)},
        { Curve::InBack, getName(Curve::InBack), getDescription(Curve::InBack), getResourceImage(Curve::InBack)},
        { Curve::OutBack, getName(Curve::OutBack), getDescription(Curve::OutBack), getResourceImage(Curve::OutBack)},
        { Curve::InOutBack, getName(Curve::InOutBack), getDescription(Curve::InOutBack), getResourceImage(Curve::InOutBack)},
        { Curve::OutInBack, getName(Curve::OutInBack), getDescription(Curve::OutInBack), getResourceImage(Curve::OutInBack)},
        { Curve::InBounce, getName(Curve::InBounce), getDescription(Curve::InBounce), getResourceImage(Curve::InBounce)},
        { Curve::OutBounce, getName(Curve::OutBounce), getDescription(Curve::OutBounce), getResourceImage(Curve::OutBounce)},
        { Curve::InOutBounce, getName(Curve::InOutBounce), getDescription(Curve::InOutBounce), getResourceImage(Curve::InOutBounce)},
        { Curve::OutInBounce, getName(Curve::OutInBounce), getDescription(Curve::OutInBounce), getResourceImage(Curve::OutInBounce)},
    };
}

QVector<Interpolation::CurveInfo> Interpolation::CurveData = Interpolation::buildCurveData();

QHash<QString, int> Interpolation::buildIndexMap() {
    QHash<QString, int> ret;
    for(auto info : CurveData) {
        ret.insert(info.name, (int)info.value);
    }
    return ret;
}
QHash<QString, int> Interpolation::NameToIndex = Interpolation::buildIndexMap();


std::optional<Interpolation::Curve> Interpolation::getByName(QString name) {
    auto iter = NameToIndex.find(name);
    if (iter == NameToIndex.end()) {
        return std::optional<Interpolation::Curve>();
    }
    // Getting the info out of the CurveData and returing the correct Curve value.
    return std::optional<Interpolation::Curve>(CurveData[*iter].value);
}

Interpolation::CurveInfo *Interpolation::getCurveInfoByCurve(Curve c) {
    auto name = getName(c);
    qDebug() << "What's my name?" << name;
    qDebug() << "Number of thing: " << NameToIndex.size();
    auto iter = NameToIndex.find(name);
    if (iter == NameToIndex.end()) {
        // This is logically unreachable.
        return nullptr;
    }
    // Returning a pointer to the curve info.
    return &CurveData[*iter];
}

QString Interpolation::getDescription(Interpolation::Curve curve) {
    switch(curve) {
    case Interpolation::Curve::Linear:
        return DescriptionLinear;
    case Interpolation::Curve::InQuad:
        return DescriptionInQuad;
    case Interpolation::Curve::OutQuad:
        return DescriptionOutQuad;
    case Interpolation::Curve::InOutQuad:
        return DescriptionInOutQuad;
    case Interpolation::Curve::OutInQuad:
        return DescriptionOutInQuad;
    case Interpolation::Curve::InCubic:
        return DescriptionInCubic;
    case Interpolation::Curve::OutCubic:
        return DescriptionOutCubic;
    case Interpolation::Curve::InOutCubic:
        return DescriptionInOutCubic;
    case Interpolation::Curve::OutInCubic:
        return DescriptionOutInCubic;
    case Interpolation::Curve::InQuart:
        return DescriptionInQuart;
    case Interpolation::Curve::OutQuart:
        return DescriptionOutQuart;
    case Interpolation::Curve::InOutQuart:
        return DescriptionInOutQuart;
    case Interpolation::Curve::OutInQuart:
        return DescriptionOutInQuart;
    case Interpolation::Curve::InQuint:
        return DescriptionInQuint;
    case Interpolation::Curve::OutQuint:
        return DescriptionOutQuint;
    case Interpolation::Curve::InOutQuint:
        return DescriptionInOutQuint;
    case Interpolation::Curve::OutInQuint:
        return DescriptionOutInQuint;
    case Interpolation::Curve::InSine:
        return DescriptionInSine;
    case Interpolation::Curve::OutSine:
        return DescriptionOutSine;
    case Interpolation::Curve::InOutSine:
        return DescriptionInOutSine;
    case Interpolation::Curve::OutInSine:
        return DescriptionOutInSine;
    case Interpolation::Curve::InExpo:
        return DescriptionInExpo;
    case Interpolation::Curve::OutExpo:
        return DescriptionOutExpo;
    case Interpolation::Curve::InOutExpo:
        return DescriptionInOutExpo;
    case Interpolation::Curve::OutInExpo:
        return DescriptionOutInExpo;
    case Interpolation::Curve::InCirc:
        return DescriptionInCirc;
    case Interpolation::Curve::OutCirc:
        return DescriptionOutCirc;
    case Interpolation::Curve::InOutCirc:
        return DescriptionInOutCirc;
    case Interpolation::Curve::OutInCirc:
        return DescriptionOutInCirc;
    case Interpolation::Curve::InElastic:
        return DescriptionInElastic;
    case Interpolation::Curve::OutElastic:
        return DescriptionOutElastic;
    case Interpolation::Curve::InOutElastic:
        return DescriptionInOutElastic;
    case Interpolation::Curve::OutInElastic:
        return DescriptionOutInElastic;
    case Interpolation::Curve::InBack:
        return DescriptionInBack;
    case Interpolation::Curve::OutBack:
        return DescriptionOutBack;
    case Interpolation::Curve::InOutBack:
        return DescriptionInOutBack;
    case Interpolation::Curve::OutInBack:
        return DescriptionOutInBack;
    case Interpolation::Curve::InBounce:
        return DescriptionInBounce;
    case Interpolation::Curve::OutBounce:
        return DescriptionOutBounce;
    case Interpolation::Curve::InOutBounce:
        return DescriptionInOutBounce;
    case Interpolation::Curve::OutInBounce:
        return DescriptionOutInBounce;
    default:
        assert(!"Invalid curve value!");
        return "";
    }
}

QString Interpolation::getResourceImage(Interpolation::Curve curve) {
    switch(curve) {
        case Interpolation::Curve::Linear:
        return ImageUriLinear;
        case Interpolation::Curve::InQuad:
        return ImageUriInQuad;
        case Interpolation::Curve::OutQuad:
        return ImageUriOutQuad;
        case Interpolation::Curve::InOutQuad:
        return ImageUriInOutQuad;
        case Interpolation::Curve::OutInQuad:
        return ImageUriOutInQuad;
        case Interpolation::Curve::InCubic:
        return ImageUriInCubic;
        case Interpolation::Curve::OutCubic:
        return ImageUriOutCubic;
        case Interpolation::Curve::InOutCubic:
        return ImageUriInOutCubic;
        case Interpolation::Curve::OutInCubic:
        return ImageUriOutInCubic;
        case Interpolation::Curve::InQuart:
        return ImageUriInQuart;
        case Interpolation::Curve::OutQuart:
        return ImageUriOutQuart;
        case Interpolation::Curve::InOutQuart:
        return ImageUriInOutQuart;
        case Interpolation::Curve::OutInQuart:
        return ImageUriOutInQuart;
        case Interpolation::Curve::InQuint:
        return ImageUriInQuint;
        case Interpolation::Curve::OutQuint:
        return ImageUriOutQuint;
        case Interpolation::Curve::InOutQuint:
        return ImageUriInOutQuint;
        case Interpolation::Curve::OutInQuint:
        return ImageUriOutInQuint;
        case Interpolation::Curve::InSine:
        return ImageUriInSine;
        case Interpolation::Curve::OutSine:
        return ImageUriOutSine;
        case Interpolation::Curve::InOutSine:
        return ImageUriInOutSine;
        case Interpolation::Curve::OutInSine:
        return ImageUriOutInSine;
        case Interpolation::Curve::InExpo:
        return ImageUriInExpo;
        case Interpolation::Curve::OutExpo:
        return ImageUriOutExpo;
        case Interpolation::Curve::InOutExpo:
        return ImageUriInOutExpo;
        case Interpolation::Curve::OutInExpo:
        return ImageUriOutInExpo;
        case Interpolation::Curve::InCirc:
        return ImageUriInCirc;
        case Interpolation::Curve::OutCirc:
        return ImageUriOutCirc;
        case Interpolation::Curve::InOutCirc:
        return ImageUriInOutCirc;
        case Interpolation::Curve::OutInCirc:
        return ImageUriOutInCirc;
        case Interpolation::Curve::InElastic:
        return ImageUriInElastic;
        case Interpolation::Curve::OutElastic:
        return ImageUriOutElastic;
        case Interpolation::Curve::InOutElastic:
        return ImageUriInOutElastic;
        case Interpolation::Curve::OutInElastic:
        return ImageUriOutInElastic;
        case Interpolation::Curve::InBack:
        return ImageUriInBack;
        case Interpolation::Curve::OutBack:
        return ImageUriOutBack;
        case Interpolation::Curve::InOutBack:
        return ImageUriInOutBack;
        case Interpolation::Curve::OutInBack:
        return ImageUriOutInBack;
        case Interpolation::Curve::InBounce:
        return ImageUriInBounce;
        case Interpolation::Curve::OutBounce:
        return ImageUriOutBounce;
        case Interpolation::Curve::InOutBounce:
        return ImageUriInOutBounce;
        case Interpolation::Curve::OutInBounce:
        return ImageUriOutInBounce;
        default:
        return "";
    }
}

QString Interpolation::getName(Interpolation::Curve curve) {
    switch(curve) {
    case Interpolation::Curve::Linear:
        return CurveLinear;
    case Interpolation::Curve::InQuad:
        return CurveInQuad;
    case Interpolation::Curve::OutQuad:
        return CurveOutQuad;
    case Interpolation::Curve::InOutQuad:
        return CurveInOutQuad;
    case Interpolation::Curve::OutInQuad:
        return CurveOutInQuad;
    case Interpolation::Curve::InCubic:
        return CurveInCubic;
    case Interpolation::Curve::OutCubic:
        return CurveOutCubic;
    case Interpolation::Curve::InOutCubic:
        return CurveInOutCubic;
    case Interpolation::Curve::OutInCubic:
        return CurveOutInCubic;
    case Interpolation::Curve::InQuart:
        return CurveInQuart;
    case Interpolation::Curve::OutQuart:
        return CurveOutQuart;
    case Interpolation::Curve::InOutQuart:
        return CurveInOutQuart;
    case Interpolation::Curve::OutInQuart:
        return CurveOutInQuart;
    case Interpolation::Curve::InQuint:
        return CurveInQuint;
    case Interpolation::Curve::OutQuint:
        return CurveOutQuint;
    case Interpolation::Curve::InOutQuint:
        return CurveInOutQuint;
    case Interpolation::Curve::OutInQuint:
        return CurveOutInQuint;
    case Interpolation::Curve::InSine:
        return CurveInSine;
    case Interpolation::Curve::OutSine:
        return CurveOutSine;
    case Interpolation::Curve::InOutSine:
        return CurveInOutSine;
    case Interpolation::Curve::OutInSine:
        return CurveOutInSine;
    case Interpolation::Curve::InExpo:
        return CurveInExpo;
    case Interpolation::Curve::OutExpo:
        return CurveOutExpo;
    case Interpolation::Curve::InOutExpo:
        return CurveInOutExpo;
    case Interpolation::Curve::OutInExpo:
        return CurveOutInExpo;
    case Interpolation::Curve::InCirc:
        return CurveInCirc;
    case Interpolation::Curve::OutCirc:
        return CurveOutCirc;
    case Interpolation::Curve::InOutCirc:
        return CurveInOutCirc;
    case Interpolation::Curve::OutInCirc:
        return CurveOutInCirc;
    case Interpolation::Curve::InElastic:
        return CurveInElastic;
    case Interpolation::Curve::OutElastic:
        return CurveOutElastic;
    case Interpolation::Curve::InOutElastic:
        return CurveInOutElastic;
    case Interpolation::Curve::OutInElastic:
        return CurveOutInElastic;
    case Interpolation::Curve::InBack:
        return CurveInBack;
    case Interpolation::Curve::OutBack:
        return CurveOutBack;
    case Interpolation::Curve::InOutBack:
        return CurveInOutBack;
    case Interpolation::Curve::OutInBack:
        return CurveOutInBack;
    case Interpolation::Curve::InBounce:
        return CurveInBounce;
    case Interpolation::Curve::OutBounce:
        return CurveOutBounce;
    case Interpolation::Curve::InOutBounce:
        return CurveInOutBounce;
    case Interpolation::Curve::OutInBounce:
        return CurveOutInBounce;
    default:
        return CurveLinear;
    }
}


QEasingCurve::Type Interpolation::intoEasingCurveType(Curve curve) {
    switch(curve) {
    case Curve::Linear:
        return QEasingCurve::Type::Linear;
    case Curve::InQuad:
        return QEasingCurve::Type::InQuad;
    case Curve::OutQuad:
        return QEasingCurve::Type::OutQuad;
    case Curve::InOutQuad:
        return QEasingCurve::Type::InOutQuad;
    case Curve::OutInQuad:
        return QEasingCurve::Type::OutInQuad;
    case Curve::InCubic:
        return QEasingCurve::Type::InCubic;
    case Curve::OutCubic:
        return QEasingCurve::Type::OutCubic;
    case Curve::InOutCubic:
        return QEasingCurve::Type::InOutCubic;
    case Curve::OutInCubic:
        return QEasingCurve::Type::OutInCubic;
    case Curve::InQuart:
        return QEasingCurve::Type::InQuart;
    case Curve::OutQuart:
        return QEasingCurve::Type::OutQuart;
    case Curve::InOutQuart:
        return QEasingCurve::Type::InOutQuart;
    case Curve::OutInQuart:
        return QEasingCurve::Type::OutInQuart;
    case Curve::InQuint:
        return QEasingCurve::Type::InQuint;
    case Curve::OutQuint:
        return QEasingCurve::Type::OutQuint;
    case Curve::InOutQuint:
        return QEasingCurve::Type::InOutQuint;
    case Curve::OutInQuint:
        return QEasingCurve::Type::OutInQuint;
    case Curve::InSine:
        return QEasingCurve::Type::InSine;
    case Curve::OutSine:
        return QEasingCurve::Type::OutSine;
    case Curve::InOutSine:
        return QEasingCurve::Type::InOutSine;
    case Curve::OutInSine:
        return QEasingCurve::Type::OutInSine;
    case Curve::InExpo:
        return QEasingCurve::Type::InExpo;
    case Curve::OutExpo:
        return QEasingCurve::Type::OutExpo;
    case Curve::InOutExpo:
        return QEasingCurve::Type::InOutExpo;
    case Curve::OutInExpo:
        return QEasingCurve::Type::OutInExpo;
    case Curve::InCirc:
        return QEasingCurve::Type::InCirc;
    case Curve::OutCirc:
        return QEasingCurve::Type::OutCirc;
    case Curve::InOutCirc:
        return QEasingCurve::Type::InOutCirc;
    case Curve::OutInCirc:
        return QEasingCurve::Type::OutInCirc;
    case Curve::InElastic:
        return QEasingCurve::Type::InElastic;
    case Curve::OutElastic:
        return QEasingCurve::Type::OutElastic;
    case Curve::InOutElastic:
        return QEasingCurve::Type::InOutElastic;
    case Curve::OutInElastic:
        return QEasingCurve::Type::OutInElastic;
    case Curve::InBack:
        return QEasingCurve::Type::InBack;
    case Curve::OutBack:
        return QEasingCurve::Type::OutBack;
    case Curve::InOutBack:
        return QEasingCurve::Type::InOutBack;
    case Curve::OutInBack:
        return QEasingCurve::Type::OutInBack;
    case Curve::InBounce:
        return QEasingCurve::Type::InBounce;
    case Curve::OutBounce:
        return QEasingCurve::Type::OutBounce;
    case Curve::InOutBounce:
        return QEasingCurve::Type::InOutBounce;
    case Curve::OutInBounce:
        return QEasingCurve::Type::OutInBounce;
    default:
        return QEasingCurve::Type::Linear;
    }
}

Interpolation::Curve Interpolation::curve() const {
    return m_data;
}

qreal Interpolation::apmliatude() const {
    return m_ampliatude;
}

QString Interpolation::name() const {
    return getName(m_data);
}

QString Interpolation::description() const {
    return getDescription(m_data);
}

QString Interpolation::imageResourcePath() const {
    return getResourceImage(m_data);
}

QEasingCurve Interpolation::easingCurve() const {
    QEasingCurve curve(intoEasingCurveType(m_data) );
    curve.setAmplitude(m_ampliatude);
    return curve;
}

void Interpolation::setCurve(Curve curve) {
    if (m_data != curve) {
        m_data = curve;
        emit curveChanged(m_data);
    }
}

void Interpolation::setAmplitude(qreal amplitude) {
    if (amplitude == 0.0)
        return;
    if (m_ampliatude != amplitude) {
        m_ampliatude = amplitude;
        emit setAmplitudeChanged(m_ampliatude);
    }
}
