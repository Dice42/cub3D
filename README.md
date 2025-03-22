# cub3D

cub3D is a simple 3D game engine developed as part of the 42 curriculum. It uses raycasting techniques to render a 3D representation of a 2D map, similar to early first-person shooter games like **Wolfenstein 3D**.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Resources](#resources)
- [Contributing](#contributing)
- [License](#license)

## Features

- Real-time rendering with raycasting
- Textured walls and sprites
- Basic movement and collision detection
- Mini-map implementation
- Keyboard controls for navigation

## Requirements

- **Operating System:** macOS or Linux
- **Compiler:** `gcc`
- **Libraries:**
  - [minilibX](https://harm-smits.github.io/42docs/libs/minilibx): A simple X-Window library for rendering graphics

## Installation

1. **Clone the repository:**

   ```bash
   git clone https://github.com/yourusername/cub3D.git
   cd cub3D
   ```

2. **Install minilibX:**

   Follow the instructions in the [minilibX documentation](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html) to install the library on your system.

3. **Compile the project:**

   ```bash
   make
   ```

   This will generate the `cub3D` executable in the root directory.

## Usage

Run the program with a valid map file:

```bash
./cub3D maps/your_map.cub
```

- **Map Files:**
  - Must have a `.cub` extension
  - Define the layout, textures, and configurations
  - Ensure the map adheres to the project specifications

### Example

```bash
./cub3D maps/demo.cub
```

## Controls

- **W / Up Arrow:** Move forward
- **S / Down Arrow:** Move backward
- **A:** Move left
- **D:** Move right
- **Left Arrow:** Turn left
- **Right Arrow:** Turn right
- **Esc:** Exit the game

## Project Structure

- `src/`: Source code files
- `include/`: Header files
- `maps/`: Map files
- `textures/`: Texture images
- `Makefile`: Compile instructions

## Resources

- [minilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
