# raylib_project

MinGW-w64 + VSCode 的 raylib 工程模板。

## 环境

| 项目 | 路径 / 版本 |
| --- | --- |
| 编译器 | `D:\mingw64\bin\gcc.exe` (GCC 15.2.0, x86_64) |
| 调试器 | `D:\mingw64\bin\gdb.exe` |
| raylib | `D:\raylib\raylib-6.0_win64_mingw-w64` (6.0, mingw-w64 版) |
| 链接方式 | 静态链接 `libraylib.a` |

因为用的是静态链接，生成的 `bin\main.exe` 只依赖 Windows 系统 DLL，
**拷到别的电脑上也能直接双击运行**，不需要带上 raylib.dll。

## 用法

用 VSCode 打开本文件夹（`文件 → 打开文件夹`），然后：

| 操作 | 快捷键 | 说明 |
| --- | --- | --- |
| 编译 | `Ctrl+Shift+B` | 编译 `src` 下所有 `.c`，输出到 `bin\main.exe` |
| 调试运行 | `F5` | 自动先编译，再启动 gdb，可下断点 |
| 生成并运行 | `Ctrl+Shift+P` → `Tasks: Run Task` | 选 `raylib: 生成并运行 (build & run)` |
| 直接运行 ▶ | 右上角三角按钮 | Code Runner 插件，编译后直接在终端里运行 |

三个按钮都能用，区别是：`F5` 能下断点单步调试；`Ctrl+Shift+B` 只编译不运行；
右上角 ▶ 是 Code Runner 的快捷运行，命令写在 `.vscode\settings.json` 里，
覆盖了你全局那条只编译单文件的 `gcc` 命令。

## 添加新代码

- 新增 `.c` 文件直接丢进 `src\`，会被自动一起编译，不用改配置。
- 头文件也放 `src\`，用 `#include "xxx.h"` 引。
- 想引用图片/字体/音频，在工程根目录建个 `resources\` 放，
  代码里用相对路径（`cwd` 已设为工程根目录）。

## 复制成新工程

整个 `raylib_project` 文件夹复制一份改名即可，`.vscode` 里的路径都是
绝对路径指向 `D:\mingw64` 和 `D:\raylib`，不用改。

## 如果换 raylib 版本

raylib 的路径写死在三个文件里，升级时一起改：

- `.vscode\tasks.json` — 编译参数里的 `-I` 和 `-L`
- `.vscode\c_cpp_properties.json` — `includePath`

链接选项 `-lraylib -lopengl32 -lgdi32 -lwinmm` 是 raylib 在 Windows 上的
固定搭配，一般不用动。
