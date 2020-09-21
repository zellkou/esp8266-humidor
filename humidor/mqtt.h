#ifndef MQTT
#define MQTT
void connectToWifi()

void onWifiConnect

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event)

void connectToMqtt()

void onMqttConnect(bool sessionPresent)

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason

void onMqttPublish(uint16_t packetId)

#endif