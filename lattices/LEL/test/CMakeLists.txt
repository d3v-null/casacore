set (tests
tLEL
tLELAttribute
tLELMedian
tLatticeExpr
tLatticeExpr2
tLatticeExpr3
tLatticeExprNode
tLatticeExpr2Node
tLatticeExpr3Node
)

foreach (test ${tests})
    add_executable (${test} ${test}.cc)
    add_pch_support(${test})
    target_link_libraries (${test} casa_lattices)
    add_test (${test} ${CMAKE_SOURCE_DIR}/cmake/cmake_assay ./${test})
    add_dependencies(check ${test})
endforeach (test)
