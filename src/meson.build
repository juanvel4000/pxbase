common = static_library('common', files('common.c'), include_directories: include)
commondep = declare_dependency(link_with: common, include_directories: include)

bins = {}

prog_link_args = []
if get_option('static')
  prog_link_args += ['-static']
endif

foreach prog : progs
  bins += {
    prog: executable(
      prog,
      [prog + '.c'],
      link_args: prog_link_args,
      dependencies: [commondep],
      install: true,
    ),
  }
endforeach
