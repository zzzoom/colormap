project('colormap', 'cpp')

colormap_inc = include_directories('.')

cxx = meson.get_compiler('cpp')
m_dep = cxx.find_library('m', required : true)

gtest = subproject('gtest')
gtest_dep = gtest.get_variable('gtest_dep')

colormap_tests = executable('colormap_tests',
    'tests.cpp',
    include_directories: colormap_inc,
    dependencies: [ m_dep, gtest_dep ]
)

test('colormap tests', colormap_tests)
