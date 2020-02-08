
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include "Webserver.h"

void Webserver::sending()
{       
        Summery(SendState, Cubes);
        Client_->get(Send);
        Send = "";
        while (Client_->available())
        {
            Response = Client_->responseBody();
        }
        Serial.println(Response);
}
void Webserver::Setup(HttpClient *Client_)
{

    this->Client_ = Client_;

    while (WifiState != WL_CONNECTED)
    {
        WifiState = WiFi.begin("ZbW-IoT", "gargamel");
        delay(10000);
    }
    Serial.println("Connected to WiFi");

}
void Webserver::Summery()
{
    String send_[4] = {"http://192.168.1.125/save_data.php?State=","","&Cubes=",""};
    send_[1] = String(RXBuffer[STATE_INDEX]);
    send_[3] = String(RXBuffer[CUBES_INDEX]);
    for (int i = 0; i < 4; i++)
    {
         Send +=send_[i];
    }
}
void Webserver::Reading_Serial()
{
    rxindex == 0;
    while (Serial1.available() > 0 && rxindex < sizeof(RXBuffer))
    {
        RXBuffer[rxindex] = Serial1.read();
        rxindex++;
    }
}