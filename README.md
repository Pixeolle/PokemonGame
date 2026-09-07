# Pokémon Battle Simulator

A turn-based battle simulator in modern C++20, written as an exercise in memory ownership and object-oriented architecture rather than as a game.

## Focus

The gameplay is deliberately simple — the point of the project was what sits underneath it:

**Ownership over raw pointers.** Every owned entity is held through `std::unique_ptr`: a trainer owns its team, the loader hands ownership of parsed entities to the caller. Non-owning access is expressed by returning raw pointers or const references, so the type of every handle states who is responsible for the lifetime. Destruction follows scope automatically, with no manual `delete` anywhere in the codebase.

**Const-correctness as a design constraint.** Immutable attributes are declared `const` at the member level — a Pokémon's name, max HP, and types cannot change after construction. Accessors are `const` and `[[nodiscard]]`, so the compiler rejects both accidental mutation and silently discarded return values.

**Polymorphism through abstract interfaces.** `Interagir` declares a pure virtual `interact()`; `Entraineur` is an abstract base with pure virtual `defeated()` and `canInteract()`, specialized by `Joueur`, `Leader`, and `Maitre`. Base classes declare virtual destructors, so deleting through a base pointer destroys the derived object correctly.

**Meyer's singleton for the type chart.** `TypeManager` holds the type effectiveness matrix — global by nature, meaningless to duplicate. It uses a function-local static, which C++11 guarantees to be initialized exactly once and thread-safely on first use, avoiding the initialization-order problem of a namespace-scope static. All five special member functions are deleted so no copy or move can bypass the single instance.

## Architecture

| File | Role |
|---|---|
| `Pokemon` | Battle entity: stats, types, damage and healing |
| `Entraineur` | Abstract trainer base; owns a team of up to six Pokémon |
| `Joueur` / `Leader` / `Maitre` | Concrete trainers: player, gym leader, elite master |
| `TypeManager` | Singleton type effectiveness chart |
| `CombatManager` | Turn resolution and damage computation |
| `DataLoader` | CSV parsing into owned game entities |
| `Menu` | Console interface and game flow |
| `Types` / `Utils` | Type enum and conversions, shared helpers |

## Data files

The simulator is data-driven: Pokémon, trainers, and the type chart are all loaded from CSV at startup. **These files are not included in this repository** — the paths are configurable at launch. The expected schemas:

**Pokémon** — required columns: `Nom`, `Points de Vie`, `Type 1`, `Attaque`, `Dégâts d'Attaque`. Optional: `Type 2`.

**Player / Masters** — required columns: `Nom`, `Pokemon1` … `Pokemon6`, each referencing a Pokémon by name.

**Gym leaders** — same, plus `Gymnase` and `Medaille`.

**Type chart** — a matrix: the first row lists defending types from the second column onward, each subsequent row starts with an attacking type followed by its multipliers.

Type names must match the `Type` enum: `FEU`, `EAU`, `PLANTE`, `ELECTRIK`, `GLACE`, `COMBAT`, `POISON`, `SOL`, `VOL`, `PSY`, `INSECTE`, `ROCHE`, `SPECTRE`, `DRAGON`, `TENEBRES`, `ACIER`, `FEE`, `NORMAL`.

Missing required columns raise a `std::runtime_error` naming the offending file, and an unreadable path raises `std::invalid_argument` — failures surface at load time rather than as undefined behaviour mid-game.

## Building

```bash
cmake -B build
cmake --build build
```

Requires CMake 3.30+ and a C++20 compiler.

## Note

Class names, comments, and CSV column headers are in French, as the project was written in an academic context.