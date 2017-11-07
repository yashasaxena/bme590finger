int prPin = A0;
int v_init; //initial light reading
int prNew; //new voltage drop read
int chk_1;
int x;
int chk_2;
int ledPin[] = {8,9,10,11};

void setup() {
  Serial.begin(9600); // start serial monitor  
  pinMode(13, OUTPUT); // set output pin
  v_init = analogRead(prPin); // set initial brightness reading to check against
  Serial.println(v_init); // print initial brightness value
  x = 0; // set counter to zero

  // loop initializes Binary counter pins
 for (int i =0;i<4;i++){
     pinMode(ledPin[i], OUTPUT);
     }
}

void loop() {
  chk_1 = analogRead(prPin); // read first value   
 
 // Serial.print(chk_1); // print count
 
  delay(100); // delay between two read values, change delay time to increase sensitivity ****
  chk_2 = analogRead(prPin); // read second value to compare to
  
   // Serial.print("    "); 
  // Serial.println(chk_2); // print coun

// Primary loop to detect falling edge of darkness values, change difference value to titrate sensitivity ****
  if((chk_1 - chk_2) > 80 ) {
    chk_2 = analogRead(prPin); // read second value
  // Secondary loop to count values, by comparing checked values to initial--- adjust difference value ****
      if ((v_init - chk_2) > 150) { 
        x = x+1; // add to the counter
        displayBinary(x); // run function to convert to binary
          }
        Serial.println(x); // print count
    }
}

// Function that converts counter to binary
void displayBinary(byte numToShow){
  for (int i =0;i<4;i++){
    if (bitRead(numToShow, i)==1){
      digitalWrite(ledPin[i], HIGH); 
    }
    else{
      digitalWrite(ledPin[i], LOW); 
    }
  }
}
