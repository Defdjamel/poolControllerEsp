 #define BLYNK_PRINT Serial
 #define BLYNK_TEMPLATE_ID "TMPL5SBIKrCyr"
#define BLYNK_TEMPLATE_NAME "Pool Controller"
#define BLYNK_DEVICE NAME "ESP32_S1"
 #define BLYNK_AUTH_TOKEN "E4I5fTOZjOggStL57OhplNxTd0oHZqyV"
#define BLYNK_FIRMWARE_VERSION        "0.2.0"

#include <BlynkSimpleEsp32.h>
#include "events/EventsManager.h"
#define PH_VAL V0
#define TEMP_WATER V1
#define PH_DOSAGE V2
#define ORP_VAL V3
#define ORP_DOSAGE V4


BLYNK_WRITE(TEMP_WATER)
{
  // Local variable `value` stores the incoming LED switch state (1 or 0)
  // Based on this value, the physical LED on the board will be on or off:
    String value = param.asString();
    // phAuto = value;

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
    Blynk.syncVirtual(TEMP_WATER);
     Blynk.syncVirtual(ORP_DOSAGE);
   
}