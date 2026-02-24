# rust_core
Rust 实现的密码核心，导出 C ABI：

- `ps_generate_password(int length, char* out_buffer, size_t out_buffer_len)`
- 产物类型：`staticlib`（`libps_core.a`）

构建（在仓库根目录）：

```bash
cargo build --release --target x86_64-pc-windows-gnu --manifest-path src/rust_core/Cargo.toml
```
