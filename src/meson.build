bins = {}
foreach prog : progs
  bins += {prog: executable(
    prog,
    [prog + '.c'],
    include_directories: include,
    install: true,
  )}
endforeach
