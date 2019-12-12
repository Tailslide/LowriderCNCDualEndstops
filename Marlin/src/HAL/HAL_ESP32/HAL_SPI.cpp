/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 * Copyright (c) 2017 Victor Perez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifdef ARDUINO_ARCH_ESP32

#include "HAL.h"
#include "../shared/HAL_SPI.h"
#include <pins_arduino.h>
#include "spi_pins.h"
#include <SPI.h>

#include "../../core/macros.h"

// ------------------------
// Public Variables
// ------------------------

static SPISettings spiConfig;

// ------------------------
// Public functions
// ------------------------

<<<<<<< HEAD:Marlin/src/HAL/HAL_ESP32/HAL_spi_ESP32.cpp
// --------------------------------------------------------------------------
=======
#if ENABLED(SOFTWARE_SPI)

  // ------------------------
  // Software SPI
  // ------------------------
  #error "Software SPI not supported for ESP32. Use Hardware SPI."

#else

// ------------------------
>>>>>>> 1f20e5936e06b0542a858cb041acb8b628751024:Marlin/src/HAL/HAL_ESP32/HAL_SPI.cpp
// Hardware SPI
// ------------------------

void spiBegin() {
  #if !PIN_EXISTS(SS)
    #error "SS_PIN not defined!"
  #endif

  OUT_WRITE(SS_PIN, HIGH);
}

void spiInit(uint8_t spiRate) {
  uint32_t clock;

  switch (spiRate) {
    case SPI_FULL_SPEED:    clock = SPI_CLOCK_DIV2;  break;
    case SPI_HALF_SPEED:    clock = SPI_CLOCK_DIV4;  break;
    case SPI_QUARTER_SPEED: clock = SPI_CLOCK_DIV8;  break;
    case SPI_EIGHTH_SPEED:  clock = SPI_CLOCK_DIV16; break;
    case SPI_SPEED_5:       clock = SPI_CLOCK_DIV32; break;
    case SPI_SPEED_6:       clock = SPI_CLOCK_DIV64; break;
    default:                clock = SPI_CLOCK_DIV2; // Default from the SPI library
  }

  spiConfig = SPISettings(clock, MSBFIRST, SPI_MODE0);
  SPI.begin();
}

uint8_t spiRec() {
  SPI.beginTransaction(spiConfig);
  uint8_t returnByte = SPI.transfer(0xFF);
  SPI.endTransaction();
  return returnByte;
}

void spiRead(uint8_t* buf, uint16_t nbyte) {
  SPI.beginTransaction(spiConfig);
  SPI.transferBytes(0, buf, nbyte);
  SPI.endTransaction();
}

void spiSend(uint8_t b) {
  SPI.beginTransaction(spiConfig);
  SPI.transfer(b);
  SPI.endTransaction();
}

void spiSendBlock(uint8_t token, const uint8_t* buf) {
  SPI.beginTransaction(spiConfig);
  SPI.transfer(token);
  SPI.writeBytes(const_cast<uint8_t*>(buf), 512);
  SPI.endTransaction();
}

void spiBeginTransaction(uint32_t spiClock, uint8_t bitOrder, uint8_t dataMode) {
  spiConfig = SPISettings(spiClock, bitOrder, dataMode);

  SPI.beginTransaction(spiConfig);
}

#endif // ARDUINO_ARCH_ESP32
