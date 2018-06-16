# esp8266-wifi-microphone

Project name: esp8266-wifi-microphone
Copyright (C) 2018  hjltu@ya.ru

esp8266-wifi-microphone is free software: you can redistribute
it and/or modifyit under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

esp8266-wifi-microphone is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

esp8266-wifi-mic.ino - Arduino IDE file for esp8266,nodemcu or wemos d1 mini
conv.sh - file for converting raw audio in wav 16bit and send to Yandex SpeechKit Cloud and receiving text
test16.wav - sample

The microphone(max4466) is connected to A0 in esp8266
esp8266 transmit raw audio to MQTT server.
conv.sh converting audio and with yandex speechkit getting text.
