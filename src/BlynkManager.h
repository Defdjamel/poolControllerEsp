
#include <BlynkSimpleEsp32.h>
#include "events/EventsManager.h"
#define PH_VAL V1
#define PH_FORCE V1
#define PH_DOSAGE V2

BLYNK_WRITE(V0)
{
  // Local variable `value` stores the incoming LED switch state (1 or 0)
  // Based on this value, the physical LED on the board will be on or off:
  int value = param.asInt();

  if (value == 1) {
   
    Serial.print("BLYNK value =");
    Serial.println(value);
  } else {
    Serial.print("BLYNK value = ");
    Serial.println(value);
  }
}
BLYNK_WRITE(PH_FORCE)
{
  // Local variable `value` stores the incoming LED switch state (1 or 0)
  // Based on this value, the physical LED on the board will be on or off:
    int value = param.asInt();
    phAuto = ( value == 0) ? true : false;

    Serial.print("PH_FORCE value =");
    Serial.println(value);
      EventsManager::shared().callEvent(EVENT_STATE_PH_AUTO);
}

BLYNK_WRITE(PH_DOSAGE)
{
  // Local variable `value` stores the incoming LED switch state (1 or 0)
  // Based on this value, the physical LED on the board will be on or off:
  double value = param.asDouble();

    phDosage = value;
  Serial.print("PH_DOSAGE value =");
    Serial.println(value);
     EventsManager::shared().callEvent(EVENT_STATE_PH_AUTO);
}
BLYNK_CONNECTED() {
     Serial.print(" Blynk.syncAll()");
    Blynk.syncAll();
    Blynk.syncVirtual(PH_DOSAGE);
    Blynk.syncVirtual(PH_FORCE);
   
}