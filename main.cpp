#define INITIALIZE_A3D_API
#include <A3DSDKIncludes.h>
#include <iostream>
#include <string>

std::string getName( A3DEntity *ntt ) {
    std::string name;
    A3DRootBaseData rbd;
    A3D_INITIALIZE_DATA( A3DRootBaseData, rbd );
    if( A3D_SUCCESS == A3DRootBaseGet( ntt, &rbd ) ) {
        name = rbd.m_pcName ? rbd.m_pcName : "";
    }
    A3DRootBaseGet( nullptr, &rbd );
    return name;
}

void traverse( A3DAsmProductOccurrence *po, int indent = 1) {
    if( nullptr == po ) {
        return;
    }

    std::cout << std::string( 2*indent, ' ' ) << getName( po ) << std::endl;

    A3DAsmProductOccurrenceData pd;
    A3D_INITIALIZE_DATA( A3DAsmProductOccurrenceData, pd );
    if( A3D_SUCCESS == A3DAsmProductOccurrenceGet( po, &pd ) ) {
        for(A3DUns32 idx = 0u; idx < pd.m_uiPOccurrencesSize; ++idx ) {
            traverse( pd.m_ppPOccurrences[idx], indent + 1 );
        }
    }
    A3DAsmProductOccurrenceGet( nullptr, &pd );
}

int main(int, char**) { 
    A3DSDKHOOPSExchangeLoader loader("X:/HOOPS_Exchange_Publish_2021_SP2_U2/bin/win64_v140");
    if( ! loader.m_bSDKLoaded ) {
        std::cerr << "Unable to load HOOPS Exchange." << std::endl;
        std::cerr << "Status: " << A3DMiscGetErrorMsg(loader.m_eSDKStatus) << std::endl;
        return -1;
    }

    std::cout << "Ready for use." << std::endl;

    A3DRWParamsLoadData load_params;
    A3D_INITIALIZE_DATA( A3DRWParamsLoadData, load_params );
    A3DAsmModelFile *model_file = nullptr;
    char const *input_file = 
        "X:/HOOPS_Exchange_2021_SP2_U2/samples/data/prc/__drill.prc";
    A3DStatus load_status = A3DAsmModelFileLoadFromFile( input_file, &load_params, &model_file );
    if( A3D_SUCCESS != load_status ) {
        std::cerr << "Unable to load the specified file: " << input_file << std::endl;
        std::cerr << "Status: " << A3DMiscGetErrorMsg( load_status ) << std::endl;
        return -1;
    } else {
        std::cout << "Loaded file: " << input_file << std::endl;
    }

    std::cout << getName( model_file ) << std::endl;

    A3DAsmModelFileData mfd;
    A3D_INITIALIZE_DATA( A3DAsmModelFileData, mfd );
    if( A3D_SUCCESS == A3DAsmModelFileGet( model_file, &mfd ) ) {
        for( A3DUns32 idx = 0u; idx < mfd.m_uiPOccurrencesSize; ++idx ) {
            traverse( mfd.m_ppPOccurrences[idx] );
        }
    }
    A3DAsmModelFileGet( nullptr, &mfd );

    A3DAsmModelFileDelete( model_file );
    model_file = nullptr;
    return 0;
}

