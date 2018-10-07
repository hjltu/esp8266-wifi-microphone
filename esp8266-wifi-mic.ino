// Project name: hjhome
// Copyright (C) 2016  hjltu@ya.ru
// https://launchpad.net/hjhome

// hjhome is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// hjhome is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

	//	FOR esp-07	//

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid =  "hj-dir-300";
const char *pass =  "9090068900";

WiFiClient wclient;
IPAddress mqtt_server(192,168,0,20);
PubSubClient client(wclient, mqtt_server);

//	client name
String str_name="esp1";

String str_topic = String("/" + str_name + "/out/stream");
String str_payload;

bool bt;
byte rec;
int count;

void setup()
{
	Serial.begin(115200);
	Serial.println(0);			//start
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, pass);
	pinMode(4,INPUT_PULLUP);	//	bt
	pinMode(2,OUTPUT);			//	led
	delay(3000);
}

void loop()
{
	my_connect();
	if(client.connected())
	{
		my_button();
		my_analog();
	}

}

void my_connect()
{
	if (WiFi.status() != WL_CONNECTED)
	{
		Serial.println(1);			//Connecting to
		WiFi.begin(ssid, pass);

		if(WiFi.waitForConnectResult() != WL_CONNECTED)
		{
			Serial.println(2);		//WiFi NOT connected
			if(digitalRead(2)==LOW)
				digitalWrite(2,HIGH);
			return;
		}
		Serial.println(3);			//WiFi connected
	}
	if(WiFi.status() == WL_CONNECTED)
	{
		if(!client.connected())
		{
			Serial.println(4);				//Connecting to MQTT server
			if(client.connect(str_name))
			{
				Serial.println(5);				//Connected to MQTT server
				client.set_callback(callback);
				client.subscribe("/" + str_name + "/#");
			}
			else
			{
				Serial.println(6);		//Could not connect to MQTT server
				if(digitalRead(2)==LOW)
					digitalWrite(2,HIGH);
			}
		}
		if(client.connected())
		{
			client.loop();
			if(digitalRead(2)==HIGH)
				digitalWrite(2,LOW);
		}
	}
}

void callback(const MQTT::Publish& pub)
{
	String inc_topic = pub.topic();
	String inc_payload = pub.payload_string();
	
	if(inc_topic.indexOf("/in")>0)
	{
		Serial.println(F("incoming"));
		if(inc_topic.indexOf("/led")>0)
		{
			if(inc_payload=="0" || inc_payload=="false" || inc_payload=="OFF")
				if(bt==false)
					bt=true;
		}
	}
}

void my_print()
{
	client.publish(str_topic,str_payload);
	str_payload="";
}

void my_button()
{
	if(digitalRead(4)==LOW && count<15)
		count++;
	if(digitalRead(4)==HIGH && count>0)
		count--;
	if(count>10 && bt==false)
		bt=true;
	if(count==0 && bt==true)
		bt=false;
}

void my_analog()
{
	if(bt==true)
	{
		if(digitalRead(2)==LOW)
			digitalWrite(2,HIGH);
		my_record();
	}
}

void my_record()
{
	bt=false;
	for(int y=0;y<31;y++)
	{
		for(int i=0;i<1000;i++)
		{
			str_payload += char(analogRead(A0)/4);
		}
	my_print();
	}
	if(digitalRead(2)==HIGH)
		digitalWrite(2,LOW);
}
