
int onDur = 70;
char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
char morseCode[] = "01222221000222101022210022220222222001022211022220000222002222201112221012222010022211222221022222111222201102221101222010222200022221222222001222200012220112222100122210112221100222";

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void blnk() {
  Serial.print("blink");
  digitalWrite(13, HIGH); 
  delay(onDur);  
  digitalWrite(13, LOW);       
  
}

void lngblk() {
  Serial.print("long blink");
  digitalWrite(13, HIGH); 
  delay(onDur*3);  
  digitalWrite(13, LOW);    
}

void blinkMorse(int characterIndex) {
  int startLoopIndex = characterIndex*7;
  int stopLoopIndex = (startLoopIndex)+7;
  int count = startLoopIndex;
  while(count<stopLoopIndex) {
    if (morseCode[count]=='0') {
      blnk();
      Serial.print("part gap (for 1)");
      delay(onDur);
    }
    else if (morseCode[count]=='1') {
      lngblk();
      Serial.print("part gap (for 1)");
      delay(onDur);
    }
    Serial.print(morseCode[count]);
    count++;
  }
  Serial.print("letter gap (for 2)");
  delay(onDur*2);
}

void loop() {
  if (Serial.available() > 0) {
    String string = Serial.readString();
    Serial.print(string);
    int i = 0;
    int j = 0;
    for (i = 0; i<string.length(); i++) {
      for (j = 0; j<26; j++) {
        if (string[i]==alphabet[j]) {
          Serial.println(alphabet[j]);
          Serial.println(j);
          blinkMorse(j);
        }
      }
      if (string[i]==' ') {
        Serial.print("SPAACCEEd (for 4)");
        delay(onDur*4);
      }
    }
  }
}
