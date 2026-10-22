# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- add `-l` and `-1` to ls
- add a basic `hostname` utility
- add a basic `sync` utility
- add a basic `env` utility
- add a basic `printenv` utility
- add a basic `logname` utility
- add a basic `nohup` utility

### Changed

- rename the project to pxbase

### Fixed

- fix `dirname` structure
- use `_DEFAULT_SOURCE` instead of `_POSIX_C_SOURCE` in meson.build
- clarify `README.md` overview prose
- fix `pxbase_tty` function name

## [0.4.0] - 2026-10-10

### Added

- add a basic `sleep` program
- add a basic `tty` program
- add a basic `rmdir` program
- add a basic (unfinished) `touch` program
- add a basic `test`/`[` program
- add a basic (unfinished) `ls` program
- add `LICENSE` sections to all manpages

### Changed

- support static builds

## [0.3.0] - 2026-10-04

### Added

- add a basic `echo` program
- add a basic `uname` program
- add a basic `cat` program
- add a basic `mkdir` program
- add a basic `rm` program

### Changed

### Fixed

- clean up blank lines in manpages

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
