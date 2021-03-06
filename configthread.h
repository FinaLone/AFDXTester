#ifndef CONFIGTHREAD_H
#define CONFIGTHREAD_H
#include <QThread>
#include <QTimer>
#include "a664_api/a664_api.h"

#define MAC_CONFIGURATION      "D:/Temp/configurations/ES_1_PERSEUS_MAC_2P_8ss.hex"
#define COM_TX_CONFIGURATION   "D:/Temp/configurations/ES_1_PERSEUS_COM_TX_V0.hex"
#define COM_RX_CONFIGURATION   "D:/Temp/configurations/ES_1_PERSEUS_COM_RX_V0.hex"

#define MAX_FILENAME_LENGTH 1500
#define MAX_UDP_FRAME_SIZE  8192
extern int externtest;
class ConfigThread : public QThread
{
    Q_OBJECT
public:
    ConfigThread();
    ~ConfigThread()
    {
        requestInterruption();
        quit();
        wait();
    }

protected:
    void run();
    void runConfigThread();
private:
    int init();
    void sendPackets();
    void sendPacket();
    int packetSize = 0;
    int txSpeed = 0;
    int packetCount = 0;
    QTimer * timer;
    A664Configuration es_config;
    uint8_t* data_snic;
    uint8_t* data_tx_nios;
    uint8_t* data_rx_nios;
    char txdata[MAX_UDP_FRAME_SIZE] = { 0 };
    uint8_t rxdata[MAX_UDP_FRAME_SIZE] = { 0 };
    uint32_t port_id = 0;
    uint32_t data_length = 0;
    int32_t retval;
    uint32_t deviceCount;

    A664EndSystemInfo esInfo = { 0 };
    A664Version api_version;
    A664Version driver_version;
    A664PhyStatus PhyStatus = { 0 };
    A664EndSystemHandle esHandle = { 0 };
    A664TxComUdpHandle tx_handle = { 0 };
    A664RxComUdpHandle rx_handle = { 0 };
    A664TxMessagePortStatus tx_status;
    A664TxUdpStatus tx_udp_status;
    A664TxIpStatus tx_ip_status;
    A664MacStatus tx_mac_status;
    A664NetworkInterface network = A664_NETWORK_A;

    bool initFlag = false; // 是否初始化
};

#endif // CONFIGTHREAD_H
