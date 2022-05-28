/*
 *    LedControl_HW.cpp - A library for controling Leds with a MAX7219/MAX7221
 *    Copyright (c) 2007 Eberhard Fahle
 * 
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 * 
 *    This permission notice shall be included in all copies or 
 *    substantial portions of the Software.
 * 
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */


#include "LedControl_HW.h"
#include <SPI.h>

//the opcodes for the MAX7221 and MAX7219
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15


LedControl_HW::LedControl_HW(byte csPin, byte numDevices) {
    SPI_CS=csPin;
    if(numDevices<=0 || numDevices>MAX_NUM_OF_MATRIX )
        numDevices=MAX_NUM_OF_MATRIX;
    maxDevices=numDevices;
    pinMode(MOSI,OUTPUT);
    pinMode(SCK,OUTPUT);
    pinMode(SPI_CS,OUTPUT);
		SPI.setBitOrder(MSBFIRST);
		SPI.setDataMode(SPI_MODE0);
		SPI.begin();
    digitalWrite(SPI_CS,HIGH);
    for(int i=0;i<MAX_NUM_OF_MATRIX*8;i++) 
        LedStatus_arr[i]=0x00;
    for(byte i=0;i<maxDevices;i++) 
	{
        spiTransfer(i,OP_DISPLAYTEST,0);
        //scanlimit is set to max on startup
        setScanLimit(i,7);
        //decode is done in source
        spiTransfer(i,OP_DECODEMODE,0);
        clearDisplay(i);
        //we go into shutdown-mode on startup
        shutdown(i,true);
    }
}

byte LedControl_HW::getDeviceCount() 
{
    return maxDevices;
}

void LedControl_HW::shutdown(byte addr, bool b) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(b)
        spiTransfer(addr, OP_SHUTDOWN,0);
    else
        spiTransfer(addr, OP_SHUTDOWN,1);
}

void LedControl_HW::setScanLimit(byte addr, byte limit) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(limit>=0 && limit<8)
        spiTransfer(addr, OP_SCANLIMIT,limit);
}

void LedControl_HW::setIntensity(byte addr, byte intensity) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(intensity>=0 && intensity<16)	
        spiTransfer(addr, OP_INTENSITY,intensity);
}

void LedControl_HW::LC_ClearLedStatus() 
{
    memset(LedStatus_arr, 0, MAX_NUM_OF_MATRIX * 8);
}



void LedControl_HW::LC_XY_2_LedAddress(stLedAddress *a_pLedAddr_s, byte x, byte y)
{
	x=31-x;
	y=31-y;
	
	a_pLedAddr_s->m_Addr = x/8 + (y/8) * 4;
	a_pLedAddr_s->m_Raw  = 7-(y%8);
	a_pLedAddr_s->m_bit  = (x%8);
}


byte LedControl_HW::LC_GetPoint_from_LedStatus(byte x, byte y) 
{
	stLedAddress LA_s;
	LC_XY_2_LedAddress(&LA_s, x, y);
	return (LedStatus_arr[ LA_s.m_Addr * 8 + LA_s.m_Raw ] & (B00000001 << LA_s.m_bit)>0);
}




void LedControl_HW::LC_SetPoint_on_LedStatus(byte x, byte y, byte val = 1) 
{
	stLedAddress LA_s;
	LC_XY_2_LedAddress(&LA_s, x, y);
	
	if (val)
		LedStatus_arr[ LA_s.m_Addr * 8 + LA_s.m_Raw ] |= (B00000001 << LA_s.m_bit);
	else
		LedStatus_arr[ LA_s.m_Addr * 8 + LA_s.m_Raw ] &= (B11111111^(B00000001 << LA_s.m_bit));

}

void LedControl_HW::LC_SetLine_on_LedStatus(byte x0, byte y0, byte x1, byte y1) 
{
	int dx = x1-x0;
	int dy = y1-y0;
	byte x, y;
	if (abs(dx) > abs(dy))
	{
		for (x = x0; x!=x1; x = x + SIGN(dx))
		{
			y = y0 + round((x-x0) *dy/dx);
			LC_SetPoint_on_LedStatus(x, y);
		}
	}
	else
	{
		for (y = y0; y!=y1; y = y + SIGN(dy))
		{
			x = x0 + round((y-y0) *dx/dy);
			LC_SetPoint_on_LedStatus(x,y);
		}
	}
}





void LedControl_HW::clearDisplay(byte addr) {
    int offset;

    if(addr<0 || addr>=maxDevices)
        return;
    offset=addr*8;
    for(byte i=0;i<8;i++) 
	{
        LedStatus_arr[offset+i]=0;
        spiTransfer(addr, i+1, 0);
    }
//	LC_UpdateLeds();
}

void LedControl_HW::setLed(byte addr, byte row, byte column, boolean state) 
{
    int offset;
    byte val=0x00;

    if(addr<0 || addr>=maxDevices)
        return;
    if(row<0 || row>7 || column<0 || column>7)
        return;
    offset=addr*8;
    val=B10000000 >> column;
    if(state)
        LedStatus_arr[offset+row]=LedStatus_arr[offset+row]|val;
    else {
        val=~val;
        LedStatus_arr[offset+row]=LedStatus_arr[offset+row]&val;
    }
    spiTransfer(addr, row+1, LedStatus_arr[offset+row]);
}


void LedControl_HW::LC_ClearLeds_notLedStatus() 
{
    for(byte addr=0; addr<maxDevices; addr++)
	{		
		for(byte i=0; i<8; i++) 
		{
			spiTransfer(addr, i+1,0);
		}
	}
}

void LedControl_HW::LC_UpdateLeds() 
{
	
	SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE2));
	for (byte r=0; r<8; r++)
	{
		digitalWrite(SPI_CS,LOW);
		for(byte d=0; d<maxDevices; d++)
		{
			SPI.transfer(r+1); // row opcode
			SPI.transfer(LedStatus_arr[(8*(maxDevices-d-1)+r)]);
			
		}
		digitalWrite(SPI_CS, HIGH);
	}
	
	SPI.endTransaction();
}

void LedControl_HW::setRow(byte addr, byte row, byte value) 
{
    int offset;
    if(addr<0 || addr>=maxDevices)
        return;
    if(row<0 || row>7)
        return;
    offset = addr*8;
    LedStatus_arr[offset+row]=value;
    spiTransfer(addr, row+1,LedStatus_arr[offset+row]);
}

void LedControl_HW::setColumn(byte addr, byte col, byte value) {
    byte val;

    if(addr<0 || addr>=maxDevices)
        return;
    if(col<0 || col>7) 
        return;
    for(int row=0;row<8;row++) {
        val=value >> (7-row);
        val=val & 0x01;
        setLed(addr,row,col,val);
    }
}

void LedControl_HW::setDigit(byte addr, byte digit, byte value, boolean dp) {
    int offset;
    byte v;

    if(addr<0 || addr>=maxDevices)
        return;
    if(digit<0 || digit>7 || value>15)
        return;
    offset=addr*8;
    v=pgm_read_byte_near(charTable + value); 
    if(dp)
        v|=B10000000;
    LedStatus_arr[offset+digit]=v;
    spiTransfer(addr, digit+1,v);
}

void LedControl_HW::setChar(byte addr, byte digit, byte value, boolean dp) {
    int offset;
    byte index,v;

    if(addr<0 || addr>=maxDevices)
        return;
    if(digit<0 || digit>7)
        return;
    offset=addr*8;
    index=(byte)value;
    if(index >127) {
        //no defined beyond index 127, so we use the space char
        index=32;
    }
    v=pgm_read_byte_near(charTable + index); 
    if(dp)
        v|=B10000000;
    LedStatus_arr[offset+digit]=v;
    spiTransfer(addr, digit+1,v);
}

void LedControl_HW::spiTransfer(byte addr, byte opcode, byte data) 
{
    int offset=addr*2;
    int maxbytes=maxDevices*2;
	int i;
    digitalWrite(SPI_CS,LOW);
	SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE2));
   
    for(i=0; i<maxbytes-offset-2; i++)
	{
		SPI.transfer(0);
	}
    SPI.transfer(opcode);
    SPI.transfer(data);
	
	for(i+=2; i<maxbytes; i++)
	{
		SPI.transfer(0);
	}
	SPI.endTransaction();
  
    digitalWrite(SPI_CS,HIGH);

}    


