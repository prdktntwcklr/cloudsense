# Cloudsense

**Cloudsense** is a reference implementation for hardware-independent firmware
development using Zephyr RTOS. By simulating sensors and abstracting hardware,
it allows developers to prototype, test, and integrate firmware in CI pipelines
without physical devices—reducing development bottlenecks and accelerating
delivery.

## Getting Started

### Prerequisites

The project runs inside a **VS Code Dev Container**, ensuring a consistent
environment with all required dependencies pre-installed.

- Install [Docker Desktop](https://www.docker.com/products/docker-desktop/)
- Install [VS Code Dev Containers Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

### Quick Start (Inside the Container)

The `postStartCommand` automatically initializes the workspace when the
container starts. You can then immediately build and run the firmware:

```bash
# Build for the Native Simulator (no hardware required)
west build -b native_sim firmware

# Run the binary (press CTRL+C to exit)
./build/zephyr/zephyr.exe
```

## Automated Testing

The project includes a set of unit, integration, and end-to-end tests. To run
the tests, use:

```bash
# Run all automated tests with the "cloudsense" tag
west twister -p native_sim -T firmware -t cloudsense --outdir test-results -v
```

## Hardware-Independent Simulation

Cloudsense includes a simulated temperature sensor driver which allows
developers to:

- Build and test firmware without waiting for physical hardware
- Rapidly prototype features and validate application logic
- Run automated tests locally and in CI pipelines
- Easily migrate to real hardware with board-specific configurations, while
keeping the application code unchanged
