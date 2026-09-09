# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- add a basic `echo` program

### Changed

### Fixed

### Removed

## [0.2.0] - 2026-09-09

### Added

- add a header for `pwd.c`
- add a basic test suite
- add a basic `basename` program
- add a basic `dirname` program

### Changed

- add a `common.c` helper library for `usage_exit`
- expand and improve the readme
- namespace header guards
- use `EXIT_SUCCESS` and `EXIT_FAILURE` everywhere
- use `main(void)` for `true` and `false`
- include their respective headers for each program

### Fixed

- copy input path to local buffer in `basename.c`
- avoid mutating `argv` in `yes.c`
- fix prose in `yes.1`
- fix minor inconsistency in `false.1`
- deduplicate default-arg logic in `yes.c`

### Removed

## [0.1.0] - 2026-09-08

### Added

- add a basic `pwd` program
- add a basic `false` program
- add a basic `true` program
- add a basic `yes` program
- add `VERSION`, `CONTRIBUTING.md`, `README.md`, `LICENSE`, `CHANGELOG.md`, `.gitignore`, and a `.clang-format`

### Changed

### Fixed

### Removed
