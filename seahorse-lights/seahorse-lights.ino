// Christmas Tree Seahorse LED manipulation

// Copyright (C) 2016 Embecosm Limited <www.embecosm.com>

// Contributor Peter Bennett <thelargeostrich@gmail.com>
// Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

// This file is part of the Embecosm Christmas Tree decoration project 2016.

// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.

// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.

// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>. */


// Embecosm has a tree in the 2016 Lymington Christmas Tree Festival. It is
// decorated with 3D printed decorations and assorted embecosm circuits
// including the Seahorse and Cuttlefish.

// This is the program to control the Seahorse LEDs.
 

// Enum for colors

enum led_color {
  R,
  G,
  X
};

// Structure for describing LEDs.

struct led_info
{
  int             pin;
  enum led_color  color;
  int             on;		// HIGH or LOW
  int             off;		// HIGH or LOW
};

// Vector describing all lights clockwise from the belly

static struct led_info leds [] =
  { { 13, X, HIGH, LOW  },
    { 12, G, HIGH, LOW  },
    { 10, R, LOW , HIGH },
    {  9, G, HIGH, LOW  },
    { 11, R, LOW , HIGH },
    {  7, G, HIGH, LOW  },
    {  8, R, LOW , HIGH },
    {  6, G, HIGH, LOW  },
    {  5, R, LOW , HIGH },
    {  3, R, LOW , HIGH },
    { 16, G, HIGH, LOW  },
    { 18, R, LOW , HIGH },
    { 17, G, HIGH, LOW  } };

static int num_leds;


// Flash the lights, allowing the specified millisecs between each.

static void
flashy (int ms)
{
  int i;

  // Half the LEDs are active high, half are active low. Turn each
  // batch each way.
  for (i = 0; i < num_leds; i++)
    digitalWrite (leds[i].pin, HIGH);

  delay(ms);               // wait for a second

  for (i = 0; i < num_leds; i++)
    digitalWrite (leds[i].pin, LOW);
    
  delay(ms);               // wait for a second

}	// flashy


// Sinusoidal fading. Arg specifies number of slices (more = slower)

static void
blender (float slices)
{
  float j;

  for (j = 0.0; j < (2.0 * PI); j += PI / slices)
  {
    int i;
    int red   = max ((int) (10.0 * sinf (j)) + 8, 0);
    int green = max (6 - (int) (8.0 * sinf (j)), 0);
    
    red = max (red, 0);
    green = max (green, 0);

    for (i = 0; i < num_leds; i++)
      if (leds[i].color == G)
        digitalWrite (leds[i].pin, leds[i].on);		// GREEN On
      else
        digitalWrite (leds[i].pin, leds[i].off);	// RED/Unknown Off

    delay (green);               // wait for a second
  
    for (i = 0; i < num_leds; i++)
      if (leds[i].color == G)
        digitalWrite (leds[i].pin, leds[i].off);	// GREEN Off
      else
        digitalWrite (leds[i].pin, leds[i].on)	;	// RED/Unknown On

    delay(red);               // wait for a second

    for (i = 0; i < num_leds; i++)
      digitalWrite (leds[i].pin, leds[i].off);		// All Off
  }
}	// blender ()


// Loop clockwise, with specified millisec delay between each step

static void
clock_loop (int ms)
{
  int i;
  
  for (i = 0; i < num_leds; i++)
    digitalWrite (leds[i].pin, leds[i].off);	// All Off

  // Turn the current pin on and the one two before off

  for (i = 0; i < num_leds + 2; i++)
    {
      int p = (i + num_leds - 2) % num_leds;

      digitalWrite (leds[i].pin, leds[i].on);	// Current pin off
      digitalWrite (leds[p].pin, leds[p].off);	// Current pin off

      delay (ms);
    }
}	// clock_loop ()


// Loop anti-clockwise, with specified millisec delay between each step

static void
anticlock_loop (int ms)
{
  int i;
  
  for (i = 0; i < num_leds; i++)
    digitalWrite (leds[i].pin, leds[i].off);	// All Off

  // Turn the current pin on and the one two before off

  for (i = num_leds + 1; i >= 0; i--)
    {
      int n = (i + num_leds + 2) % num_leds;

      digitalWrite (leds[i].pin, leds[i].on);	// Current pin off
      digitalWrite (leds[n].pin, leds[n].off);	// Current pin off

      delay (ms);
    }
}	// anticlock_loop ()


// the setup routine runs once when you press reset:

void setup() {
  int  i;

  num_leds = sizeof (leds) / sizeof (led_info);

  // initialize the pins as output

  for (i = 0; i < num_leds; i++)
    pinMode(leds[i].pin, OUTPUT);

}	// setup ()

// the loop routine runs over and over again forever:

void loop() {
  int i;
    
  for (i = 0; i < 15; i++)
    blender (30.0);

  for (i = 0; i < 10; i++)
    clock_loop (100);
    
  for (i = 0; i < 10; i++)
    anticlock_loop (100);
    
  for (i = 0; i < 10; i++)
    blender (100.0);

  for (i = 0; i < 7; i++)
    flashy (380);
    
  for (i = 0; i < 15; i++)
    flashy (125);

  for (i = 0; i < 30; i++)
    clock_loop (20);

  for (i = 0; i < 30; i++)
    anticlock_loop (20);

}

