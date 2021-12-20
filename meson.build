project('opctest', 'c', default_options : ['c_std=c99'] )

cmake = import('cmake')

open62541_options = cmake.subproject_options()
open62541_options.add_cmake_defines (
  {'BUILD_SHARED_LIBS': 'ON'},
  {'CMAKE_BUILD_TYPE': 'RelWithDebInfo'},
  {'UA_NAMESPACE_ZERO': 'REDUCED'},
  {'OPEN62541_VERSION': 'v1.3'},
  {'UA_ENABLE_DISCOVERY': 'ON'},
  {'UA_ENABLE_DISCOVERY_MULTICAST': 'ON'},
  {'UA_ENABLE_PUBSUB': 'ON'},
  {'UA_ENABLE_PUBSUB_FILE_CONFIG': 'ON'},
  {'UA_ARCH_REMOVE_FLAGS': '-Werror'},
  {'UA_MULTITHREADING': '200'}
)

open62541 = cmake.subproject('open62541', options:open62541_options)
opc_dep = open62541.dependency('open62541')

opctest_dependencies = [opc_dep]

apps = ['producer', 'consumer']

foreach a: apps
  executable(a, a + '.c', dependencies: opctest_dependencies, install: true)
endforeach
