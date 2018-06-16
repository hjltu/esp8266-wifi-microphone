# esp8266-wifi-microphone

**esp8266-wifi-mic.ino** - Arduino IDE file for esp8266,
nodemcu or wemos d1 mini
**conv.sh** - file for converting raw audio in wav 16bit and
send to Yandex SpeechKit Cloud and receiving text
**test16.wav** - sample

The microphone(max4466) is connected to A0 in esp8266
esp8266 transmit raw audio to MQTT server.
conv.sh converting audio and with yandex speechkit getting text.
