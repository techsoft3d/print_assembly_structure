#define INITIALIZE_A3D_API
#include <A3DSDKIncludes.h>
#include <iostream>

int main(int, char**) {
    A3DBool is_loaded = A3DSDKLoadLibraryA("/opt/local/ts3d/HOOPS_Exchange_2021_SP2_U2/bin/macos");
    if( !is_loaded ) {
        std::cerr << "Unable to load HOOPS Exchange." << std::endl;
        return -1;
    }
}
