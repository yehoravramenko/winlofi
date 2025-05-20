CXX_SRC = files(
    'main.cxx',
)

CFLAGS = [
    '/WX',
    '/sdl',
    '/options:strict',
]

executable(
    'winlofi',
    CXX_SRC,
    cpp_args: CFLAGS,
    win_subsystem: 'windows',
)