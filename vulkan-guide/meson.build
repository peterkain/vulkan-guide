project('vulkan-guide', 'cpp', default_options : ['cpp_std=c++17', 'warning_level=3', 'werror=true'])

#add_global_arguments('GLFW_DLL', language : 'cpp')

src = ['src/main.cpp', 'src/vulkan_example.cpp', 'src/validation_layers.cpp', 'src/physical_devices_and_queue_families.cpp',
       'src/logical_device.cpp']
inc_dirs = include_directories(['include', 'extern/include'])
lib_dir = meson.current_source_dir() + '/extern/lib'

cc = meson.get_compiler('cpp')
lib_vulkan = cc.find_library('vulkan-1', dirs : [lib_dir])
lib_glfw = cc.find_library('libglfw3', dirs : [lib_dir])

executable('vkguide', sources : src, include_directories : inc_dirs,
           dependencies : [lib_vulkan, lib_glfw])