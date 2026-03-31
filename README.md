# Cloudsense

**Cloudsense** is a hardware-agnostic firmware project built on Zephyr RTOS,
designed for rapid prototyping and testing of sensor-based applications. By
leveraging simulated (dummy) sensors and flexible board configurations,
Cloudsense enables development, testing, and CI workflows without requiring
physical hardware.

## Getting Started

### Prerequisites

This project is designed to run inside a **VS Code Dev Container**, ensuring a
consistent environment with all Zephyr dependencies pre-installed.

- Install [Docker Desktop](https://www.docker.com/products/docker-desktop/)
- Install [VS Code Dev Containers Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

### Quick Start (Inside the Container)

The `postStartCommand` automatically initializes the workspace when the
container starts. You can immediately build and run the firmware:

```bash
# Build for the Native Simulator
west build -b native_sim firmware

# Run the binary (press CTRL+C to exit)
./build/zephyr/zephyr.exe
```

## Running tests

Run the full test suite using `west twister`:

```bash
# Run all tests with the "cloudsense" tag
west twister -p native_sim -T firmware -t cloudsense --outdir test-results -v
```

## Dummy Temperature Sensor & Hardware Agnostic Development

Cloudsense includes a dummy temperature sensor driver for Zephyr RTOS which
enables developers to:

- Develop and test sensor-based features without real hardware
- Run firmware in the native simulator (`native_sim`)
- Rapidly prototype and validate features
- Maintain portable, hardware-agnostic application logic

### Extending or Using the Dummy Sensor

- Enabled by default in the native simulator configuration
- Add custom simulated sensor data by extending the driver in `firmware/drivers/sensor/dummy_sensor/`
- Easily switch to real hardware by adding your board configuration and device
tree overlays

This design keeps the codebase flexible, testable, and portable across different
hardware platforms.
