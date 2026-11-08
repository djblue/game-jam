# froggy

## Build

To run or build the game from source, you will need a few dependencies installed:

### Dependencies

- java - platform specific
- [jank][install-jank]
- [babashka][install-bb]
- [lein][install-lein]

### Run the game

Lein is used to manage the project. To simply run the game, do:

```bash
lein run
```

If you would like a REPL as well, do:

```bash
lein repl # call (-main) to launch game window
```

### Appimage for Linux

```bash
lein appimage
./target/Froggy-x86_64.AppImage
```

### DMG for macos

```bash
brew install dylibbundler
lein dmg
open target/Froggy.dmg
```

> [!WARNING] 
> To open the `.app` in the DMG, you will need to allow it to run under macos
> security settings.

[install-jank]: https://book.jank-lang.org/getting-started/01-installation.html?highlight=install#installation
[install-bb]: https://github.com/babashka/babashka#installation
[install-lein]: https://leiningen.org/