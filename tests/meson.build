test('false-exits-1', bins['false'], expected_fail: true)
test('true-exits-0', bins['true'])

test('pwd-matches-shell', find_program('test-pwd.sh'), args: [bins['pwd']])
test('yes-repeats-args', find_program('test-yes.sh'), args: [bins['yes']])
test('echo-prints-strings', find_program('test-echo.sh'), args: [bins['echo']])
test(
  'basename-slices-path',
  find_program('test-basename.sh'),
  args: [bins['basename']],
)

test(
  'dirname-slices-filename',
  find_program('test-dirname.sh'),
  args: [bins['dirname']],
)
