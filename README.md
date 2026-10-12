# xv6 Memory Management | xv6 内存管理

A C implementation of memory-management features for COMPSCI 340 Assignment 2, based on the University of Auckland's RISC-V xv6 starter repository.

本项目基于奥克兰大学提供的 RISC-V xv6 初始代码，使用 C 语言实现 COMPSCI 340 作业二的内存管理功能。

## Features | 实现功能

### 1. Used-Memory Query | 内存查询

Adds the `getusedmem()` system call and the `used` program. The implementation recursively traverses the kernel page table and reports the total bytes represented by valid leaf mappings.

新增 `getusedmem()` 系统调用和 `used` 用户程序，递归遍历内核页表，统计有效叶子映射对应的总字节数。

This value includes mapped RAM and device regions. It does not represent the physical-memory allocator's current allocation usage.

该数值包括映射的物理内存和设备区域，不代表物理内存分配器当前实际分配的内存量。

### 2. Page Write Protection | 页面写保护

Adds `mprotect()` and `munprotect()` to remove and restore write permission on a user page. Invalid addresses return `-1`, and permission changes flush the TLB.

新增 `mprotect()` 和 `munprotect()`，分别移除和恢复用户页面的写权限。无效地址返回 `-1`，修改权限后刷新 TLB。

### 3. Null-Pointer Protection | 空指针保护

User programs start at `0x1000`, and page zero is inaccessible to user mode. Unresolved page faults print `Segmentation Fault!` and terminate the affected process.

用户程序从 `0x1000` 开始，第零页禁止用户态访问。无法处理的页错误会输出 `Segmentation Fault!`，并终止发生错误的进程。

## Project Structure | 项目结构

| Path / 路径 | Description / 说明 |
|---|---|
| `kernel/` | Kernel source and memory management / 内核代码及内存管理实现 |
| `mkfs/` | Filesystem image creation tool / 文件系统镜像创建工具 |
| `user/` | User programs, libraries, and tests / 用户程序、函数库及测试 |
| `Makefile` | Build and QEMU configuration / 编译及 QEMU 配置 |
| `test-xv6.py` | Existing xv6 test runner / 原有 xv6 测试脚本 |
| `README.xv6` | Original documentation required by the build / 编译所需的原始说明文档 |
| `LICENSE` | Original xv6 license / xv6 原始许可证 |

## Build and Run | 编译与运行

Use a Linux environment, such as Ubuntu or Ubuntu through WSL. The project requires a RISC-V GCC/binutils toolchain and QEMU 7.2 or newer.

请使用 Linux 环境，例如 Ubuntu 或 WSL 中的 Ubuntu。项目需要 RISC-V GCC/binutils 工具链，以及 QEMU 7.2 或更新版本。

Install the dependencies on Ubuntu:

在 Ubuntu 中安装依赖：

```sh
sudo apt update
sudo apt install build-essential gcc-riscv64-linux-gnu \
  binutils-riscv64-linux-gnu qemu-system-misc \
  python3 perl bc
```

Build and launch xv6 from the project directory:

在项目目录中编译并启动 xv6：

```sh
make clean
make qemu
```

To exit QEMU, press **Ctrl+A**, then **X**.

退出 QEMU 时，先按 **Ctrl+A**，再按 **X**。

## Assignment Tests | 作业测试

Run these commands at the xv6 shell:

在 xv6 命令行中运行：

```text
used
mprotecttest
nullptrtest
```

### Used Memory | 内存查询

The `used` program prints the mapped-memory total in bytes. The number depends on the kernel's mappings.

`used` 程序输出映射内存的总字节数，具体数值取决于内核的映射配置。

```text
Used memory: <number> bytes
```

### Page Protection | 页面保护

With `*address = 0x34;` commented out, the assignment's test prints `1886`: decimal `18` followed by decimal `86`, without a separator. This checks that reading remains possible after protection and writing works after unprotection.

注释掉 `*address = 0x34;` 时，作业测试输出 `1886`，即十进制的 `18` 和 `86` 连续显示，没有分隔符。这用于检查页面保护后仍可读取，解除保护后可以写入。

```text
1886
```

Uncommenting that statement attempts to write to the protected page. The process should print `Segmentation Fault!` and terminate. Rebuild and restart xv6 after editing the test.

取消该语句的注释后，程序会尝试写入受保护的页面，应输出 `Segmentation Fault!` 并终止。修改测试后需要重新编译并启动 xv6。

```text
Segmentation Fault!
```

### Null-Pointer Access | 空指针访问

The `nullptrtest` program should print `Segmentation Fault!` when dereferencing a null pointer. The shell should remain usable afterward.

`nullptrtest` 程序解引用空指针时，应输出 `Segmentation Fault!`。发生错误后，仍可继续使用命令行。

```text
Segmentation Fault!
```

## General Tests | 通用测试

The existing xv6 test runner can be invoked from Linux:

可以在 Linux 中运行原有的 xv6 测试脚本：

```sh
python3 test-xv6.py -q usertests
```

These general tests check different behavior from the assignment examples. Passing the assignment examples does not establish that the entire general test suite passes.

通用测试与作业示例检查的内容不同。作业示例通过，不代表全部通用测试都已通过。

## Credits and License | 来源与许可证

Based on the University of Auckland's [xv6-c-student](https://github.com/UoA-CS340-SE370-OSDev/xv6-c-student) starter repository and MIT's xv6 teaching operating system. Assignment-specific changes implement the memory-management features described above.

本项目基于奥克兰大学的 [xv6-c-student](https://github.com/UoA-CS340-SE370-OSDev/xv6-c-student) 初始代码，以及 MIT 的 xv6 教学操作系统。作业相关修改实现了上述内存管理功能。

Original copyright and license notices are retained in `LICENSE`.

原始版权及许可证声明保留在 `LICENSE` 文件中。