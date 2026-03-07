# Shell

**Shell** is a Command Line Interface (CLI) application for the [Mk](https://github.com/EmbSoft3/Mk)
operating system. It supports both built-in commands and externally loaded commands, and
serves as a reference example for writing Mk applications.

![shell](Screenshots/screenshot_shell.bmp)

---

## Commands

Type `help` in the shell to display all available commands.

| Command | Description |
|---------|-------------|
| `ls` | List directory contents |
| `cd` | Change current directory |
| `pwd` | Print working directory |
| `lsdsk` | List mounted disks and partitions |
| `launch` | Load and run an external `.elf` application |
| `install` / `uninstall` | Install or remove an application |
| `terminate` | Stop a running application |
| `getapps` | List installed applications |

---

## Installation

Build the application (see [Build](#build) below), then copy `shellRelease.elf` and its
icon `mk_shell.bmp` to the Mk file system at:

```
mk/apps/shell/
```

This path corresponds to [`Mk/Storage/mk/apps/shell/`](https://github.com/EmbSoft3/Mk/tree/main/Mk/Storage/mk/apps/shell)
in the Mk repository. Once installed, Shell appears in the Mk home screen application list.

---

## Build

### Requirements

- [GNU Arm Embedded Toolchain 10.3-2021.10](https://developer.arm.com/downloads/-/gnu-rm)
- GNU Make 4.x
- [Mk Includes](https://github.com/EmbSoft3/Mk/tree/main/Mk/Includes)

### Steps

1. Open `Shell/Make/makefile` and set:
   - `TOOLCHAIN_PATH` — path to your ARM toolchain `bin/` directory
   - `INCLUDES_API_PATH` — path to the Mk [`Includes/`](https://github.com/EmbSoft3/Mk/tree/main/Mk/Includes) directory

2. Build:

```
make clean
make all
```

This produces `shellRelease.elf`, ready to install on the target.

> Use the `Debug` target for a `-O0` build with full debug symbols:
> ```
> make Debug
> ```

The application is compiled as a position-independent shared object (`-fPIC -shared`) and is relocatable into any 64 KB SDRAM page by the Mk dynamic loader.

### Compiler versions

| Tool | Version |
|------|---------|
| `arm-none-eabi-gcc` | 10.3.1 20210824 (GNU Arm Embedded Toolchain 10.3-2021.10) |
| `arm-none-eabi-g++` | 10.3.1 20210824 (GNU Arm Embedded Toolchain 10.3-2021.10) |
| `make` | GNU Make 4.4.1 (Windows32) |

---

## Writing your own application

Shell is the reference example for the Mk application model. For a step-by-step guide
on how to structure your own Mk application — descriptor, entry point, event listeners,
memory layout — see the [Mk wiki](https://github.com/EmbSoft3/Mk/wiki/Writing-Your-First-Application).

---

## License

Copyright © 2024 **Mathieu Renard**. All rights reserved.

This project is licensed under the **BSD 3-Clause License** — see the
[LICENSE](LICENSE) file for details.
