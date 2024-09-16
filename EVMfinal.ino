#include <Keypad.h>
#include <LiquidCrystal.h>
// #include<vector>

// Define a map with key-value pairs
// map<char, int> myMap;

// Define pin numbers for components
// const int rgbLedR = 27;      // Red pin of the RGB LED
// const int rgbLedG = 23;     // Green pin of the RGB LED
// const int rgbLedB = 25;     // Blue pin of the RGB LED
const int redLed = 52;        // Red LED pin
const int buttonPin = 44;     //yellow    // Button for casting vote
const int buzzerPin = 23;     // Buzzer pin
const int party1Button = 42;  //green // Button for Party 1
const int party2Button = 40;  //blue  Button for Party 2
// Add more party buttons as needed
const int passwordButton = 38;  //red // Button for entering passwords
const int passwordLED = 53;     // LED to indicate password entry

// Define LCD screen
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define keypad
const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 22, 24, 26, 28 }; /* connect to  row pinouts of the keypad */
byte colPins[COLS] = { 30, 33, 34, 36 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define variables for vote count
int party1Votes = 0;
bool c1 = false;
bool c2 = false;
int party2Votes = 0;
bool alreadyCasted[10] = { false };
char k = 'x';
bool checkUser = false;
// bool gh = false;
int j = 0;
char m;
char t;
// bool voteMode = false;
// bool resultMode = false;
// myMap["1"] = true;
// myMap["2"] = true;
// myMap["3"] = true;
// Add more variables for other parties as needed

// Flag to indicate if the results are displayed
bool displayResults = false;

void setup() {
  // Initialize components
  // pinMode(rgbLedR, OUTPUT);
  // pinMode(rgbLedG, OUTPUT);
  // pinMode(rgbLedB, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(party1Button, INPUT);
  pinMode(party2Button, INPUT);
  // Initialize more party buttons as needed
  pinMode(passwordButton, INPUT);
  pinMode(passwordLED, OUTPUT);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Elections 2023");
  delay(2000);
  lcd.clear();

  Serial.begin(9600);
  // Set RGB LED to green (ready for voting)
  // digitalWrite(rgbLedR, 0);
  // digitalWrite(rgbLedG, 255);
  // delay(1000);
  // digitalWrite(rgbLedB, 0);
}

void loop() {
  // Serial.println("loop");
  // Check if the EVM is active (password entered)
  // while(true){
  //   char z = keypad.getKey();
  //   if(z == 'A'){
  //     voteMode = true;
  //     break;
  //   }
  //   if(z == 'B'){
  //     resultMode = true;
  //     break;
  //   }
  // }

  while (true) {
    // Serial.print("Xxxxxxxxxxxxx");
    lcd.clear();
    // lcd.setCursor(0, 0);
    lcd.println("Enter Unique-Key");

    while (true) {
      char k = keypad.getKey();
      m = k;
      // Serial.println(k);
      if (k) {
        break;
      }
    }
    // if (k=='0'){
    //   j=0;
    // }

    Serial.print(m);
    if (m == '1') {
      j = 1;
    }
    if (m == '2') {
      j = 2;
    }
    if (m == '3') {
      j = 3;
    }
    if (m == '4') {
      j = 4;
    }
    if (m == '5') {
      j = 5;
    }
    if (m == '6') {
      j = 6;
    }
    if (m == '7') {
      j = 7;
    }
    if (m == '8') {
      j = 8;
    }
    if (m == '9') {
      j = 9;
    }
    if (m == '#') {
      break;
    }
    Serial.println(j);
    if (alreadyCasted[j]) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Already Voted");
      delay(3000);
      continue;
    } else{

      
      alreadyCasted[j] = true;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter PIN");


    // Check for party button presses and increment vote count

    while (checkPassword()) {
      lcd.clear();
      lcd.print("Caste Your vote");
      while (true) {
        // lcd.print("Caste Your vote");

        if (digitalRead(party1Button) == HIGH) {
          party1Votes++;
          c1 = true;
          castVote();
          c1 = false;
          checkUser = true;  // Activate buzzer and LED for Party 1 vote
          break;
        }
        if (digitalRead(party2Button) == HIGH) {
          party2Votes++;
          // c2=true;
          castVote();
          checkUser = true;
          // c2=false;
          // Activate buzzer and LED for Party 2 vote
          break;
        }
      }
      if (checkUser) {
        break;
      }
    }
  }

  // Add more party buttons as needed
  // gh = false;

  // Check if password for displaying results is entered

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Security Key?");
  delay(2000);
  if (checkPassword() == false) {
    if (digitalRead(passwordButton) == LOW) {
      while (true) {
        if (digitalRead(passwordButton) == HIGH) {
          displayResults = true;
          break;
        }
      }
    }


    if (displayResults && displayVotes()) {
      // Display results and prevent further votes
      while (true) {
        // Code to keep results displayed and prevent further voting
        if (digitalRead(buttonPin) == HIGH) {
          party1Votes = 0;
          party2Votes = 0;
          lcd.clear();
          lcd.setCursor(0, 0);
          for (int i = 0; i < 10; i++) {
            alreadyCasted[i] = false;
          }
          lcd.print("Enter PIN");
          break;
        }
      }
    }
  }
}

void castVote() {
  // Turn on the red LED and play a sound
  lcd.clear();
  delay(1000);
  Serial.println("Vote casted");
  lcd.print("Vote Casted");
  lcd.setCursor(0, 1);
  if (c1 == true) {
    lcd.print("to Party 1");
  } else {
    lcd.print("to Party 2");
  }
  digitalWrite(redLed, HIGH);
  tone(buzzerPin, 1000);  // Play a 1000Hz tone for 200ms
  delay(3000);
  noTone(buzzerPin);  // Wait for a moment
  digitalWrite(redLed, LOW);
  digitalWrite(passwordLED, LOW);
  lcd.clear();
  lcd.print("Enter Pin");
}

bool displayVotes() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Party 1 Votes: ");
  lcd.print(party1Votes);
  lcd.setCursor(0, 1);
  lcd.print("Party 2 Votes: ");
  lcd.print(party2Votes);
  // Add more displays for other parties as needed
  return true;
}

// bool checkPassword() {

//   // Check if the password is entered correctly
//   char password[5] = "1111";  // Change this to your password
//   char enteredPassword[5] = "";
//   int passwordIndex = 0;

//   digitalWrite(passwordLED, LOW);  // Turn off password LED

//   while (passwordIndex < 4) {
//     char key = keypad.getKey();
//     if (key) {
//       enteredPassword[passwordIndex] = key;
//       lcd.setCursor(passwordIndex, 1);  // move cursor to   (cursorColumn, 0)
//       lcd.print(key);
//       Serial.println(enteredPassword);
//       passwordIndex++;
//     }
//   }

//   if (strcmp(password, enteredPassword) == 0) {
//     // Password is correct
//     lcd.clear();
//     lcd.setCursor(0, 1);
//     lcd.print("Password Accepted");
//     Serial.println("Success");
//     digitalWrite(passwordLED, HIGH);  // Turn on password LED
//     delay(2000);
//     lcd.clear();
//     return true;
//   } else {
//     // Password is incorrect
//     lcd.clear();
//     lcd.setCursor(0, 1);
//     lcd.print("Passwd Wrong");
//     Serial.println("Fail");
//     delay(2000);
//     lcd.clear();
//     return false;
//   }
// }
bool checkPassword() {




  // Check if the password is entered correctly
  char password[5] = "1234";  // Change this to your password
  char resPass[5] = "9999";
  char enteredPassword[5] = "";
  int passwordIndex = 0;




  digitalWrite(passwordLED, LOW);  // Turn off password LED

  while (passwordIndex < 4) {
    char key = keypad.getKey();
    if (key) {
      enteredPassword[passwordIndex] = key;
      lcd.setCursor(passwordIndex, 1);  // move cursor to   (cursorColumn, 0)
      lcd.print("*");
      Serial.println(enteredPassword);
      passwordIndex++;
    }
  }
  int j = 0;
  if (strcmp(password, enteredPassword) == 0) {
    // Password is correct
    digitalWrite(passwordLED, HIGH);
    lcd.clear();
    lcd.print("Correct Pin");  // Turn on password LED
    delay(2000);
    return true;
  } else {
    // Password is incorrect
    lcd.clear();
    lcd.setCursor(0, 0);
    // lcd.print("Password Incorrect");
    if (strcmp(resPass, enteredPassword) == 0) {
      j = 0;
      lcd.setCursor(0, 0);
      lcd.print("Display Results");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Incorrect PIN");
      j = 1;
      delay(3000);
      lcd.clear();
      lcd.print("Try Again");
    }
  }
  if (j == 1) {
    bool b1 = checkPassword();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Caste Vote");


    return b1;
  } else {
    gh = true;
    return false;
  }
}
