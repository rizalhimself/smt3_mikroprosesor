/*arduino, play despacito
*/
 
#include "pitches.h"

//notes in the melody:
int melody[] = {
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4,
  NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_B4, NOTE_D5, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_E5, NOTE_A5, NOTE_G5, NOTE_A5,
  NOTE_G5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, NOTE_F5, NOTE_D5,
  NOTE_E5, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_E5,
  0,
};

// note durations: 4 = quarter note, 8 = eighth note, etc
int noteDurations[] = {
  2, 2, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 2,
  8,
  2, 2, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 2,
  
  
};

void setup(){
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
