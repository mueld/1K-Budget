#include "Parking.h"
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include "Webserver.h"

void Webserver::sending()
{       
        Summery(SendState, Cubes);
        SendDebugMessage("Get-Request:");
        SendDebugMessage(Send);
        Client_->get(Send);
        Send = "";
        while (Client_->available())
        {
            Response = Client_->responseBody();
        }
        SendDebugMessage("Get response:");
        SendDebugMessage(Response);
}
void Webserver::Setup(Processstate &SendState, int &Cubes, HttpClient *Client_, ToF *sensors, DrivesController *Controller)
{
    this->SendState = (int)SendState;
    this->Cubes = Cubes;
    this->Client_ = Client_;
    Errors[0] = sensors;
    Errors[1] = Controller;
    while (WifiState != WL_CONNECTED)
    {
        WifiState = WiFi.begin("ZbW-IoT", "zbwzbw");
        SendDebugMessage("Try to Connect with WIFI");
        delay(10000);
    }
    Serial.println("Connect to WiFi");

}
void Webserver::Summery(const Processstate SendState, const int Cubes)
{
    String send_[4] = {"http://192.168.1.112/save_data.php?State=","","&Cubes=",""};
    send_[1] = String(SendState);
    send_[3] = String(Cubes);
    for (int i = 0; i < 4; i++)
    {
         Send +=send_[i];
    }
}
bool Webserver::ReadStart()
{
    if(Response == "1")
    {
        return true;
    }
    return false;
}