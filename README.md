# Featherarchy

**A security-hardened Monero wallet fork, optimized for Omarchy Linux.**

Featherarchy is a privacy-focused fork of [Feather Wallet](https://featherwallet.org) with enhanced security measures, memory safety improvements, and the Omarchy dark theme.

## Security Enhancements

This fork includes critical security and stability fixes not yet in upstream:

### Memory Safety
- **QrCode memory leaks fixed** - PaymentRequestDialog and URWidget no longer leak memory on repeated QR generation
- **Smart pointer migration** - Critical objects now use `QScopedPointer` for automatic cleanup
- **Ownership semantics documented** - Clear non-owning pointer patterns prevent use-after-free

### Input Validation
- **Address validation** - All user-input Monero addresses validated before use (ContactsDialog, OutputSweepDialog, SendWidget multi-destination)
- **Path canonicalization** - Wallet paths sanitized to prevent directory traversal attacks
- **Bounds checking** - Transaction fee calculations protected against unsigned integer underflow

### Code Quality
- **Dead code removed** - Legacy commented-out code blocks eliminated
- **Secure password handling** - Password fields wiped from memory after use

## Omarchy Theme

Ships with the **Omarchy** dark theme - a clean, minimal aesthetic designed for extended use:

- High contrast for readability
- Reduced eye strain in low-light environments
- Consistent with Omarchy Linux desktop theming

## Building

```bash
# Clone with submodules
git clone --recursive https://github.com/johnzfitch/featherarchy.git
cd featherarchy

# Build
mkdir build && cd build
cmake ..
make -j$(nproc)

# Binary location
./bin/feather
```

### Dependencies (Arch Linux)

```bash
sudo pacman -S base-devel cmake qt6-base qt6-svg qt6-websockets \
    libgcrypt libsodium hidapi protobuf libusb boost
```

## Differences from Upstream Feather

| Feature | Feather | Featherarchy |
|---------|---------|--------------|
| QrCode memory management | Raw pointers (leaks) | QScopedPointer |
| Address validation | Partial | Complete |
| Path traversal protection | Basic tilde expansion | Full canonicalization |
| Fee calculation safety | No bounds checking | Underflow protected |
| Theme | Light/Dark | + Omarchy |
| Target distro | General | Omarchy Linux |

## Upstream

This fork tracks [feather-wallet/feather](https://github.com/feather-wallet/feather). Security fixes will be proposed upstream via PR.

## License

BSD-3-Clause - Same as upstream Feather.

Copyright (c) 2020-2025, The Monero Project
Fork modifications (c) 2025, johnzfitch
