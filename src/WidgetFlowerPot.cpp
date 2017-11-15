#include "WidgetFlowerPot.h"


WidgetFlowerPot::WidgetFlowerPot(uint8_t ucItem)
{
    _Item=ucItem;
    memset(pDataStatusTopic,0,sizeof(pDataStatusTopic));
    memset(pCmdWaterTopic,0,sizeof(pCmdWaterTopic));
    memset(pDataSoilHumidityTopic,0,sizeof(pDataSoilHumidityTopic));
    memset(pDataAirTempTopic,0,sizeof(pDataAirTempTopic));
    memset(pDataAirHumidityTopic,0,sizeof(pDataAirHumidityTopic));
    memset(pDataIlluminationTopic,0,sizeof(pDataIlluminationTopic));

    sprintf(pDataStatusTopic,"channel/flowerPot_%d/data/status",_Item);
    sprintf(pCmdWaterTopic,"channel/flowerPot_%d/cmd/watering",_Item);
    sprintf(pDataSoilHumidityTopic,"channel/flowerPot_%d/data/soilHumidity",_Item);
    sprintf(pDataAirTempTopic,"channel/flowerPot_%d/data/airTemp",_Item);
    sprintf(pDataAirHumidityTopic,"channel/flowerPot_%d/data/airHumidity",_Item);
    sprintf(pDataIlluminationTopic,"channel/flowerPot_%d/data/illumination",_Item);

}

WidgetFlowerPot::~WidgetFlowerPot()
{
}

void WidgetFlowerPot::begin(void (*UserCallBack)(void))
{
    _EventCb=UserCallBack;
    IntoRobot.subscribe(pCmdWaterTopic, NULL, this);
}

void WidgetFlowerPot::displayWaterStatus(uint8_t status)
{
    IntoRobot.publish(pDataStatusTopic,status);
}


void WidgetFlowerPot::displaySoilHumidity(uint8_t soilHumidity)
{
    IntoRobot.publish(pDataSoilHumidityTopic,soilHumidity);
}

void WidgetFlowerPot::displayIllumination(float illumination)
{
    IntoRobot.publish(pDataIlluminationTopic,illumination);
}

void WidgetFlowerPot::displayAirTemp(char airTemp)
{
    IntoRobot.publish(pDataAirTempTopic,airTemp);
}


void WidgetFlowerPot::displayAirHumidity(uint8_t airHumidity)
{
    IntoRobot.publish(pDataAirHumidityTopic,airHumidity);
}

uint8_t WidgetFlowerPot::getWaterSwitch(void)
{
    return _switchKey;
}

void WidgetFlowerPot::control(uint8_t pin,uint8_t status)
{
    pinMode(pin,OUTPUT);
    digitalWrite(pin,status);
    displayWaterStatus(status);
}

int WidgetFlowerPot:: getWateringTime(void)
{
    return _wateringTime;
}

void WidgetFlowerPot::widgetBaseCallBack(uint8_t *payload, uint32_t len)
{
    if(!jsonGetValue(payload, "status", _switchKey)) return;
    if(!jsonGetValue(payload, "time", _wateringTime)) return;
    _EventCb();
}


