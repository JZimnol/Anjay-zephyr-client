# Sensors in Embedded Applications Project

This directory contains files that implement LwM2M Client Application which
targets [esp32](https://www.espressif.com/en/products/devkits/esp32-devkitc)
board with [ENS210](https://eu.mouser.com/new/sciosense/ams-ens210-sensor/)
sensor connected via ``I2C`` interface.

## Supported objects

This application supports the following LwM2M objects:
* ``/0`` (Security)
* ``/1`` (Server)
* ``/3`` (Device)
* ``/3303`` (Temperature)
* ``/3304`` (Humidity)

## Compilation

Set West manifest path to ``Anjay-zephyr-client/agh_swaw_project``, and manifest
file to ``west.yml`` and do ``west update``.

```
west config manifest.path Anjay-zephyr-client/agh_swaw_project
west config manifest.file west.yml
west update
```

You can now compile the project for esp32 board using the ``west build -b
esp32`` command in the ``agh_swaw_project`` directory.

```
cd Anjay-zephyr-client/agh_swaw_project
west build -b esp32
```

After successful build you can flash the target using ``west flash``.
