#include "../include/outputs/MqttOutput.h"
#include "../include/services/JsonService.h"

MqttOutput::MqttOutput(MqttService &mqttService, QuizStateService &stateService, const char *topic)
    : mqttService(mqttService), stateService(stateService), topic(topic)
{
}
void MqttOutput::begin()
{
    mqttService.begin();
}
bool MqttOutput::send(const SensorData &data)
{

    if (!mqttService.isConnected())
    {

        return false;
    }

    JsonService jsonService;
    String json = jsonService.toJson(data, stateService.getStateName());
    bool ok = mqttService.publish(topic, json);

    return ok;
}
String MqttOutput::getName() const
{
    return "MQTT";
}