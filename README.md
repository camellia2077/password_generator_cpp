# password_generator
同仓库维护两套实现：

- C++: 表现层 + IO 层 + Core 适配层
- Rust: Core 实现（静态库 `libps_core.a`，C ABI 导出）

## 目录结构
- `src/presentation`: 表现层（CLI 和控制台输出流程）
- `src/io`: 文件读写
- `src/core`: C++ Core 适配层（静态调用 C ABI）
- `src/rust_core`: Rust Core（导出 `ps_generate_password`）

## 构建
在仓库根目录执行：

```bash
rustup target add x86_64-pc-windows-gnu
cmake -S . -B build
cmake --build build
```

构建完成后：
- 可执行文件：`build/bin/password_generator_cpp.exe`
- Rust 静态库：`src/rust_core/target/x86_64-pc-windows-gnu/release/libps_core.a`

## 运行
```bash
build/bin/password_generator_cpp.exe --version
build/bin/password_generator_cpp.exe -n 3 -l 12
```

## 最基本测试
在完成构建后执行：

```bash
ctest --test-dir build --output-on-failure
```

当前 smoke test 会验证：
- `password_generator_cpp.exe` 存在
- 可执行文件能正常运行（`-n 3 -l 12`）
- 生成 `passwords.txt`，并且有 3 行、每行长度为 12

更新历史见 `docs/HISTORY.md`。
