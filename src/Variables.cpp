#include "Variables.h"
#include "FirstRound.h"
#include <EEPROM.h>

void EncoderTraceA_Linear()
{
    n = digitalRead(EncoderPinA_L);
    if ((encoder0PinALast == LOW) && (n == HIGH))
    {
        if (m == LOW)
        {
            Encoder_L--;
        }
        else
        {
            Encoder_L++;
        }
    }
}