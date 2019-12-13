#include "Parking.h"
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include "Webserver.h"

void Webserver::sending()
{
        Summery(SendState, Cubes);
        Serial.println(Send);
        Client_->get(Send);
}
void Webserver::Setup(Processstate &SendState, int &Cubes, HttpClient *Client_)
{
    this->SendState = (int)SendState;
    this->Cubes = Cubes;
    this->Client_ = Client_;

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