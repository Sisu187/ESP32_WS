#include <Arduino.h>
#include <DHT.h>
const int DHT_PIN = 22;                // aus der Pintabelle
const int LED_PIN = 5;                // aus der Pintabelle
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
      Serial.println("Error: Temperature or Humidity is NaN");
    }
    else
    {
      float temperature = dht.readTemperature(false);
      float humidity = dht.readHumidity();

      Serial.printf("Temperature: %.2f°C, Humidity: %.2f%%\n", temperature, humidity);

      if(humidity >= GRENZWERT_FEUCHTE) {
        REG_WRITE(GPIO_OUT_W1TS_REG, 1UL << LED_PIN);
      }
      else {
        REG_WRITE(GPIO_OUT_W1TC_REG, 1UL << LED_PIN);

      }
    }
  }
}