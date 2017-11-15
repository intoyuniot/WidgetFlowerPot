/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 花园管家：检测花园环境温湿度、光照强度、土壤湿度，同时可以控制浇水

 所需器件:
 1. DHT11 温湿度传感器模块
 2. YL38 土壤湿度检测传感器模块
 3. GY30 光照传感器模块
 4. 电磁阀

 接线说明
 YL38            核心板
 +               VIN
 -               GND
 S               A0

 DHT11
 VCC             3V3
 GND             GND
 DATA            D0

 GY30
 VCC             3V3
 GND             GND
 SDA             I2C(Wire组)的SDA
 SCL             I2C(Wire组)的SCL

 继电器模块
 DC+             5V0
 DC-             GND
 IN              D3

 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 请注意各核心板的I2C引脚区别，避免接线错误。
*/

#include <gy30.h>
#include <IntoRobot_DHT.h>
#include <yl38.h>
#include <WidgetFlowerPot.h>


#define  WATERING_SWITCH_PIN    D3 //浇水开关引脚
#define  DHT_TYPE   DHT11
#define  DHT11_PIN  D0
#define  YL38_PIN   A0
 
IntoRobot_DHT dht11(DHT11_PIN,DHT_TYPE); //温湿度传感器
YL38 yl38 = YL38(YL38_PIN);     //土壤湿度传感器
GY30 gy30;                //光照强度传感器
WidgetFlowerPot flowerPot = WidgetFlowerPot();

uint8_t   wateringDelay;  //浇水时间
uint8_t   wateringFlag;   //浇水标志
uint32_t  wateringTimer;  //浇水定时器

//花盆浇水回调
void flowerPotWateringCb(void)
{
    int wateringStatus;
    wateringDelay = flowerPot.getWateringTime();

    if(flowerPot.getWaterSwitch())
    {
        flowerPot.control(WATERING_SWITCH_PIN,1);//打开浇水
        if(wateringDelay != 0)
        {
            wateringFlag = 1;
            wateringTimer = timerGetId();
        }
        else
        {
            wateringFlag = 0;
        }
    }
    else
    {
        flowerPot.control(WATERING_SWITCH_PIN,0); //关闭浇水
        wateringFlag = 0;
    }
}

void setup()
{
    //初始化
    yl38.begin();
    dht11.begin();
    gy30.begin();
    //接受浇水指令
    flowerPot.begin(flowerPotWateringCb);
}

void loop()
{
    flowerPot.displayAirTemp(dht11.getTempCelcius());      //上送温度
    flowerPot.displayAirHumidity(dht11.getHumidity());      //上送湿度
    flowerPot.displayIllumination(gy30.Read());              //上送光照强度
    flowerPot.displaySoilHumidity(yl38.CalculateHumidity()); //上送土壤湿度

    if(wateringFlag && (timerIsEnd(wateringTimer,wateringDelay*60000)))
    {
        flowerPot.control(WATERING_SWITCH_PIN,0); //花盆浇水时间到，关闭浇水
        wateringFlag = 0;
    }

    delay(3000);
}
