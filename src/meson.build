common = static_library('common', files('common.c'), include_directories: include)
commondep = declare_dependency(link_with: common, include_directories: include)
bins = {}
foreach prog : progs
  bins += {
    prog: executable(
      prog,
      [prog + '.c'],
      dependencies: [commondep],
      install: true,
    ),
  }
endforeach
