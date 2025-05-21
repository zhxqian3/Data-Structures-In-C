project(
    'main',
    'c',
    meson_version: '>= 1.3.0',
    version: '0.1',
    default_options: ['warning_level=3'],
)

dependencies = []

src = ['main.c', 'linklist.c']

exe = executable('main', src, dependencies: dependencies, install: true)

test('basic', exe)
