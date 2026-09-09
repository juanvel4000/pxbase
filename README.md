# hbase

POSIX core user utils implementation, written in C.

hbase is a minimalistic implementation of core POSIX user utilities. It aims for POSIX.1-2013 compliance and ANSI C89.

## currently implemented programs

- `yes`
- `true`
- `false`
- `pwd`
- `basename`
- `dirname`
- `echo`

## quick start

configure the project

```sh
meson setup build
```

build the project

```sh
meson compile -C build
```

> optionally, run tests
>
> ```sh
> meson test -C build
> ```

install the project

```sh
meson install -C build
```

## dependencies

build-time dependencies include

- Meson
- Ninja
- a POSIX-compatible libc
- a C89-compatible C compiler

## building

### configuration

hbase exposes several meson build-time options

| option  | type    | default   | description         |
| ------- | ------- | --------- | ------------------- |
| `tests` | feature | `enabled` | hbase test suite    |
| `doc`   | feature | `enabled` | hbase documentation |

> set with, e.g.:
>
> ```sh
> meson setup build -Dtests=enabled -Ddoc=disabled
> ```

### testing

the `tests/` directory provides a simple test suite for

- validating true/false status code
- validating pwd logical path resolution
- yes output generation

these can be executed by running

```sh
 meson test -C build
```

## documentation

man pages are installed when documentation is enabled at build time

| manpage       | describes              |
| ------------- | ---------------------- |
| `yes(1)`      | the `yes` program      |
| `true(1)`     | the `true` program     |
| `false(1)`    | the `false` program    |
| `pwd(1)`      | the `pwd` program      |
| `basename(1)` | the `basename` program |
| `dirname(1)`  | the `dirname` program  |
| `echo(1)`     | the `echo` program     |

## project status

hbase is in active development and should currently be considered experimental.

the implemented utilities are functional, but POSIX conformance and portability are still being validated. hbase is not currently recommended as a system utility replacement.

- [CHANGELOG.md](CHANGELOG.md) -- release history
- [CONTRIBUTING.md](CONTRIBUTING.md) -- how to report bugs and send patches

## license

BSD-3-Clause, see [LICENSE](LICENSE).
