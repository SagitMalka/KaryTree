// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include "doctest.h"
// #include "tree.hpp"
// #include "Complex.hpp"
// using namespace ariel;

// TEST_CASE("Tree and Complex Tests") {
//     Tree<int, 3> tree;
//     tree.add_root(1).add_sub_node(1, 2).add_sub_node(1, 3).add_sub_node(2, 4).add_sub_node(2, 5).add_sub_node(3, 6);

//     CHECK(tree.getRoot()->_val == 1);
//     CHECK(tree.getRoot()->_children[0]->_val == 2);
//     CHECK(tree.getRoot()->_children[1]->_val == 3);
//     CHECK(tree.getRoot()->_children[0]->_children[0]->_val == 4);
//     CHECK(tree.getRoot()
//               ->_children[0]->_children[1]->_val == 5);
//     CHECK(tree.getRoot()->_children[1]->_children[0]->_val == 6);
// }

// TEST_CASE("Basic Tree Structure") {
//     Tree<int, 3> tree;
//     tree.add_root(1);

//     SUBCASE("Add children to root") {
//         tree.add_sub_node(1, 2).add_sub_node(1, 3).add_sub_node(1, 4);
//         CHECK(tree.getRoot()->_children[0]->_val == 2);
//         CHECK(tree.getRoot()->_children[1]->_val == 3);
//         CHECK(tree.getRoot()->_children[2]->_val == 4);
//     }

//     SUBCASE("Add grandchildren") {
//         tree.add_sub_node(1, 2).add_sub_node(2, 5).add_sub_node(2, 6);
//         CHECK(tree.getRoot()->_children[0]->_children[0]->_val == 5);
//         CHECK(tree.getRoot()->_children[0]->_children[1]->_val == 6);
//     }
// }

// TEST_CASE("Tree Traversal") {
//     Tree<int, 3> tree;
//     tree.add_root(1).add_sub_node(1, 2).add_sub_node(1, 3).add_sub_node(2, 4).add_sub_node(2, 5).add_sub_node(3, 6);

//     SUBCASE("DFS Traversal") {
//         std::vector<int> dfs_result;
//         for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
//             dfs_result.push_back(*it);
//         }
//         std::vector<int> expected = {1, 4, 5, 2, 6, 3, 1}; // Finishing times
//         CHECK(dfs_result == expected);
//     }

//     SUBCASE("BFS Traversal") {
//         std::vector<int> bfs_result;
//         for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
//             bfs_result.push_back(*it);
//         }
//         std::vector<int> expected = {1, 1, 2, 3, 4, 5, 6};
//         CHECK(bfs_result == expected);
//     }
// }

// TEST_CASE("Empty tree") {
//     Tree<int, 3> tree;

//     SUBCASE("Empty Tree") {
//         CHECK(tree.getRoot() == nullptr);
//     }

// }

// TEST_CASE("Complex Number Tree") {
//     Tree<Complex, 3> tree;
//     Complex c1(1.0, 1.0), c2(2.0, 2.0), c3(3.0, 3.0);
//     tree.add_root(c1).add_sub_node(c1, c2).add_sub_node(c1, c3);

//     CHECK(tree.getRoot()->_val.toString() == "1 + 1i");
//     CHECK(tree.getRoot()->_children[0]->_val.toString() == "2 + 2i");
//     CHECK(tree.getRoot()->_children[1]->_val.toString() == "3 + 3i");
// }

// TEST_CASE("Parent Pointer Tests") {
//     Tree<int, 3> tree;
//     tree.add_root(1).add_sub_node(1, 2).add_sub_node(1, 3).add_sub_node(2, 4);

//     CHECK(tree.getRoot()->_children[0]->_parent.lock() == tree.getRoot());
//     CHECK(tree.getRoot()->_children[1]->_parent.lock() == tree.getRoot());
//     CHECK(tree.getRoot()->_children[0]->_children[0]->_parent.lock() == tree.getRoot()->_children[0]);
// }
// TEST_CASE("Invalid Argument Tests") {
//     Tree<int, 3> tree;

//     SUBCASE("Add sub-node to non-existent parent") {
//         tree.add_root(1);
//         CHECK_THROWS_AS(tree.add_sub_node(2, 3), std::invalid_argument);
//     }

//     SUBCASE("Exceed maximum children") {
//         tree.add_root(1).add_sub_node(1, 2).add_sub_node(1, 3).add_sub_node(1, 4);
//         CHECK_THROWS_AS(tree.add_sub_node(1, 5), std::invalid_argument);
//     }
// }
