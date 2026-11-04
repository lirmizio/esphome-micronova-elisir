# esphome-micronova-elisir

Copy of the ESPHome `micronova` component (ESPHome 2026.10.1) with four changes, for an Extraflame Elisir
pellet stove (Micronova board J034_5) read through a PC817 optocoupler interface.

1. **Receive path off at rest.** Upstream keeps `enable_rx_pin` low between commands, so the receive
   optocoupler stays on and loads the stove's DATA line. On this stove that blocked the IR remote
   (remote dead with the ESP32 powered, working again with it unpowered). Here the pin is high at rest
   and low only from the end of a transmission until the reply or the 200 ms timeout.
2. **Scan logging.** Every successful read, including those behind an entity, is logged at INFO as
   `Registro LL:AA = value` (-1 = checksum mismatch). Reads can be queued from a lambda with
   `queue_read_request(location, address)`, so a whole RAM/EEPROM sweep can be captured from the log.
3. **Write codes never read.** `queue_read_request` refuses a location with bit 7 set and addresses 0x80/0xA0
   (the RAM/EEPROM write codes), so a dropped byte cannot turn repeated reads into a valid write frame.
   `pending_reads()` exposes the read queue length for slow one-address-at-a-time scans.
4. **Stove state bound check.** Codes above 10 are shown as `Codice N` instead of indexing past the
   11-entry state table.

```yaml
external_components:
  - source: github://lirmizio/esphome-micronova-elisir@v4
    components: [micronova]
```

Derived from ESPHome; same license (C++ files GPLv3, Python MIT), see `LICENSE`.
