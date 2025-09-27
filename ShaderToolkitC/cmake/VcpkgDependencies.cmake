
# Slang does not have config files, so we need to find it manually. Find the include and lib paths.
FIND_PATH(SLANG_INCLUDE_DIR slang.h
        PATHS ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)
FIND_LIBRARY(SLANG_LIBRARY NAMES slang
        PATHS ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib)

SET(PACKAGES_LIBRARIES
        ${PACKAGES}
        ${SLANG_LIBRARY}
)

SET(PACKAGES_INCLUDE
        ${PACKAGES_INCLUDE}
        ${SLANG_INCLUDE_DIR}
)

