curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source $HOME/.cargo/env
RUSTUP=$HOME/.cargo/bin/rustup
CARGO=$HOME/.cargo/bin/cargo

install_rust() {
    $RUSTUP install stable --profile minimal
    cargo install cargo-hack
}

run_clippy() {
    $CARGO clippy -- -D warnings
    if [ $? -ne 0 ]; then
        echo "Clippy failed"
        exit 1
    fi
}

run_fmt() {
    $CARGO fmt --check
    if [ $? -ne 0 ]; then
        echo "Formatting failed"
        exit 1
    fi
}

run_test() {
    $CARGO hack test
    if [ $? -ne 0 ]; then
        echo "Tests failed"
        exit 1
    fi
}

install_rust
run_clippy
run_fmt
run_test
