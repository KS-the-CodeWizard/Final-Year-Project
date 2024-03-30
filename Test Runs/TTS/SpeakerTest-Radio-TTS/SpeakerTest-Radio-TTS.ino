#include <Audio.h>



#include <Arduino.h>
#include <WiFi.h>


// Define I2S connections Alternative
// #define I2S_DOUT  22
// #define I2S_BCLK  26
// #define I2S_LRC   25


#define I2S_DOUT 25
#define I2S_BCLK 27
#define I2S_LRC  26

Audio audio;


void setup()
{

  Serial.begin(115200);

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin( "Galaxy F22 E9F4", "KS1234321");

  while (WiFi.status() != WL_CONNECTED)
    delay(1500);

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(100);
  // audio.connecttospeech("Play Music", "en"); // Google TTS
  // delay(1000);
  audio.connecttohost("https://ks-the-codewizard.github.io/Audio-player/RIMJHIM%20gire.mp3");//Internet Radio
}


void loop()

{
  audio.loop();
}

void audio_info(const char *info) {
  Serial.print("audio_info: "); Serial.println(info);
}