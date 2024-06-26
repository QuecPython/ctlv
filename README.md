# TLV Serialization Format - C Language Implementation (ctlv)

[中文](README_ZH.md) | English

## Overview

TLV (Type Length Value) is a data encoding format composed of the type of data (Tag), length of data (Length), and value of data (Value). This format is widely used in fields such as data communication and protocol design because it is simple, efficient, and has good scalability.

`ctlv` is a TLV structure codec written in C language, which is commonly used in serial port, Bluetooth, and even network data transmission.

## Usage

- [API Reference Manual](./docs/en/API_Reference.md)
- [Example Code](./code/demo.c)

## Contribution

We welcome contributions to improve this project! Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/your-feature`).
3. Commit your changes (`git commit -m 'Add your feature'`).
4. Push to the branch (`git push origin feature/your-feature`).
5. Open a Pull Request.

## License

This project is licensed under the Apache License. See the [LICENSE](LICENSE) file for details.

## Support

If you have any questions or need support, please refer to the [QuecPython documentation](https://python.quectel.com/doc/en) or open an issue in this repository.