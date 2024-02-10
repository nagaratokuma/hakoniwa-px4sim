English ｜ [日本語](README-ja.md)

[![Build](https://github.com/toppers/hakoniwa-px4sim/actions/workflows/build.yml/badge.svg)](https://github.com/toppers/hakoniwa-px4sim/actions/workflows/build.yml)

This repository is a simulation environment for drone plant models that can be integrated with PX4. This simulation environment accurately models drone behavior based on physical equations and is implemented in C language.


# Table of Contents

- [Features](#features)
- [Environment](#environment)
- [Preliminary Preparations](#preliminary-preparations)
- [Installation Instructions for hakoniwa-px4sim](#installation-instructions-for-hakoniwa-px4sim)
- [Installation Instructions for Hakoniwa](#installation-instructions-for-hakoniwa)
- [Simulation Execution Instructions](#simulation-execution-instructions)
- [Integration with MATLAB](#integration-with-matlab)
- [Effects from the Environment](#effects-from-the-environment)
- [Headless Simulation](#headless-simulation)
- [Community and Support](#community-and-support)
- [About This Repository and License](#about-this-repository-and-license)
- [Contribution Guidelines](#contribution-guidelines)

# Features

1. **Physics-based Plant Model:** Drone behavior is represented by high-precision models based on physics. Developed in C language, it seamlessly integrates with PX4. For more details, please refer [here](https://github.com/toppers/hakoniwa-px4sim/tree/main/drone_physics). It is capable of simulating physical reactions in real-time during collisions with obstacles (`v1.1.0`). For more details, see [here](#collision-with-obstacles).

2. **Visualization via Game Engines:** The visual representation of drones is realized using game engines. This visualization serves as an aid to physical simulations, primarily aimed at visualization purposes. Visual representation of collisions with obstacles is also possible (`v1.1.0`). For more details, see [here](#collision-with-obstacles).

3. **Engine Flexibility:** Currently supports the Unity engine, but the architecture is designed to enable integration with other game engines as well. A plugin for integration with Unreal Engine is available [here](https://github.com/toppers/hakoniwa-unreal-simasset-plugin/tree/main) (`v1.1.0`).

4. **Compatibility with MATLAB/Simulink:** The physics model can be integrated with models created in MATLAB/Simulink. For more details, see [here](#integration-with-matlab).

5. **Sensor Model Organization:** Sensor models are organized within the architecture based on clear specifications. This allows users to exchange sensor models according to the specifications. For more details, please refer [here](https://github.com/toppers/hakoniwa-px4sim/tree/main/docs/phys_specs).

6. **Headless Support:** Simulation can be run without Unity. This enables simulation execution in environments that do not require a graphical interface (`v1.1.0`). For more details, see [here](#headless-simulation).

7. **Support for Automated Testing:** Enables test scenario-based automated testing. This makes it possible to automate repeated and consecutive tests, thereby streamlining the development process. For more details, please refer [here](https://github.com/toppers/hakoniwa-px4sim/tree/main/px4/auto-test).

8. **External Parameterization of Aircraft Characteristics:** The characteristics of the drone can be parameterized externally. This allows for simulations tailored to various aircraft characteristics, enabling support for a wider range of test scenarios. For an example of parameter settings, see [here](https://github.com/toppers/hakoniwa-px4sim/blob/main/hakoniwa/config/drone_config.json).

![スクリーンショット 2024-01-30 10 22 34](https://github.com/toppers/hakoniwa-px4sim/assets/164193/be993a09-ac40-4328-9602-6a593cd105b1)

# Environment

* Supported OS:
  * Arm-based Macs (M1 Mac, M2 Mac)
  * Windows 10/11
* Required Environment:
  * For Arm-based Macs:
    * Python 3.10
      * Recommended to install via pyenv
      * Jinja2 (`pip install -U jinja2`)
  * For Windows:
    * Follow the same setup as the [Hakoniwa configuration example for Windows](https://github.com/toppers/hakoniwa-document/blob/main/architecture/examples/README-win.md).
* Drones to Use:
  * https://github.com/toppers/hakoniwa-unity-drone-model/tree/main
  * Please clone in the same directory structure as this repository:
    ```
    hakoniwa-unity-drone-model/
    hakoniwa-px4sim/
    ```

# Preliminary Preparations

Clone two repositories:

```
git clone --recursive https://github.com/toppers/hakoniwa-px4sim.git
```

```
git clone --recursive https://github.com/toppers/hakoniwa-unity-drone-model.git
```

For the installation instructions of hakoniwa-unity-drone-model, please refer to the following:

https://github.com/toppers/hakoniwa-unity-drone-model

# Installation Instructions for hakoniwa-px4sim

Follow the steps below to install PX4:

https://github.com/toppers/hakoniwa-px4sim/tree/main/px4


# Installation Instructions for Hakoniwa

Follow the steps below to install Hakoniwa:

https://github.com/toppers/hakoniwa-px4sim/tree/main/hakoniwa


# Simulation Execution Instructions

Prepare two terminals:

* Terminal A: For running the PX4 simulator
* Terminal B: For running Hakoniwa

## Terminal A

Navigate to the PX4-Autopilot directory:

```
cd hakoniwa-px4sim/px4/PX4-Autopilot
```

Launch PX4 on SITL:

```
bash ../sim/simstart.bash
```

Upon successful execution, it will wait for a connection on a TCP port as follows.

```
% bash ../sim/simstart.bash
[0/1] launching px4 none_iris (SYS_AUTOSTART=10016)

______  __   __    ___ 
| ___ \ \ \ / /   /   |
| |_/ /  \ V /   / /| |
|  __/   /   \  / /_| |
| |     / /^\ \ \___  |
\_|     \/   \/     |_/

px4 starting.

INFO  [px4] startup script: /bin/sh etc/init.d-posix/rcS 0
env SYS_AUTOSTART: 10016
INFO  [param] selected parameter default file parameters.bson
INFO  [param] importing from 'parameters.bson'
INFO  [parameters] BSON document size 568 bytes, decoded 568 bytes (INT32:14, FLOAT:13)
INFO  [param] selected parameter backup file parameters_backup.bson
INFO  [dataman] data manager file './dataman' size is 7868392 bytes
INFO  [init] PX4_SIM_HOSTNAME: localhost
INFO  [simulator_mavlink] Waiting for simulator to accept connection on TCP port 4560
```

Continuing from the previous step, we now switch to Terminal B.

## Terminal B

Navigate to the Hakoniwa directory:

```
cd hakoniwa-px4sim/hakoniwa
```

If you are using Windows, enter the Docker container with the following command:

```
bash docker/run.bash
```

Execute the script to launch Hakoniwa:

```
bash run.bash 
```

Upon successful execution, it will proceed as follows.

```
% bash run.bash 
HAKO_CAPTURE_SAVE_FILEPATH : ./capture.bin
HAKO_BYPASS_IPADDR : 127.0.0.1
HAKO_CUSTOM_JSON_PATH : ../config/custom.json
DRONE_CONFIG_PATH : ../config/drone_config.json
HAKO_BYPASS_PORTNO : 54001
INFO: shmget() key=255 size=1129352 
INFO: hako_master_init() success
Robot: DroneAvator, PduWriter: DroneAvator_drone_motor
channel_id: 0 pdu_size: 88
INFO: DroneAvator create_lchannel: logical_id=0 real_id=0 size=88
Robot: DroneAvator, PduWriter: DroneAvator_drone_pos
channel_id: 1 pdu_size: 48
INFO: DroneAvator create_lchannel: logical_id=1 real_id=1 size=48
WAIT START
INFO: px4 reciver start
INFO: COMMAND_LONG ack sended
```

At this point, on Terminal A, you may see messages regarding poll timeouts like the following, but this is not a cause for concern.

```
ERROR [simulator_mavlink] poll timeout 0, 111
ERROR [simulator_mavlink] poll timeout 0, 111
ERROR [simulator_mavlink] poll timeout 0, 111
```

## Unity

In this state, please start the Unity simulation.

![Screenshot 2024-01-26 9 34 16](https://github.com/toppers/hakoniwa-px4sim/assets/164193/1f6c417d-cb58-4c21-9dd0-7b59964eeadf)

Then, by pressing the `START` button, the simulation will begin.


## Terminal A

At this time, Terminal A will enter a ready state as follows.

```
INFO  [lockstep_scheduler] setting initial absolute time to 1699681315573127 us
INFO  [commander] LED: open /dev/led0 failed (22)
WARN  [health_and_arming_checks] Preflight Fail: ekf2 missing data
INFO  [mavlink] mode: Normal, data rate: 4000000 B/s on udp port 18570 remote port 14550
INFO  [mavlink] mode: Onboard, data rate: 4000000 B/s on udp port 14580 remote port 14540
INFO  [mavlink] mode: Onboard, data rate: 4000 B/s on udp port 14280 remote port 14030
INFO  [mavlink] mode: Gimbal, data rate: 400000 B/s on udp port 13030 remote port 13280
INFO  [logger] logger started (mode=all)
INFO  [logger] Start file log (type: full)
INFO  [logger] [logger] ./log/2023-11-11/05_41_55.ulg	
INFO  [logger] Opened full log file: ./log/2023-11-11/05_41_55.ulg
INFO  [mavlink] MAVLink only on localhost (set param MAV_{i}_BROADCAST = 1 to enable network)
INFO  [mavlink] MAVLink only on localhost (set param MAV_{i}_BROADCAST = 1 to enable network)
INFO  [px4] Startup script returned successfully
pxh> INFO  [tone_alarm] home set
INFO  [tone_alarm] notify negative
INFO  [commander] Ready for takeoff!
```

At this point, please execute the following command in Terminal A:

```
commander takeoff
```

Upon success, the drone in Unity will start hovering.

![Screenshot 2024-01-26 9 36 02](https://github.com/toppers/hakoniwa-px4sim/assets/164193/eba3b933-6789-4a2e-b742-de27a1ae1bce)

## How to Stop the Simulation

To stop the simulation, please follow these steps in order:

1. Stop the Unity simulation.
2. Stop the PX4 simulation with CTRL+C.
3. Stop the Hakoniwa simulation with CTRL+C.

## How to Integrate with QGroundControl

By installing [QGroundControl](http://qgroundcontrol.com/), you can control the aircraft from QGC.

After launching QGC, you need to set up the connection with PX4.

Click on the logo at the top right of the screen to access the "Application Settings," as shown in the image below.

![image](https://github.com/toppers/hakoniwa-px4sim/assets/164193/b17cd3a1-23c3-4b0b-b46c-d4c98d375102)

Next, click on "Comm Links" and then press the "Add" button.

![image](https://github.com/toppers/hakoniwa-px4sim/assets/164193/60389069-46a5-4801-aba5-af06f7582a53)

Make the necessary settings.

![image](https://github.com/toppers/hakoniwa-px4sim/assets/164193/6d916332-7be6-4f33-855d-cc657919076b)

Set the following:

* Name: `hakoniwa` (you can specify any name you like)
* Type: `UDP`
* Port: `18570`
* Server Address: The setting differs depending on the OS
  * For Windows: On WSL2, check and set the IP address of eth0.
  * For non-Windows: Check and set the IP address of your ethernet.

Example of how to check the IP address:

```
$ ifconfig eth0
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 172.29.246.4  netmask 255.255.240.0  broadcast 172.29.255.255
        inet6 fe80::215:5dff:feae:5d59  prefixlen 64  scopeid 0x20<link>
        ether 00:15:5d:ae:5d:59  txqueuelen 1000  (Ethernet)
        RX packets 2104410  bytes 2461696811 (2.4 GB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 1152573  bytes 1569239960 (1.5 GB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```

After setting up, press the "Add Server" button and then click the "OK" button.

![image](https://github.com/toppers/hakoniwa-px4sim/assets/164193/1da37afa-886d-4122-b115-b7f12808fb75)

Finally, clicking the "Connect" button will complete the setup.

![image](https://github.com/toppers/hakoniwa-px4sim/assets/164193/cb40933f-329c-4f86-bac8-782be71f7de2)

Below is an example of operating QGC:

https://github.com/toppers/hakoniwa-px4sim/assets/164193/88934527-58dd-46f7-abc1-0e2d49c44935

1. Takeoff
2. Move east
3. Move north

# Integration with MATLAB

From version v2.0.0 onwards, the feature to generate code from models created in MATLAB/Simulink and simulate them on Hakoniwa has been supported.

Currently, the supported features are as follows:

- [X] Drone Physics Model
- [ ] Sensor Model
- [ ] Actuator Model

## Overview of the Development Flow

The process of migrating models from MATLAB/Simulink to the Hakoniwa simulation environment is as illustrated below.

Currently, the flow involves constructing drone physics models for a predefined C interface in Hakoniwa. Future updates are planned to develop the workflow further, including interface definitions and incorporating sensors/actuators.

![Screenshot 2024-01-31 13 49 04](https://github.com/toppers/hakoniwa-px4sim/assets/164193/be7e404f-c6b4-4b2a-8545-aec4239f7043)

* MATLAB/Simulink Hakoniwa Templates
  * Interfaces for MATLAB/Simulink models are defined on the Hakoniwa side. For more details, see [here](https://github.com/toppers/hakoniwa-px4sim/blob/main/matlab-if/README.md).
  * Templates for connecting MATLAB/Simulink models to Hakoniwa are provided. For more details, see [here](https://github.com/toppers/hakoniwa-px4sim/tree/main/matlab-if/model_template).
* MATLAB/Simulink Process
  * With the Hakoniwa input/output interfaces defined in the template, create a model that converts input data to output data.
  * Simulate and check the created model in MATLAB.
  * After verifying the simulation in MATLAB, generate C code.
* Hakoniwa Simulation Process
  * Place the generated C code under `matlab-if` in hakoniwa-px4sim.
  * Edit the `CMakeLists.txt` under `matlab-if` to include it in the build targets (inside the `HAKONIWA_MATLAB_BUILD` block).
  * Compile according to the Hakoniwa build process.
  * Once compilation is successful, proceed with the simulation according to the Hakoniwa simulation execution process.

# Effects from the Environment

From version v1.1.0 onwards, it is possible for the drone in the simulation environment to be affected by external environmental factors.

For instance, using a game engine, it is possible to simulate in real-time the physical impact of a drone colliding with an obstacle.

The current support situation is as follows:

- [X] Collision with obstacles
- [ ] Impact of wind
- [ ] Effects of direct sunlight

## Collision with Obstacles

By placing obstacles within the game engine, information about the aircraft's interaction with these obstacles can be fed back to the physical model.

To use this feature, set the `collision_detection` parameter in `droneDynamics` to `true`.

Example of settings:

```json
      "droneDynamics": {
          "physicsEquation": "BodyFrame",
          "collision_detection": true,
          "manual_control": false,
          "airFrictionCoefficient": [ 0.0001, 0.0 ],
          "inertia": [ 0.0000625, 0.00003125, 0.00009375 ],
          "mass_kg": 0.1,
          "body_size": [ 0.1, 0.1, 0.01 ],
          "position_meter": [ 0, 0, 0 ],
          "angle_degree": [ 0, 0, 0 ]
        },
```

Example of execution:

https://github.com/toppers/hakoniwa-px4sim/assets/164193/c1305966-d782-42f4-bd5b-13c57b1ff726


# Headless Simulation

In Hakoniwa, drones can be tested for PID control without the use of Unity and PX4 (headless simulation). This is convenient for checking the operation of the drone dynamics you have created.

https://github.com/toppers/hakoniwa-px4sim/tree/main/hakoniwa/src/assets/drone/controller

# Community and Support

Questions and discussions about this project take place on the [Hakoniwa Community Forum](https://github.com/toppers/hakoniwa/discussions). Here, you can resolve doubts about the project, share ideas, and provide feedback. Information on the latest news and updates about the project is also shared here.

If you have questions or suggestions about the project, or if you want to exchange opinions with other users facing the same issues, please feel free to post [here](https://github.com/toppers/hakoniwa/discussions).

# About This Repository and License

The content of this repository is open under the license specified in each file. For content that is not specifically licensed, it is published under the [TOPPERS License](https://www.toppers.jp/license.html).

The TOPPERS License is a license for open-source projects, setting conditions for the use, modification, and distribution of software. For details about the license, please refer to the link above.

# Contribution Guidelines

Thank you for your interest in contributing to this project. Contributions of various forms are welcomed. Below are guidelines for contributing to the project.

## Reporting Issues

- Please use GitHub Issues to report bugs or suggest new features.
- Before creating an issue, check if there is already an existing issue on the same topic.
- When creating an issue, provide as much information as possible, including steps to reproduce, expected behavior, actual behavior, and your environment.

## Pull Requests

- Contributions related to code, such as adding new features or fixing bugs, should be made through pull requests.
- For adding new features or making significant changes, it is recommended to discuss it in a related issue beforehand.
- Please follow the existing code style and coding standards to maintain consistency.

## Communication

- Use [Discussions](https://github.com/toppers/hakoniwa/discussions) for project-related discussions and questions.
- Communicate with other contributors with respect.

## Other Contributions

- Improvements to documentation and translations, among other non-code contributions, are also welcome.
