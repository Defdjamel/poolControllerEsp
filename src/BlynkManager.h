
#include <BlynkSimpleEsp32.h>
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

    Serial.print("PH_FORCE value =");
    Serial.println(value);
}

BLYNK_WRITE(PH_DOSAGE)
{
  // Local variable `value` stores the incoming LED switch state (1 or 0)
  // Based on this value, the physical LED on the board will be on or off:
  int value = param.asInt();
  Serial.print("PH_DOSAGE value =");
    Serial.println(value);
}