#include "YAGE/Log.h"


int main(int argc, char* argv[])
{
    Yage::Log::Init();
    YAGE_ERROR("This is an error");
    YAGE_WARN("This is a warning");
    YAGE_INFO("This is an info");
    YAGE_TRACE("This is a trace");
    return 0;
}
