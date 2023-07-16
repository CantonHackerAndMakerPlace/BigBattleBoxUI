#ifndef ARDUINOCONNECTIONMANAGER_H
#define ARDUINOCONNECTIONMANAGER_H

#include <QObject>
#include <QSerialPort>

class QTimer;
class QFileSystemWatcher;
class ArduinoConnection;

class ArduinoConnectionManager : public QObject
{
    Q_OBJECT
public:
    explicit ArduinoConnectionManager(QObject *parent = nullptr);

    QStringList availableSerialPorts() const;
    static constexpr std::size_t BUFFER_SIZE = 256;

    bool isConnected() const;
public slots:
    void connectToSerialPort(QString port);

private slots:
    void checkSerialPorts();
    void checkSerialBuffer();
    void errorOccurred(QSerialPort::SerialPortError error);
public slots:
    bool sendData(QString data);
signals:
    void availableSerialPortsChanged(const QStringList &port);
    void addedCOMPorts(const QStringList& port);
    void removedCOMPorts(const QStringList& port);
    void receivedData(QString data);
    void disconnected(QString portName);
    void connected(QString portName);
    // Emitted when there's some kind of failure.
    void error(QString msg);
private:
    QTimer *m_updateTimer;
    QTimer *m_readTimer;
    QStringList m_serialPorts;
    QSerialPort *m_conn;
    char *buffer[BUFFER_SIZE];
};

#endif // ARDUINOCONNECTIONMANAGER_H
