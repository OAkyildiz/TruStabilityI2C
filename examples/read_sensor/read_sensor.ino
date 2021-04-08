
#include <Wire.h>
#include "TruStabilityI2C.h"

// see hsc_ssc_i2c.h for a description of these values
// these defaults are valid for the HSCMRNN030PA2A3 chip
#define SLAVE_ADDR 0x28
     // 90% of 2^14 - 1
#define PRESSURE_MIN 0.0        // min is 0 for sensors that give absolute values
#define PRESSURE_MAX 100.0   // 100mbar

#define T_STEP 1000

uint32_t prev = 0; 


void setup()
{
    delay(200);            // my particular board needs this
    Serial.begin(9600);
    Wire.begin();
    Wire.setClock(200000);
}

void loop()
{
    static struct cs_raw ps;
    static char p_str[10], t_str[10];
    static uint8_t el;
    static float p, t;

    el = ps_get_raw(SLAVE_ADDR, &ps);
    // for some reason my chip triggers a diagnostic fault
    // on 50% of powerups without a notable impact 
    // to the output values.
    // TODO: put rep into the library
    static char rep[23];
    ps_report(rep, el);
    Serial.println(rep);

    if (el< ERROR_NO_DEVICE){
        Serial.println("status | bridge | temp");
        Serial.print("     "); Serial.print(ps.status, BIN);
        Serial.print("     "); Serial.print(ps.bridge_data, DEC);
        Serial.print("     "); Serial.println(ps.temperature_data, DEC);
        Serial.println("");

        ps_convert(ps, &p, &t, PRESSURE_MIN,
                PRESSURE_MAX);
    
        Serial.print("P: ");
        Serial.print(p,2);
        Serial.println("mbar");
        Serial.print("T: ");
        Serial.print(t,2);
        Serial.println("°C");
        Serial.println("");
        }

        delay(T_STEP);
}
