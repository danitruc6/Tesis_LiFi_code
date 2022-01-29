// Arduino variables
int photoPin = A0;
int photo2Pin = A1;
int delayTime = 50;
int analogValue;
int analog2Value;
int lowThreshold = 60;
int highThreshold;

// Serial variables
int i = 0;
char value;
String values;
int binStrings;
String binString;
String asciiString;

void setup() {
  // Serial comm
  Serial.begin(9600);
  
  // Threshold
  analogValue = analogRead(photoPin);
  while (analogValue < 60) {
    analogValue = analogRead(photoPin);
  }
  if (analogValue >= 70) {
    highThreshold = analogValue - 5;
  }
  else if (analogValue < 70 && analogValue >= 65) {
    highThreshold = analogValue - 3;
  }
  else if (analogValue < 65 && analogValue >= 60) {
    highThreshold = analogValue;
  }
  else {
    Serial.println("ERROR: insufficient light conditions");
    Serial.end();
  }
  Serial.print("Threshold: ");
  Serial.print(lowThreshold);
  Serial.print(" - ");
  Serial.println(highThreshold);
  Serial.println();
}

void loop() {
  // Read photo while photo2 is receiving light
  analog2Value = analogRead(photo2Pin);
  if (analog2Value > highThreshold) {
    while (analog2Value > highThreshold) {
      // OOK demodulation
      analogValue = analogRead(photoPin);
      if (analogValue < lowThreshold) {
        value = '0';
      }
      else if (analogValue > highThreshold) {
        value = '1';
      }
      
      // Build string
      values = values + String(value);
      
      // Loop
      delay(delayTime);
      analog2Value = analogRead(photo2Pin);
    }
  }
  
  if (values != "") {
    // Print binary
    Serial.print(values);
    Serial.print(" = ");
    
    // Print if error
    if (values.length() % 8 != 0) {
      Serial.println("ERROR: insufficient data");
    }
    
    // Print ASCII
    else {
      binStrings = values.length() / 8;
      for (int i = 0; i < binStrings; i++) {
        binString = values.substring(0 + 8*i, 8 + 8*i);
        asciiString = asciiString + String(binToASCII(binString));
      }
      if (asciiString.indexOf('|') == -1) {
        Serial.println(asciiString);
      }
      else {
        Serial.println("ERROR: unsupported characters");
      }
    }
    
    // Reset variables
    values = "";
    asciiString = "";
  }
}

// Convert binary to ACII ("tables")
char binToASCII(String binString) {
  // Symbols
  if (binString == "00100000") {
    return ' ';
  }  
  else if (binString == "01100110") {
    return 'f';
  }  
  else if (binString == "00100001") {
    return '!';
  }  
  else if (binString == "00100010") {
    return '"';
  }  
  else if (binString == "00100011") {
    return '#';
  }  
  else if (binString == "00100100") {
    return '$';
  }  
  else if (binString == "00100101") {
    return '%';
  }  
  else if (binString == "00100110") {
    return '&';
  }  
  else if (binString == "00100111") {
    return '\'';
  }  
  else if (binString == "00101000") {
    return '(';
  }  
  else if (binString == "00101001") {
    return ')';
  }  
  else if (binString == "00101010") {
    return '*';
  }  
  else if (binString == "00101011") {
    return '+';
  }  
  else if (binString == "00101100") {
    return ',';
  }  
  else if (binString == "00101101") {
    return '-';
  }  
  else if (binString == "00101110") {
    return '.';
  }  
  else if (binString == "00101111") {
    return '/';
  }  
  else if (binString == "00111010") {
    return ':';
  }  
  else if (binString == "00111011") {
    return ';';
  }  
  else if (binString == "00111100") {
    return '<';
  }  
  else if (binString == "00111101") {
    return '=';
  }  
  else if (binString == "00111110") {
    return '>';
  }  
  else if (binString == "00111111") {
    return '?';
  }  
  else if (binString == "01000000") {
    return '@';
  }
  
  // Lowercase
  else if (binString == "01100001") {
    return 'a';
  }
  else if (binString == "01100010") {
    return 'b';
  }
  else if (binString == "01100011") {
    return 'c';
  }
  else if (binString == "01100100") {
    return 'd';
  }
  else if (binString == "01100101") {
    return 'e';
  }  
  else if (binString == "01100110") {
    return 'f';
  }
  else if (binString == "01100111") {
    return 'g';
  }
  else if (binString == "01101000") {
    return 'h';
  }
  else if (binString == "01101001") {
    return 'i';
  }
  else if (binString == "01101010") {
    return 'j';
  }
  else if (binString == "01101011") {
    return 'k';
  }
  else if (binString == "01101100") {
    return 'l';
  }  
  else if (binString == "01101101") {
    return 'm';
  }
  else if (binString == "01101110") {
    return 'n';
  }
  else if (binString == "01101111") {
    return 'o';
  }  
  else if (binString == "01110000") {
    return 'p';
  }
  else if (binString == "01110001") {
    return 'q';
  }
  else if (binString == "01110010") {
    return 'r';
  }
  else if (binString == "01110011") {
    return 's';
  }
  else if (binString == "01110100") {
    return 't';
  }
  else if (binString == "01110101") {
    return 'u';
  }
  else if (binString == "01110110") {
    return 'v';
  }
  else if (binString == "01110111") {
    return 'w';
  }
  else if (binString == "01111000") {
    return 'x';
  }
  else if (binString == "01111001") {
    return 'y';
  }
  else if (binString == "01111010") {
    return 'z';
  }

  // Capital
  else if (binString == "01000001") {
    return 'A';
  }
  else if (binString == "01000010") {
    return 'B';
  }
  else if (binString == "01000011") {
    return 'C';
  }
  else if (binString == "01000100") {
    return 'D';
  }  
  else if (binString == "01000101") {
    return 'E';
  }  
  else if (binString == "01000110") {
    return 'F';
  }  
  else if (binString == "01000111") {
    return 'G';
  }
  else if (binString == "01001000") {
    return 'H';
  }
  else if (binString == "01001001") {
    return 'I';
  }
  else if (binString == "01001010") {
    return 'J';
  }
  else if (binString == "01001011") {
    return 'K';
  }
  else if (binString == "01001100") {
    return 'L';
  }
  else if (binString == "01001101") {
    return 'M';
  }
  else if (binString == "01001110") {
    return 'N';
  }
  else if (binString == "01001111") {
    return 'O';
  }
  else if (binString == "01010000") {
    return 'P';
  }
  else if (binString == "01010001") {
    return 'Q';
  }
  else if (binString == "01010010") {
    return 'R';
  }
  else if (binString == "01010011") {
    return 'S';
  }
  else if (binString == "01010100") {
    return 'T';
  }
  else if (binString == "01010101") {
    return 'U';
  }
  else if (binString == "01010110") {
    return 'V';
  }
  else if (binString == "01010111") {
    return 'W';
  }
  else if (binString == "01011000") {
    return 'X';
  }
  else if (binString == "01011001") {
    return 'Y';
  }
  else if (binString == "01011010") {
    return 'Z';
  }
  
  // Numbers
  else if (binString == "00110000") {
    return '0';
  }
  else if (binString == "00110001") {
    return '1';
  }
  else if (binString == "00110010") {
    return '2';
  }
  else if (binString == "00110011") {
    return '3';
  }
  else if (binString == "00110100") {
    return '4';
  }
  else if (binString == "00110101") {
    return '5';
  }
  else if (binString == "00110110") {
    return '6';
  }
  else if (binString == "00110111") {
    return '7';
  }
  else if (binString == "00111000") {
    return '8';
  }
  else if (binString == "00111001") {
    return '9';
  }
  
  // Error
  else {
    return '|';
  }
}
