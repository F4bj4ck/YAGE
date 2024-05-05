#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <optional>
#include <array>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui_impl_glfw.h"
#include "ImGui/imgui_impl_vulkan.h"

#include "Window.h"
#include "ImGui/imgui.h"

namespace Yage
{
    //TODO: ImGui Test
    static void checkVkResult(VkResult err)
    {
        if (err == 0)
        {
            return;;
        }
        fprintf(stderr, "[Vulkan] Error: VKResult = %d\n", err);
        YAGE_ERROR(err);
        if (err < 0)
        {
            abort();
        }
    }
    //------------------------------------------------------------------------------------
    
    
    //TODO: REMOVE THESE ASAP
    const std::string MODEL_PATH = "models/viking_room.obj";
    const std::string TEXTURE_PATH = "textures/viking_room.png";
    
    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    struct UniformBufferObject
    {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
    };
    
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct Vertex
    {
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec2 texCoord;

        static VkVertexInputBindingDescription GetBindingDescription()
        {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> GetAttributeDescriptions()
        {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);
        
            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

            return attributeDescriptions;
        }

        bool operator== (const Vertex& other) const
        {
            return pos == other.pos && color == other.color && texCoord == other.texCoord;
        }
    };
    
#ifdef NDEBUG
    const bool m_enableValidationLayers = false;
#else
    const bool m_enableValidationLayers = true;
#endif
    
    class VulkanContext
    {
    public:
        VulkanContext(GLFWwindow* window);
        ~VulkanContext();
        void Init();
        static VulkanContext* Create(GLFWwindow* window);
        void DrawFrame();
        void RecreateSwapChain();
        
    private:
        float m_RenderTime = 0;
        bool m_ShowDemoWindow = true;
        ImVec4 m_Color;
        
        GLFWwindow* m_Window;
        VkInstance m_Instance;
        VkSurfaceKHR m_Surface;
        VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
        VkDevice m_Device;
        VkQueue m_GraphicsQueue;
        uint32_t m_QueueFamily;
        VkQueue m_PresentQueue;
        VkSwapchainKHR m_SwapChain;
        std::vector<VkImage> m_SwapChainImages;
        VkFormat m_SwapChainImageFormat;
        VkExtent2D m_SwapChainExtent;

        VkRenderPass m_RenderPass;
        VkDescriptorSetLayout m_DescriptorSetLayout;
        VkPipelineLayout m_PipelineLayout;
        VkPipeline m_GraphicsPipeline;

        VkCommandPool m_CommandPool;

        VkImage m_ColorImage;
        VkDeviceMemory m_ColorImageMemory;
        VkImageView m_ColorImageView;

        VkImage m_DepthImage;
        VkDeviceMemory m_DepthImageMemory;
        VkImageView m_DepthImageView;

        //TODO: move into material class
        uint32_t m_MipLevels;
        VkImage m_textureImage;
        VkDeviceMemory m_TextureImageMemory;

        VkBuffer m_StagingBuffer;
        VkDeviceMemory m_StagingBufferMemory;

        VkImageView m_TextureImageView;
        VkSampler m_TextureSampler;

        //TODO: move into mesh class
        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;
        VkBuffer m_VertexBuffer;
        VkDeviceMemory m_VertexBufferMemory;
        VkBuffer m_IndexBuffer;
        VkDeviceMemory m_IndexBufferMemory;

        std::vector<VkBuffer> m_UniformBuffers;
        std::vector<VkDeviceMemory> m_UniformBuffersMemory;

        VkDescriptorPool m_DescriptorPool;
        std::vector<VkDescriptorSet> m_DescriptorSets;

        std::vector<VkCommandBuffer> m_CommandBuffers;

        std::vector<VkImageView> m_SwapChainImageViews;
        std::vector<VkFramebuffer> m_SwapChainFramebuffers;

        std::vector<VkSemaphore> m_ImageAvailableSemaphores;
        std::vector<VkSemaphore> m_RenderFinishedSemaphores;
        std::vector<VkFence> m_InFlightFences;

        // viewport
        /*std::vector<VkImage> m_ViewportImages;
        std::vector<VkDeviceMemory> m_ViewportImageMemory;
        std::vector<VkImageView> m_ViewportImageViews;

        VkRenderPass m_ViewportRenderPass;
        VkPipeline m_ViewportPipeline;
        VkCommandPool m_ViewportCommandPool;
        std::vector<VkFramebuffer> m_ViewportFramebuffers;
        std::vector<VkCommandBuffer> m_ViewportCommandBuffers;

        std::vector<VkDescriptorSet> m_ViewportDescriptorSet;*/

        const int MAX_FRAMES_IN_FLIGHT = 2;

        uint32_t m_CurrentFrame = 0;
        
        VkSampleCountFlagBits m_MsaaSamples = VK_SAMPLE_COUNT_1_BIT;
        
        void CreateInstance();
        void CreateSurface();
        void PickPhysicalDevice();
        void CreateLogicalDevice();
        void CreateSwapChain();
        void CreateImageViews();
        void CreateRenderPass();
        void CreateDescriptorSetLayout();
        void CreateGraphicsPipeline();
        void CreateCommandPool(VkCommandPool* commandPool);
        void CreateColorResources();
        void CreateDepthResources();
        void CreateFramebuffers();
        void CreateTextureImage();
        void CreateTextureImageView();
        void CreateTextureSampler();
        void LoadModel();
        void CreateVertexBuffer();
        void CreateIndexBuffer();
        void CreateUniformBuffers();
        void CreateDescriptorPool();
        void CreateDescriptorSets();
        void CreateCommandBuffers();
        void CreateSyncObjects();
        
        bool IsDeviceSuitable(VkPhysicalDevice device);
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
        bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
        SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
        VkSampleCountFlagBits GetMaxUsableSampleCount();
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
        VkFormat FindDepthFormat();
        VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkShaderModule CreateShaderModule(const std::vector<char>& code);
        void CreateImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
        uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void TransitionImageLayout(VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
        VkCommandBuffer BeginSingleTimeCommands(const VkCommandPool &commandPool);
        void EndSingleTimeCommands(VkCommandBuffer commandBuffer, const VkCommandPool &commandPool);
        void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
        void GenerateMipMaps(VkImage image, VkFormat format, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
        void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void UpdateUniformBuffer(uint32_t currentImage);
        void RecordCommandBuffer(VkCommandBuffer commandbuffer, uint32_t imageIndex);

        //viewport setup
        /*void CreateViewportImages();
        void CreateViewportImageViews();
        void InsertImageMemoryBarrier(VkCommandBuffer commandBuffer, VkImage image, VkAccessFlags srcAccessFlags, VkAccessFlags dstAccessFlags, VkImageLayout oldImageLayout, VkImageLayout newImageLayout, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkImageSubresourceRange subresourceRange);
        void CreateViewportFrameBuffers();*/
        
        void CleanUpSwapChain();
        
        //TODO: move to file reader class
        static std::vector<char> ReadFile(const std::string& filename);
        
        bool CheckValidationLayerSupport();
        void CleanUp();

        const std::vector<const char*> m_validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };
    };
}

namespace std
{
    template<> struct hash<Yage::Vertex>
    {
        size_t operator() (Yage::Vertex const& vertex) const
        {
            return ((hash<glm::vec3>()(vertex.pos) ^
                    (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
                        (hash<glm::vec2>()(vertex.texCoord) << 1);
        }    
    };
}