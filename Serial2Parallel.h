/*
  All Content Copyright (C) 2011 by Jack W. Kern <jack.w.kern@gm**l.com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef __SERIAL2PARALLEL_H_
#define __SERIAL2PARALLEL_H_


class Serial2Parallel
{
protected:
  // Each Serial2Parallel object only uses 8 bytes of memory 
  //  with no dynamic allocation.
  unsigned char data;   // The data pin
  unsigned char clock;  // The clock pin
  unsigned char reset;  // The reset pin
  unsigned char chips;  // The number of chips in this S2P chain (up to 4)
  unsigned long flags;  // The data for the chain (32 bit flags)
  
public:
         Serial2Parallel ();
  
  // ---------------------------------------------------------------- //
  // Use this function to initialize the object, this will also
  //  take care of setting the data/clock/reset pins as output pins.
  void   init  ( unsigned char data
               , unsigned char clock
               , unsigned char reset
               , unsigned char chipCount = 1 );
  
  // ---------------------------------------------------------------- //
  // Setters / Getters
  bool   get   ( unsigned char index ); // NOTE: This will not read the value of the pin, just the flag in memory.
  void   set   ( unsigned char index
               , bool          value );
  void   set   ( unsigned long flags );
  
  // ---------------------------------------------------------------- //
  // Clear resets the flags to zero
  void   clear ();
  
  // ---------------------------------------------------------------- //
  // Shift out all of the flags to the shift register
  void   sync  ();
};

#endif //__SERIAL2PARALLEL_H_