project('game01', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'default_library=static'])

sdl2_dep = dependency('sdl2')
sdl2_img_dep = dependency('sdl2_image')

exe = executable('game01', 'game01.c',
  install : true,
  dependencies: [sdl2_dep, sdl2_img_dep])

test('basic', exe)
