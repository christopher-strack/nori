#include "output_printer.h"
#include "nori/detail/log.h"


namespace nori {
namespace testing {

void output_printer::OnTestProgramEnd(const ::testing::UnitTest& unit_test) {
    if (unit_test.Passed()) {
        detail::log_raw(
            "ALL TESTS PASSED (%d tests)\n",
            unit_test.total_test_count());
    }
    else {
        detail::log_raw(
            "TESTS FAILED (%d test(s) failed)\n",
            unit_test.failed_test_count());
    }
}

void output_printer::OnTestStart(const ::testing::TestInfo& test_info) {
    detail::log_raw("[Test] %s.%s... ", test_info.test_case_name(), test_info.name());
}

void output_printer::OnTestPartResult(const ::testing::TestPartResult& result) {
    if (result.failed()) {
        if (result.file_name() != 0) {
            detail::log_raw("\n%s:%d\n", result.file_name(), result.line_number());
        }
        else {
            detail::log_raw("failed");
        }

        detail::log_raw("%s\n", result.summary());
    }
}

void output_printer::OnTestEnd(const ::testing::TestInfo& test_info) {
    const ::testing::TestResult* result = test_info.result();
    if (result && result->Passed()) {
        detail::log_raw("ok (%dms)\n", result->elapsed_time());
    }
}


} /* namespace testing */
} /* namespace nori */
