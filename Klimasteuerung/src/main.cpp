#include <Arduino.h>
#include <DHT.h>
const int DHT_PIN = NULL;                // aus der Pintabelle
const int LED_PIN = NULL;                // aus der Pintabelle
const float GRENZWERT_FEUCHTE = 60.0;    // in Prozent
const unsigned long INTERVALL_MS = 2000; // der DHT22 misst höchstens alle 2 s

DHT dht(DHT_PIN, DHT22);
unsigned long letzteMessung = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();
}

void loop()
{
  if (millis() - letzteMessung >= INTERVALL_MS)
  {
    letzteMessung = millis();
    float feuchte = dht.readHumidity();
    float temperatur = dht.readTemperature();
    
    if (isnan(feuchte) || isnan(temperatur))
    {
      // TODO: Fehlermeldung ausgeben, LED aus
    }
    else
    {
      // TODO: Messwerte ausgeben
      // TODO: LED abhängig vom Grenzwert schalten
    }
  }
}