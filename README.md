A cross-platform crash handling system for Geometry Dash that automatically saves your progress when the game crashes.

## What it does

- Detects crashes and unexpected shutdowns
- Automatically saves your game progress
- Saves level editor progress
- Works on Windows, macOS, iOS, and Android
- Provides crash callbacks for other mods to use

## For developers

Other mods can register their own crash callbacks.

Add to your `mod.json` the `dependencies`:
```json
"dependencies": {
	"user95401.save-on-crash-handler": ">=v1.0.0"
}
```
(supports `suggested` type)

Usage:

```cpp
// Contains MBO and tools for shared CrashHandler*
#include <user95401.save-on-crash-handler/include/main.hpp>

void setupCrashHandler();
$on_mod(Loaded) { setupCrashHandler(); }
inline void setupCrashHandler() {
    CrashHandler::get()->onCrash(
        [](const std::string& crashInfo) {
            // Your crash handling code here
            log::info("Crash detected: {}", crashInfo);
        }
    );
}
```

Parameters of `onCrash` and `onLevelSavedAtCrash`:
- `callback`: New function for callbacks list
- `prepend`: Add to front of callback list (default: false)  
- `replace`: Replace all existing callbacks (default: false)

## Technical details

- Uses signal handlers (SIGSEGV, SIGBUS, SIGFPE, SIGILL) on Unix-like systems
- Tries to use structured exception handling on Windows
- Includes stack traces on macOS/iOS

## Notes

- Crash detection isn't 100% guaranteed for all crash types
- Some crashes might be too severe to allow saving
- Stack overflow crashes are particularly hard to handle
- Works best with access violations and similar common crashes