project('okgame', 'cpp',   
version : '1',
license : 'do whatever')

add_global_arguments('-DSOME_TOKEN=value', language : 'cpp')


boost_dep = dependency('boost')
ctpl_dep = dependency('ctpl')
glew_dep = dependency('glew')
gwen_dep = dependency('gwen')
hq2x_dep = dependency('hq2x')
sigar_dep = dependency('sigar')
libmodplug_dep = dependency('libmodplug')
lz4_dep = dependency('lz4')
micropather_dep = dependency('micropather')
miniz_dep = dependency('miniz')
modplay_dep = dependency('modplay')
nanogui_dep = dependency('nanogui')
nanovg_dep = dependency('nanovg')
nngui_dep = dependency('nngui')
poco_dep = dependency('poco')

sdl2_gfx_dep = dependency('sdl2_gfx')
sdl2_image_dep = dependency('sdl2_image')
sdl2_mixer_dep = dependency('sdl2_mixer')
sdl2_net_dep = dependency('sdl2_net')
sdl2_ttf_dep = dependency('sdl2_ttf')
sdl2_dep = dependency('sdl2')

timidity_dep = dependency('timidity')
base64_dep = dependency('base64')
dgmisc_dep = dependency('dgmisc')
md5_dep = dependency('md5')

sdl_platform_dep = dependency('sdl_platform')
sdl_stbimage_dep = dependency('sdl_stbimage')
sdl2_scancode_to_dinput_dep = dependency('sdl2_scancode_to_dinput')

soundtouch_dep = dependency('soundtouch')

stb_image_dep = dependency('stb_image')
stb_image_resize_dep = dependency('stb_image_resize')
stb_image_write_dep = dependency('stb_image_write')
stb_truetype_dep = dependency('stb_truetype')
stb_vorbis_dep = dependency('stb_vorbis')


inc = include_directories('include')

subdir('include')
subdir('src')



executable('okgame', 'src/main.cpp', dependencies : boost_dep, ctpl_dep, glew_dep, gwen_dep, hq2x_dep, sigar_dep, libmodplug_dep, lz4_dep, micropather_dep, miniz_dep, modplay_dep, nanogui_dep, nanovg_dep, nngui_dep, poco_dep, sdl2_gfx_dep, sdl2_image_dep, sdl2_mixer_dep, sdl2_net_dep, sdl2_ttf_dep, sdl2_dep, timidity_dep, base64_dep, dgmisc_dep, md5_dep, sdl_platform_dep, sdl_stbimage_dep, sdl2_scancode_to_dinput_dep, soundtouch_dep, stb_image_dep, stb_image_resize_dep, stb_image_write_dep, stb_truetype_dep, stb_vorbis_dep)