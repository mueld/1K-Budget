#include "Parking.h"
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include "Webserver.h"

void Webserver::sending()
{
        Summery(SendState, Cubes);
        Serial.println(Send);
        Client_->get(Send);
        Send = "";
        while (Client_->available())
        {
            buffer = Client_->read();
        }
}
void Webserver::Setup(Processstate &SendState, int &Cubes, HttpClient *Client_, ToF *sensors, DrivesController *Controller)
{
    this->SendState = (int)SendState;
    this->Cubes = Cubes;
    this->Client_ = Client_;
    Errors[0] = sensors;
    Errors[1] = Controller;
}
void Webserver::Summery(const Processstate SendState, const int Cubes)
{
    String send_[4] = {"http://192.168.1.111/index.php?Cubes=","","?State=",""};
    send_[1] = String(Cubes);
    send_[3] = String(SendState);
    for (int i = 0; i < 4; i++)
    {
         Send +=send_[i];
    }
}
bool Webserver::ReadStart()
{
    if(buffer == "1")
    {
        return true;
    }
    return false;
}