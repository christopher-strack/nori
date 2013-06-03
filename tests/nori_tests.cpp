#include "output_printer.h"

#include "nori/application.h"
#include "nori/main.h"
#include "nori/log.h"

#include <gtest/gtest.h>

#include <stdexcept>


class nori_tests : public nori::application
{
public:
    nori_tests(const nori::application_arguments& args)
        : _application_arguments(args), result(0)
    {
    }

    int result;

protected:
    virtual void on_initialized() {
        int argc = _application_arguments.argc;
        ::testing::InitGoogleTest(&argc, _application_arguments.argv);

        ::testing::UnitTest& unit_test = *::testing::UnitTest::GetInstance();
        ::testing::TestEventListeners& listeners = unit_test.listeners();
        listeners.Append(new nori::testing::output_printer());

        result = RUN_ALL_TESTS();

        shutdown();
    }

private:
    const nori::application_arguments& _application_arguments;
};


int nori_main(const nori::application_arguments& args)
{
    try {
        nori_tests tests(args);
        tests.run(args);
        return tests.result;
    }
    catch (const std::runtime_error& error) {
        nori::log_error(error.what());
        return 1;
    }

    return 0;
}
