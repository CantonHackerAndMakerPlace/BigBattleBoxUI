#include "arduinoconnectionmanager.h"
#include <QTimer>
#include <set>
#include <iterator>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>

ArduinoConnectionManager::ArduinoConnectionManager(QObject *parent)
    : QObject{parent}
    , m_updateTimer(new QTimer(this))
    , m_readTimer(new QTimer(this))
    , m_conn(new QSerialPort(this))
{

    connect(m_conn, &QSerialPort::errorOccurred,
            this, &ArduinoConnectionManager::errorOccurred);
    m_conn->setBaudRate(9600);
    checkSerialPorts();
    connect(m_updateTimer, &QTimer::timeout,
            this, &ArduinoConnectionManager::checkSerialPorts);
    m_updateTimer->start(100);

    // Setting up read timer.
    connect(m_readTimer, &QTimer::timeout,
            this, &ArduinoConnectionManager::checkSerialBuffer);
    m_readTimer->start(10);

}

void ArduinoConnectionManager::connectToSerialPort(QString port) {
    if (port == "") {
        m_conn->disconnect();
        emit disconnected(m_conn->portName());
        m_conn->setPortName("");
    } else {
        m_conn->setPortName(port);
    }

}

QStringList ArduinoConnectionManager::availableSerialPorts() const {
    return m_serialPorts;
}

bool ArduinoConnectionManager::isConnected() const {
    return m_conn->isOpen();
}

namespace {
    template<typename ForwardIt1, typename ForwardIt2,
             typename ForwardIt3, typename ForwardIt4>
    void set_full_diff(ForwardIt1 first1, ForwardIt1 last1,
                       ForwardIt2 first2, ForwardIt2 last2,
                       ForwardIt3 d1_first, ForwardIt4 d2_first) {

        while (first1 != last1)
        {
            if (first2 == last2) {
                std::copy(first1, last1, d1_first);
                return;
            }

            if (*first1 < *first2)
                *d1_first++ = *first1++;
            else
            {
                if (*first2 < *first1)
                    *d2_first++ = *first2;
                else
                    ++first1;
                ++first2;
            }
        }
        std::copy(first2, last2, d2_first);
        return;
    }
}

void ArduinoConnectionManager::checkSerialPorts() {
    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
    std::set<QString> currentSerialPort(m_serialPorts.begin(), m_serialPorts.end());
    std::set<QString> newSerialPorts;
    for (QSerialPortInfo &port : list) {
        newSerialPorts.insert(port.portName());
    }

    QStringList added;
    QStringList removed;
    std::less<QString const&> cmp;
    set_full_diff(currentSerialPort.begin(), currentSerialPort.end(),
                  newSerialPorts.begin(), newSerialPorts.end(),
                  std::back_inserter(removed), std::back_inserter(added));

    if (!added.empty() || !removed.empty()) {
        if (!removed.empty()){
            emit removedCOMPorts(removed);
        }
        if (!added.empty()){
            emit addedCOMPorts(added);
        }

        m_serialPorts.clear();
        for (const QString &n : newSerialPorts) {
            m_serialPorts.push_back(n);
        }
        emit availableSerialPortsChanged(m_serialPorts);
        // Check if we removed the current serail port and emit a disconnected
        // message or something?
        if (std::find(removed.begin(), removed.end(), m_conn->portName()) != removed.end()) {
            if (!m_conn->isOpen()) {
                m_conn->disconnect();
                emit disconnected(m_conn->portName());
            }
        } else if (std::find(added.begin(), added.end(), m_conn->portName()) != added.end()) {
            if (m_conn->isOpen()) {
                m_conn->disconnect();
                emit disconnected(m_conn->portName());
            }
            m_conn->open(QIODeviceBase::ReadWrite);
            if (m_conn->isOpen()) {
                emit connected(m_conn->portName());
            }
        }
    } else if(!m_conn->isOpen() && m_conn->portName() != ""
              && (std::find(m_serialPorts.begin(),
                            m_serialPorts.end(),
                            m_conn->portName()) != m_serialPorts.end())) {
        qDebug() << "Connecting to arduino: " << m_conn->portName();
        m_conn->open(QIODeviceBase::ReadWrite);
        if (m_conn->isOpen()) {
            emit connected(m_conn->portName());
        }
    }
}

void ArduinoConnectionManager::checkSerialBuffer() {
    if (!m_conn->isOpen()) {
        return;
    }

    if (m_conn->canReadLine()) {
        auto readLength = m_conn->readLine((char*)buffer, BUFFER_SIZE);
        if (readLength < 0) {
            qDebug() << "Failed to get data";
            return;
        }

        buffer[readLength] = 0;
        QString response((char*)buffer);
        qDebug() << "Received data" << response;
        emit receivedData(response);
    }
}

bool ArduinoConnectionManager::sendData(QString data) {
    if (!m_conn->isOpen()) {
        return false;
    }
    data.append('\n');
    auto dataArray = data.toLocal8Bit();
    auto written = m_conn->write(dataArray);
    if (written != dataArray.size()) {
        qDebug() << "Failed to write all data into serial connection";
        qWarning() << "Wrote" << written << "of" <<dataArray.size() << "bytes";
    }
    if (!m_conn->flush() ) {
        qWarning() << "flush failed and returned false?";
    }
    return true;
}

void ArduinoConnectionManager::errorOccurred(QSerialPort::SerialPortError e) {
    if (e != QSerialPort::SerialPortError::NoError) {
        emit error(m_conn->errorString());
        m_conn->clearError();
    }
}

