project(
  'hbase',
  'c',
  version: files('VERSION'),
  default_options: ['warning_level=3', 'c_std=c89', 'werror=true', 'c_args=-Wall -Wextra'],
  meson_version: '>=1.12',
)

add_project_arguments(
  '-D_DEFAULT_SOURCE',
  language: 'c',
)

progs = [
  'yes',
  'true',
  'pwd',
  'false',
  'basename',
  'dirname',
  'echo',
  'uname',
  'cat',
  'mkdir',
  'rm',
  'sleep',
  'tty',
  'rmdir',
  'touch',
  'test',
  'ls',
  'hostname',
  'sync',
  'env',
]

include = include_directories('include')

subdir('src')

if get_option('doc').enabled()
  subdir('doc')
endif

if get_option('tests').enabled()
  subdir('tests')
endif
