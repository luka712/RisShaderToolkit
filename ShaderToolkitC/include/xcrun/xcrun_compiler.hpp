#ifndef XCRUN_COMPILER_H
#define XCRUN_COMPILER_H

#include "data/enums.hpp"
#include <map>
#include "xcrun/xcrun_compile_result.hpp"

namespace ris_shader_toolkit
{
    //! The XcrunCompiler class provides functionality to compile shaders using the xcrun tool.
    class XcrunCompiler
    {
        public:
        //! The constructor.
        XcrunCompiler();
        
            //! Compile a intermediate metal shader file (.air) to a metallib file (.metallib) using xcrun.
            //! @param inputFilePath The path to the input metal shader file.
            //! @param outputFilePath The path to the output metallib file.
            //! @param sdk The target Apple SDK platform (default is AppleSdk::macOS).
            XcrunCompileResult compileIntermediateToMetallib(
                const std::string& inputFilePath,
                const std::string& outputFilePath,
                AppleSdk sdk = AppleSdk::macOS
            );

        //! Compile a metal shader file to a intermediate format (.air) using xcrun.
        //! @param inputFilePath The path to the input metal shader file.
        //! @param outputFilePath The path to the output metallib file.
        //! @param sdk The target Apple SDK platform (default is AppleSdk::macOS).
        XcrunCompileResult compileMetalToIntermediate(
            const std::string& inputFilePath,
            const std::string& outputFilePath,
            AppleSdk sdk = AppleSdk::macOS
        );
        
    private:
        std::map<AppleSdk, std::string> mapSdk;
        
    };

}


#endif //XCRUN_COMPILER_H
