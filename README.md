# ESP32 Linux WiFi OTA Crasher

This is a small POC, exploiting CVE-2022-42722 from a ESP32 to crash Linux devices over the air.

Prerequisites:
- You need a WiFi P2P device set up. This is usually the case if you have NetworkManager running. You can also create one manually, see [here](https://github.com/PurpleVsGreen/beacown/blob/088f476e2ce7b0d14f02c2d3214498f07621a097/README#L118).

The exact config I tested (works reliably):
- ESP32-WROOM-32D board
- Linux 5.15.0-48-generic #54~20.04.1-Ubuntu SMP

This code is only for exploiting CVE-2022-42722. Most of the other vulnerability payloads consist of fragmented frames, which ESP32 [does not support sending](https://docs.espressif.com/projects/esp-idf/en/v4.3-beta2/esp32/api-guides/wifi.html#wi-fi-fragment).

Instructions:
- Install ESP-IDF SDK
- Turn off WiFi on your build machine
- Build and flash this to an ESP32
- Plug the ESP32 to power
- Turn on WiFi
- Crash!


ESP32 code .

## Attributions and Licenses

Raw WiFi frames are from <https://github.com/PurpleVsGreen/beacown>.

Code to send raw frames on ESP32 is forked off <https://github.com/Jeija/esp32-80211-tx>.

```
MIT License

Copyright (c) 2022 Jeija

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

This code is under MIT license:

```
MIT License

Copyright (c) 2022 jo-m

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
