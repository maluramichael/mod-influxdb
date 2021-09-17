# InfluxDB Module

## Description

Sends player and server events to an influx db instances via the /write API.

## How to use ingame

Right now there is nothing you can do ingame. Works automagically on the worldserver.

## Requirements

InfluxDB Module requires:

- AzerothCore v3.0.0+
- libcurl

## Installation

1) Simply `git clone` the module under the `modules` directory of your AzerothCore source or copy paste it manually.
2) Install libcurl development libraries. For example on debian run `apt install -y libcurl4-openssl-dev`
3) Re-run cmake and launch a clean build of AzerothCore.


## TODO

* Implement authentication
* Handle more player and world scripts
* Make tracked events configurable
* Implement a windows build
* Handle possible crashes when influxdb is not avaible
* Add realm identifier to track multiple realms

## Edit the module's configuration (optional)

If you need to change the module configuration, go to your server configuration directory (where your `worldserver` or `worldserver.exe` is), copy `InfluxDB.conf.dist` to `InfluxDB.conf` and edit that new file.

## Credits

* [Me](https://github.com/maluramichael) (author of the module)
* AzerothCore: [repository](https://github.com/azerothcore) - [website](http://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)
