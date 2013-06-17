#ifndef NORI_OUTPUT_PRINTER_H_
#define NORI_OUTPUT_PRINTER_H_

#include <gtest/gtest.h>


namespace nori {
namespace testing {

class output_printer : public ::testing::EmptyTestEventListener
{
protected:
    virtual void OnTestProgramEnd(const ::testing::UnitTest& unitTest);
    virtual void OnTestStart(const ::testing::TestInfo& testInfo);
    virtual void OnTestPartResult(const ::testing::TestPartResult& testPartResult);
    virtual void OnTestEnd(const ::testing::TestInfo& testInfo);
};

} // namespace testing
} // namespace nori

#endif /* NORI_OUTPUT_PRINTER_H_ */
