# SalaryCat 72x40 OLED

把开源项目 [Einswen/SalaryCat](https://github.com/Einswen/SalaryCat) 里的 `cat.GIF` 转成 72x40 单色轮廓点阵，并在 ESP32-C3 Super Mini + 0.42 寸 OLED 上循环播放。

当前工程已经内置转换后的 28 帧动画，刷入后无需文件系统、SD 卡或网络，开发板上电即可显示月薪猫。

## 效果

- 屏幕：72x40 I2C OLED
- 动画：28 帧月薪猫轮廓动画
- 帧率：约 22 FPS
- 接口：I2C
- 默认引脚：`SDA=IO5`，`SCL=IO6`

## 硬件清单

- ESP32-C3 Super mini带OLED屏[点击购买](https://item.taobao.com/item.htm?id=965597504812&mi_id=0000Tsyfi7JPjkZA0IVB35pOD8qbz-8FKhmi1us6fzx1GGE&skuId=6070989050842&spm=tbpc.boughtlist.suborder_itempic.d965597504812.41152e8dD6MavP) 

## 接线

| OLED | ESP32-C3 Super Mini |
| --- | --- |
| `VCC` | `3V3` |
| `GND` | `GND` |
| `SDA` | `IO5` |
| `SCL` | `IO6` |

如果你的 OLED 模块支持 5V 供电，也建议优先接 `3V3`，这样和 ESP32-C3 的 I2C 电平更一致。

## PlatformIO 快速烧录

推荐使用 PlatformIO，工程已经带好 `platformio.ini`。

1. 安装 VS Code 和 PlatformIO 插件，或安装 PlatformIO Core。
2. 克隆本仓库。
3. 插上 ESP32-C3 Super Mini。
4. 如端口不是 `COM21`，修改 `platformio.ini` 里的 `upload_port` 和 `monitor_port`。
5. 编译上传：

```powershell
pio run -t upload
```

上传成功后开发板会自动复位，OLED 会开始播放动画。

## Arduino IDE 使用

也可以用 Arduino IDE 打开 `YueXinCat72x40/YueXinCat72x40.ino`。

1. 安装 ESP32 开发板支持。
2. 安装库：`U8g2`
3. 选择 ESP32-C3 相关开发板。
4. 打开 `YueXinCat72x40/YueXinCat72x40.ino`。
5. 编译上传。

代码中已经固定 I2C 引脚：

```cpp
constexpr uint8_t OLED_SDA = 5;
constexpr uint8_t OLED_SCL = 6;
Wire.begin(OLED_SDA, OLED_SCL);
```

## 屏幕型号不一致

当前默认使用 SSD1306 72x40：

```cpp
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
```

如果你的 72x40 OLED 是 SH1106，可以尝试替换为：

```cpp
U8G2_SH1106_72X40_WISE_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
```

如果屏幕完全不亮，优先检查：

- `SDA` 和 `SCL` 是否接反
- OLED 是否为 3.3V 供电
- I2C 地址是否为常见的 `0x3C`
- 控制芯片是否不是 SSD1306

## 文件结构

```text
.
├── YueXinCat72x40/
│   ├── YueXinCat72x40.ino   # 主程序
│   └── cat_frames.h         # 72x40 单色动画点阵
├── platformio.ini           # PlatformIO 配置
├── README.md
└── .gitignore
```

## GIF 来源与说明

动画帧由 [Einswen/SalaryCat](https://github.com/Einswen/SalaryCat) 的 `cat.GIF` 转换而来：

- 原 GIF 尺寸：240x240
- 原 GIF 帧数：28 帧
- 本工程转换尺寸：72x40
- 转换方式：裁剪主体、缩放、二值化、边缘轮廓提取、打包为 XBM 格式字节数组

感谢原项目作者。原项目采用 Apache-2.0 License，本工程中的 `cat_frames.h` 是基于该 GIF 转换得到的派生点阵数据；第三方许可证文本保存在 `third_party/SalaryCat/LICENSE`，请在分发时保留来源说明。

## 自定义

如果你想调整播放速度，修改 `YueXinCat72x40/cat_frames.h` 里的：

```cpp
constexpr uint16_t CAT_FRAME_MS = 45;
```

数值越小播放越快，数值越大播放越慢。

## 更多教程
更多教程可以到我的网站[微联编程](https://code.welinklab.com)进行学习
