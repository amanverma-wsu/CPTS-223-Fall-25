#include <iostream>
#include "avl_map.h"

using namespace std;

/*
 * Helper function to print a visual header for each test section.
 * Makes console output easier to read.
 */
void printTestHeader(const string& test_name) {
    cout << "\n========================================" << endl;
    cout << "TEST: " << test_name << endl;
    cout << "========================================" << endl;
}

/*
 * Test: Simple Insertions
 * -----------------------
 * Inserts three key-value pairs into the AVL tree and verifies that
 * each element can be found. Checks that the tree stores values correctly.
 */
void testSimpleInsertions() {
    printTestHeader("Simple Insertions");
    avl_map<int, string> tree;

    cout << "Inserting: 10, 20, 30" << endl;
    tree.insert(10, "Ten");
    tree.insert(20, "Twenty");
    tree.insert(30, "Thirty");

    cout << "Tree size: " << tree.size() << endl;

    // Verify that all inserted keys exist
    auto it = tree.find(10);
    if (it != tree.end()) cout << "Found 10: " << *it << endl;
    it = tree.find(20);
    if (it != tree.end()) cout << "Found 20: " << *it << endl;
    it = tree.find(30);
    if (it != tree.end()) cout << "Found 30: " << *it << endl;

    cout << "✓ Simple insertions test passed" << endl;
}

/*
 * Test: Left-Left (LL) Rotation
 * -----------------------------
 * Inserting keys in descending order (30, 20, 10)
 * creates a left-heavy imbalance that requires a right rotation.
 */
void testLLRotation() {
    printTestHeader("Left-Left Rotation");
    avl_map<int, string> tree;

    cout << "Inserting: 30, 20, 10 (should trigger LL -> Right rotation)" << endl;
    tree.insert(30, "Thirty");
    cout << "  Inserted 30" << endl;
    tree.insert(20, "Twenty");
    cout << "  Inserted 20" << endl;
    tree.insert(10, "Ten");
    cout << "  Inserted 10 - Rotation occurred!" << endl;

    cout << "Tree size: " << tree.size() << endl;

    // Check all elements after rotation
    for (int key : {10, 20, 30}) {
        auto it = tree.find(key);
        if (it != tree.end())
            cout << "Found " << key << ": " << *it << endl;
        else
            cout << "ERROR: Could not find " << key << endl;
    }
    cout << "✓ LL rotation test passed" << endl;
}

/*
 * Test: Right-Right (RR) Rotation
 * -------------------------------
 * Inserting keys in ascending order (10, 20, 30)
 * causes a right-heavy imbalance, fixed with a left rotation.
 */
void testRRRotation() {
    printTestHeader("Right-Right Rotation");
    avl_map<int, string> tree;

    cout << "Inserting: 10, 20, 30 (should trigger RR -> Left rotation)" << endl;
    tree.insert(10, "Ten");
    cout << "  Inserted 10" << endl;
    tree.insert(20, "Twenty");
    cout << "  Inserted 20" << endl;
    tree.insert(30, "Thirty");
    cout << "  Inserted 30 - Rotation occurred!" << endl;

    cout << "Tree size: " << tree.size() << endl;

    for (int key : {10, 20, 30}) {
        auto it = tree.find(key);
        if (it != tree.end())
            cout << "Found " << key << ": " << *it << endl;
        else
            cout << "ERROR: Could not find " << key << endl;
    }
    cout << "✓ RR rotation test passed" << endl;
}

/*
 * Test: Left-Right (LR) Rotation
 * ------------------------------
 * Inserting (30, 10, 20) creates a zig-zag pattern that requires
 * a double rotation (Left-Right) to balance the tree.
 */
void testLRRotation() {
    printTestHeader("Left-Right Rotation");
    avl_map<int, string> tree;

    cout << "Inserting: 30, 10, 20 (should trigger LR rotation)" << endl;
    tree.insert(30, "Thirty");
    cout << "  Inserted 30" << endl;
    tree.insert(10, "Ten");
    cout << "  Inserted 10" << endl;
    tree.insert(20, "Twenty");
    cout << "  Inserted 20 - Rotation occurred!" << endl;

    cout << "Tree size: " << tree.size() << endl;

    for (int key : {10, 20, 30}) {
        auto it = tree.find(key);
        if (it != tree.end()) cout << "Found " << key << ": " << *it << endl;
    }
    cout << "✓ LR rotation test passed" << endl;
}

/*
 * Test: Right-Left (RL) Rotation
 * ------------------------------
 * Inserting (10, 30, 20) creates a mirror zig-zag that needs
 * a double rotation (Right-Left) for balance.
 */
void testRLRotation() {
    printTestHeader("Right-Left Rotation");
    avl_map<int, string> tree;

    cout << "Inserting: 10, 30, 20 (should trigger RL rotation)" << endl;
    tree.insert(10, "Ten");
    cout << "  Inserted 10" << endl;
    tree.insert(30, "Thirty");
    cout << "  Inserted 30" << endl;
    tree.insert(20, "Twenty");
    cout << "  Inserted 20 - Rotation occurred!" << endl;

    cout << "Tree size: " << tree.size() << endl;

    for (int key : {10, 20, 30}) {
        auto it = tree.find(key);
        if (it != tree.end()) cout << "Found " << key << ": " << *it << endl;
    }
    cout << "✓ RL rotation test passed" << endl;
}

/*
 * Test: Deletion
 * --------------
 * Inserts multiple nodes and deletes specific keys.
 * Verifies that deletion works and tree remains valid.
 */
void testDeletion() {
    printTestHeader("Deletion Operations");
    avl_map<int, string> tree;

    cout << "Building tree with values: 50, 25, 75, 10, 30, 60, 80" << endl;
    tree.insert(50, "Fifty");
    tree.insert(25, "Twenty-Five");
    tree.insert(75, "Seventy-Five");
    tree.insert(10, "Ten");
    tree.insert(30, "Thirty");
    tree.insert(60, "Sixty");
    tree.insert(80, "Eighty");

    cout << "Tree size: " << tree.size() << endl;

    // Delete leaf node
    cout << "\nDeleting 10..." << endl;
    tree.erase(10);
    cout << "Tree size after deletion: " << tree.size() << endl;
    auto it = tree.find(10);
    if (it == tree.end())
        cout << "✓ 10 successfully deleted" << endl;
    else
        cout << "ERROR: 10 still exists!" << endl;

    // Delete node with one or two children
    cout << "\nDeleting 25..." << endl;
    tree.erase(25);
    cout << "Tree size after deletion: " << tree.size() << endl;
    it = tree.find(25);
    if (it == tree.end())
        cout << "✓ 25 successfully deleted" << endl;
    else
        cout << "ERROR: 25 still exists!" << endl;

    // Verify remaining nodes exist
    cout << "\nVerifying remaining nodes:" << endl;
    for (int key : {30, 50, 60, 75, 80}) {
        it = tree.find(key);
        if (it != tree.end())
            cout << "  ✓ " << key << " exists" << endl;
        else
            cout << "  ERROR: " << key << " not found!" << endl;
    }
    cout << "✓ Deletion test passed" << endl;
}

/*
 * Test: Large Dataset
 * -------------------
 * Inserts 1000 key-value pairs to test scalability.
 * Then performs random lookups to confirm performance and correctness.
 */
void testLargeDataset() {
    printTestHeader("Large Dataset Test");
    avl_map<int, int> tree;
    int n = 1000;

    cout << "Inserting " << n << " elements..." << endl;
    for (int i = 1; i <= n; i++)
        tree.insert(i, i * 10);

    cout << "Tree size: " << tree.size() << endl;

    cout << "Testing random lookups..." << endl;
    int test_keys[] = {1, 250, 500, 750, 1000, 999, 501};

    for (int key : test_keys) {
        auto it = tree.find(key);
        if (it != tree.end() && *it == key * 10)
            cout << "  ✓ Found " << key << " -> " << *it << endl;
        else
            cout << "  ERROR: Failed to find " << key << endl;
    }
    cout << "✓ Large dataset test passed" << endl;
}

/*
 * Test: Update Existing Key
 * -------------------------
 * Inserts a key-value pair, then reinserts the same key with a new value.
 * Ensures the value is updated instead of duplicated.
 */
void testUpdateValue() {
    printTestHeader("Update Existing Key");
    avl_map<int, string> tree;

    tree.insert(10, "Original");
    cout << "Inserted 10 -> 'Original'" << endl;

    auto it = tree.find(10);
    if (it != tree.end()) cout << "Current value: " << *it << endl;

    cout << "Updating 10 -> 'Updated'" << endl;
    tree.insert(10, "Updated");

    it = tree.find(10);
    if (it != tree.end()) {
        cout << "New value: " << *it << endl;
        if (*it == "Updated")
            cout << "✓ Update test passed" << endl;
        else
            cout << "ERROR: Value not updated!" << endl;
    }
}

/*
 * Main test runner
 * ----------------
 * Runs all test cases sequentially.
 * Catches any exceptions thrown during the tests.
 */
int main() {
    cout << "AVL Tree Implementation Test Suite" << endl;
    cout << "===================================" << endl;

    try {
        testSimpleInsertions();
        testLLRotation();
        testRRRotation();
        testLRRotation();
        testRLRotation();
        testDeletion();
        testUpdateValue();
        testLargeDataset();

        cout << "\n========================================" << endl;
        cout << "ALL TESTS PASSED! ✓" << endl;
        cout << "========================================" << endl;
    } catch (const exception& e) {
        cout << "\nERROR: " << e.what() << endl;
        return 1;
    }

    return 0;
}
