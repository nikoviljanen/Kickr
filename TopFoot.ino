//FootTop -aliohjelmalla tunnistetaan jalkapöytään tulevat pallokosketukset
//Aliohjelman toiminta perustuu siihen, että pallon kontaktiaika palloon on noin 5-10 millisekunttia
//Aliohjelma tunnistaa nämä nopeat painepiikit antureista
//Vastaavanlaisia painepiikkejä ei yleisesti ottaen voi muusta jalan toiminnasta tulla

void FootTop()
{
  // Tarkastetaan onko nykyinen näyte suurempi kuin edellinen arvo ynnä ennalta määritelty herkkyys
  // Tällä varmistetaan, että kyseessä on nopea painepiikki
  if(!peakEQA)
  {
    if (currentSampleA > previousSampleA + sensitivityT)
    {
      // Serial.print("t");
      // Tässä vaiheessa ei voida olla vielä varmoja onko kyseessä nopea piikkimäinen isku, joten nykyinen anturiarvo sijoitetaan maybeSampleen lisävertailua varten
      maybeSampleA = currentSampleA;
      // peakSwitch kytkekään päälle ja se ilmoittaa, että piikki on mahdollisesti tunnistettu
      peakSwitchA = true;
          
    }
  }
  // Seuraavaksi tutkitaan laskeeko piikki nopeasti alas
  if(peakSwitchA)
  {
    // Piikillä on tietty aika tippua alas ja se aika lasketaan peakTimerilla
    // Jos piikki ei ole tietyssä ajassa tippunut alas, ei kyseessä ole enää voimakas piikki
    peakTimerA++;
    
    // Kuunnellaan piikin tippumista
    if(peakTimerA<8)
    {
      // Serial.print("o");
      // Jos maybeSample, eli tällä hetkellä se arvo, joka saattaa olla lähellä piikin huippuarvoa, on isompi kuin nykyinen näyte ja herkkyys:
      // Voidaan olettaa että anturiarvo on noussut ja laskenut voimakkaasti 5-10 millisekunnin sisällä, jolloin se tulkitaan pallokosketukseksi
      if(maybeSampleA > currentSampleA + sensitivityT)
      {
        TcounterA++;
        Tcounter2A = TcounterA + Tcounter2A;
        Serial.print("#");
        Serial.print("t");
        Serial.print("+");
        mySerial.print("#");
        mySerial.print("t");
        mySerial.print("+");
       
      /*Serial.print(Tcounter2);
        Serial.print(",");
        Serial.print(peakTimer);
        Serial.print(",");
        Serial.print(maybeSample);*/
        maybeSampleA = 0;
        TcounterA = 0;
        peakSwitchA = false;
        peakTimerA=0;
        noNull = true;
        peakEQA = true;
      }
    }    
  }
  // Kun mahdollinen piikki tunnistetaan sillä on viisi näyettä aikaa laskea alas, jotta se voidaan tulkita piikiksi
   if(peakTimerA>=8)
    {
      peakTimerA = 0;
      peakSwitchA = false;
    }
    
      if(peakEQA)
      {
        peakEQTimerA++;
        
        if(peakEQTimerA >= 50)
        {
          peakEQTimerA = 0;
          peakEQA = false;
        }
      }
      
      
    // Debuggausta varten
    /*if(noNull)
    {
       Serial.print(",");
    Serial.println(Aint);
    noNull=false; 
    }
    else
    {
     Serial.print("0");
    Serial.print(",");
     Serial.print("0");
    Serial.print(",");
    Serial.print("0");
    Serial.print(",");
    Serial.println(Aint); 
    }
  */
}
  

