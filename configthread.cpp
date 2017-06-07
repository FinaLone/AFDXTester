#include "configthread.h"
#include <QDebug>
#include <QSettings>
#include <QTimer>
#include <QTime>
#include "utils.h"

ConfigThread::ConfigThread()
{
}

void ConfigThread::run()
{
        init();
        sendPackets();
        this->exec();
}

void ConfigThread::runConfigThread()
{

}

int ConfigThread::init()
{
    qDebug()<<"ConfigThread::init()";
    FILE* configurationFile;
    A664Return result;
    int return_value = EXIT_SUCCESS;

    printf("Begin init\r\n");
    qDebug()<<"qdebug into init...";
    result = a664Init(A664_API_IO_VERSION, &this->deviceCount);
    if (result != A664_API_OK) {
        printf("Error:a664Init result = %d\r\n", (signed int)result);
        printf("No device found.\r\n");
        return_value = EXIT_FAILURE;
    }
    else {
        printf("Found %d device(s)\r\n", (int)this->deviceCount);
        qDebug()<<"Found "<<(int)this->deviceCount<<" devices";
    }
    result = a664GetApiVersions(&api_version, &driver_version);//版本信息
    printf("========================API Versions========================");
    if (result != A664_API_OK) {
        printf("Error:a664GetApiVersions result = %d\r\n", (signed int)result);
        return_value = EXIT_FAILURE;
    }
    else {
        printf("%s: %u.%u.%u.%u\r\n", "API Version", api_version.mVersionMajor, api_version.mVersionMinor, api_version.mVersionMaintenance, api_version.mVersionRevision);
        printf("%s: %u.%u.%u.%u\r\n", "Driver Version", driver_version.mVersionMajor, driver_version.mVersionMinor, driver_version.mVersionMaintenance, driver_version.mVersionRevision);
        qDebug()<<"API Version: "<<api_version.mVersionMajor<<"."<< api_version.mVersionMinor<<"."<<api_version.mVersionMaintenance<<"."<< api_version.mVersionRevision;
        qDebug()<<"Driver Version: "<<driver_version.mVersionMajor<<"."<<driver_version.mVersionMinor<<"."<<driver_version.mVersionMaintenance<<"."<<driver_version.mVersionRevision;
    }
    result = a664ESGetCount(&deviceCount);//端系统数量
    if (result != A664_API_OK) {
        printf("Error:a664ESGetCount result = %d\r\n", (signed int)result);
        return_value = EXIT_FAILURE;
    }
    else {
        printf("%s:%u\r\n", "number of end systems", (unsigned int)deviceCount);
    }
    result = a664ESGetInfo(0, &esInfo);
    printf("====================End System Info=========================");
    if (result != A664_API_OK) {
        printf("Error:a664ESGetInfo result = %d\r\n", (signed int)result);
        return_value = EXIT_FAILURE;
    }
    else {
        printf("ES Id: %u\r\n", esInfo.aESId);
        printf("ES Part Number: %u\r\n", esInfo.aESPartNumber);
        printf("Network Interface Count: %u\r\n", esInfo.aNumNetworkInterfaces);
        printf("%s: %u.%u.%u.%u\n"
            , "sNIC Version            "
            , esInfo.sNicVersion.mVersionMajor
            , esInfo.sNicVersion.mVersionMinor
            , esInfo.sNicVersion.mVersionMaintenance
            , esInfo.sNicVersion.mVersionRevision
        );
        printf("%s: %u.%u.%u.%u\n"
            , "Tx NIOS Version         "
            , esInfo.txNIOSVersion.mVersionMajor
            , esInfo.txNIOSVersion.mVersionMinor
            , esInfo.txNIOSVersion.mVersionMaintenance
            , esInfo.txNIOSVersion.mVersionRevision
        );
        printf("%s: %u.%u.%u.%u\n"
            , "Rx NIOS Version         "
            , esInfo.rxNIOSVersion.mVersionMajor
            , esInfo.rxNIOSVersion.mVersionMinor
            , esInfo.rxNIOSVersion.mVersionMaintenance
            , esInfo.rxNIOSVersion.mVersionRevision
        );
        printf("%s: %u.%u.%u.%u\n"
            , "Tx NIOS Boot App Version"
            , esInfo.txBootNIOSVersion.mVersionMajor
            , esInfo.txBootNIOSVersion.mVersionMinor
            , esInfo.txBootNIOSVersion.mVersionMaintenance
            , esInfo.txBootNIOSVersion.mVersionRevision
        );
        printf("%s: %u.%u.%u.%u\n"
            , "Rx NIOS Boot App Version"
            , esInfo.rxBootNIOSVersion.mVersionMajor
            , esInfo.rxBootNIOSVersion.mVersionMinor
            , esInfo.rxBootNIOSVersion.mVersionMaintenance
            , esInfo.rxBootNIOSVersion.mVersionRevision
        );

        printf("%s: %u %u %s\n"
            , "Device Identification   "
            , esInfo.deviceIdent.vid   //Vendor ID
            , esInfo.deviceIdent.did   //Device ID
            , esInfo.deviceIdent.name  //Device name
        );
    }
    result = a664ESOpen(0, &esHandle);
    printf("================EndSystem of AFDXGateway Initialization========================\r\n");
    if (result != A664_API_OK) {
        printf("Error:a664ESOpen result = %d\r\n", (signed int)result);
        return_value = EXIT_FAILURE;
    }
    else
    {
        printf("EndSystem of AFDXGateway open successfully...\r\n");
        qDebug()<<"EndSystem of AFDXGateway open successfully...";
    }
    result = a664ESReset(esHandle);
    if (result != A664_API_OK) {
        printf("Error:a664ESReset result = %d\r\n", (signed int)result);
    }
    else {
        printf("Get the EndSyetem Infomation successfully by using EndSystem Handle.\n");
        qDebug("Get the EndSyetem Infomation successfully by using EndSystem Handle.");
    }



    /******************************加载MAC配置文件*******************************/
    printf("Loading MACConfigurationFile:%s\n", MAC_CONFIGURATION);
    qDebug()<<"Loading MAC Configuration File: "<< MAC_CONFIGURATION;
    configurationFile = fopen(MAC_CONFIGURATION, "r");
    if (configurationFile != 0)
    {
        long fileSize;
        size_t result;
        fseek(configurationFile, 0, SEEK_END);
        fileSize = ftell(configurationFile);
        rewind(configurationFile);
        data_snic = (uint8_t*)malloc(sizeof(uint8_t) * fileSize);
        if (data_snic == 0) { fputs("Memory allocation error", stderr); return -1; }
        result = fread(data_snic, 1, fileSize, configurationFile);
        if (result <= 0) { fputs("Read error", stderr); return -1; }
        fclose(configurationFile);
        configurationFile = 0;
    }
    else
    {
        printf("Error opening file: %s\n", MAC_CONFIGURATION);
        return -1;
    }
    /***********************************************************/

    /******************************加载Tx配置文件*******************************/
    printf("Loading  TXConfigurationFile:%s\n", COM_TX_CONFIGURATION);
    qDebug()<<"Loading TX Configuration File: "<<COM_TX_CONFIGURATION;
    configurationFile = fopen(COM_TX_CONFIGURATION, "r");
    if (configurationFile != 0)
    {
        long fileSize;
        size_t result;
        fseek(configurationFile, 0, SEEK_END);
        fileSize = ftell(configurationFile);
        rewind(configurationFile);
        data_tx_nios = (uint8_t*)malloc(sizeof(uint8_t) * fileSize);
        if (data_tx_nios == 0) { fputs("Memory allocation error", stderr); return -1; }
        result = fread(data_tx_nios, 1, fileSize, configurationFile);
        if (result <= 0) { fputs("Read error", stderr); return -1; }
        fclose(configurationFile);
        configurationFile = 0;
    }
    else
    {
        printf("Error opening file: %s\n", COM_TX_CONFIGURATION);
        return -1;
    }
    /***********************************************************/

    /******************************加载Rx配置文件*******************************/
    printf("Loading  RXConfigurationFile:%s\r\n", COM_RX_CONFIGURATION);
    qDebug()<<"Loading RX Configuration File: "<< COM_RX_CONFIGURATION;
    configurationFile = fopen(COM_RX_CONFIGURATION, "r");
    if (configurationFile != 0)
    {
        long fileSize;
        size_t result;
        fseek(configurationFile, 0, SEEK_END);
        fileSize = ftell(configurationFile);
        rewind(configurationFile);
        data_rx_nios = (uint8_t*)malloc(sizeof(uint8_t) * fileSize);
        if (data_rx_nios == 0) { fputs("Memory allocation error", stderr); return -1; }
        result = fread(data_rx_nios, 1, fileSize, configurationFile);
        if (result <= 0) { fputs("Read error", stderr); return -1; }
        fclose(configurationFile);
        configurationFile = 0;
    }
    else
    {
        printf("Error opening file: %s\n", COM_RX_CONFIGURATION);
        return -1;
    }
    es_config.aSnicConf = data_snic;
    es_config.aTxUlpConf = data_tx_nios;
    es_config.aRxUlpConf = data_rx_nios;
    a664ESConfigure(esHandle, &es_config);
    free(data_snic);
    free(data_tx_nios);
    free(data_rx_nios);
    printf("EndSystem of AFDXGateway configured successfully!\n");
    qDebug()<<"EndSystem of AFDX configured successfully";

    /*****************显示端系统PHY状态信息********************/
    result = a664ESGetPhyStatus(esHandle, &PhyStatus);
    if (result != A664_API_OK)
    {
        printf("ERROR:a664ESGetPhyStatus result=%d\r\n", (signed int)result);
        return_value = EXIT_FAILURE;
    }
    printf("========================PHY Status==============================\r\n");
    printf("%s:%u\n"
        , "Boolean link status for channel 0"
        , PhyStatus.linkStatusCh0
    );
    printf("%s:%u\n"
        , "Boolean link status for channel 1"
        , PhyStatus.linkStatusCh1
    );
    if (PhyStatus.speedCh0 == 01)
    {
        printf("Configured speed for channel 0 :100 Mbit/s\n");
    }
    else if (PhyStatus.speedCh0 == 10)
    {
        printf("Configured speed for channel 0 :1 Gbit/s\n");
    }
    else
    {
        printf("%s:%u\n"
            , "Configured speed for channel 0 "
            , PhyStatus.speedCh0
        );
    }
    if (PhyStatus.speedCh1 == 01)
    {
        printf("Configured speed for channel 1 :100 Mbit/s\n");
    }
    else if (PhyStatus.speedCh1 == 10)
    {
        printf(" Configured speed for channel 1 :1 Gbit/s\n");
    }
    else
    {
        printf("%s:%u\n"
            , "Configured speed for channel 0 "
            , PhyStatus.speedCh0
        );
    }
    initFlag = true;
    printf("================================================================\r\n");
    //初始化完成。
    return return_value;
}
void ConfigThread::sendPackets()//单次测试发送包
{
    QSettings setting("418", "AFDXTester");
    setting.beginGroup("Tx Config");
    packetSize = setting.value("PacketSize").toInt(); // 包长
    txSpeed = setting.value("TxSpeed").toInt();  // 发送速度
    setting.endGroup();
    qDebug()<<"PS:"<<packetSize<<"; TS:"<<txSpeed;
    utils genString;
    char* packetc = genString.genRandomString(packetSize);//生成随机数据包内容
    qDebug()<<"packetc:"<<packetc;
    strcpy_s(txdata, packetc);
    a664TxComUdpOpen(esHandle, 0, &tx_handle);// 打开端口
    QTime time;
    time.start();
    sleep(3);   //等待3秒 配置完成
    qDebug()<<"Time cost:"<<time.elapsed()/1000.0<<"s";
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &ConfigThread::sendPacket, Qt::DirectConnection);
    timer->start(txSpeed);
    qDebug()<<"After timer start";

}
void ConfigThread::sendPacket()//发送一个包
{
    qDebug()<<"sendpacket";
    qDebug()<<txdata;

    data_length = strlen(txdata);

//    for (int i = 0; i<data_length; i++)  // data_length ´óÐ¡ÓÐÎÊÌâ
//    {
//        txdata[i] = data[i];
//    }

    uint16_t byteswritten;
    a664TxComUdpWrite(tx_handle, data_length, txdata, &byteswritten);
    ++packetCount;
    if(packetCount>=20){
        timer->stop();
        packetCount = 0;
        qDebug()<<"timer stoped.";
    }
    //printf("Wrote successfully %d th to tx port\n", times);
//    for (int i = 0; i<data_length; i++)
//    {
//        txdata[i] = '\0';
//    }
//    data_length = 0;
}
