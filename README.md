# esphome-micronova-elisir

Copy of the ESPHome `micronova` component (ESPHome 2026.10.1) with three changes, for an Extraflame Elisir
pellet stove (Micronova board J034_5) read through a PC817 optocoupler interface.

1. **Receive path off at rest.** Upstream keeps `enable_rx_pin` low between commands, so the receive
   optocoupler stays on and loads the stove's DATA line. On this stove that blocked the IR remote
   (remote dead with the ESP32 powered, working again with it unpowered). Here the pin is high at rest
   and low only from the end of a transmission until the reply or the 200 ms timeout.
2. **Scan logging.** A read with no entity behind it (queued from a lambda with
   `queue_read_request(location, address)`) is logged at INFO as `Registro LL:AA = value`, so a whole
   RAM/EEPROM sweep can be captured from the log.
3. **Stove state bound check.** Codes above 10 are shown as `Codice N` instead of indexing past the
   11-entry state table.

```yaml
external_components:
  - source: github://lirmizio/esphome-micronova-elisir@main
    components: [micronova]
```

Derived from ESPHome; same license (C++ files GPLv3, Python MIT), see `LICENSE`.
