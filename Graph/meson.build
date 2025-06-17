project(
  'main',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : ['warning_level=3'],
)

dependencies = [
]

globber = run_command('find', '.', '-path', './build', '-prune', '-or', '-name', '*.c', '-print', check: true)
src = globber.stdout().strip().split('\n')

exe = executable(
  'main',
  src,
  dependencies : dependencies,
  install : true,
)

test('basic', exe)
