project(
  'hbase',
  'c',
  version: run_command('cat', 'VERSION', check: true).stdout().strip(),
  default_options: ['warning_level=3', 'c_std=c89'],
  meson_version: '>=1.11',
)

add_project_arguments(
  '-D_POSIX_C_SOURCE=200809L',
  language: 'c',
)

progs = ['yes', 'true', 'pwd', 'false', 'basename', 'dirname']

include = include_directories('include')

subdir('src')

if get_option('doc').enabled()
  subdir('doc')
endif

if get_option('tests').enabled()
  subdir('tests')
endif
