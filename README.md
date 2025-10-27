# Esphome Integration of Clockwise 

* https://clockwise.page/
* https://github.com/jnthas/clockwise

This project provides a wrapper for clockwise as Esphome external component (Mario and Pacman).

The original main.cpp is completly replaced by the wrapper.

Necessary changes on the rest of the original code:
* no subfolders are allowed (or at least I don't know, how to make the esphome compiler look also in subfolders)
  * ``#include "gfx/Super_Mario_Bros__24pt7b.h"`` -> ``#include "Super_Mario_Bros__24pt7b.h"``
* includes need to have " " instead of < >, e.g. ``#include <Game.h>`` -> ``#include "Game.h"``
* custom implementation of ``CWDateTime.cpp``
* some smaller changes (adding some missing #pragma once)

This project is still just a prove oc concept (I just copied all files I needed from the original repos and changed them as needed).

Goal: provide the wrapper, that uses all original files

## HUB75 Board Presets Integration

The upstream HUB75 ESPHome component (https://github.com/stuartparmenter/hub75-esphome) recently added board presets (commit 334dc0e) including a `huidu-hd-wf2` definition. Using a board preset automatically maps all HUB75 pins and suppresses boot warnings about strapping/PSRAM pins.

### Why Use Board Presets?
* No manual 14-pin mapping in YAML
* Reduced chance of wiring mistakes
* Built-in handling of strapping pin warnings
* Cleaner configuration diffs

### Example (HD-WF2 board)

```yaml
display:
  - platform: hub75
    id: matrix_display
    board: huidu-hd-wf2
    panel_width: 64
    panel_height: 64
    shift_driver: FM6126A
    scan_wiring: STANDARD_TWO_SCAN
    brightness: 128
    clock_speed: 20MHZ
    update_interval: never
```

Then reference the display in the Clockwise integration:

```yaml
clockwise_hub75:
  id: clockwise_main
  hub75_id: matrix_display
  clockface_type: PACMAN
  initial_brightness: 128
```

Older examples that used explicit `r1_pin`, `g1_pin`, etc. for HD-WF2 have been updated to rely on `board: huidu-hd-wf2`.
