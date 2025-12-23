
# Slang does not have config files, so we need to find it manually. Find the include and lib paths.
FIND_PATH(SLANG_INCLUDE_DIR slang.h
        PATHS ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)
FIND_LIBRARY(SLANG_LIBRARY NAMES slang
        PATHS ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib)

find_package(glslang CONFIG REQUIRED)
find_package(SPIRV-Tools CONFIG REQUIRED)
find_package(SPIRV-Tools-link CONFIG REQUIRED)
find_package(SPIRV-Tools-lint CONFIG REQUIRED)
find_package(SPIRV-Tools-opt CONFIG REQUIRED)
find_package(spirv_cross_core CONFIG REQUIRED)
find_package(spirv_cross_glsl CONFIG REQUIRED)
find_package(spirv_cross_reflect CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

SET(PACKAGES_LIBRARIES
        ${PACKAGES}
        ${SLANG_LIBRARY}
        glslang::glslang glslang::glslang-default-resource-limits glslang::SPIRV glslang::SPVRemapper
        # SPIRV-Tools-shared
        # SPIRV-Tools
        SPIRV-Tools-link
        SPIRV-Tools-lint
        SPIRV-Tools-opt
        spirv-cross-core
        spirv-cross-glsl
        spirv-cross-reflect
        spdlog::spdlog
)

SET(PACKAGES_INCLUDE
        ${PACKAGES_INCLUDE}
        ${SLANG_INCLUDE_DIR}
)

