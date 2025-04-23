# BiopticCoder Keymap for Keychron Q11 ANSI Encoder

This keymap provides the following layers and features:

## Layers

### MAC_BASE (Layer 0)
- Standard alphanumeric layout for macOS.
- Home-row mods:
  - A → Left Control when held, A when tapped
  - S → Left Shift when held, S when tapped
  - D → Left Alt when held, D when tapped
  - F → Left GUI when held, F when tapped
- Right home-row mods:
  - J → Right GUI, K → Right Alt, L → Right Shift, `;` → Right Control
- Hyper and Meh modifiers:
  - E → Hyper, R → Meh, U → Meh, I → Hyper
- Tap-Hold shortcuts for Z/X/C/V:
  - Tap sends key, hold sends Command+key
- Rotary encoder controls volume
- RGB: light blue background, F & J keys in red at 50% brightness

### MAC_FN (Layer 1)
- Function layer for macOS:
  - Media and backlight controls via QMK's RM_* keys
  - Transparent elsewhere

### WIN_BASE (Layer 2)
- Standard alphanumeric layout for Windows.
- Same home-row mods and Hyper/Meh as MAC_BASE.
- Tap-Hold shortcuts for Z/X/C/V send key on tap, Ctrl+key on hold.
- Rotary encoder controls volume
- RGB: dark green background, F & J keys in red at 50% brightness

### WIN_FN (Layer 3)
- Function layer for Windows:
  - Media and backlight controls via QMK's RM_* keys
  - Transparent elsewhere

### NAV (Layer 4)
- Vim-style navigation layer, held by left spacebar (tap for space).
- Home-row one-shot modifiers on left:
  - A → one-shot Ctrl, S → one-shot Shift, D → one-shot Alt, F → one-shot GUI
- QWERTY row one-shot modifiers:
  - E → one-shot Hyper, R → one-shot Meh
- H/J/K/L positions map to Left/Down/Up/Right arrows
- Arrow keys light red on this layer

## Features

- **Home-row Mods**: Efficient modifiers without leaving home row.
- **Hyper & Meh**: Multi-mod combos (Hyper = Ctrl+Shift+Alt+GUI, Meh = Ctrl+Shift+Alt).
- **Tap-Hold Shortcuts**: Z/X/C/V send key on tap, send modifier+key on hold.
- **Chordal Hold**: Mod-Tap holds when another key is pressed before release.
- **One-Shot Mods**: Tap once for a modifier; next key is modified automatically.
- **VIA Support**: Dynamic remapping via VIA.
- **RGB Layers** with custom colors and key-specific highlights.
- **5 Dynamic Layers** supported.

## Compilation & Flashing

```sh
qmk compile -kb keychron/q11/ansi_encoder -km biopticcoder
qmk flash   -kb keychron/q11/ansi_encoder -km biopticcoder
```
