# 智能题卡

---

# 停止更新说明

感谢大家一直以来对这个项目的支持与贡献！由于我已经毕业，且目前没有平台账号和相关的条件继续维护该项目，因此我将停止对该仓库进行更新。

尽管如此，我仍然欢迎大家提交PR（拉取请求）和报告Bug Issues。我会尽力审阅和回应这些贡献，尽管更新频率可能会较低。

感谢大家的理解与支持！

---

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
  - [ ] 错题本功能
  - [ ] ~~启动器多平台支持~~
- 性能
  - [ ] 使用MVC优化题卡数据显示

## ⚡ Visitor count

![](https://profile-counter.glitch.me/LFWQSP2641-ZhiNengTiKa/count.svg)