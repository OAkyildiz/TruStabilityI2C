#ifndef __hsc_ssc_i2c_h_
#define __hsc_ssc_i2c_h_

#include <Arduino.h>
#define OUTPUT_MIN 0x0666        // 10%
#define OUTPUT_MAX 0x3999  

#define ERROR_NO_DEVICE 4
#define STATUS_DIAGNOSTIC_FAULT 3
#define STATUS_STALE 2
#define STATUS_COMMAND 1
#define STATUS_OK 0
#define REPORT_LENGTH 23

//TODO: Own raw data as union of unit32, 16, and 8
struct cs_raw {
    
    uint8_t status;             // 2 bit
    uint16_t bridge_data;       // 14 bit
    uint16_t temperature_data;  // 11 bit
};

//TODO: constructor to init from part no.
/// function that requests raw data from the sensor via i2c
///
/// input
///  slave_addr    - i2c slave addr of the sensor chip
///
/// output
///  raw           - struct containing 4 bytes of read data
///
/// returns
///         0 if all is fine
///         1 if chip is in command mode
///         2 if old data is being read
///         3 if a diagnostic fault is triggered in the chip
///         4 if the sensor is not hooked up
uint8_t ps_get_raw(const uint8_t slave_addr, struct cs_raw *raw);

/// function that converts raw data read from the sensor into temperature and pressure values
///
/// input:
///  raw            - struct containing all 4 bytes read from the sensor
///  output_min     - output at minimal calibrated pressure (counts)
///  output_max     - output at maximum calibrated pressure (counts)
///  pressure_min   - minimal value of pressure range
///  pressure_max   - maxium value of pressure range
///
/// output:
///  pressure
///  temperature
//TODO: separate conversion
uint8_t ps_convert(const struct cs_raw raw, float *pressure, float *temperature,
                   const float pressure_min, const float pressure_max);

void ps_report(char *rep, const uint8_t status);

#endif
