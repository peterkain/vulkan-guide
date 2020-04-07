project('vulkan-guide', 'cpp', default_options : ['cpp_std=c++17', 'warning_level=3', 'werror=true'])

#add_global_arguments('GLFW_DLL', language : 'cpp')

src = ['src/main.cpp', 'src/vulkan_example.cpp', 'src/validation_layers.cpp', 'src/physical_devices_and_queue_families.cpp',
       'src/logical_device.cpp', 'src/surface.cpp', 'src/swap_chain.cpp', 'src/image_views.cpp', 'src/graphics_pipeline.cpp',
	   'src/frame_and_command_buffers.cpp', 'src/triangle.cpp']
inc_dirs = include_directories(['include', get_option('glfw_include_dir'), get_option('vk_include_dir')])
#lib_dir = meson.current_source_dir() + '/extern/lib'

cc = meson.get_compiler('cpp')
lib_vulkan = cc.find_library('vulkan-1', dirs : [get_option('vk_lib_dir')], required : false, disabler : true)
lib_glfw = cc.find_library('libglfw3', dirs : [get_option('glfw_lib_dir')], required : false, disabler : true)

if (not lib_vulkan.found())
    lib_vulkan = cc.find_library('libvulkan', dirs : [get_option('vk_lib_dir')])
endif

if (not lib_glfw.found())
    lib_glfw = cc.find_library('libglfw', dirs : [get_option('glfw_lib_dir')])
endif

executable('vkguide', sources : src, include_directories : inc_dirs,
           dependencies : [lib_vulkan, lib_glfw])
