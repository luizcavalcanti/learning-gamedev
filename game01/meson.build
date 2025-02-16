project('game01', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'default_library=static'])

sdl2_dep = dependency('sdl2')
sdl2_img_dep = dependency('sdl2_image')

sources = ['game.cpp', 'game_object.cpp', 'player.cpp', 'utils.cpp']

exe = executable('game01', sources,
  install : true,
  dependencies: [sdl2_dep, sdl2_img_dep])

test('basic', exe)
