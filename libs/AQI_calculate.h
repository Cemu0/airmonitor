#include "esphome.h"

float aqi_calulate(){
    float pm25 = id(pm_2_5).state;
    float aqi;
    

    if (pm25 > 0.0 && pm25 <= 12.0) {
        aqi = 50.0 / 12.0 * pm25;
    } else if (pm25 > 12.0 && pm25 <= 35.4) {
        aqi = 50.0 / 23.4 * (pm25 - 12.0) + 50.0;
    } else if (pm25 > 35.4 && pm25 <= 55.4) {
        aqi = 50.0 / 20.0 * (pm25 - 35.4) + 100.0;
    } else if (pm25 > 55.4 && pm25 <= 150.4) {
        aqi = 50.0 / 95.0 * (pm25 - 55.4) + 150.0;
    } else if (pm25 > 150.4 && pm25 <= 250.4) {
        aqi = 50.0 / 100.0 * (pm25 - 150.4) + 200.0;
    } else if (pm25 > 250.4 && pm25 <= 350.4) {
        aqi = 50.0 / 100.0 * (pm25 - 250.4) + 300.0;
    } else if (pm25 > 350.4 && pm25 <= 500.4) {
        aqi = 50.0 / 150.0 * (pm25 - 350.4) + 400.0;
    } else if (pm25 > 500.4) {
        aqi = 501.0; // Assuming the AQI is capped at 500 for values above 500.4
    } else {
        aqi = -1;
    }
          
    return aqi;
}

int check_save_air(){
    float pm25 = id(pm_2_5).state;
    float co2 = id(co2_sensor).state;
    bool mq2 = id(mq2_sensor).state;
    bool mq135 = id(mq135_sensor).state;

    int return_value = 0;

    //wait for warm up
    if(id(uptime_sensor).state > 60){
        if(id(enable_mq).state){
            if (mq2)
                return 3;
            if (mq135)
                return 4;
        }

        if (co2 > 2000)
            return 2;

        if (pm25 > 200)
            return 1;
    }
    

    return return_value;
}