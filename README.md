# 📈 Function Graph Visualizer

A portable ANSI C console application that parses and visualizes mathematical functions of a single real variable. The output is a PostScript file (.ps) containing a graph of the given function.

## 🚀 Features

- Parse mathematical expressions (including operations like `+`, `-`, `*`, `/`, `^` and functions like `sin`, `cos`, `log`).
- Validate function syntax automatically.
- Generate smooth and scaled PostScript graphs.
- Allow optional specification of the x- and y-axis range.
- Cross-platform support (Windows and Linux).

## 🔧 Installation

### Build

- **Windows**:  
  Use `mingw32-make` (Makefile provided).

- **Linux**:  
  Use `make`.

This will produce the executable `graph.exe` (or `graph` on Linux) in the current directory.

## 📜 Usage

```bash
graph.exe <expression> <output_file> [<limits>]
```

- `<expression>`: Mathematical expression involving variable `x`.  
- `<output_file>`: Name of the output PostScript file (e.g., `graph.ps`).  
- `[<limits>]` (optional): Format `xmin:xmax:ymin:ymax` (e.g., `-10:10:-1:1`).

**Example:**

```bash
graph.exe "sin(x^2)" graph.ps -10:10:-1:1
```

This command draws the graph of the function `sin(x²)` over `x ∈ [-10, 10]` and `y ∈ [-1, 1]`.

If the `[<limits>]` argument is not provided, the default range `x ∈ [-10, 10]` and `y ∈ [-5, 5]` is used.

**Note**: Do not use spaces in the expression!

## 🧠 Internals

The application consists of multiple modules:

- **Tokenizer**: Breaks input into tokens (operators, numbers, functions).
- **Parser**: Converts the expression into postfix notation using the **Shunting-yard algorithm** and builds an **expression tree**.
- **Evaluator**: Recursively computes y-values from the expression tree for given x-values.
- **Graph Generator**: Creates a smooth and scaled graph using PostScript commands.
- **Main Program**: Handles command-line arguments and orchestrates all modules.

## 📷 Output Examples

| Expression | Limits | Example Output |
|------------|--------|----------------|
| `sin(x^2)*cos(x)` | `-10:10:-5:5` | Graph of `y = sin(x²)·cos(x)` |
| `ln(sin(x))` | `0:10:-5:0` | Graph of `y = ln(sin(x))` |

Generated graphs include axes, gridlines, and automatic scaling for better readability.

## 📌 Future Improvements

- Support for user-defined functions.
- Export graphs to other formats (SVG, PNG).
- Interactive GUI input.
- Graph analytics like derivatives or integrals.
