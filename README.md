# Cloudsense

## Getting Started

### Prerequisites

This project is designed to be developed inside a **VS Code Dev Container**.
This ensures a consistent build environment with all Zephyr dependencies
pre-installed.

- Install [Docker Desktop](https://www.docker.com/products/docker-desktop/)
- Install [VS Code Dev Containers Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

### Quick Start (Inside Container)

Once the container starts, the `postStartCommand` automatically initializes the
workspace. You can build the firmware immediately:

```bash
# Build for the Native Simulator
west build -b native_sim firmware

# Run the simulation (press CTRL+C to exit)
./build/zephyr/zephyr.exe
```
