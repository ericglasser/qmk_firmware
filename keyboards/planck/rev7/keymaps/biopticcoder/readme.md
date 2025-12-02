# Biopticcoder Planck Layout

A highly customized ergonomic layout for the Planck Rev7, featuring Home Row Mods, Vim-style navigation, and a dedicated "Fast" number/symbol layer.

## Layout Overview

### Base Layer (`_QWERTY`)
Clean base layer with Home Row Mods and essential shortcuts.

```
,-----------------------------------------------------------------------------------.
| GESC |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
|------+------+------+------+------+------+------+------+------+------+------+------|
|  -   |Undo-Z|Cut-X |Copy-C|Pst-V |   B  |   N  |   M  |   ,  |   .  |   /  |  =   |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Caps | Prev | Play | Next |Lower | Space| Fast |Func | Vol- | Vol+ | Mute | Rep  |
`-----------------------------------------------------------------------------------'
```
*   **Home Row Mods**: A/S/D/F (Left) and J/K/L/; (Right) act as Ctrl/Shift/Alt/Gui when held.
*   **Thumbs**:
    *   **Left Space**: Tap for Space, Hold for `_FUNC` layer.
    *   **Right Space**: Tap for Space, Hold for `_FAST` layer.
    *   **Combo**: Press **Both Spacebars** to toggle `_FUNC` layer (One Shot).
*   **Bottom Row**:
    *   **Left**: Dedicated Caps Lock (VoiceOver), Media Controls (Prev, Play, Next).
    *   **Right**: Volume Controls, Repeat Key.

### Fast Layer (`_FAST`)
Triggered by holding **Right Space**. Optimized for numbers and symbols.

```
,-----------------------------------------------------------------------------------.
|   -  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   =  |
|------+------+------+------+------+------+------+------+------+------+------+------|
|   [  |      |      |      |      |   \  |   `  |      |      |      |      |   ]  |
|------+------+------+------+------+------+------+------+------+------+------+------|
|   _  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   +  |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |             |      |      |      |      |      |
`-----------------------------------------------------------------------------------'
```
*   **Top Row**: Numbers `1` - `0`.
*   **Bottom Row**: Symbols `!` - `)`.
*   **Home Row**: `[` (Tab), `\` (G), `` ` `` (H), `]` (Enter). Modifiers (A-F, J-;) are transparent for easy shortcuts (e.g., `Ctrl` + `1`).

### Nav Layer (`_LOWER`)
Vim-style navigation and window management.

```
,-----------------------------------------------------------------------------------.
|      |      |      |      |      |      | Home | PgDn | PgUp | End  |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |      | Left | Down |  Up  |Right |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |      | PrevW| NextW|      |      |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |             |      |      |      |      |      |
`-----------------------------------------------------------------------------------'
```
*   **Right Hand**: `HJKL` for Left/Down/Up/Right.
*   **Left Hand**: Transparent (Modifiers accessible).

### Numpad Layer (`_RAISE`)
Standard Numpad for data entry.

```
,-----------------------------------------------------------------------------------.
|      |      |      |      |      |      |      |   7  |   8  |   9  |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |      |      |   4  |   5  |   6  |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |      |      |   1  |   2  |   3  |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |             |   0  |   0  |   .  |      |      |
`-----------------------------------------------------------------------------------'
```
*   **Right Hand**: Numpad centered on `K` (5).

### Function Layer (`_FN_KEYS`)
F-keys and Media.

*   **Top Row**: F1 - F12.
*   **Media**: `Prev` (H), `Play` (J), `Next` (K), `Stop` (M).

## Features

### Achordion
Improves Home Row Mod usability by intelligently deciding when a dual-role key should be a tap or a hold. It prioritizes bilateral combinations (holding a mod on one hand and tapping a key on the other).

### Caps Word
Smart capitalization. Toggles on by pressing **Both Shifts** (or via `_ADJUST` layer). Capitalizes the next word you type and automatically turns off at the end of the word (space, punctuation).

### Combos
*   `Q` + `W` = `Escape`
*   `O` + `P` = `Backspace`
*   `Left Space` + `Right Space` = Toggle `_FN_KEYS` layer (One Shot).

## Building and Flashing

To compile and flash this keymap:

```bash
qmk flash -kb planck/rev7 -km biopticcoder
```

If the device is not detected, put it into bootloader mode by pressing the physical reset button on the PCB or holding the `Reset` keycode (on the `_ADJUST` layer) while plugging it in.
