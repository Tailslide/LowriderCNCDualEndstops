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
#pragma once

/**
 * Fast I/O interfaces for STM32
 * These use GPIO register access for fast port manipulation.
 */

// ------------------------
// Public Variables
// ------------------------

extern GPIO_TypeDef * FastIOPortMap[];

// ------------------------
// Public functions
// ------------------------

void FastIO_init(); // Must be called before using fast io macros

// ------------------------
// Defines
// ------------------------

#define _BV32(b) (1UL << (b))

#ifndef PWM
  #define PWM OUTPUT
#endif

#if defined(STM32F0xx) || defined(STM32F1xx) || defined(STM32F3xx) || defined(STM32L0xx) || defined(STM32L4xx)
  #define _WRITE(IO, V) do { \
    if (V) FastIOPortMap[STM_PORT(digitalPin[IO])]->BSRR = _BV32(STM_PIN(digitalPin[IO])) ; \
    else   FastIOPortMap[STM_PORT(digitalPin[IO])]->BRR  = _BV32(STM_PIN(digitalPin[IO])) ; \
  }while(0)
#else
  #define _WRITE(IO, V) (FastIOPortMap[STM_PORT(digitalPin[IO])]->BSRR = _BV32(STM_PIN(digitalPin[IO]) + (V ? 0 : 16)))
#endif

#define _READ(IO)               bool(READ_BIT(FastIOPortMap[STM_PORT(digitalPin[IO])]->IDR, _BV32(STM_PIN(digitalPin[IO]))))
#define _TOGGLE(IO)             (FastIOPortMap[STM_PORT(digitalPin[IO])]->ODR ^= _BV32(STM_PIN(digitalPin[IO])))

#define _GET_MODE(IO)
#define _SET_MODE(IO,M)         pinMode(IO, M)
#define _SET_OUTPUT(IO)         pinMode(IO, OUTPUT)                               /*!< Output Push Pull Mode & GPIO_NOPULL   */

#define WRITE(IO,V)             _WRITE(IO,V)
#define READ(IO)                _READ(IO)
#define TOGGLE(IO)              _TOGGLE(IO)

#define OUT_WRITE(IO,V)         do{ _SET_OUTPUT(IO); WRITE(IO,V); }while(0)

#define SET_INPUT(IO)           _SET_MODE(IO, INPUT)                              /*!< Input Floating Mode                   */
#define SET_INPUT_PULLUP(IO)    _SET_MODE(IO, INPUT_PULLUP)                       /*!< Input with Pull-up activation         */
#define SET_INPUT_PULLDOWN(IO)  _SET_MODE(IO, INPUT_PULLDOWN)                     /*!< Input with Pull-down activation       */
#define SET_OUTPUT(IO)          OUT_WRITE(IO, LOW)
#define SET_PWM(IO)             _SET_MODE(IO, PWM)

<<<<<<< HEAD:Marlin/src/HAL/HAL_STM32/fastio_STM32.h
#define GET_INPUT(IO)
#define GET_OUTPUT(IO)
#define GET_TIMER(IO)

#define PWM_PIN(P)              digitalPinHasPWM(P)
#define USEABLE_HARDWARE_PWM(P) PWM_PIN(P)
=======
#define IS_INPUT(IO)
#define IS_OUTPUT(IO)

#define PWM_PIN(P)              digitalPinHasPWM(P)
>>>>>>> 1f20e5936e06b0542a858cb041acb8b628751024:Marlin/src/HAL/HAL_STM32/fastio.h

// digitalRead/Write wrappers
#define extDigitalRead(IO)    digitalRead(IO)
#define extDigitalWrite(IO,V) digitalWrite(IO,V)
