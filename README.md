# ttd

A simple ncurses-based terminal drawing program.

## Features

- Draw with multiple colors and symbols
- Based on C programming language and ncurses, so it is very fast and lightweight
- Simple command system

## How to use

Just run `./ttd`

## Key Bindings

| Key               | Action                 |
| ----------------- | ---------------------- |
| Arrow keys / WASD | Move cursor            |
| Space             | Draw at cursor         |
| Q / E             | Previous / Next color  |
| O / P             | First / Last color     |
| Z / C             | Previous / Next symbol |
| K / L             | First / Last symbol    |
| I                 | Eraser                 |
| :                 | Command Mode           |
| Esc               | Quit Command Mode      |
| X                 | Exit                   |

## Commands

- `:draw`           — Draw at current position
- `:draw +N`        — Draw right N times (stop at border)
- `:draw -N`        — Draw left N times (stop at border)
- `:draw +*`        — Draw right until border
- `:draw -*`        — Draw left until border
- `:draw (N`        — Draw up N times (stop at border)
- `:draw )N`        — Draw down N times (stop at border)
- `:draw (*`        — Draw up until border
- `:draw )*`        — Draw down until border
- `:move`           — Move cursor to (1, 1)
- `:move y x`       — Move cursor to (y, x)
- `:quit`           — Quit the program

Example:

```
:draw +10
:draw (*
:move 5 10
:quit
```

## Build

Install `libncurses5-dev` in your computer. Then run: `make`

## Other 

It is just a part of my programming learning.