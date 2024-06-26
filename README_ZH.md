# TLV序列化格式 —— C语言实现（ctlv）

中文 | [English](README.md)

## 概述

 TLV（Type-Length-Value）是一种数据编码格式，由数据的类型（Tag）、数据的长度（Length）、数据的值（Value）组成。这种格式在数据通信、协议设计等领域广泛应用，因为它简单高效且具有良好的可扩展性。 

`ctlv`是用 C 语言编写的 TLV 结构编解码器，在串口、蓝牙甚至网络数据传输中比较常用。

## 用法

- [API 参考手册](./docs/zh/API参考手册.md)
- [示例代码](./code/demo.c)

## 贡献

我们欢迎对本项目的改进做出贡献！请按照以下步骤进行贡献：

1. Fork 此仓库。
2. 创建一个新分支（`git checkout -b feature/your-feature`）。
3. 提交您的更改（`git commit -m 'Add your feature'`）。
4. 推送到分支（`git push origin feature/your-feature`）。
5. 打开一个 Pull Request。

## 许可证

本项目使用 Apache 许可证。详细信息请参阅 [LICENSE](LICENSE) 文件。

## 支持

如果您有任何问题或需要支持，请参阅 [QuecPython 文档](https://python.quectel.com/doc) 或在本仓库中打开一个 issue。
