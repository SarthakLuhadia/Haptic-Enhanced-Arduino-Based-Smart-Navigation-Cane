#include <SoftwareSerial.h>
#include <TinyGPS.h>

const int trig = 7;
const int echo = 8;
const int buzzer = 2;
const int vibration = 3;

SoftwareSerial mySerial(0, 1); // RX, TX
TinyGPS gps;

unsigned long previousMillis = 0;
const long interval = 5000; // Interval to read GPS data (5 seconds)
unsigned long ultrasonicPreviousMillis = 0;
const long ultrasonicInterval = 100; // Interval to read ultrasonic sensor (100 milliseconds)

void gpsdump(TinyGPS &gps);
void printFloat(double f, int digits = 2);

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(vibration, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  // Read ultrasonic sensor
  if (currentMillis - ultrasonicPreviousMillis >= ultrasonicInterval) {
    ultrasonicPreviousMillis = currentMillis;

    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    int duration = pulseIn(echo, HIGH);
    int distance = duration * 0.034 / 2;

    Serial.println(distance);

    if (distance < 50) {
      tone(buzzer, 400, 25);
      digitalWrite(vibration, HIGH);
    } else {
      tone(buzzer, 0, 25);
      digitalWrite(vibration, LOW);
    }
  }

  // Read GPS data
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    bool newdata = false;
    while (mySerial.available()) {
      char c = mySerial.read();
      if (gps.encode(c)) {
        newdata = true;
      }
    }

    if (newdata) {
      Serial.println("Acquired Data");
      Serial.println("-------------");
      gpsdump(gps);
      Serial.println("-------------");
      Serial.println();
    }
  }
}

void gpsdump(TinyGPS &gps) {
  long lat, lon;
  float flat, flon;
  unsigned long age, date, time, chars;
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned short sentences, failed;

  gps.get_position(&lat, &lon, &age);
  Serial.print("Lat/Long(10^-5 deg): "); Serial.print(lat); Serial.print(", "); Serial.print(lon); 
  Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");
  
  // On Arduino, GPS characters may be lost during lengthy Serial.print()
  // On Teensy, Serial prints to USB, which has large output buffering and
  //   runs very fast, so it's not necessary to worry about missing 4800
  //   baud GPS characters.

  gps.f_get_position(&flat, &flon, &age);
  Serial.print("Lat/Long(float): "); printFloat(flat, 5); Serial.print(", "); printFloat(flon, 5);
  Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");

  gps.get_datetime(&date, &time, &age);
  Serial.print("Date(ddmmyy): "); Serial.print(date); Serial.print(" Time(hhmmsscc): ");
    Serial.print(time);
  Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");

  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  Serial.print("Date: "); Serial.print(static_cast<int>(month)); Serial.print("/"); 
    Serial.print(static_cast<int>(day)); Serial.print("/"); Serial.print(year);
  Serial.print("  Time: "); Serial.print(static_cast<int>(hour)); Serial.print(":"); 
    Serial.print(static_cast<int>(minute)); Serial.print(":"); Serial.print(static_cast<int>(second));
    Serial.print("."); Serial.print(static_cast<int>(hundredths));
  Serial.print("  Fix age: ");  Serial.print(age); Serial.println("ms.");

  Serial.print("Alt(cm): "); Serial.print(gps.altitude()); Serial.print(" Course(10^-2 deg): ");
    Serial.print(gps.course()); Serial.print(" Speed(10^-2 knots): "); Serial.println(gps.speed());
  Serial.print("Alt(float): "); printFloat(gps.f_altitude()); Serial.print(" Course(float): ");
    printFloat(gps.f_course()); Serial.println();
  Serial.print("Speed(knots): "); printFloat(gps.f_speed_knots()); Serial.print(" (mph): ");
    printFloat(gps.f_speed_mph());
  Serial.print(" (mps): "); printFloat(gps.f_speed_mps()); Serial.print(" (kmph): ");
    printFloat(gps.f_speed_kmph()); Serial.println();

  gps.stats(&chars, &sentences, &failed);
  Serial.print("Stats: characters: "); Serial.print(chars); Serial.print(" sentences: ");
    Serial.print(sentences); Serial.print(" failed checksum: "); Serial.println(failed);
}

void printFloat(double number, int digits) {
  // Handle negative numbers
  if (number < 0.0) {
     Serial.print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  Serial.print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    Serial.print("."); 

  // Extract digits from the remainder one at a time
  while (digits-- > 0) {
    remainder *= 10.0;
    int toPrint = int(remainder);
    Serial.print(toPrint);
    remainder -= toPrint;
  }
}
