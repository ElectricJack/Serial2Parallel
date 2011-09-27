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

#include <WProgram.h>
#include <Serial2Parallel.h>

#define  reset_us   10
#define  data_us    10
#define  clock_us   10

// ---------------------------------------------------------------------------- //
Serial2Parallel::Serial2Parallel()
  : data  ( 0 )
  , clock ( 0 )
  , reset ( 0 )
  , chips ( 0 )
  , flags ( 0 )
{
}
// ---------------------------------------------------------------------------- //
void Serial2Parallel::init( unsigned char  _data
                          , unsigned char  _clock
                          , unsigned char  _reset
                          , unsigned char  _chips /*=1*/ )
{
  data  = _data;
  clock = _clock;
  reset = _reset;
  chips = _chips;
  
  // Each shifter structure can only support up to 4 shift registers
  if( chips > 4 ) chips = 4;
  
  pinMode( data,  OUTPUT );
  pinMode( clock, OUTPUT );
  pinMode( reset, OUTPUT );
}
// ---------------------------------------------------------------------------- //
void Serial2Parallel::clear()
{
  flags = 0;
  digitalWrite      ( reset, LOW );
  delayMicroseconds ( reset_us );
  digitalWrite      ( reset, HIGH );
  delayMicroseconds ( reset_us );
}
// ---------------------------------------------------------------------------- //
void Serial2Parallel::sync()
{  
  digitalWrite      ( reset, HIGH );

  // Set all the bits in reverse order
  unsigned char maxBit = chips*8 - 1;
  for( unsigned char k = maxBit; k >= 0; --k )
  {
    // Set the data bit      
    digitalWrite      ( data, get(k) ? HIGH : LOW );
    delayMicroseconds ( data_us );
    
    // Flip the clock switch to set the bit  
    digitalWrite      ( clock, HIGH );
    delayMicroseconds ( clock_us );
    digitalWrite      ( clock, LOW );
    delayMicroseconds ( clock_us );
  }
}
// ---------------------------------------------------------------------------- //
bool Serial2Parallel::get( unsigned char index )
{
  unsigned char maxBit = chips*8 - 1;
  if( index < 0 || index > maxBit ) return false;
  
  return (flags & (1 << index)) != 0;
}
// ---------------------------------------------------------------------------- //
void Serial2Parallel::set( unsigned char _flags )
{
  flags = _flags;
}
// ---------------------------------------------------------------------------- //
void Serial2Parallel::set( unsigned char index, bool value )
{
  unsigned char maxBit = chips*8 - 1;
  if( index < 0 || index > maxBit ) return;
  
  if( value ) flags |=  (1 << index); // set the bitflag at index to true  (1)
  else        flags &= ~(1 << index); // set the bitflag at index to false (0)
}  