project(
    'hbase',
    'c',
    version: run_command('cat', 'VERSION', check: true).stdout().strip(),
    default_options: ['warning_level=3', 'c_std=c89'],
    meson_version: '>=1.1',
)

add_project_arguments(
  '-D_POSIX_C_SOURCE=200809L',
  language: 'c',
)

progs = [
  'yes',
  'true',
  'pwd',
]

include = include_directories('include')

if get_option('doc').enabled()
  subdir('doc')
endif

subdir('src')
