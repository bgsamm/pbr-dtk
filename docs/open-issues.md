# Open issues

Temporary notes about imported code that differs from the game, until they are written as comments in the files concerned.

- `vf/nand_drv.c`: only one function is in the binary; the game uses a different NAND driver from the imported source.
- `AXVPB`: four functions of the game's version are not in ogws, so they have to be written from the binary.
- OSAudioSystem: needs the DSP boot code, which is in the game data.
