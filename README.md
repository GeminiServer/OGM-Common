# OpenKNX Common

OpenKNX Common is a library meant to be used once in every OpenKNX Device firmware.

The main functions are:
- setup and calling the knx stack
- setup and calling of the OpenKNX Modules
- flash handling for persistent data of the OpenKNX Modules

## Usage

It is designed for usage with the headerfile generated by [OpenKNXproducer](https://github.com/OpenKNX/OpenKNXproducer), which provides the necessary defines in knxprod.h:
```
MAIN_OpenKnxId
MAIN_ApplicationNumber
MAIN_ApplicationVersion

# optional (delivered by OAM-LogicModule)
LOG_StartupDelayBase
ParamLOG_StartupDelayTimeMS
LOG_HeartbeatDelayBase
KoLOG_Heartbeat
ParamLOG_HeartbeatDelayTimeMS
```
## Hardware

| ARCH   | info                                                                    |
| ------ | ----------------------------------------------------------------------- |
| RP2040 | the reference platform with full support (including dual core support)  |
| SAMD21 | obsolete but still supported. no hw should be developed on this anymore |
| ESP32  | experimental                                                            |

To configure the Hardware-Setup use the following defines in hardware.h

```
SAVE_INTERRUPT_PIN
INFO_LED_PIN
PROG_BUTTON_PIN
PROG_LED_PIN_ACTIVE_ON
PROG_LED_PIN
KNX_UART_RX_PIN
KNX_UART_TX_PIN
```

## Configuration


| define                            |     default | unit  | function                                                                                                                                                                                   |
| --------------------------------- | ----------: | :---: | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| OPENKNX_RECOVERY_TIME             |        6000 |  ms   | hold prog button to erase knx and openknx data (not firmware or filesystem). Turn off with 0                                                                                               |
| OPENKNX_DUALCORE                  |             |       | build with dualcore support (only on RP2040)                                                                                                                                               |
| OPENKNX_WATCHDOG                  |             |       | compile with watchdog (use only for releases. debugger not working with active watchdog)                                                                                                   |
| OPENKNX_WATCHDOG_MAX_PERIOD       |       16384 |  ms   | the timeout period of watchdog                                                                                                                                                             |
| OPENKNX_MAX_MODULES               |           9 |       |                                                                                                                                                                                            |
| OPENKNX_WAIT_FOR_SERIAL           |        2000 |  ms   | wait at startup until SERIAL_DEBUG is connected.<br/>(optional with timeout - in devmode use high values like 20000 - 0 will disable waiting)<br/>Not supported on ESP32                   |
| OPENKNX_MAX_LOOPTIME              |        4000 |  µs   | how much time is the loop allowed to consume. (soft limit)                                                                                                                                 |
| OPENKNX_LOOPTIME_WARNING          |           7 |  ms   | issue a warning if the loop has lasted X ms or longer longer.                                                                                                                              |
| OPENKNX_LOOPTIME_WARNING_INTERVAL |        1000 |  ms   | how often the warning may be issued in the console                                                                                                                                         |
| OPENKNX_RUNTIME_STAT              |             |       | Integrate Collection of Runtime-Statistics  for core0.                                                                                                                                     |
| OPENKNX_RUNTIME_STAT_BUCKETN      |          16 |       | the number of histogram buckets for Runtime-Statistics                                                                                                                                     |
| OPENKNX_RUNTIME_STAT_BUCKETS      | default set |  µs   | The upper (included) limits of histogram bucket, without last bucket as this will be limited by data-type only. Must be a comma-separated list with OPENKNX_RUNTIME_STAT_BUCKETN-1 entries |
| OPENKNX_DEBUG                     |             |       | Enable debug mode                                                                                                                                                                          |
| OPENKNX_TRACE1..5                 |             |       | Enable debug mode + tracing. to see trace logs, they must match one of the 5 regex filters.                                                                                                |
| OPENKNX_RTT                       |             |       | Enable RTT Mode (Disable USB Serial output) + Increase BUFFER_SIZE_UP to 10240!                                                                                                            |
| BUFFER_SIZE_UP                    |        1024 | Bytes | Using by Segger RTT                                                                                                                                                                        |

### Leds

| define                            |     default | unit  | function                                                                                                                                                                                   |
| --------------------------------- | ----------: | :---: | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| OPENKNX_NO_BOOT_PULSATING         |       undef |       | Turn off the pulsating LED during the boot phase. (Only necessary for specific hardware where the LED cannot be controlled via PWM).                                                       |
| OPENKNX_LEDEFFECT_PULSE_FREQ      |        1000 |  ms   |                                                                                                                                                                                            |
| OPENKNX_LEDEFFECT_BLINK_FREQ      |        1000 |  ms   |                                                                                                                                                                                            |
| OPENKNX_HEARTBEAT                 |        1000 |  ms   | enable heartbeat mode (optional with with specific failure time)                                                                                                                           |
| OPENKNX_HEARTBEAT_PRIO            |        3000 |  ms   | enable heartbeat prio mode (optional with with specific failure time)                                                                                                                      |
| OPENKNX_HEARTBEAT_FREQ            |         200 |  ms   |                                                                                                                                                                                            |
| OPENKNX_HEARTBEAT_PRIO_ON_FREQ    |         200 |  ms   |                                                                                                                                                                                            |
| OPENKNX_HEARTBEAT_PRIO_OFF_FREQ   |        1000 |  ms   |                                                                                                                                                                                            |
| OPENKNX_SERIALLED_ENABLE          |       undef |       | activate the usage of Serial LEDs (WS2812, Neopixel)                                                                                                                                       |
| OPENKNX_SERIALLED_PIN             |       undef |       | the GPIO to drive the Serial LEDs                                                                                                                                                          |
| OPENKNX_SERIALLED_NUM             |       undef |       | the number of Serial LEDs to control (max: 24, if no other RMT is needed)                                                                                                                  |
| PROG_LED_PIN                      |       undef |       | the GPIO to drive the LED, if SERIALLED is enabled, the number of the LED in the strip (zero-based)                                                                                        |
| PROG_LED_PIN_ACTIVE_ON            |       undef |       | values: LOW or HIGH, indicates at which GPIO state the LED is active (no function with SERIALLED)                                                                                          |
| PROG_LED_COLOR                    |      63,0,0 |       | set the color for the LED, default: 50% Red - only for SERIALLED                                                                                                                           |
| INFO1_LED_PIN                     |       undef |       | the GPIO to drive the LED, if SERIALLED is enabled, the number of the LED in the strip (zero-based)                                                                                        |
| INFO1_LED_PIN_ACTIVE_ON           |       undef |       | values: LOW or HIGH, indicates at which GPIO state the LED is active (no function with SERIALLED)                                                                                          |
| INFO1_LED_COLOR                   |      0,63,0 |       | set the color for the LED, default: 50% green - only for SERIALLED                                                                                                                         |
| INFO2_LED_PIN                     |       undef |       | the GPIO to drive the LED, if SERIALLED is enabled, the number of the LED in the strip (zero-based)                                                                                        |
| INFO2_LED_PIN_ACTIVE_ON           |       undef |       | values: LOW or HIGH, indicates at which GPIO state the LED is active (no function with SERIALLED)                                                                                          |
| INFO2_LED_COLOR                   |      0,63,0 |       | set the color for the LED, default: 50% green - only for SERIALLED                                                                                                                         |
| INFO3_LED_PIN                     |       undef |       | the GPIO to drive the LED, if SERIALLED is enabled, the number of the LED in the strip (zero-based)                                                                                        |
| INFO3_LED_PIN_ACTIVE_ON           |       undef |       | values: LOW or HIGH, indicates at which GPIO state the LED is active (no function with SERIALLED)                                                                                          |
| INFO3_LED_COLOR                   |      0,63,0 |       | set the color for the LED, default: 50% green - only for SERIALLED                                                                                                                         |


### Heartbeat (Mode: Normal)
You can enable a debug heartbeat to see if a loop is stuck. The progLed (for loop) and infoLed (for loop1) will blinking if the loop hangs.

### Heartbeat (Mode: Prio)
In the prio mode the leds blinking (`OPENKNX_HEARTBEAT_PRIO_OFF_FREQ`) and stop as soon as the relevant loop hangs.
If programing mode is active, the progLed will blink faster (`OPENKNX_HEARTBEAT_PRIO_ON_FREQ`).

So, if the device is NOT blinking, anything is wrong.