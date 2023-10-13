#include "Duration.h"
#include "TimeSimulator.h"
#include "assure.h"
#include <thread>

using namespace timeutils;
using namespace timeutils_simulator;

namespace duration_tests
{

TEST_CASE("Duration", "Duration")
{
    TimeSimulator simulator;
    Duration d;
    simulator.steadyClockElapseMilliSeconds(1);
    ASSURE_EQ(d.getLastDurationMs(), 1);
    ASSURE_EQ(d.getTotalDurationMs(), 1);

    simulator.steadyClockElapseSeconds(1);
    ASSURE_EQ(d.getLastDurationMs(), 1000);
    ASSURE_EQ(d.getTotalDurationMs(), 1001);

    simulator.steadyClockElapseMinutes(1);
    ASSURE_EQ(d.getLastDurationMs(), 60000);
    ASSURE_EQ(d.getTotalDurationMs(), 61001);

    simulator.steadyClockElapseHours(1);
    ASSURE_EQ(d.getLastDurationMs(), 3600000);
    ASSURE_EQ(d.getTotalDurationMs(), 3661001);

    simulator.steadyClockElapseDays(1);
    ASSURE_EQ(d.getLastDurationMs(), 24 * 3600000);
    ASSURE_EQ(d.getTotalDurationMs(), 24 * 3600000 + 3661001);
}


}
