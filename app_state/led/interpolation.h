#ifndef INTERPOLATION_H
#define INTERPOLATION_H
#include <QObject>
#include <QEasingCurve>
#include <QVector>
#include <QHash>
// Check for the kinds of interpolation here: https://doc.qt.io/qt-6/qeasingcurve.html#Type-enum

class Interpolation : public QObject
{
    Q_OBJECT
    Q_ENUMS(Curve)
public:
    enum class Curve {
        Linear,
        InQuad, OutQuad, InOutQuad, OutInQuad,
        InCubic, OutCubic, InOutCubic, OutInCubic,
        InQuart, OutQuart, InOutQuart, OutInQuart,
        InQuint, OutQuint, InOutQuint, OutInQuint,
        InSine, OutSine, InOutSine, OutInSine,
        InExpo, OutExpo, InOutExpo, OutInExpo,
        InCirc, OutCirc, InOutCirc, OutInCirc,
        InElastic, OutElastic, InOutElastic, OutInElastic,
        InBack, OutBack, InOutBack, OutInBack,
        InBounce, OutBounce, InOutBounce, OutInBounce,
    };
    struct CurveInfo {
        Curve value;
        QString name;
        QString description;
        QString imageLocation;
    };
private:
    static QVector<CurveInfo> buildCurveData();
    static QHash<QString, int> buildIndexMap();
public:
    static QVector<CurveInfo> CurveData;
    static QHash<QString, int> NameToIndex;
public:
    // Static functions that are used in order to get info about different possible
    // easing curves.

    /// Returns the enum given a name, if the name doesn't name a kind of curve
    /// than we return Optional None instead.
    static std::optional<Curve> getByName(QString name);

    /// Returns a text description for a given curve.
    static QString getDescription(Curve curve);

    /// Returns the resource image assocaited with a given curve.
    static QString getResourceImage(Curve curve);

    /// Returns the long name of a curve
    static QString getName(Curve curve);

    static QEasingCurve::Type intoEasingCurveType(Curve curve);

    explicit Interpolation(Curve data = Curve::Linear, qreal ampliatude = 1.0, QObject *parent = nullptr);

    /// Returns the name of the selected value
    Curve curve() const;

    /// The amount to multiply the curvature by cannot be zero.
    qreal apmliatude() const;

    /// Retrurns the long name of a curve.
    QString name() const;

    /// Returns a text description of the current enumeration value.
    QString description() const;

    /// Returns the resource path string for a given kind of interpolation.
    QString imageResourcePath() const;

    /// Build an easing curve for interpolation.
    QEasingCurve easingCurve() const;

public slots:
    /// Set the value of a curve.
    void setCurve(Curve curve);

    /// Set the value of the amplitude of the curve.
    void setAmplitude(qreal amplitude);

signals:
    /// Emitted when the curve changes.
    void curveChanged(Curve curve);
    /// This is invoked when the amplitude of the curve is chagned.
    void setAmplitudeChanged(qreal amplitude);
private:
    Curve m_data;
    qreal m_ampliatude;
};

#endif // INTERPOLATION_H
