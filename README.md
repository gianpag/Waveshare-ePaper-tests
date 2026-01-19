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

## Ribbon orientation note
On the screen-side connector (not the rest of the ribbon extension), the panel
flex inserts with the visible contacts facing the PCB. The other connectors are
opposite (contacts face up).

Reference photos show the display-side flex contacts facing the PCB, while the
board-side extension ribbon has contacts facing up.

## Panel swap toggle
`src/main.cpp` has a `PANEL_75` define. Set it to `1` for the 7.5" HINK-E075A07-A0
panel, or `0` for the 5.83" Z83 panel.
