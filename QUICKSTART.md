# Clockwise HUB75 Quick Start Guide

This guide will help you get your Clockwise HUB75 clock up and running quickly.

## 📋 Prerequisites

- **Hardware**:
  - ESP32 development board (ESP32, ESP32-S3, or ESP32-S2)
  - HUB75 RGB LED Matrix panel (64×32 or 64×64)
  - 5V power supply (adequate for your panel size)
  - Jumper wires for connections

- **Software**:
  - ESPHome installed (via Home Assistant or standalone)
  - Access to your Home Assistant instance

## 🚀 Quick Setup (5 Minutes)

### Step 1: Choose Your Configuration

Pick the configuration file that matches your hardware:

- `clockwise_hub75.yaml` - Standard ESP32 + 64×32 panel
- `clockwise_hub75_esp32s3.yaml` - ESP32-S3 + 64×64 panel
- `clockwise_hub75_multi_panel.yaml` - Multi-panel setup

### Step 2: Configure Secrets

1. Copy the secrets template:
   ```bash
   cp examples/secrets.yaml.template examples/secrets.yaml
   ```

2. Edit `secrets.yaml` with your credentials:
   ```yaml
   wifi_ssid: "YourWiFiSSID"
   wifi_password: "YourWiFiPassword"
   api_encryption_key: "generated-by-esphome"
   ota_password: "your-secure-password"
   ```

### Step 3: Wire Your Display

**Standard ESP32 DevKit Connections:**

| HUB75 Pin | ESP32 GPIO | Description |
|-----------|------------|-------------|
| R1 | GPIO25 | Red (top) |
| G1 | GPIO26 | Green (top) |
| B1 | GPIO27 | Blue (top) |
| R2 | GPIO14 | Red (bottom) |
| G2 | GPIO12 | Green (bottom) |
| B2 | GPIO13 | Blue (bottom) |
| A | GPIO23 | Row select A |
| B | GPIO19 | Row select B |
| C | GPIO5 | Row select C |
| D | GPIO17 | Row select D |
| E | - | Not used for 32px high |
| LAT | GPIO4 | Latch |
| OE | GPIO15 | Output Enable |
| CLK | GPIO16 | Clock |
| GND | GND | Ground |

**Power Connections:**
- Connect panel GND to ESP32 GND
- Connect panel 5V to external 5V power supply
- Connect ESP32 VIN to same 5V power supply

⚠️ **Important**: Always use an external power supply for the panel. Do not power large panels through the ESP32.

### Step 4: Flash Your ESP32

1. **Connect ESP32 to your computer via USB**

2. **Compile and upload** (choose one method):

   **Via ESPHome Dashboard:**
   ```bash
   esphome run examples/clockwise_hub75.yaml
   ```

   **Via Home Assistant:**
   - Go to ESPHome dashboard
   - Click "New Device" → "Continue" → "Skip"
   - Paste your YAML configuration
   - Click "Install" → "Plug into this computer"

3. **Wait for compilation and upload** (first time takes 5-10 minutes)

### Step 5: Add to Home Assistant

1. ESPHome device will appear in Home Assistant notifications
2. Click "Configure" and add the device
3. You'll see the following entities:
   - `number.display_brightness` - Brightness control (0-255)
   - `switch.display_power` - Turn display on/off
   - `select.clockface` - Choose clockface (Pacman, Mario, Clock)

## 🎨 Home Assistant Dashboard Example

Add this to your Lovelace dashboard:

```yaml
type: entities
title: Clockwise Clock
entities:
  - entity: switch.display_power
  - entity: number.display_brightness
    name: Brightness
  - entity: select.clockface
    name: Clock Style
```

Or use a more visual card:

```yaml
type: vertical-stack
cards:
  - type: button
    entity: switch.display_power
    name: Clock Display
    tap_action:
      action: toggle
    hold_action:
      action: more-info
  
  - type: entities
    entities:
      - entity: number.display_brightness
        name: Brightness
      - entity: select.clockface
        name: Style
```

## 🔧 Troubleshooting

### Display is blank or flickering

1. **Check power supply**: Ensure adequate current (see power requirements below)
2. **Verify pin connections**: Double-check all wiring
3. **Try lower clock speed**: Change `clock_speed: 10MHZ` in YAML
4. **Check shift_driver**: Try `shift_driver: FM6126A` if panel uses that chip

### Wrong colors or corrupted display

1. **Verify RGB pin connections**: Ensure R1/G1/B1/R2/G2/B2 are correct
2. **Try different shift_driver**: Test `GENERIC`, `FM6126A`, `ICN2038S`
3. **Check clock speed**: Lower to `8MHZ` or `10MHZ`

### ESP32 won't boot / boot loops

1. **Avoid strapping pins**: Some default GPIOs are strapping pins
2. **Disconnect during boot**: Try disconnecting HUB75 during power-on
3. **Use alternative pins**: See ESP32-S3 example for non-strapping pins

### No entities in Home Assistant

1. **Check API logs**: Look for connection errors in ESPHome logs
2. **Verify encryption key**: Ensure secrets.yaml has correct key
3. **Reboot HA**: Sometimes needed for new integrations
4. **Check firewall**: Ensure ports 6053 (API) are open

## ⚡ Power Requirements

Calculate your power needs:

**Formula**: `(width × height ÷ 2) × 0.06A` at maximum brightness

**Examples**:
- 64×32 panel: 0.96A at full white brightness
- 64×64 panel: 1.92A at full white brightness
- 128×32 (2 panels): 1.92A at full white brightness

**Recommendations**:
- Use 5V power supply with 20% overhead
- Add 1000µF+ capacitor near panel power input
- For multiple panels, consider separate power injection

## 📊 Display Settings Guide

### Brightness
- **Range**: 0-255
- **Default**: 128
- **Recommendation**: Start at 64 for testing, increase as needed
- **Note**: Lower brightness = less power consumption

### Bit Depth
- **Range**: 6-12
- **Default**: 8
- **Higher values**: Better colors, lower refresh rate
- **Lower values**: Higher refresh rate, acceptable colors

### Refresh Rate
- **Range**: 30-200 Hz
- **Default**: 60 Hz
- **ESP32-S3**: Can handle 120+ Hz
- **ESP32**: 60-80 Hz recommended

## 🎯 Panel Layout Options

### Single Panel
```yaml
layout_cols: 1
layout_rows: 1
layout: HORIZONTAL
```

### Horizontal Chain (2 panels side-by-side)
```yaml
layout_cols: 2
layout_rows: 1
layout: HORIZONTAL
```

### 2×2 Grid
```yaml
layout_cols: 2
layout_rows: 2
layout: TOP_LEFT_DOWN_ZIGZAG
```

### Zigzag (Serpentine) Wiring
If your panels are wired with alternating orientation:
```yaml
layout: TOP_LEFT_DOWN_ZIGZAG
```

## 📚 Next Steps

1. **Customize your clockface**: Edit the render methods in `clockwise_hub75.cpp`
2. **Add animations**: Implement smooth transitions between clockfaces
3. **Create automations**: Use HA to control display based on time/events
4. **Optimize power**: Set lower brightness at night via automation

## 🆘 Getting Help

- **HUB75 Issues**: [hub75-esphome GitHub](https://github.com/stuartparmenter/hub75-esphome/issues)
- **Clockwise Issues**: [Your repository issues]
- **ESPHome Docs**: [esphome.io](https://esphome.io)
- **Community**: [ESPHome Discord](https://discord.gg/KhAMKrd)

## 📖 Additional Resources

- [HUB75 Component Documentation](https://github.com/stuartparmenter/hub75-esphome)
- [ESPHome Display Components](https://esphome.io/components/display/)
- [Home Assistant Integration](https://www.home-assistant.io/integrations/esphome/)

---

**Happy Clocking! 🕐✨**