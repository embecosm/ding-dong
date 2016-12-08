// Christmas Tree Star LED manipulation

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

// This is the program to control the Star LEDs.


// PWM ratio

#define PWM_RAT 2

// Enum for colors

enum led_color {
  B,
  G,
  X
};

// Enum for position

enum led_pos {
  INNER,
  OUTER
};

// Structure for describing LEDs.

struct led_info
{
  int             pin;
  enum led_color  color;
  enum led_pos    pos;
  int             on;		// HIGH or LOW
  int             off;		// HIGH or LOW
};

// Vector describing all lights clockwise from the top

static struct led_info leds [] =
  { {  2, G, INNER, HIGH, LOW },
    {  9, B, OUTER, HIGH, LOW },
    {  3, G, INNER, HIGH, LOW },
    { 10, B, OUTER, HIGH, LOW },
    {  4, G, INNER, HIGH, LOW },
    { 11, B, OUTER, HIGH, LOW },
    {  5, G, INNER, HIGH, LOW },
    { 12, B, OUTER, HIGH, LOW },
    {  6, G, INNER, HIGH, LOW },
    { 13, B, OUTER, HIGH, LOW },
    {  7, G, INNER, HIGH, LOW },
    { 14, B, OUTER, HIGH, LOW } };

static int num_leds;


// Flash the lights, allowing the specified millisecs between each.

static void
flashy (int ms)
{
  int j;

  // Alternate having the inner and outer LEDs on.

  for (j = 0; j < ms; j++)
    {
      int  i;
      
      for (i = 0; i < num_leds; i++)
	if (leds[i].color == G)
	  {
	    int dir = (j % PWM_RAT) == 0 ? leds[i].on : leds[i].off;

	    digitalWrite (leds[i].pin, dir);
	  }
	else
	  {
	    digitalWrite (leds[i].pin, leds[i].off);
	  }

      delay(1);               // wait for a millisecond
    }
  
  for (j = 0; j < ms; j++)
    {
      int  i;
      
      for (i = 0; i < num_leds; i++)
	if (leds[i].color != G)
	  {
	    int dir = (j % PWM_RAT) == 0 ? leds[i].on : leds[i].off;

	    digitalWrite (leds[i].pin, dir);
	  }
	else
	  {
	    digitalWrite (leds[i].pin, leds[i].off);
	  }

      delay(1);               // wait for a millisecond
    }
}	// flashy


// Sinusoidal fading. Arg specifies number of slices (more = slower)

static void
blender (float slices)
{
  float j;

  for (j = 0.0; j < (2.0 * PI); j += PI / slices)
  {
    int i;
    int red   = max ((int) (8.0 * sinf (j)) + 6, 0);
    int green = max (6 - (int) (8.0 * sinf (j)), 0);
    
    for (i = 0; i < num_leds; i++)
      if (leds[i].color == G)
        digitalWrite (leds[i].pin, leds[i].on);		// GREEN On
      else
        digitalWrite (leds[i].pin, leds[i].off);	// BLUE Off

    delay (green);
  
    for (i = 0; i < num_leds; i++)
      if (leds[i].color != G)
        digitalWrite (leds[i].pin, leds[i].on)	;	// BLUE On
      else
        digitalWrite (leds[i].pin, leds[i].off);	// GREEN Off

    delay(red);

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

  // Turn the current and prev pin on and the one two before off

  for (i = 0; i < num_leds + 1; i++)
    {
      int j;
      int p1 = i - 1;
      int p2 = i - 2;

      for (j = 0; j < ms; j++)
	{
	  // Current LED

	  if (i < num_leds)
	    {
	      int dir = (j % PWM_RAT) == 0 ? leds[i].on : leds[i].off;

	      digitalWrite (leds[i].pin, dir);	// Current pin on?
	    }

	  // Prev LED

	  if ((0 <= p1) && (p1 < num_leds))
	    {
	      int dir = (j % PWM_RAT) == 0 ? leds[p1].on : leds[p1].off;

	      digitalWrite (leds[p1].pin, dir);	// Prev pin on?
	    }

	  // Prev but 2 LED
	  
	  if ((0 <= p2) && (p2 < num_leds))
	    digitalWrite (leds[p2].pin, leds[p2].off);	// Prev pin but 2 off

	  delay (1);
	}
    }

  for (i = 0; i < num_leds; i++)
    digitalWrite (leds[i].pin, leds[i].off);	// All Off

}	// clock_loop ()


// Loop anti-clockwise, with specified millisec delay between each step

static void
anticlock_loop (int ms)
{
  int i;
  
  for (i = 0; i < num_leds; i++)
    digitalWrite (leds[i].pin, leds[i].off);	// All Off

  // Turn the current and next pin on and the one two after off

  for (i = num_leds - 1; i >= -1; i--)
    {
      int j;
      int n1 = i + 1;
      int n2 = i + 2;

      for (j = 0; j < ms; j++)
	{
	  // Current LED
	  
	  if (i >= 0)
	    {
	      int dir = (j % PWM_RAT) == 0 ? leds[i].on : leds[i].off;

	      digitalWrite (leds[i].pin, dir);	// Current pin on
	    }

	  // Next LED

	  if ((0 <= n1) && (n1 < num_leds))
	    {
	      int dir = (j % PWM_RAT) == 0 ? leds[n1].on : leds[n1].off;

	      digitalWrite (leds[n1].pin, dir);	// Prev pin on?
	    }
	  
	  // Prev but 2 LED
	  
	  if ((0 <= n2) && (n2 < num_leds))
	    digitalWrite (leds[n2].pin, leds[n2].off);	// Prev pin but 2 off

	  delay (1);
	}
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

void loop () {
  int i;
    
  for (i = 0; i < 15; i++)
    blender (30.0);

  for (i = 0; i < 10; i++)
    clock_loop (100);
    
  for (i = 0; i < 7; i++)
    flashy (380);
    
  for (i = 0; i < 10; i++)
    anticlock_loop (100);
    
  for (i = 0; i < 10; i++)
    blender (100.0);

  for (i = 0; i < 30; i++)
    clock_loop (30);

  for (i = 0; i < 15; i++)
    flashy (125);

  for (i = 0; i < 30; i++)
    anticlock_loop (30);

}	// loop ()
