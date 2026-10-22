# hbase

POSIX core user utils implementation.

hbase aims to provide a core userland utilities set conforming (mostly) to POSIX.1-2008 and implemented purely in ANSI C.

hbase includes conventional extensions in utilities and functionality

## currently implemented programs

- `yes(1)`: output a string repeatedly
- `true(1)`: return a successful status code
- `false(1)`: return an unsuccessful status code
- `pwd(1)`: print the current working directory
- `basename(1)`: strip directory and suffix components from path
- `dirname(1)`: strip last component from path
- `echo(1)`: print a line of text
- `uname(1)`: print system information
- `cat(1)`: concatenate files
- `mkdir(1)`: create directories
- `rm(1)`: unlink files
- `sleep(1)`: pause for seconds
- `tty(1)`: print the name of the terminal connected to stdin
- `rmdir(1)`: remove empty directories
- `touch(1)`: update timestamps or create files (unfinished)
- `test(1)`: compare and validate values
- `ls(1)`: list directory contents (unfinished)
- `hostname(1)`: set/get the system's hostname
- `sync(8)`: flush cache
- `env(1)`: set environment and execute a command, or print environment
- `printenv(1)`: print out the environment
- `logname(1)`: print the user's login name
- `nohup(1)`: invoke a command immune to hangups

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
- a C89-compatible C compiler (e.g. `clang`)

## building

### configuration

hbase exposes several meson build-time options

| option   | type    | default   | description                               |
| -------- | ------- | --------- | ----------------------------------------- |
| `tests`  | feature | `enabled` | hbase test suite                          |
| `doc`    | feature | `enabled` | hbase documentation                       |
| `static` | boolean | `false`   | build statically linked hbase executables |

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
| `cat(1)`      | the `cat` program      |
| `mkdir(1)`    | the `mkdir` program    |
| `rm(1)`       | the `rm` program       |
| `sleep(1)`    | the `sleep` program    |
| `tty(1)`      | the `tty` program      |
| `rmdir(1)`    | the `rmdir` program    |
| `touch(1)`    | the `touch` program    |
| `test(1)`     | the `test` program     |
| `ls(1)`       | the `ls` program       |
| `hostname(1)` | the `hostname` program |
| `sync(8)`     | the `sync` program     |
| `env(1)`      | the `env` program      |
| `printenv(1)` | the `printenv` program |
| `logname(1)`  | the `logname` program  |
| `nohup(1)`    | the `nohup` program    |

## project status

hbase is in active development and should currently be considered experimental.

the implemented utilities are functional, but POSIX conformance and portability are still being validated. hbase is not currently recommended as a system utility replacement.

- [CHANGELOG.md](CHANGELOG.md) -- release history
- [CONTRIBUTING.md](CONTRIBUTING.md) -- how to report bugs and send patches

## license

BSD-3-Clause, see [LICENSE](LICENSE).
