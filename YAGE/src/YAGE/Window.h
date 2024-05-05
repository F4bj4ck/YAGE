#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "GLFW/glfw3.h"

namespace Yage
{
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "YAGE",
                    unsigned int width = 1280,
                    unsigned int height = 720)
                : Title(title), Width(width), Height(height)
        {
        }
    };
    
    class Window
    {
    public:
        using EventCallbackFunction = std::function<void(Event&)>;
        
        Window(const WindowProps& props);
        ~Window();

        void OnUpdate();

        unsigned int GetWidth();
        unsigned int GetHeight();

        void SetEventCallback(const EventCallbackFunction& callback);
        void SetVSync(bool enabled);
        bool IsVSync() const;

        static Window* Create(const WindowProps& props = WindowProps());

        GLFWwindow* GetGLFWWindow();

    private:
        void Init(const WindowProps& props);
        void ShutDown();
    private:
        GLFWwindow* m_Window;
        
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFunction EventCallback;
        };

        WindowData m_Data;
    };
}