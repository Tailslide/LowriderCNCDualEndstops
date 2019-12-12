/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
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

//
// SD Card Menu
//

#include "../../inc/MarlinConfigPre.h"

#if HAS_LCD_MENU && ENABLED(SDSUPPORT)

#include "menu.h"
#include "../../sd/cardreader.h"

#if !PIN_EXISTS(SD_DETECT)
  void lcd_sd_refresh() {
    encoderTopLine = 0;
    card.mount();
  }
#endif

void lcd_sd_updir() {
  ui.encoderPosition = card.cdup() ? ENCODER_STEPS_PER_MENU_ITEM : 0;
  encoderTopLine = 0;
  screen_changed = true;
  ui.refresh();
}

#if ENABLED(SD_REPRINT_LAST_SELECTED_FILE)

  uint32_t last_sdfile_encoderPosition = 0xFFFF;

  void MarlinUI::reselect_last_file() {
    if (last_sdfile_encoderPosition == 0xFFFF) return;
    //#if HAS_GRAPHICAL_LCD
    //  // This is a hack to force a screen update.
    //  ui.refresh(LCDVIEW_CALL_REDRAW_NEXT);
    //  ui.synchronize();
    //  safe_delay(50);
    //  ui.synchronize();
    //  ui.refresh(LCDVIEW_CALL_REDRAW_NEXT);
    //  ui.drawing_screen = screen_changed = true;
    //#endif

<<<<<<< HEAD:Marlin/src/lcd/menu/menu_sdcard.cpp
    goto_screen(menu_sdcard, last_sdfile_encoderPosition);
    last_sdfile_encoderPosition = 0xFFFF;
=======
    goto_screen(menu_media, sd_encoder_position, sd_top_line, sd_items);
    sd_encoder_position = 0xFFFF;
>>>>>>> 1f20e5936e06b0542a858cb041acb8b628751024:Marlin/src/lcd/menu/menu_media.cpp

    defer_status_screen(true);

    //#if HAS_GRAPHICAL_LCD
    //  update();
    //#endif
  }
#endif

<<<<<<< HEAD:Marlin/src/lcd/menu/menu_sdcard.cpp
=======
inline void sdcard_start_selected_file() {
  card.openAndPrintFile(card.filename);
  ui.return_to_status();
  ui.reset_status();
}

#if ENABLED(SD_MENU_CONFIRM_START)

  void menu_sd_confirm() {
    char * const longest = card.longest_filename();
    char buffer[strlen(longest) + 2];
    buffer[0] = ' ';
    strcpy(buffer + 1, longest);
    do_select_screen(
      PSTR(MSG_BUTTON_PRINT), PSTR(MSG_BUTTON_CANCEL),
      sdcard_start_selected_file, ui.goto_previous_screen,
      PSTR(MSG_START_PRINT), buffer, PSTR("?")
    );
  }

#endif

>>>>>>> 1f20e5936e06b0542a858cb041acb8b628751024:Marlin/src/lcd/menu/menu_media.cpp
class MenuItem_sdfile {
  public:
    static void action(PGM_P const pstr, CardReader &) {
      #if ENABLED(SD_REPRINT_LAST_SELECTED_FILE)
<<<<<<< HEAD:Marlin/src/lcd/menu/menu_sdcard.cpp
        last_sdfile_encoderPosition = ui.encoderPosition;  // Save which file was selected for later use
=======
        // Save menu state for the selected file
        sd_encoder_position = ui.encoderPosition;
        sd_top_line = encoderTopLine;
        sd_items = screen_items;
      #endif
      #if ENABLED(SD_MENU_CONFIRM_START)
        MenuItem_submenu::action(pstr, menu_sd_confirm);
      #else
        sdcard_start_selected_file();
        UNUSED(pstr);
>>>>>>> 1f20e5936e06b0542a858cb041acb8b628751024:Marlin/src/lcd/menu/menu_media.cpp
      #endif
      card.openAndPrintFile(theCard.filename);
      ui.return_to_status();
      ui.reset_status();
    }
};

class MenuItem_sdfolder {
  public:
    static void action(PGM_P const, CardReader &theCard) {
      card.cd(theCard.filename);
      encoderTopLine = 0;
      ui.encoderPosition = 2 * ENCODER_STEPS_PER_MENU_ITEM;
      screen_changed = true;
      #if HAS_GRAPHICAL_LCD
        ui.drawing_screen = false;
      #endif
      ui.refresh();
    }
};

void menu_media() {
  ui.encoder_direction_menus();

  #if HAS_GRAPHICAL_LCD
    static uint16_t fileCnt;
    if (ui.first_page) fileCnt = card.get_num_Files();
  #else
    const uint16_t fileCnt = card.get_num_Files();
  #endif

  START_MENU();
  MENU_BACK(MSG_MAIN);
  if (card.flag.workDirIsRoot) {
    #if !PIN_EXISTS(SD_DETECT)
      MENU_ITEM(function, LCD_STR_REFRESH MSG_REFRESH, lcd_sd_refresh);
    #endif
  }
  else if (card.isMounted())
    MENU_ITEM(function, LCD_STR_FOLDER "..", lcd_sd_updir);

  if (ui.should_draw()) for (uint16_t i = 0; i < fileCnt; i++) {
    if (_menuLineNr == _thisItemNr) {
      const uint16_t nr =
        #if ENABLED(SDCARD_RATHERRECENTFIRST) && DISABLED(SDCARD_SORT_ALPHA)
          fileCnt - 1 -
        #endif
      i;

      card.getfilename_sorted(nr);

      if (card.flag.filenameIsDir)
        MENU_ITEM(sdfolder, MSG_MEDIA_MENU, card);
      else
        MENU_ITEM(sdfile, MSG_MEDIA_MENU, card);
    }
    else {
      MENU_ITEM_DUMMY();
    }
  }
  END_MENU();
}

#endif // HAS_LCD_MENU && SDSUPPORT
