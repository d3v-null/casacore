#foreach (files
#antenna.params
#feed.params
#field.params
#obs.params
#range-obs.params
#selector-obs.params
#spw.params
#)
#    configure_file (${CMAKE_CURRENT_SOURCE_DIR}/${files} ${CMAKE_CURRENT_BINARY_DIR}#/${files} COPYONLY)
#endforeach (files)

set (tests
tMeasurementSet
tMSColumns
tMSDataDescBuffer
tMSFieldBuffer
tMSFieldEphem
tMSIter
tMSMainBuffer
tMSPolBuffer
tStokesConverter
)

foreach (test ${tests})
	add_executable (${test} ${test}.cc)
	add_pch_support(${test})
	target_link_libraries (${test} casa_ms)
	add_test (${test} ${CMAKE_SOURCE_DIR}/cmake/cmake_assay ./${test})
	add_dependencies(check ${test})
endforeach (test)
