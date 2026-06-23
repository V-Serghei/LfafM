# LFaf

LFaf is a console C++ project for working with formal grammar production rules. The program reads grammar rules from standard input, applies a sequence of transformations, and prints the result after each step.

The project currently supports two main workflows:

- converting a grammar to Chomsky normal form;
- converting a grammar to Greibach normal form.

Epsilon productions are represented by `0`.

## Program Behavior

After startup, the application shows this menu:

```text
1) Normal Form Of Khom
2) Normal form of Greibach
3) End
```

The Chomsky normal form workflow:

1. reads grammar rules;
2. removes epsilon productions;
3. removes unreachable symbols;
4. removes unproductive symbols;
5. removes chain replacements;
6. converts the rules to Chomsky normal form.

The Greibach normal form workflow:

1. reads grammar rules;
2. removes epsilon productions;
3. removes unreachable and unproductive symbols;
4. removes left recursion;
5. converts the rules to Greibach normal form;
6. prints the final rules and their notation as `A0`, `A1`, `A2`, and so on.

## Input Format

Each production rule is entered on a separate line:

```text
S AC
A a
C 0
```

The left-hand side must start with an uppercase letter. The left-hand side and right-hand side must be separated by a space. To finish entering rules, type:

```text
end
```

Example input:

```text
S AC
A d
A dS
A BdB
B a
B aA
B BC
C bC
C 0
end
```

## Project Structure

```text
.
|-- .github/
|   `-- workflows/
|       `-- ci.yml
|-- CMakeLists.txt
|-- README.md
|-- include/
|   `-- lfaf/
|       `-- RegularLanguage.h
|-- src/
|   |-- main.cpp
|   `-- RegularLanguage.cpp
`-- tests/
    `-- regular_language_tests.cpp
```

- `src/main.cpp` contains the console menu and the order in which algorithms are executed.
- `include/lfaf/RegularLanguage.h` declares the `RegularLanguage` class, its state, and public operations.
- `src/RegularLanguage.cpp` implements rule input, grammar cleanup, and normal form transformations.
- `tests/regular_language_tests.cpp` contains basic CTest checks for helper methods.
- `.github/workflows/ci.yml` builds the project and runs tests for the `master` branch.
- `CMakeLists.txt` defines the `LFaf` executable, the core library, and the test target.

## Build And Run

Requirements:

- CMake;
- a C++ compiler with C++20 support.

Build from the project root:

```bash
cmake -S . -B build
cmake --build build
```

Run tests:

```bash
ctest --test-dir build --output-on-failure
```

Run on Windows:

```bash
.\build\LFaf.exe
```

If you use CLion, open the repository as a CMake project and run the `LFaf` target from the IDE.

## Usage

1. Start the program.
2. Choose `1` for Chomsky normal form or `2` for Greibach normal form.
3. Enter grammar rules, one rule per line.
4. Use `0` for epsilon productions.
5. Enter `end` to finish rule input.
6. Review the intermediate and final rules printed in the console.
