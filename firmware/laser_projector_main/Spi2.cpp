/*
  Spi.cpp - SPI library
  Copyright (c) 2008 Cam Thompson.
  Author: Cam Thompson, Micromega Corporation, <www.micromegacorp.com>
  Version: December 15, 2008

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
#include "Spi2.h"

//---------- constructor ----------------------------------------------------

SPI2::SPI2()
{
  // initialize the SPI pins
  pinMode(SCK_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  pinMode(SS_PIN, OUTPUT);

  // enable SPI Master, MSB, SPI mode 0, FOSC/4
  mode(0);
}

//------------------ mode ---------------------------------------------------

void SPI2::mode(byte config)
{
  byte tmp;

  // enable SPI master with configuration byte specified
  SPCR = 0;
  SPCR = (config & 0x7F) | (1<<SPE) | (1<<MSTR);
  tmp = SPSR;
  tmp = SPDR;
}

//------------------ transfer -----------------------------------------------

byte SPI2::transfer(byte value)
{
  SPDR = value;
  while (!(SPSR & (1<<SPIF))) ;
  return SPDR;
}

byte SPI2::transfer(byte value, byte period)
{
  SPDR = value;
  if (period > 0) delayMicroseconds(period);
  while (!(SPSR & (1<<SPIF))) ;
  return SPDR;
}


//---------- preinstantiate SPI object --------------------------------------

SPI2 Spi = SPI2();
