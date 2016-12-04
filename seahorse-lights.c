/*
  Christmas Tree Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// LEDs on when HI
#define NUM_HLED 7

#define BELLY_H        13
#define SNOUT_G_H      17
#define HEAD_G_H       16
#define TAIL_LEFT_G_H   6
#define TAIL_BOT_G_H    7
#define TAIL_RIGHT_G_H  9
#define UNDERBELLY_G_H 12

#define SNOUT_R_L      18
#define HEAD_R_L        3
#define TAIL_LEFT_R_L   5
#define TAIL_BOT_R_L    8
#define TAIL_RIGHT_R_L 11
#define UNDERBELLY_R_L 10

#define PI = 3.14159265

int hled[NUM_HLED] = {
  13,  // Belly (prev pin 10)
  17,  // Snout green (analog pin 3)
  16,  // Head green (analog pin 2)
   6,  // Tail left green
   7,  // Tail bottom green
   9,  // Tail right green
  12   // Underbelly green
};

// LEDs on when LO
#define NUM_LLED 6
int lled[NUM_LLED] = {
  18,  // Snout red (analog pin 4)
   3,  // Head red (prev analog pin 0)
   5,  // Tail left red
   8,  // Tail bottom red
  11,  // Tail right red
  10   // Underbelly red  
};

// the setup routine runs once when you press reset:
void setup() {                
  int  i;
  
  // initialize the pins as output
  for (i = 0; i < NUM_HLED; i++)
    pinMode(hled[i], OUTPUT);
    
  for (i = 0; i < NUM_LLED; i++)
    pinMode(lled[i], OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int i;
    
  for (i = 0; i < 15; i++)
    blendfast ();

  for (i = 0; i < 10; i++)
    clock_loop (100);
    
  for (i = 0; i < 10; i++)
    blendslow ();

  for (i = 0; i < 7; i++)
    flashy ();
    
  for (i = 0; i < 15; i++)
    flashy2 ();

  for (i = 0; i < 30; i++)
    clock_loop (20);

}

// Flash the lights
void flashy () {
  int i;

  for (i = 0; i < NUM_HLED; i++)
    digitalWrite(hled[i], HIGH); // On

  for (i = 0; i < NUM_LLED; i++)
    digitalWrite(lled[i], HIGH); // Off

  delay(380);               // wait for a second
  
  for (i = 0; i < NUM_HLED; i++)
    digitalWrite(hled[i], LOW); // Off

  for (i = 0; i < NUM_LLED; i++)
    digitalWrite(lled[i], LOW); // On
    
  delay(380);               // wait for a second
}
void flashy2 () {
  int i;

  for (i = 0; i < NUM_HLED; i++)
    digitalWrite(hled[i], HIGH); // On

  for (i = 0; i < NUM_LLED; i++)
    digitalWrite(lled[i], HIGH); // Off

  delay(125);               // wait for a second
  
  for (i = 0; i < NUM_HLED; i++)
    digitalWrite(hled[i], LOW); // Off

  for (i = 0; i < NUM_LLED; i++)
    digitalWrite(lled[i], LOW); // On
    
  delay(125);               // wait for a second
}

void blendslow () {
  int i;
  double j;
  int red;
  int green;

  for (j = 0.0; j < (2.0 * PI); j += PI / 100.0)
  {
    red = (int) (10.0 * sin(j)) + 8;
    green = 6 - (int) (8.0 * sin(j));
    
    red = max (red, 0);
    green = max (green, 0);

    for (i = 0; i < NUM_HLED; i++)
      digitalWrite(hled[i], HIGH); //GREEN On

    for (i = 0; i < NUM_LLED; i++)
      digitalWrite(lled[i], HIGH); //RED Off

    delay(green);               // wait for a second
  
    for (i = 0; i < NUM_HLED; i++)
      digitalWrite(hled[i], LOW); //GREEN Off

    for (i = 0; i < NUM_LLED; i++)
      digitalWrite(lled[i], LOW); //RED On
    
    delay(red);               // wait for a second
        for (i = 0; i < NUM_HLED; i++)
      digitalWrite(hled[i], LOW); //GREEN Off

    for (i = 0; i < NUM_LLED; i++)
      digitalWrite(lled[i], HIGH); //RED Off
  }
}
void blendfast () {
  int i;
  double j;
  int red;
  int green;

  for (j = 0.0; j < (2.0 * PI); j += PI / 30.0)
  {
    red = (int) (10.0 * sin(j)) + 8;
    green = 6 - (int) (8.0 * sin(j));
    
    red = max (red, 0);
    green = max (green, 0);

    for (i = 0; i < NUM_HLED; i++)
      digitalWrite(hled[i], HIGH); //GREEN On

    for (i = 0; i < NUM_LLED; i++)
      digitalWrite(lled[i], HIGH); //RED Off

    delay(green);               // wait for a second
  
    for (i = 0; i < NUM_HLED; i++)
      digitalWrite(hled[i], LOW); //GREEN Off

    for (i = 0; i < NUM_LLED; i++)
      digitalWrite(lled[i], LOW); //RED On
    
    delay(red);               // wait for a second
        for (i = 0; i < NUM_HLED; i++)
      digitalWrite(hled[i], LOW); //GREEN Off

    for (i = 0; i < NUM_LLED; i++)
      digitalWrite(lled[i], HIGH); //RED Off
  }
}
void clock_loop (int n) {
  int i;
  
  for (i = 0; i < NUM_LLED; i++)
    digitalWrite(lled[i], HIGH); // Off
    
  for (i = 0; i < NUM_HLED; i++)
    digitalWrite(hled[i], LOW); // Off
    
  digitalWrite(BELLY_H, HIGH);
  digitalWrite(HEAD_R_L, LOW);
  delay(n);
  digitalWrite(HEAD_G_H, HIGH); 
  digitalWrite(TAIL_LEFT_R_L, HIGH);
  delay(n);
  digitalWrite(SNOUT_R_L, LOW); 
  digitalWrite(HEAD_R_L, HIGH);
  delay(n);
  digitalWrite(HEAD_G_H, LOW); 
  digitalWrite(SNOUT_G_H, HIGH);
  delay(n);
  digitalWrite(SNOUT_R_L, HIGH); 
  digitalWrite(BELLY_H, LOW);
  delay(n);
  digitalWrite(SNOUT_G_H, LOW); 
  digitalWrite(UNDERBELLY_G_H, HIGH);
  delay(n);
  digitalWrite(UNDERBELLY_R_L, LOW); 
  digitalWrite(BELLY_H, HIGH);
  delay(n);
  digitalWrite(UNDERBELLY_G_H, LOW); 
  digitalWrite(TAIL_RIGHT_G_H, HIGH);
  delay(n);
  digitalWrite(UNDERBELLY_R_L, HIGH); 
  digitalWrite(TAIL_RIGHT_R_L, LOW);
  delay(n);
  digitalWrite(TAIL_RIGHT_G_H, LOW); 
  digitalWrite(TAIL_BOT_G_H, HIGH);
  delay(n);
  digitalWrite(TAIL_BOT_R_L, LOW); 
  digitalWrite(TAIL_RIGHT_R_L, HIGH);
  delay(n);
  digitalWrite(TAIL_BOT_G_H, LOW); 
  digitalWrite(TAIL_LEFT_G_H, HIGH);
  delay(n);
  digitalWrite(TAIL_BOT_R_L, HIGH); 
  digitalWrite(TAIL_LEFT_R_L, LOW);
  delay(n);
  digitalWrite(TAIL_LEFT_G_H, LOW); 
}
