project('opctest', 'c', default_options : ['c_std=c99'] )

opc_dep = dependency('open62541', version:'>=1.2.0', method : 'cmake')

opctest_dependencies = [opc_dep]

apps = ['producer', 'consumer']

foreach a: apps
  executable(a, a + '.c', dependencies: opctest_dependencies, install: true)
endforeach
