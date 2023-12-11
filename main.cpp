#define INITIALIZE_A3D_API
#include <A3DSDKIncludes.h>

#include <iostream>
#include <string>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////
/// INPUT_FILE
/// Default CAD input file, relative to Exchange sample data folder.
/// To see how the value is used, check the `main()` function.
#define INPUT_FILE "/prc/_micro engine.prc"

void traverse_tree(A3DTree* const hnd_tree, A3DTreeNode* const hnd_node, size_t depth) {
    // Display node's entity name
    std::cout << std::string(2 * depth, ' '); // Print indent

    A3DUTF8Char* node_name = 0;
    if (A3DTreeNodeGetName(hnd_node, &node_name) == A3D_SUCCESS && node_name != 0) {
        std::cout << node_name << std::endl;
        A3DTreeNodeGetName(0, &node_name);
    } else {
        std::cout << "N/A" << std::endl;
    }
    
    // Recursively call traverse_tree on chil nodes
    A3DUns32 n_child_nodes    = 0;
    A3DTreeNode** child_nodes = 0;

    if(A3DTreeNodeGetChildren(hnd_tree, hnd_node, &n_child_nodes, &child_nodes) == A3D_SUCCESS) {
        for (A3DUns32 n = 0 ; n < n_child_nodes ; ++n) {
            traverse_tree(hnd_tree, child_nodes[n], depth+1);
        }
        A3DTreeNodeGetChildren(0, 0, &n_child_nodes, &child_nodes);
    }
}
 
int main(int argc, char* argv[])
{
    /////////////////////////////////////////////////////
    // INITIALIZE HOOPS EXCHANGE AND LOAD THE MODEL FILE.
    A3DSDKHOOPSExchangeLoader he_loader(HE_BINARY_DIRECTORY);
    assert(he_loader.m_eSDKStatus == A3D_SUCCESS);
    
    A3DImport he_import(HE_DATA_DIRECTORY INPUT_FILE);
    A3DStatus status = he_loader.Import(he_import);
    assert(status == A3D_SUCCESS);
    A3DAsmModelFile* model_file = he_loader.m_psModelFile;

    ////////////////////////////////////////////////////////
    // TRAVERSE THE MODEL TREE
    A3DTree*         hnd_tree = 0;

    status = A3DTreeCompute(model_file, &hnd_tree, 0);
    assert(status == A3D_SUCCESS);

    A3DTreeNode* hnd_root_node = 0;
    status = A3DTreeGetRootNode(hnd_tree, &hnd_root_node);
    assert(status == A3D_SUCCESS);

    traverse_tree(hnd_tree, hnd_root_node, 0);

    A3DTreeCompute(0, &hnd_tree, 0);

    /////////////////////////////////////////////////////////
    // Everything is loaded to GPU, Exchange can be released.
    A3DAsmModelFileDelete(model_file);
    A3DDllTerminate();
    A3DSDKUnloadLibrary();

    return EXIT_SUCCESS;
}
