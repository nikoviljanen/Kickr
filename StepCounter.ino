//stepEqualizer = 200, aika, jolloin ei voi tulla uusia askeleita

void StepCounter()
{
  // Jos jalkapohja-anturi ylittää alaraja-arvon ja edellinen näyte on alle alaraja-arvon
  // eli tutkitaan onko anturin arvo kasvamassa ja ylittääkö se tietyn voimarajan
  if(currentSampleD >= stepSensitivity && previousSampleD < stepSensitivity)
  {
   // Laskuri i rupeaa laskemaan ja sillä varmistetaan ettei anturiarvon huojunnasta tule yhtä useampaa askelta nopeassa ajassa
   stepTimer++;
   
    if(stepTimer<2)
     { 
      //Tulostetaan askel, jos nämä ehdot täyttyvät
      Serial.print("#");
      Serial.print("s");
      Serial.print("+");
      mySerial.print("#");
      mySerial.print("s");
      mySerial.print("+");
      // Serial.print(previousSampleD);
      // stepWatch muuttuu trueksi, jos askel toteutuu
      stepWatch = true;
     }
  }
  
  if(stepWatch)
  {
    // Laskuri i:hin lisätään summaa, kunnes se saavuttaa stepEqualizerin arvon
    // stepEqualizerin arvoa muuttamalla voidaan säädellä, kuinka pitkään laskuri i estää anturiarvon huojunnasta johtuvan virheellisen askeltulkinnan
   stepTimer++;
  
    if(stepTimer>=stepEqualizer)
      {
        stepTimer=0;
        stepWatch = false;
      }
  }
}
