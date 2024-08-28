 #define BLYNK_PRINT Serial
 #define BLYNK_TEMPLATE_ID "TMPL5SBIKrCyr"
#define BLYNK_TEMPLATE_NAME "Pool Controller"
#define BLYNK_DEVICE NAME "ESP32 QA"
 #define BLYNK_AUTH_TOKEN "E4I5fTOZjOggStL57OhplNxTd0oHZqyV"
#define BLYNK_FIRMWARE_VERSION        "0.2.0"

#include <BlynkSimpleEsp32.h>
#include "events/EventsManager.h"
#define PH_VAL V0
#define PH_FORCE V1
#define PH_DOSAGE V2
#define ORP_VAL V3
#define ORP_DOSAGE V4

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
    phAuto = value;

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

BLYNK_WRITE(ORP_DOSAGE)
{
  // Local variable `value` stores the incoming LED switch state (1 or 0)
  // Based on this value, the physical LED on the board will be on or off:
  double value = param.asDouble();

    orpDosage = value;
  Serial.print("ORP_DOSAGE value =");
    Serial.println(value);
     EventsManager::shared().callEvent(EVENT_STATE_PH_AUTO);
}



BLYNK_CONNECTED() {
     Serial.print(" Blynk.syncAll()");
    Blynk.syncAll();
    Blynk.syncVirtual(PH_DOSAGE);
    Blynk.syncVirtual(PH_FORCE);
     Blynk.syncVirtual(ORP_DOSAGE);
   
}