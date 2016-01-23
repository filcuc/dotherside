project('DOtherSide', 'cpp', default_options : ['cpp_std=c++14'])

lib_version = '1.0.0'
lib_dependencies = dependency('qt5', modules : ['Core', 'Widgets', 'Quick', 'Qml'])
lib_sources = [
  'lib/src/DosQAbstractListModel.cpp',
  'lib/src/DosQMetaObject.cpp',
  'lib/src/DosQObject.cpp',
  'lib/src/DosQObjectImpl.cpp',
  'lib/src/DOtherSide.cpp',
  'lib/src/DOtherSideTypesCpp.cpp',
  'lib/src/OnSlotExecutedHandler.cpp'
]
lib_include_directories = ['lib/include', 'lib/include/Qt']

lib = shared_library('DOtherSide',
  sources : lib_sources,
  include_directories : include_directories(lib_include_directories),
  dependencies : lib_dependencies,
  version: lib_version,
  soversion:0
)

test_dependencies = dependency('qt5', modules : ['Core', 'Widgets', 'Quick', 'Qml', 'Test'])
test_sources = 'test/test_dotherside.cpp'
test_resources = 'test/Resources.qrc'
test_include_directories = ['lib/include', 'lib/include/Qt']

qt5 = import('qt5')
test_moc_files = qt5.preprocess(moc_sources : test_sources, qresources : test_resources)

executable('TestDOtherSide',
  sources : [test_sources, test_moc_files],
  include_directories : include_directories(test_include_directories),
  link_with : lib,
  dependencies : test_dependencies
)