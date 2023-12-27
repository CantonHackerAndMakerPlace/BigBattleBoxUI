#ifndef LEDALGOCONFIG_H
#define LEDALGOCONFIG_H

#include <QObject>

// TODO: Implement me!
/// Base class for LED algorithm configuration that will allow for
/// switching between multiple algorithm configurations.
class LEDAlgoConfig : public QObject
{
    Q_OBJECT
    Q_ENUMS(Curve)

public:
    // This type is associated with a specific kind of
    enum class Kind {

    };

    explicit LEDAlgoConfig(QString const& parentKey, QObject *parent = nullptr);



signals:

};

#endif // LEDALGOCONFIG_H
