# Moveo BCN3D Firmware

Moveo is an alternative firmware for the Open source 3D printer robot arm [BCN3D-MOVEO](https://www.bcn3dtechnologies.com/en/bcn3d-moveo-the-future-of-learning/) based on the [Arduino](https://www.arduino.cc/) platform.

## Contributing

If you have coding or writing skills you're encouraged to contribute to Moveo firmware. You may also contribute suggestions, feature requests, and bug reports through the moveo-firmware Issue Queue.

## Resources

- [BCN3D-MOVEO Announcement](https://www.bcn3dtechnologies.com/en/bcn3d-moveo-the-future-of-learning/) - The BCN3D-MOVEO announcement.
- [BCN3D-MOVEO Repository](https://github.com/BCN3D/BCN3D-Moveo) - All BCN3D-MOVEO information.

## License

Moveo firmware is published under the [GPLv3 license](https://raw.githubusercontent.com/eballetbo/moveo-firmware/master/LICENSE) because we believe in open development. The GPL comes with both rights and obligations. Whether you use the Moveo firmware as the driver for your open or closed-source product, you must keep Moveo open, and you must provide your compatible Moveo source code to end users upon request. The most straightforward way to comply with the Moveo license is to make a fork of Moveo on Github, perform your modifications, and direct users to your modified fork.

## G-codes subset

This section tries to describe the flavour of G-codes that the Moveo firmware use and how they work.

### G1 : Linear Interpolation

**Usage:**
```
G1 Xnnn Ynnn Znnn Annn Bnnn
```

**Parameters:**

All parameters are required, but if you don't want to move a specific axis just put 0.
```
Xnnn The position to move to on the X axis (in steps)
Ynnn The position to move to on the Y axis (in steps)
Znnn The position to move to on the Z axis (in steps)
Annn The position to move to on the A axis (in steps)
Bnnn The position to move to on the B axis (in steps)
```

**Examples:**
```
G1 10 -15 20
G1 10 0 0 -20 20
```

### M280 : Set servo positon

**Usage:**
```
M280 Annn
```

**Parameters:**

All parameters are required.
```
Annn The angle (between 0 and 180)
```

**Examples:**
```
M280 0
M280 90
```
