int prPin = A1;
int v_init; //initial light reading
int prNew; //new voltage drop read
int chk_1;
int x;
int v;
int chk_2;
int val;
int resetPin = 8; // push variable for reset
int ledPin[] = {9,10,11,12};

void setup() {
  Serial.begin(9600); // start serial monitor  
  //pinMode(13, OUTPUT); // set output pin
  pinMode(8, INPUT); // set reset pin
  v_init = analogRead(prPin); // set initial brightness reading to check against
  Serial.println(v_init); // print initial brightness value
  x = 0; // set counter to zero

  // loop initializes Binary counter pins
 for (int i =0;i<4;i++){
     pinMode(ledPin[i], OUTPUT);
     }
}

void loop() {
displayReset(); // check if need to reset program
fingerTrem(); // look for finger Tremor Event
}


/// FUNCTIONS

// convert counter to binary
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

// Function to check for finger counting event
// CHANGE VARIABLES WITH STARS IN COMMENTS TO ADJUST SENSITIVITY

void fingerTrem(){
  chk_1 = analogRead(prPin); // read first value   
  delay(70); // delay between two read values, change delay time to increase sensitivity ****
  chk_2 = analogRead(prPin); // read second value to compare to
// Primary loop to detect falling edge of darkness values, change difference value to titrate sensitivity ****
  if((chk_1 - chk_2) > 35 ) {
    chk_2 = analogRead(prPin); // read second value
// Secondary loop to count values, by comparing checked values to initial--- adjust difference value ****
      if ((v_init - chk_2) > 80) { 
        x = x+1; // add to the counter
        Serial.println(x);
        displayBinary(x); // run function to convert to binary
        
          }
    }  
}

//Reset counter if button pressed
void displayReset(){
  val = digitalRead(resetPin);
      if (val == 1){
        x = 0;
        displayBinary(x);
        v_init = analogRead(prPin);
     }  
}

