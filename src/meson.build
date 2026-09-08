foreach prog : progs
  executable(
    prog,
    [prog + '.c'],
    include_directories: include,
    link_with: common,
    install: true,
  )
endforeach
