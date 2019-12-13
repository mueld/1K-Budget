#include "Parking.h"
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include "Webserver.h"

void Webserver::Execute()
{
    switch (State)
    {
    case Webserver_openConnection:
        Client_->get("192.168.1.111/index.php?State ="+*SendState+"&Cubes ="+*Cubes);
        break;

    default:
        break;
    }
}
void Webserver::Setup(int *SendState, int *Cubes, HttpClient *Client_)
{
    this->SendState = SendState;
    this->Cubes = Cubes;
    this->Client_ = Client_;
}