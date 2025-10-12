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
