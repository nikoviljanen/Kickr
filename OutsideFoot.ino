void FootOutside()
{
  // Tarkastetaan onko nykyinen näyte suurempi kuin edellinen arvo ynnä ennalta määritelty herkkyys
  // Tällä varmistetaan, että kyseessä on nopea painepiikki
  if(!peakEQC)
  {
    if (currentSampleC > previousSampleC + sensitivityO)
    { 
      // Serial.print("t");
      // Tässä vaiheessa ei voida olla vielä varmoja onko kyseessä nopea piikkimäinen isku, joten nykyinen anturiarvo sijoitetaan maybeSampleen lisävertailua varten
      maybeSampleC = currentSampleC;
      // peakSwitch kytkekään päälle ja se ilmoittaa, että piikki on mahdollisesti tunnistettu
      peakSwitchC = true;    
    }
  }
  // Seuraavaksi tutkitaan laskeeko piikki nopeasti alas
  if(peakSwitchC)
  {
    // Piikillä on tietty aika tippua alas ja se aika lasketaan peakTimerilla
    // Jos piikki ei ole tietyssä ajassa tippunut alas, ei kyseessä ole enää voimakas piikki
    peakTimerC++;
    
    // Kuunnellaan piikin tippumista
    if(peakTimerC<8)
    { 
      //Serial.print("o");
      //Jos maybeSample, eli tällä hetkellä se arvo, joka saattaa olla lähellä piikin huippuarvoa, on isompi kuin nykyinen näyte ja herkkyys:
      //voidaan olettaa että anturiarvo on noussut ja laskenut voimakkaasti 5-10 millisekunnin sisällä, jolloin se tulkitaan pallokosketukseksi
      if(maybeSampleC > currentSampleC + sensitivityO)
      {
        TcounterC++;
        Tcounter2C = TcounterC + Tcounter2C;
        Serial.print("#");
        Serial.print("o");
        Serial.print("+");
        mySerial.print("#");
        mySerial.print("o");
        mySerial.print("+");
       
      /*Serial.print(Tcounter2);
        Serial.print(",");
        Serial.print(peakTimer);
        Serial.print(",");
        Serial.print(maybeSample);*/
        maybeSampleC = 0;
        TcounterC = 0;
        peakSwitchC = false;
        peakTimerC = 0;
        // noNull = true;
        peakEQC = true;
      }
    }    
  }
  
  // Kun mahdollinen piikki tunnistetaan sillä on viisi näyettä aikaa laskea alas, jotta se voidaan tulkita piikiksi
   if(peakTimerC>=8)
    {
      peakTimerC = 0;
      peakSwitchC = false;
    }
    
    if(peakEQC)
    {
      peakEQTimerC++;
      if(peakEQTimerC >= 50)
      {
        peakEQTimerC = 0;
        peakEQC = false;
      }
    }
    
    
    
}
