/*arduino, Katyusha
*/
 
#include "pitches.h"

//notHuruf:
int melody[] = {
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, 
  NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_B4, NOTE_D5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, 
  NOTE_E5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_E5, 
  NOTE_A4, NOTE_F5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_C5, NOTE_B4, NOTE_A4, 
  NOTE_E5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_E5, 
  NOTE_A4, NOTE_F5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_C5, NOTE_B4, NOTE_A4,
  0,
};

//durasiNot
int noteDurations[] = {
  2, 4, 2, 4, 5, 4, 5, 5, 2, 
  3, 2, 4, 2, 4, 5, 4, 5, 5, 2, 
  4, 3, 4, 5, 5, 6, 6, 6, 5, 3, 
  3, 4, 5, 3, 7, 5, 6, 7, 7, 2, 
  4, 3, 4, 5, 5, 6, 6, 6, 5, 3, 
  3, 4, 5, 3, 7, 5, 6, 7, 7, 2, 
  
  
};

void setup(){

  //StartBeep
  noTone(2);
  delay(2000);
  tone(2, 2000);
  delay(200);
  noTone(2);
  delay(1000); 
   
  //iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {

    /*
      to calculate the note duration, take one second divided by the note type.
      e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
     */
    int noteDuration = 1000/noteDurations[thisNote];
    tone(2, melody[thisNote],noteDuration);

    /*
      to distinguish the notes, set a minimum time between them.
      the note's duration + 30% seems to work well:
     */
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(2); //stop the tone playing:
  }
  digitalWrite(3,LOW);
}

void loop(){ /*press reset to replay. */ }
