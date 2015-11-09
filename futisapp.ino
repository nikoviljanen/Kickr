#include <SoftwareSerial.h>
SoftwareSerial mySerial(6,5); //RX,TX 

int Apin = A0;
int sensorReading;
int sensorVoltage; 
unsigned long sensorResistance;
unsigned long sensorConductance;

int Bpin = A1;
int sensorReading2;
int sensorVoltage2; 
unsigned long sensorResistance2;
unsigned long sensorConductance2;

int Cpin = A2;
int sensorReading3;
int sensorVoltage3; 
unsigned long sensorResistance3;
unsigned long sensorConductance3;

int Dpin = A3;
int sensorReading4;
int sensorVoltage4; 
unsigned long sensorResistance4;
unsigned long sensorConductance4;


int Aint;
int Bint;
int Cint;
int Dint;
int sensitivityT = 8;
int sensitivityI = 10;
int sensitivityO = 10;

//muuttujat näytteille
int currentSampleA = 0;
int currentSampleB = 0;
int currentSampleC = 0;
int currentSampleD = 0;
int previousSampleA = 0;
int previousSampleB = 0;
int previousSampleC = 0;
int previousSampleD = 0;
int maybeSampleA = 0;
int maybeSampleB = 0;
int maybeSampleC = 0;
int maybeStep = 0;

int TcounterA = 0;
int Tcounter2A = 0;
int TcounterB = 0;
int Tcounter2B = 0;
int TcounterC = 0;
int Tcounter2C = 0;
int Scounter = 0;
int Scounter2 = 0;


boolean peakSwitchA = false;
boolean peakSwitchB = false;
boolean peakSwitchC = false;
boolean stepWatch = false;

int peakTimerA = 0;
int peakTimerB = 0;
int peakTimerC = 0;
int stepTimer = 0;

boolean peakEQA = false;
boolean peakEQB = false;
boolean peakEQC = false;

int peakEQTimerA = 0;
int peakEQTimerB = 0;
int peakEQTimerC = 0;

boolean noNull = false;

int stepEqualizer = 300;
//int peakEqualizer = 200;
int stepSensitivity = 40;

int incomingByte = 0;
int      calibrationValue = 0;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(115200);

  Serial.println("Aloitetaan...");
 
  Serial.println("1");
  delay(1000);
   /* Serial.println("1");
    delay(1000);*/
    mySerial.begin(9600);
}


void loop()
{
  
    if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();
                calibrationValue = sensorConductance;
                // say what you got:
                Serial.print("I received: ");
                Serial.print(sensorReading);
 Serial.print(",");
                Serial.println(Aint);
   }
     if (mySerial.available() > 0) {
                // read the incoming byte:
                incomingByte = mySerial.read();
                calibrationValue = sensorConductance;
                // say what you got:
                mySerial.print("I received: ");
                Serial.println(incomingByte, DEC);
        }

      // Luetaan sensoridata 
      sensorReading = analogRead(Bpin); //jalkapöytä
      sensorVoltage = map(sensorReading, 0, 1023, 0, 3300);

      sensorReading2 = analogRead(Cpin); //sisä
      sensorVoltage2 = map(sensorReading2, 0, 1023, 0, 3300);
  
      sensorReading3 = analogRead(Dpin); //ulko
      sensorVoltage3 = map(sensorReading3, 0, 1023, 0, 3300);
      
      sensorReading4 = analogRead(Apin); //askel
      sensorVoltage4 = map(sensorReading4, 0, 1023, 0, 3300);


    // Jännite = Vcc * R / (R + FSR) jossa R = 1K ja Vcc = 3,3V
    // joten sensorResistance = ((Vcc - V) * R) / V       
    sensorResistance = 3300 - sensorVoltage;     // fsrVoltage on millivoltteina
    sensorResistance *= 1000;                // 1K vastus jännitteenjakajassa
    sensorResistance /= sensorVoltage;

    sensorResistance2 = 3300 - sensorVoltage2;    
    sensorResistance2 *= 1000;                
    sensorResistance2 /= sensorVoltage2;
    
    sensorResistance3 = 3300 - sensorVoltage3;     
    sensorResistance3 *= 1000;                
    sensorResistance3 /= sensorVoltage3;
    
    sensorResistance4 = 3300 - sensorVoltage4;     
    sensorResistance4 *= 1000;                
    sensorResistance4 /= sensorVoltage4;
    
    // mhos:it mitataan mikromhos:na joten:
    sensorConductance = 1000000;           
    sensorConductance /= sensorResistance;
    sensorConductance = constrain(map(sensorConductance,0,20000,0,(100 + calibrationValue)),0,(100 + calibrationValue));
    Aint = map(sensorConductance, calibrationValue, (100 + calibrationValue), 0 ,100);
    Aint = constrain(Aint,0,100);
    
    sensorConductance2 = 1000000;            
    sensorConductance2 /= sensorResistance2;
    sensorConductance2 = constrain(map(sensorConductance2,0,15000,0,100),0,100);
    
    sensorConductance3 = 1000000;          
    sensorConductance3 /= sensorResistance3;
    sensorConductance3 = constrain(map(sensorConductance3,0,7000,0,100),0,100); 
    
    sensorConductance4 = 1000000;          
    sensorConductance4 /= sensorResistance4;
    sensorConductance4 = constrain(map(sensorConductance4,0,7000,0,100),0,100); 
    
    //syötetään anturiarvot uusiin muuttujiin
    // Aint = sensorConductance; //pöytä
    Bint = sensorConductance2; //ulko
    Cint = sensorConductance3; //sisä
    Dint = sensorConductance4; //askel
      
    // Nykyinen anturiarvo sijoitetaan muuttujaan currentSample
    currentSampleA = Aint;
    currentSampleB = Bint;
    currentSampleC = Cint;
    currentSampleD = Dint;
   
    // FootInside => aliohjelma, joka tunnistaa sisäsyrjäkosketukset
    FootInside(); 
    // FootTop => aliohjelma, joka tunnistaa jalkapöytäkosketukset  
    FootTop();
    // FootOutside => aliohjelma, joka tunnistaa ulkosyrjäkosketukset
    FootOutside();
    // StepCounter = aliohjelma, joka tunnistaa käyttäjän askeleet 
    StepCounter();
    /*Serial.print(currentSampleB);
    Serial.print(",");
    Serial.print(previousSampleB);
    Serial.print(",");
    Serial.println(i);*/
   
    // Syötetään "vanhat" anturiarvot previousSample -muuttujiin, jotta sitä voidaan verrata seuraavalla kierroksella tuoreisiin anturilukemiin
    previousSampleA = currentSampleA;
    previousSampleB = currentSampleB;
    previousSampleC = currentSampleC;
    previousSampleD = currentSampleD;

}
