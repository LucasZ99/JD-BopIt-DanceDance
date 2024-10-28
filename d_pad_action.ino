/* ECE 1895: Junior Design Fundamentals */
/* Project 2                            */
/* Group Gamma - Dance Dance DJ Deck    */
/* Lizza Novikova                       */
/* D-pad action function defintion      */

/*
           _______
          |       | A
          |   ^   |
   _______|_______|_______
D |       |       |       | B
  |   <   | d-pad |   >   |
  |_______|_______|_______|
          |       |
          |   v   |
          |_______| C

*/

// action success variable
int dpad_success;

// score
long user_score = 0;


void setup() {
  // set up pins 5 and 6 as input for button action
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(9, INPUT); 
  pinMode(15, INPUT);  // analog pin 24/A1 as digital

  // set up pins 7 and 8 as output for led indication
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(10, OUTPUT);
  
}

void loop() {
  //indicates program start
  digitalWrite(7, HIGH);
  delay(1);
  digitalWrite(8, HIGH);
  delay(250);
  digitalWrite(7, LOW);
  delay(1);
  digitalWrite(8, LOW);
  delay(250);

  // time interval for command completion, in milliseconds
  unsigned long time_interval = 10000; // user has 10 seconds to complete

  dpad_success = d_pad_action(time_interval);
  //d_pad_action(time_interval);

  if (dpad_success != 0) {
    //Serial.print(F("Action failed!"));
    digitalWrite(7, HIGH);
    delay(1);
    digitalWrite(8, HIGH);
    delay(1);
    digitalWrite(7, LOW);
    delay(1);
    digitalWrite(8, LOW);
    delay(1);
    while(1);  // wait until reset
  }
  else {
    ++user_score;
  }
}

int d_pad_action(unsigned long time_interval) {
  //set up timing for pin delay
  unsigned long setup_start = millis();
  unsigned long pad1_on_time = millis();
  unsigned long pad2_on_time = millis();

  long pad1 = random(0, 4);  // randomly choose d-pad number for pad1 (choose 0, 1, 2, 3 in full implementation)
  long pad2 = random(0, 4);  // randomly choose d-pad number for pad2
  while (pad2 == pad1) { pad2 = random(0, 4); } // if pad2 == pad1, choose again

  // set up flags
  bool padA = false;
  bool padB = false;
  bool padC = false;
  bool padD = false;
  bool inputReceived = false;

  // turn on pad1 indicator LED
  switch (pad1) {
    case 0:
      // turn indicator LED for pad A on
      digitalWrite(7, HIGH);
      delay(1);
      break;
    case 1:
      // turn indicator LED for pad B on
      digitalWrite(8, HIGH);
      delay(1);
      break;
    case 2:
      // turn indicator LED for pad C on
      digitalWrite(3, HIGH);
      break;
    case 3:
      // turn indicator LED for pad D on
      digitalWrite(10, HIGH);
      break;
    default:
      // default case, should only go here if for some reason a pad # was not selected
        digitalWrite(7, HIGH);
        delay(250);
        digitalWrite(7, LOW);
        delay(1);
        digitalWrite(8, HIGH);
        delay(250);
        digitalWrite(8, LOW);
        delay(1);
      break;
  }

  // turn on pad2 indicator LED
  switch (pad2) {
    case 0:
      // turn indicator LED for pad A on
      digitalWrite(7, HIGH);
      break;
    case 1:
      // turn indicator LED for pad B on
      digitalWrite(8, HIGH);
      break;
    case 2:
      // turn indicator LED for pad C on
      digitalWrite(3, HIGH);
      break;
    case 3:
      // turn indicator LED for pad D on
      digitalWrite(10, HIGH);
      break;
    default:
      // default case, should only go here if for some reason a pad # was not selected
      // do nothing i guess
      break;
  }

  // start timer
  unsigned long start_time = millis();
  unsigned long curr_time = millis();

  // wait for user input
  while (!inputReceived) {
    // read pins
    if (digitalRead(5) == HIGH) {
      // pad A activated, input recieved
      padA = true;
      inputReceived = true;
    }

    if (digitalRead(6) == HIGH) {
      // pad B activated, input recieved
      padB = true;
      if (!inputReceived) inputReceived = true;
    }

    if (digitalRead(9) == HIGH) {
      // pad C activated, input recieved
      padC = true;
      if (!inputReceived) inputReceived = true;
    }

    if (digitalRead(15) == HIGH) {
      //pad D activated, input recieved
      padD = true;
      if (!inputReceived) inputReceived = true;
    }

    // check if time limit has been exceeded
    curr_time = millis();  // read current millis
    if (curr_time - start_time > time_interval) {
      return -1;
    }
  }

  // check if user input is correct

  // user was instructed to hit Pad A and Pad B
  if (pad1 == 0 && pad2 == 1) {
    // did user hit pad A and pad B?
    if (!padA || !padB) return -1;
  }
  else if (pad1 == 0 && pad2 == 2) {  // user was instruced to hit pad A and Pad C
    // did user hit pad A and pad C?
    if (!padA || !padC) return -1;
  }
  else if (pad1 == 0 && pad2 == 3) {  // user was instructed to hit Pad A and Pad D
    // did user hit pad A and pad D?
    if (!padA || !padD) return -1;
  }
  else if (pad1 == 1 && pad2 == 2) {  // user was instructed to hit Pad B and Pad C
    // did user hit pad B and pad C?
    if (!padB || !padC) return -1;
  }
  else if (pad1 == 1 and pad2 == 3) {  // user was instructed to hit Pad B and Pad D
    // did user hit pad B and pad D?
    if (!padB || !padD) return -1;
  }
  else if (pad1 == 2 and pad2 == 3) {  // user was instructed to hit Pad C and Pad D
    // did user hit pad C and pad D?
    if (!padC || !padD) return -1;
  }

  // user input is correct, turn off indicators and return success
  // digitalWrite(7, HIGH);
  // delay(1);
  // digitalWrite(8, HIGH);
  // delay(1);
  // digitalWrite(7, LOW);
  // delay(1);
  // digitalWrite(8, LOW);
  // delay(1);

  return 0;
}





