#ifndef WIDGET_FLOWER_POT_H_
#define WIDGET_FLOWER_POT_H_

#include "application.h"


class WidgetFlowerPot: public WidgetBaseClass
{
    public:
        WidgetFlowerPot(uint8_t ucItem = 0);
        ~WidgetFlowerPot();
        void begin(void (*UserCallBack)(void) = NULL);
        void displaySoilHumidity(uint8_t soilHumidity);
        void displayIllumination(float illumination);
        void displayAirTemp(char airTemp);
        void displayAirHumidity(uint8_t airHumidity);
        void displayWaterStatus(uint8_t status);
        uint8_t getWaterSwitch(void);
        int getWateringTime(void);
        void control(uint8_t pin,uint8_t status);


    private:
        char pCmdWaterTopic[64];
        char pDataSoilHumidityTopic[64];
        char pDataStatusTopic[64];
        char pDataAirTempTopic[64];
        char pDataAirHumidityTopic[64];
        char pDataIlluminationTopic[64];
        uint8_t _switchKey = 0;
        uint8_t _Item=0;
        int _wateringTime;
        void (*_EventCb)(void);
        void widgetBaseCallBack(uint8_t *payload, uint32_t len);

};

#endif
