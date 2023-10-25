#include <stdint.h>
#include <string>
namespace timeutils
{
    enum class TimeFormatType;
    struct WallClock
    {
        static uint64_t getCurrentTimeUTCAsMs();
        static std::string getCurrentTimeUTCAsLogTimestamp();

        template<typename FmtType>
        static std::string getCurrentTimeUTCAsString(FmtType type) {
            return getCurrentTimeUTCAsString(static_cast<int>(type));
        }

    private:
        static std::string getCurrentTimeUTCAsString(int type);
    };
}