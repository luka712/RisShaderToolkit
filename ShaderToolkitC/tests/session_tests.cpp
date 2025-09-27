#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include "slang/slang_session.hpp"

using namespace shader_toolkit;

bool create_session()
{
	shader_toolkit::SlangSession session;
	return session.initialize();
}

TEST_CASE("slang tests", "[create_slang_session]") {
    REQUIRE(create_session());
 
}