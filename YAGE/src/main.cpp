#include "YAGE/Application.h"
#include "YAGE/Log.h"

int main(int argc, char* argv[])
{
    Yage::Log::Init();

    Yage::Application app;
    app.Run();
    
    return 0;
}
