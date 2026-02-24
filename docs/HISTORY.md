# History

## 0.1.0 - 2026-02-24

### Added
- 重构为分层结构：`presentation`（表现层）+ `io`（文件层）+ `core`（核心适配层）。
- Rust 核心通过 C ABI 导出：`ps_generate_password`。
- 新增基础测试目录 `tests/`，并接入 `ctest`（运行冒烟测试与版本测试）。
- 新增命令行参数 `--version`（以及 `-V`）显示程序版本。

### Changed
- 从动态加载 `ps_core.dll` 改为 GNU 静态链接 `libps_core.a`。
- CMake 构建流程改为自动构建并链接 Rust 静态库。
- README 更新为静态链接构建与测试流程。
