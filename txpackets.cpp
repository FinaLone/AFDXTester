//#include "txpackets.h"
//#include "a664_api/a664_api.h"
//#include <stdlib.h>
//#include <iostream>
//#include <QDebug>
//#include <stdio.h>
//#include <windows.h>
//#include <string>

//TxPackets::TxPackets()
//{
//    qDebug()<<"TxPackets";
//    init();
//}

//TxPackets::~TxPackets()
//{
//    qDebug()<<"~TxPackets";
//    close();
//}

//void TxPackets::run(char *data = "", int times = 0, int speed = 0)
//{
//    A664Return result;

//    int return_value = EXIT_SUCCESS;

//    result = a664TxComUdpOpen(esHandle, 0, &tx_handle); // 打开端口
//    if (result != A664_API_OK) {
//        printf("Error:a664TxComUdpOpen result = %d\r\n", result);
//        return_value = EXIT_FAILURE;
//    }
//    else
//    {
//        printf("TxComUdp on EndSystem of AFDXGateway opened successfully!\r\n");

//    }

//    printf("=============AFDX network tests send=============\n");
//    Sleep(3000);
//    while (times-- > 0) {
////        string str_input;
////        char t[3];
////        sprintf(t, "%d", times);
////        str_input = t;
////        str_input += data;
////        data_length = str_input.length();
//        data_length = strlen(data);

//        for (uint32_t i = 0; i<data_length; i++)  // data_length ´óÐ¡ÓÐÎÊÌâ
//        {
//            txdata[i] = data[i];
//        }

//        uint16_t byteswritten;
//        a664TxComUdpWrite(tx_handle, data_length, txdata, &byteswritten);
//        printf("Wrote successfully %d th to tx port\n", times);
//        for (uint32_t i = 0; i<data_length; i++)
//        {
//            txdata[i] = '\0';
//        }
//        data_length = 0;
//        Sleep(speed);
//    }
//    result = a664TxGetMessagePortStatus(tx_handle.handle, &tx_status);
//    if (result != A664_API_OK)
//    {
//        printf("ERROR:a664TxGetMessagePortStatus =%d\r\n", result);
//        return_value = EXIT_FAILURE;
//    }
////    if (return_value != EXIT_FAILURE)
////    {
////        printf("=================Tx Port Status Statistics======================\r\n");
////        printf(" Port ID                     : %u\n", (int)tx_status.mPortId);
////        printf(" Port type                   : %s\n", portTypeToString(tx_status.mTxMessagePortType));
////        printf(" Valid message count         : %u\n", (int)tx_status.mValidMessageCount);
////        printf(" Invalid message count       : %u\n", (int)tx_status.mInvalidMessageCount);
////        printf(" mNoBufferAvailableErrorCount: %u\n", (int)tx_status.mNoBufferAvailableErrorCount);
////        printf(" mNumFullBuffers             : %u\n", (int)tx_status.mNumFullBuffers);
////        printf(" mNumEmptyBuffers            : %u\n", (int)tx_status.mNumEmptyBuffers);
////    }

//    /**************************************************************************************/

//    /********************************ÏÔÊ¾TxUDP×´Ì¬ÐÅÏ¢*************************************/
//    a664TxGetUdpStatus(esHandle, &tx_udp_status);
//    printf("=================Tx UDP Status Statistics=======================\r\n");
//    printf("Total Message Count  : %d\n", (int)tx_udp_status.mTotalMessageCount);
//    printf("Invalid Message Count: %d\n", (int)tx_udp_status.mInvalidMessageCount);
//    printf("No Port Defined Count: %d\n", (int)tx_udp_status.mNoPortCount);
//    /**************************************************************************************/

//    /***************************ÏÔÊ¾TxIP²ã×´Ì¬ÐÅÏ¢********************************/
//    printf("=================Tx IP Status Statistics========================\r\n");
//    result = a664TxGetIpStatus(esHandle, &tx_ip_status);
//    if (result != A664_API_OK)
//    {
//        printf("ERROR:a664TxGetIpStatus =%d\r\n", result);
//        return_value = EXIT_FAILURE;
//    }
//    if (return_value != EXIT_FAILURE)
//    {
//        printf(" Total packet count          : %d\n", (int)tx_ip_status.mTotalPacketCount);
//        printf(" Invalid packet count        : %d\n", (int)tx_ip_status.mInvalidPacketCount);
//        printf(" Dicard count                : %d\n", (int)tx_ip_status.mDicardCount);
//    }
//    /***********************************************************/

//    /*****************ÏÔÊ¾MAC×´Ì¬ÐÅÏ¢***************************/
//    result = a664ESGetMacStatus(esHandle, network, &tx_mac_status);//»ñÈ¡MACÐ­Òé²ã×´Ì¬ÐÅÏ¢
//    printf("========================MAC Status==============================\r\n");
//    if (result != A664_API_OK)
//    {
//        printf \
//            ("ERROR:a664ESGetMacStatus result=%d network=%d\r\n"
//                , (signed int)result, (signed int)network
//                );
//        return_value = EXIT_FAILURE;
//    }
//    if (return_value != EXIT_FAILURE)//ÏÔÊ¾MAC²ã×´Ì¬Í³¼ÆÐÅÏ¢
//    {
//        printf("Mac Status ntwrk# : %d \n", network);
//        printf("mInterfaceEnabled : %d \n", tx_mac_status.mInterfaceEnabled);
//        printf("mInterfaceEnabled : %d \n", tx_mac_status.mInterfaceEnabled);
//        printf("mInterfaceEnabled : %d \n", tx_mac_status.mInterfaceEnabled);
//        printf("mInterfaceEnabled : %d \n", tx_mac_status.mInterfaceEnabled);
//        printf("mRxBytes          : %u \n", tx_mac_status.mRxBytes);
//        printf("mTxBytes          : %u \n", tx_mac_status.mTxBytes);
//        printf("mMIIErrors        : %u \n", tx_mac_status.mMIIErrors);
//        printf("mCRCErrors        : %u \n", tx_mac_status.mCRCErrors);
//        printf("mAlignmentErrors  : %u \n", tx_mac_status.mAlignmentErrors);
//        printf("mSOFErrors        : %u \n", tx_mac_status.mSOFErrors);
//        printf("mSizeErrors       : %u \n", tx_mac_status.mSizeErrors);
//    }
//    printf("================================================================\r\n");

//    /***************************¹Ø±ÕTx¶Ë¿Ú********************************/
//    result = a664TxComUdpClose(tx_handle);//¹Ø±ÕCOM_UDPÀàÐÍ¶Ë¿Ú
//    if (result != A664_API_OK)
//    {
//        printf("ERROR:a664TxComUdpClose =%d\r\n", result);
//        return_value = EXIT_FAILURE;
//    }
//}

//int TxPackets::init()
//{
//    FILE* configurationFile;
//    A664Return result;
//    int return_value = EXIT_SUCCESS;

//    printf("Begin init\r\n");
//    qDebug()<<"qdebug into init...";
//    result = a664Init(A664_API_IO_VERSION, &this->deviceCount);
//    if (result != A664_API_OK) {
//        printf("Error:a664Init result = %d\r\n", (signed int)result);
//        printf("No device found.\r\n");
//        return_value = EXIT_FAILURE;
//    }
//    else {
//        printf("Found %d device(s)\r\n", (int)this->deviceCount);
//        qDebug()<<"Found "<<(int)this->deviceCount<<" devices";
//    }
//    result = a664GetApiVersions(&api_version, &driver_version);//版本信息
//    printf("========================API Versions========================");
//    if (result != A664_API_OK) {
//        printf("Error:a664GetApiVersions result = %d\r\n", (signed int)result);
//        return_value = EXIT_FAILURE;
//    }
//    else {
//        printf("%s: %u.%u.%u.%u\r\n", "API Version", api_version.mVersionMajor, api_version.mVersionMinor, api_version.mVersionMaintenance, api_version.mVersionRevision);
//        printf("%s: %u.%u.%u.%u\r\n", "Driver Version", driver_version.mVersionMajor, driver_version.mVersionMinor, driver_version.mVersionMaintenance, driver_version.mVersionRevision);
//        qDebug()<<"API Version: "<<api_version.mVersionMajor<<"."<< api_version.mVersionMinor<<"."<<api_version.mVersionMaintenance<<"."<< api_version.mVersionRevision;
//        qDebug()<<"Driver Version: "<<driver_version.mVersionMajor<<"."<<driver_version.mVersionMinor<<"."<<driver_version.mVersionMaintenance<<"."<<driver_version.mVersionRevision;
//    }
//    result = a664ESGetCount(&deviceCount);//端系统数量
//    if (result != A664_API_OK) {
//        printf("Error:a664ESGetCount result = %d\r\n", (signed int)result);
//        return_value = EXIT_FAILURE;
//    }
//    else {
//        printf("%s:%u\r\n", "number of end systems", (unsigned int)deviceCount);
//    }
//    result = a664ESGetInfo(0, &esInfo);
//    printf("====================End System Info=========================");
//    if (result != A664_API_OK) {
//        printf("Error:a664ESGetInfo result = %d\r\n", (signed int)result);
//        return_value = EXIT_FAILURE;
//    }
//    else {
//        printf("ES Id: %u\r\n", esInfo.aESId);
//        printf("ES Part Number: %u\r\n", esInfo.aESPartNumber);
//        printf("Network Interface Count: %u\r\n", esInfo.aNumNetworkInterfaces);
//        printf("%s: %u.%u.%u.%u\n"
//            , "sNIC Version            "
//            , esInfo.sNicVersion.mVersionMajor
//            , esInfo.sNicVersion.mVersionMinor
//            , esInfo.sNicVersion.mVersionMaintenance
//            , esInfo.sNicVersion.mVersionRevision
//        );
//        printf("%s: %u.%u.%u.%u\n"
//            , "Tx NIOS Version         "
//            , esInfo.txNIOSVersion.mVersionMajor
//            , esInfo.txNIOSVersion.mVersionMinor
//            , esInfo.txNIOSVersion.mVersionMaintenance
//            , esInfo.txNIOSVersion.mVersionRevision
//        );
//        printf("%s: %u.%u.%u.%u\n"
//            , "Rx NIOS Version         "
//            , esInfo.rxNIOSVersion.mVersionMajor
//            , esInfo.rxNIOSVersion.mVersionMinor
//            , esInfo.rxNIOSVersion.mVersionMaintenance
//            , esInfo.rxNIOSVersion.mVersionRevision
//        );
//        printf("%s: %u.%u.%u.%u\n"
//            , "Tx NIOS Boot App Version"
//            , esInfo.txBootNIOSVersion.mVersionMajor
//            , esInfo.txBootNIOSVersion.mVersionMinor
//            , esInfo.txBootNIOSVersion.mVersionMaintenance
//            , esInfo.txBootNIOSVersion.mVersionRevision
//        );
//        printf("%s: %u.%u.%u.%u\n"
//            , "Rx NIOS Boot App Version"
//            , esInfo.rxBootNIOSVersion.mVersionMajor
//            , esInfo.rxBootNIOSVersion.mVersionMinor
//            , esInfo.rxBootNIOSVersion.mVersionMaintenance
//            , esInfo.rxBootNIOSVersion.mVersionRevision
//        );

//        printf("%s: %u %u %s\n"
//            , "Device Identification   "
//            , esInfo.deviceIdent.vid   //Vendor ID
//            , esInfo.deviceIdent.did   //Device ID
//            , esInfo.deviceIdent.name  //Device name
//        );
//    }
//    result = a664ESOpen(0, &esHandle);
//    printf("================EndSystem of AFDXGateway Initialization========================\r\n");
//    if (result != A664_API_OK) {
//        printf("Error:a664ESOpen result = %d\r\n", (signed int)result);
//        return_value = EXIT_FAILURE;
//    }
//    else
//    {
//        printf("EndSystem of AFDXGateway open successfully...\r\n");
//        qDebug()<<"EndSystem of AFDXGateway open successfully...";
//    }
//    result = a664ESReset(esHandle);
//    if (result != A664_API_OK) {
//        printf("Error:a664ESReset result = %d\r\n", (signed int)result);
//    }
//    else {
//        printf("Get the EndSyetem Infomation successfully by using EndSystem Handle.\n");
//        qDebug("Get the EndSyetem Infomation successfully by using EndSystem Handle.");
//    }



//    /******************************加载MAC配置文件*******************************/
//    printf("Loading MACConfigurationFile:%s\n", MAC_CONFIGURATION);
//    qDebug()<<"Loading MAC Configuration File: "<< MAC_CONFIGURATION;
//    configurationFile = fopen(MAC_CONFIGURATION, "r");
//    if (configurationFile != 0)
//    {
//        long fileSize;
//        size_t result;
//        fseek(configurationFile, 0, SEEK_END);
//        fileSize = ftell(configurationFile);
//        rewind(configurationFile);
//        data_snic = (uint8_t*)malloc(sizeof(uint8_t) * fileSize);
//        if (data_snic == 0) { fputs("Memory allocation error", stderr); return -1; }
//        result = fread(data_snic, 1, fileSize, configurationFile);
//        if (result <= 0) { fputs("Read error", stderr); return -1; }
//        fclose(configurationFile);
//        configurationFile = 0;
//    }
//    else
//    {
//        printf("Error opening file: %s\n", MAC_CONFIGURATION);
//        return -1;
//    }
//    /***********************************************************/

//    /******************************加载Tx配置文件*******************************/
//    printf("Loading  TXConfigurationFile:%s\n", COM_TX_CONFIGURATION);
//    qDebug()<<"Loading TX Configuration File: "<<COM_TX_CONFIGURATION;
//    configurationFile = fopen(COM_TX_CONFIGURATION, "r");
//    if (configurationFile != 0)
//    {
//        long fileSize;
//        size_t result;
//        fseek(configurationFile, 0, SEEK_END);
//        fileSize = ftell(configurationFile);
//        rewind(configurationFile);
//        data_tx_nios = (uint8_t*)malloc(sizeof(uint8_t) * fileSize);
//        if (data_tx_nios == 0) { fputs("Memory allocation error", stderr); return -1; }
//        result = fread(data_tx_nios, 1, fileSize, configurationFile);
//        if (result <= 0) { fputs("Read error", stderr); return -1; }
//        fclose(configurationFile);
//        configurationFile = 0;
//    }
//    else
//    {
//        printf("Error opening file: %s\n", COM_TX_CONFIGURATION);
//        return -1;
//    }
//    /***********************************************************/

//    /******************************加载Rx配置文件*******************************/
//    printf("Loading  RXConfigurationFile:%s\r\n", COM_RX_CONFIGURATION);
//    qDebug()<<"Loading RX Configuration File: "<< COM_RX_CONFIGURATION;
//    configurationFile = fopen(COM_RX_CONFIGURATION, "r");
//    if (configurationFile != 0)
//    {
//        long fileSize;
//        size_t result;
//        fseek(configurationFile, 0, SEEK_END);
//        fileSize = ftell(configurationFile);
//        rewind(configurationFile);
//        data_rx_nios = (uint8_t*)malloc(sizeof(uint8_t) * fileSize);
//        if (data_rx_nios == 0) { fputs("Memory allocation error", stderr); return -1; }
//        result = fread(data_rx_nios, 1, fileSize, configurationFile);
//        if (result <= 0) { fputs("Read error", stderr); return -1; }
//        fclose(configurationFile);
//        configurationFile = 0;
//    }
//    else
//    {
//        printf("Error opening file: %s\n", COM_RX_CONFIGURATION);
//        return -1;
//    }
//    es_config.aSnicConf = data_snic;
//    es_config.aTxUlpConf = data_tx_nios;
//    es_config.aRxUlpConf = data_rx_nios;
//    a664ESConfigure(esHandle, &es_config);
//    free(data_snic);
//    free(data_tx_nios);
//    free(data_rx_nios);
//    printf("EndSystem of AFDXGateway configured successfully!\n");
//    qDebug()<<"EndSystem of AFDX configured successfully";

//    /*****************显示端系统PHY状态信息********************/
//    result = a664ESGetPhyStatus(esHandle, &PhyStatus);
//    if (result != A664_API_OK)
//    {
//        printf("ERROR:a664ESGetPhyStatus result=%d\r\n", (signed int)result);
//        return_value = EXIT_FAILURE;
//    }
//    printf("========================PHY Status==============================\r\n");
//    printf("%s:%u\n"
//        , "Boolean link status for channel 0"
//        , PhyStatus.linkStatusCh0
//    );
//    printf("%s:%u\n"
//        , "Boolean link status for channel 1"
//        , PhyStatus.linkStatusCh1
//    );
//    if (PhyStatus.speedCh0 == 01)
//    {
//        printf("Configured speed for channel 0 :100 Mbit/s\n");
//    }
//    else if (PhyStatus.speedCh0 == 10)
//    {
//        printf("Configured speed for channel 0 :1 Gbit/s\n");
//    }
//    else
//    {
//        printf("%s:%u\n"
//            , "Configured speed for channel 0 "
//            , PhyStatus.speedCh0
//        );
//    }
//    if (PhyStatus.speedCh1 == 01)
//    {
//        printf("Configured speed for channel 1 :100 Mbit/s\n");
//    }
//    else if (PhyStatus.speedCh1 == 10)
//    {
//        printf(" Configured speed for channel 1 :1 Gbit/s\n");
//    }
//    else
//    {
//        printf("%s:%u\n"
//            , "Configured speed for channel 0 "
//            , PhyStatus.speedCh0
//        );
//    }
//    initFlag = true;
//    printf("================================================================\r\n");
//    return return_value;
//}

//int TxPackets::runTest()
//{

//}

//void TxPackets::close()
//{
//    a664ESClose(esHandle);
//    a664Close();
//}
