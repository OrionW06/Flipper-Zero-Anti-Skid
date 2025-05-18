# Flipper-Zero-Anti-Skid
FZAS is a protective measure to ensure that flipper zero apps (and potentially other code) will not easily be skidded without the consent of the repo owner

## Usage
Import utils.h into your program and call the init_card() or init_screen() function within it at some point in your program. The rest is taken care of with no ill effects to any firmware not associated with skidding code.

## Effects
### What does FZAS do?
FZAS writes a custom message to the first 2gb worth of blocks (assuming 512 byte blocks) to the SD card of the Flipper Zero. The idea is that this will destroy the partition table of the SD card requiring the flipper to be DFU'd and the SD Card to be reformatted before they can be used again.

This causes no harm to the flipper zero itself, however with enough activations of FZAS it can eventually damage the SD card. Implement at your own risk!

# NO WARRANTY
THIS PROGRAM DOES NOT COME WITH A WARRANTY AND IS PROVIDED "AS-IS", I AM NOT REPSONSIBLE FOR DAMAGED FLIPPERS, LOST DATA, WRECKED SD CARDS, OR UPSET FEELINGS.
IMPLEMENT AT YOUR OWN RISK, THIS CODE IS PUBLIC DOMAIN AND IS NEVER GUARANTEED TO BE SAFE ON UNAFFECTED FIRMWARE.