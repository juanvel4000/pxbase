# hbase

POSIX core user utils implementation, written in C.

hbase aims to provide a core userland utilities set conforming to POSIX.1-2008 and implemented purely in strict ANSI C89.

## currently implemented programs

- `yes`
- `true`
- `false`
- `pwd`
- `basename`
- `dirname`
- `echo`
- `uname`
- `cat`
- `mkdir`

## quick start

```sh
meson setup build # setup the project
meson compile -C build # compile hbase
meson test -C build # run the test suite
meson install -C build # install hbase
```

## dependencies

build-time dependencies include

- Meson
- Ninja
- a `libc` implementing the required POSIX.1-2008 interfaces
- a C89-compatible C compiler (e.g. `gcc`)

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
| `uname(1)`    | the `uname` program    |

## project status

hbase is in active development and should currently be considered experimental.

the implemented utilities are functional, but POSIX conformance and portability are still being validated. hbase is not currently recommended as a system utility replacement.

- [CHANGELOG.md](CHANGELOG.md) -- release history
- [CONTRIBUTING.md](CONTRIBUTING.md) -- how to report bugs and send patches

## license

BSD-3-Clause, see [LICENSE](LICENSE).
