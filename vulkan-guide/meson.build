project('vulkan-guide', 'cpp', default_options : ['cpp_std=c++17', 'warning_level=3', 'werror=true'])

#add_global_arguments('GLFW_DLL', language : 'cpp')

src = ['src/main.cpp', 'src/vulkan_example.cpp', 'src/validation_layers.cpp', 'src/physical_devices_and_queue_families.cpp',
       'src/logical_device.cpp', 'src/surface.cpp', 'src/swap_chain.cpp', 'src/image_views.cpp', 'src/graphics_pipeline.cpp',
	   'src/frame_and_command_buffers.cpp', 'src/triangle.cpp']
	   
datadir = join_paths(meson.current_source_dir(), 'data')
builddir = join_paths(meson.current_source_dir(), 'build')

cc = meson.get_compiler('cpp')
#windows
if build_machine.system() == 'windows'
	inc_dirs = include_directories(['include', 'extern/include'])
	lib_dir = meson.current_source_dir() + '/extern/lib'
	lib_vulkan = cc.find_library('vulkan-1', dirs : [get_option('vk_lib_dir'), lib_dir])
	lib_glfw = cc.find_library('libglfw3', dirs : [get_option('glfw_lib_dir'), lib_dir])
	message('Please copy the data folder to the build folder to avoid errors.')
endif
if build_machine.system() == 'linux'
	inc_dirs = include_directories(['include', get_option('vk_include_dir'), get_option('glfw_include_dir')])
    lib_vulkan = cc.find_library('libvulkan', dirs : [get_option('vk_lib_dir')])
	lib_glfw = cc.find_library('libglfw', dirs : [get_option('glfw_lib_dir')])
	message('Copying ' + datadir + ' to ' + builddir)
	result = run_command('cp', datadir, builddir, '-r')
	if result.returncode() != 0
		message('Failed to copy the data folder into the build folder. Please do so manually.')
	endif
endif

executable('vkguide', sources : src, include_directories : inc_dirs,
           dependencies : [lib_vulkan, lib_glfw])
