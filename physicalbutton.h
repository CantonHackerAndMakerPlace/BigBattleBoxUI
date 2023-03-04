#ifndef PHYSICALBUTTON_H
#define PHYSICALBUTTON_H

#include <QObject>

/// PhysicalButton records the kind of switch,
/// and from that determines changes to state.
///
/// State returned from `state()` function is always
/// correct in that it will indicate if the button is
/// pressed or not. True always equals pressed and false
/// is always not pressed.
///
/// The input to the `setState` function is direct from
/// the external source and it determines based on the
/// current kind of switch if the value should be open
/// or closed and records the internal state accordingly.
class PhysicalButton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool state READ state WRITE setState NOTIFY stateChanged)
public:
    explicit PhysicalButton(QObject *parent = nullptr);

    enum class SwitchConfig {
        NormallyOpen,
        NormallyClosed,
    };
    Q_ENUM(SwitchConfig);

    bool state() const;
    PhysicalButton::SwitchConfig switchKind() const;
public slots:
    void setState(bool arg);
    void setSwitchKind(PhysicalButton::SwitchConfig cfg);
signals:
    void stateChanged(bool arg);
    void switchKindChanged(PhysicalButton::SwitchConfig cfg);
private:
    bool m_state = true;
    SwitchConfig m_switchKind = SwitchConfig::NormallyClosed;
};

inline std::optional<PhysicalButton::SwitchConfig> intToSwitchConfig(int i) {
    switch(i) {
    case 0:
        return std::optional<PhysicalButton::SwitchConfig>(PhysicalButton::SwitchConfig::NormallyOpen);
    case 1:
        return std::optional<PhysicalButton::SwitchConfig>(PhysicalButton::SwitchConfig::NormallyClosed);
    default:
        return std::optional<PhysicalButton::SwitchConfig>();
    }
}

#endif // PHYSICALBUTTON_H
