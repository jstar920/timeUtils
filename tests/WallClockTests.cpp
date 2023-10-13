#include "WallClock.h"
#include "TimeSimulator.h"
#include "assure.h"
#include <thread>

using namespace timeutils;
using namespace timeutils_simulator;

namespace wallclock_tests
{

TEST_CASE("WallClock", "WallClock")
{
    TimeSimulator simulator;
    WallClock clock;
    simulator.systemClockElapseMilliSeconds(1);
    ASSURE_EQ(clock.getCurrentTimeUTCAsMs(), 1);
    ASSURE_EQ(clock.getCurrentTimeUTCAsLogTimestamp(), "1970-01-01T00:00:00.001Z");

    simulator.systemClockElapseSeconds(1);
    ASSURE_EQ(clock.getCurrentTimeUTCAsMs(), 1000);
    ASSURE_EQ(clock.getCurrentTimeUTCAsLogTimestamp(), "1970-01-01T00:00:01.001Z");

    simulator.systemClockElapseMinutes(1);
    ASSURE_EQ(clock.getCurrentTimeUTCAsMs(), 60000);
    ASSURE_EQ(clock.getCurrentTimeUTCAsLogTimestamp(), "1970-01-01T00:01:01.001Z");

    simulator.systemClockElapseHours(1);
    ASSURE_EQ(clock.getCurrentTimeUTCAsMs(), 3600000);
    ASSURE_EQ(clock.getCurrentTimeUTCAsLogTimestamp(), "1970-01-01T01:01:01.001Z");

    simulator.systemClockElapseDays(1);
    ASSURE_EQ(clock.getCurrentTimeUTCAsMs(), 24 * 3600000);
    ASSURE_EQ(clock.getCurrentTimeUTCAsLogTimestamp(), "1970-01-02T01:01:01.001Z");
}


}