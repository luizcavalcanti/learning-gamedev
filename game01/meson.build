project('game01', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'default_library=static'])

sdl2_dep = dependency('sdl2', method: 'pkg-config')
sdl2_img_dep = dependency('sdl2_image', method: 'pkg-config')
sdl2_ttf_dep = dependency('sdl2_ttf', method: 'pkg-config')

sources = ['game.cpp', 'game_object.cpp', 'player.cpp', 'utils.cpp']

exe = executable('game01', sources,
  install : true,
  dependencies: [sdl2_dep, sdl2_img_dep, sdl2_ttf_dep])

#install_data('myapp.icns', install_dir : 'Contents/Resources')
#install_data('Info.plist', install_dir : 'Contents')

test('basic', exe)
