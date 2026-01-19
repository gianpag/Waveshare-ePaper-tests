# WaveShare 7.5" e-paper (ESP32 Rev3) notes

## Key finding
Waveshare ESP32 Driver Board Rev3 wires the panel to HSPI, but Arduino defaults to
VSPI. If HSPI pins are not set explicitly, the code can appear to run while the
panel stays blank.

### What the black/white cycling proves
- Panel is alive
- Ribbon orientation is correct
- Adapter is correct
- Power rails are working
- HSPI routing was the missing piece
- GxEPD2 is talking to the SSD1677 controller

## Practical takeaway
Always call `SPI.begin(sck, miso, mosi, ss)` with the Rev3 HSPI pin map before
`display.init(...)`.

## Hardware used
### ESP32 HAT
- Waveshare e-Paper ESP32 Driver Board Rev3

### Panels tested / planned
- 7.5" tri-color: HINK-E075A07-A0 (GoodDisplay GDEH075Z90, SSD1677)
- 5.83" tri-color: 648x480, 24-pin FPC (Waveshare 5.83" e-Paper HAT (B) class,
  commonly GDEW0583Z83 / UC8179)

## Rev3 pinout (HSPI wiring)
These pins are fixed on the Rev3 board routing:
- CS: GPIO5
- DC: GPIO17
- RST: GPIO16
- BUSY: GPIO4
- MOSI: GPIO23
- SCK: GPIO18
- MISO: GPIO19 (not always used by the panel)

## Ribbon orientation note
On the screen-side connector (not the rest of the ribbon extension), the panel
flex inserts with the visible contacts facing the PCB. The other connectors are
opposite (contacts face up).

Reference photos show the display-side flex contacts facing the PCB, while the
board-side extension ribbon has contacts facing up.

## Panel swap toggle
The panel test example at `src/examples/panel_test/main.cpp` has a `PANEL_75`
define. Set it to `1` for the 7.5" HINK-E075A07-A0 panel, or `0` for the 5.83"
Z83 panel.

## Example selection (PlatformIO)
This repo uses a single environment and a pre-build script to select which
example builds/flashes. Set `EPAPER_EXAMPLE` to the folder name under
`src/examples/`.

- Default: `panel_test`
- Flash calendar: `EPAPER_EXAMPLE=calendar pio run -t upload`
- Flash panel test: `EPAPER_EXAMPLE=panel_test pio run -t upload`
