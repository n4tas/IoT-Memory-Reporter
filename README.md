# IoT Memory Reporter

**IoT Memory Reporter** is a daemon program designed specifically for the RUTX Teltonika routers. It monitors the memory usage of the router and reports this data to the Tuya IoT Cloud platform. This project aims to enhance resource management and facilitate remote monitoring of the router's memory status.

## Features

- **Memory Monitoring**: Continuously monitors various memory metrics, including total, free, shared, buffered, available, and cached memory.
- **Tuya Integration**: Reports memory usage statistics to the Tuya IoT Cloud, enabling real-time insights and alerts.
- **Daemon Mode**: Runs as a background service on the RUTX router, ensuring minimal interference with user activities.

## Requirements

- RUTX10 Teltonika router (OpenWRT-based system)
- Necessary libraries: 
  - `libjson-c`
  - `libtuya`
  - `libubus`
  - `libubox`
  - `libblobmsg-json`

## Installation

To install **IoT Memory Reporter**, follow these steps:

1. **Clone the repository**:

   ```bash
   git clone https://github.com/yourusername/iot-memory-reporter.git
   cd iot-memory-reporter
   ```

2. **Configure the router**:
    ```bash
    make menuconfig
    ```

3. **Build the project**:

   ```bash
   make
   ```

4. **Configure packages**:
    ```bash
    make menuconfig
    ```

5. **Install the package**:

   ```bash
   make package/IoT_Memory_Reporter/install
   ```

6. **Configure the daemon**:

   - Edit the configuration file `files/iot_mem.config` to set your Tuya credentials

6.5. **Enable the daemon**:
    - To ensure that the daemon starts on restart, enter the command on your router:
    ```bash
    /etc/init.d/iot_mem enable
    ```

7. **Start the daemon**:

   ```bash
   /etc/init.d/daemon start
   ```

## Usage

After starting the daemon, it will automatically begin monitoring memory usage and reporting the data to the Tuya IoT Cloud every 5 seconds. Check the logs using the command:

## Acknowledgments

- Thanks to the developers of the libraries used in this project, including **Tuya SDK**, **libubus**, and others.
- Special thanks to the OpenWRT community for their invaluable support.
