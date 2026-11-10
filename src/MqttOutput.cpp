#include "../include/outputs/MqttOutput.h"
#include "../include/services/JsonService.h"
#include "../include/config/Config.h"

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

    if (stateService.getState() == QuizState::GAGNANT &&
        stateService.getRoundNumber() != lastResultRound)
    {
        lastResultRound = stateService.getRoundNumber();
        mqttService.publish(TOPIC_DATA,
                            JsonService::buildResult(lastResultRound, stateService.getWinner()));
    }

    return ok;
}
String MqttOutput::getName() const
{
    return "MQTT";
}