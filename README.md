# Doom Port for RISC-V (RV32IM) Processor

This project is a port of the original **DOOM** game to a **custom RISC-V processor** supporting the **RV32IM** instruction set.

https://github.com/user-attachments/assets/bda750c4-0d4c-4dc9-bb4f-c1085881695f

## Rendering

Rendering is performed directly into two memory-mapped framebuffers, each with a resolution of 160×100 pixels.  
The buffers operate in a double-buffering scheme to eliminate tearing and ensure smooth frame updates.  
Framebuffer 0 starts at address `0x20000000`, while framebuffer 1 begins at `0x20004000`.  
The active buffer is controlled via a switch bit located at address `0x50000008`.

Each pixel is encoded in a compact 8-bit RGB format, using 3 bits for red, 3 bits for green, and 2 bits for blue.  
The total framebuffer address space ranges from `0x20000000` to `0x20007FFF`, covering 32 KB in total (two 16 KB buffers).

## Critical Section (.critical)

Performance-sensitive routines are grouped into a dedicated `.critical` section defined in the linker script.
This section begins at address `0x10030000` and is intended to reside in fast, low-latency memory to minimize execution overhead.
Placing this section in high-speed memory significantly improves performance.

## Binary

The project can be built using the standard `make` command.  
The resulting binary, `emdoom`, occupies less than 4 MB and includes the first four levels of the game.  

## Running on the Emulator

The port can be tested using the RISC-V emulator available [here](https://github.com/useless-crowbars/emu_rv32i).

To run the game, execute the following command:  
```bash
./emu_rv32i ./path/to/emdoom
```
