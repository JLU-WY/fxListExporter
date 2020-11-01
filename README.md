# fxListExporter
fxListExporter is an Add-in for fx-9860 series calculators. It can help you export your calculator's list data in CSV format.

## Function
+ Generate a CSV file to storage memory.
+ Generate a CSV file to SD card.
+ Display a QR code.
+ Choose the columns and rows you want.

[中文说明](https://www.cncalc.org/thread-24753-1-1.html)

## Known Issue
When using QR code mode, this tool can't export too much data once.

## Thanks
Thanks [flaribbit](https://github.com/flaribbit) for his [fxQr](https://github.com/flaribbit/FxQr) library.

Thanks Simon Lothar for his great work in syscall.


## Build
To build this tool, you need fx-9860G Software Development Kit. You can learn more from [planet-casio](https://www.planet-casio.com/Fr/forums/topic14992-1-programmer-en-c-sur-graph-3575-e.html).

For SH4 device, you need to convert the G1A file after built process. You can use [this website](https://tools.planet-casio.com/SH4compatibilityTool/).