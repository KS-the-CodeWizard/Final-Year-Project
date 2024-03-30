#include "BluetoothA2DPSink.h"

BluetoothA2DPSink a2dp_sink;


// Define I2S connections
// #define I2S_DOUT  22
// #define I2S_BCLK  26
// #define I2S_LRC   25
// //Alter
// #define I2S_DOUT 25
// #define I2S_BCLK 27
// #define I2S_LRC  26

void setup() {
    i2s_pin_config_t my_pin_config = {
        .mck_io_num = I2S_PIN_NO_CHANGE,
        .bck_io_num = 27,
        .ws_io_num = 26,
        .data_out_num = 25,
        .data_in_num = I2S_PIN_NO_CHANGE
    };
    a2dp_sink.set_pin_config(my_pin_config);
    a2dp_sink.start("MyMusic");
}

void loop() {
}
