void FootInside()
{
  // Tarkastetaan onko nykyinen näyte suurempi kuin edellinen arvo ynnä ennalta määritelty herkkyys
  // Tällä varmistetaan, että kyseessä on nopea painepiikki
  if(!peakEQB)
  {
    if (currentSampleB > previousSampleB + sensitivityI)
    { 
      // Serial.print("t");
      // Tässä vaiheessa ei voida olla vielä varmoja onko kyseessä nopea piikkimäinen isku, joten nykyinen anturiarvo sijoitetaan maybeSampleen lisävertailua varten
      maybeSampleB = currentSampleB;
      // peakSwitch kytkekään päälle ja se ilmoittaa, että piikki on mahdollisesti tunnistettu
      peakSwitchB = true;    
    }
  }
  
  // Seuraavaksi tutkitaan laskeeko piikki nopeasti alas
  if(peakSwitchB)
  {
    // Piikillä on tietty aika tippua alas ja se aika lasketaan peakTimerilla
    // Jos piikki ei ole tietyssä ajassa tippunut alas, ei kyseessä ole enää voimakas piikki
    peakTimerB++;
    
    // Kuunnellaan piikin tippumista
    if(peakTimerB<8)
    {
      //Serial.print("o");
      //Jos maybeSample, eli tällä hetkellä se arvo, joka saattaa olla lähellä piikin huippuarvoa, on isompi kuin nykyinen näyte ja herkkyys:
      //voidaan olettaa että anturiarvo on noussut ja laskenut voimakkaasti 5-10 millisekunnin sisällä, jolloin se tulkitaan pallokosketukseksi
      if(maybeSampleB > currentSampleB + sensitivityI)
      {
        TcounterB++;
        Tcounter2B = TcounterB + Tcounter2B;
        Serial.print("#");
        Serial.print("i");
        Serial.print("+");
        mySerial.print("#");
        mySerial.print("i");
        mySerial.print("+");
       
      /*Serial.print(Tcounter2);
        Serial.print(",");
        Serial.print(peakTimer);
        Serial.print(",");
        Serial.print(maybeSample);*/
        maybeSampleB = 0;
        TcounterB = 0;
        peakSwitchB = false;
        peakTimerB=0;
        // noNull = true;
        peakEQB = true;
   
      }
    }    
  }
  
   // Kun mahdollinen piikki tunnistetaan sillä on viisi näyettä aikaa laskea alas, jotta se voidaan tulkita piikiksi
   if(peakTimerB>=8)
    {
      peakTimerB = 0;
      peakSwitchB = false;
    }
    
    if(peakEQB)
    {
      peakEQTimerB++;
      if(peakEQTimerB >= 50)
      {
        peakEQTimerB = 0;
        peakEQB = false;
      }
    }
    
   // Debuggausta varten 
   /* if(noNull)
    {
       Serial.print(",");
    Serial.println(Bint);
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
    Serial.println(Bint); 
    }*/
    
    
    
}
