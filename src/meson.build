common = static_library('common', files('common.c'), include_directories: include)
commondep = declare_dependency(link_with: common, include_directories: include)

bins = {}

prog_link_args = []
if get_option('static')
  prog_link_args += ['-static']
endif

foreach prog : progs
  if get_option('multicall').enabled()
    bins += {
      prog: static_library(
        prog,
        [prog + '.c'],
        link_args: prog_link_args,
        c_args: ['-DPXBASE_MULTICALL'],
        dependencies: [commondep],
        install: false,
      ),
    }
  else
    bins += {
      prog: executable(
        prog,
        [prog + '.c'],
        link_args: prog_link_args,
        dependencies: [commondep],
        install: true,
      ),
    }
  endif
endforeach

if get_option('multicall').enabled()
  executable(
    'pxbase',
    files('pxbase.c'),
    link_args: prog_link_args,
    link_with: bins.values(),
    dependencies: [commondep],
    install: true,
  )

  foreach prog : progs
    install_symlink(prog, install_dir: get_option('bindir'), pointing_to: 'pxbase')
  endforeach
endif

install_symlink(
  '[',
  install_dir: get_option('bindir'),
  pointing_to: get_option('multicall').enabled() ? 'pxbase' : 'test',
)
