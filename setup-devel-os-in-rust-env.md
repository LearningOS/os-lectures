
# for devel os kernel in rust, in ubuntu 20.04 x86-64

## setup rust
```
export RUSTUP_DIST_SERVER=https://mirrors.ustc.edu.cn/rust-static
export RUSTUP_UPDATE_ROOT=https://mirrors.ustc.edu.cn/rust-static/rustup

curl https://sh.rustup.rs -sSf | sh

rustup toolchain install nightly
rustup target add riscv64gc-unknown-none-elf
rustup component add llvm-tools-preview
rustup component add rust-src

cargo install cargo-binutils
```

## setup qemu
```
### install devel env for building qemu
sudo apt install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev \
              gawk build-essential bison flex texinfo gperf libtool patchutils bc \
              zlib1g-dev libexpat-dev git pkg-config  libglib2.0-dev libpixman-1-dev tmux


### get&uncompress qemu              
wget https://download.qemu.org/qemu-5.0.0.tar.xz

tar xvJf qemu-5.0.0.tar.xz

### build&install qemu
cd qemu-5.0.0
./configure --target-list=riscv64-softmmu,riscv64-linux-user
make -j$(nproc)
sudo make install
```

## riscv64 gnu tools(optional)
```
### Prebuilt Binary Packages: in https://github.com/sifive/freedom-tools/releases
#### GCC 10.1, with RVV-1.0 intrinsic supported ...
#### https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08/riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz

### download&uncompress
cd /usr/local
sudo wget https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08/riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz
sudo tar zxf riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz


```
## set env var
```
# add Below Lines to ~/.bashrc

source "$HOME/.cargo/env"
export PATH=$PATH:/usr/local/riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14/bin

```
