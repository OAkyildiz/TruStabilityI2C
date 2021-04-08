
#include <Wire.h>
#include "hsc_ssc_i2c.h"

// see hsc_ssc_i2c.h for a description of these values
// these defaults are valid for the HSCMRNN030PA2A3 chip
#define SLAVE_ADDR 0x28
     // 90% of 2^14 - 1
#define PRESSURE_MIN 0.0        // min is 0 for sensors that give absolute values
#define PRESSURE_MAX 100.0   // 100mbar

uint32_t prev = 0; 
const uint32_t interval = 5000;

void setup()
{
    delay(200);            // my particular board needs this
    Serial.begin(9600);
    Wire.begin();
    Wire.setClock(200000);
}

void loop()
{
    unsigned long now = millis();
    struct cs_raw ps;
    char p_str[10], t_str[10];
    uint8_t el;
    float p, t;
    if ((now - prev > interval) && (Serial.available() <= 0)) {
        prev = now;
        el = ps_get_raw(SLAVE_ADDR, &ps);
        // for some reason my chip triggers a diagnostic fault
        // on 50% of powerups without a notable impact 
        // to the output values.
        if ( el == 4 ) {
            Serial.println("err sensor missing");
        } else {
            if ( el == 3 ) {
                Serial.print("err diagnostic fault ");
                Serial.println(ps.status, BIN);
            }
            if ( el == 2 ) {
                // if data has already been feched since the last
                // measurement cycle
                Serial.print("warn stale data ");
                Serial.println(ps.status, BIN);
            }
            if ( el == 1 ) {
                // chip in command mode
                // no clue how to end up here
                Serial.print("warn command mode ");
                Serial.println(ps.status, BIN);
            }
            Serial.print("status      ");
            Serial.println(ps.status, BIN);
            Serial.print("bridge_data ");
            Serial.println(ps.bridge_data, DEC);
            Serial.print("temp_data   ");
            Serial.println(ps.temperature_data, DEC);
            Serial.println("");
            ps_convert(ps, &p, &t, PRESSURE_MIN,
                   PRESSURE_MAX);
     
            Serial.print("pressure    (mbar) ");
            Serial.println(p,2);
            Serial.print("temperature (dC) ");
            Serial.println(t,2);
            Serial.println("");
        }
    }
}
