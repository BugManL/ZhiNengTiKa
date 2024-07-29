# 智能题卡

## 如何使用
可以通过新教育题卡二维码或编号获取答案

## 开发

### 编译

- 必要条件:

> `Qt` `qmake` `git`

#### 编译环境
>Windows: Qt 6.7.2 + MSVC2019

>Android: Qt 6.7.2 + NDK 25.1.8937393 + JDK 17

#### 如何编译

1. 运行 `configuration.bat` 文件

2. 使用 `qmake` 编译 `3rd_build.pro`项目

3. 使用 `qmake` 编译 `ZhiNengTiKa.pro`项目

## 致谢

### 开源库

- AES加解密: [Qt-AES](https://github.com/bricke/Qt-AES)
- 二维码扫描: [ZXing-C++](https://github.com/zxing-cpp/zxing-cpp)

## 未来目标

- 功能
    - [ ] 提交题卡相关改为MVC框架
- 性能

## ⚡ Visitor count

![](https://profile-counter.glitch.me/LFWQSP2641-ZhiNengTiKa/count.svg)