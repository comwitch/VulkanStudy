#include "first_app.h"

// std
#include <array>
#include <stdexcept>

namespace lve {

    FirstApp::FirstApp() {
        loadModels();
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    FirstApp::~FirstApp() { vkDestroyPipelineLayout(lveDevice.device(), pipelineLayout, nullptr); }

    void FirstApp::run() {
        while (!lveWindow.shouldClose()) {
            glfwPollEvents();
            drawFrame();
        }

        vkDeviceWaitIdle(lveDevice.device());
    }

    

    void FirstApp::loadModels()
    {
        LveModel::Vertex V1 = { {0.0f, -0.5f} };
        LveModel::Vertex V2 = { {0.5f, 0.5f} };
        LveModel::Vertex V3 = { {-0.5f, 0.5f} };

        lveModel = std::make_unique<LveModel>(lveDevice, makeSierpinskiTriangle(V1,V2,V3,1));
    }

    void FirstApp::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;
        if (vkCreatePipelineLayout(lveDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
            VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    }

    void FirstApp::createPipeline() {
        PipelineConfigInfo pipelineConfig{};
        LvePipeline::defaultPipelineConfigInfo(
            pipelineConfig,
            lveSwapChain.width(),
            lveSwapChain.height());
        pipelineConfig.renderPass = lveSwapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        lvePipeline = std::make_unique<LvePipeline>(
            lveDevice,
            "shaders/simple_shader.vert.spv",
            "shaders/simple_shader.frag.spv",
            pipelineConfig);
    }

    void FirstApp::createCommandBuffers() {
        commandBuffers.resize(lveSwapChain.imageCount());

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = lveDevice.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if (vkAllocateCommandBuffers(lveDevice.device(), &allocInfo, commandBuffers.data()) !=
            VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        for (int i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = lveSwapChain.getRenderPass();
            renderPassInfo.framebuffer = lveSwapChain.getFrameBuffer(i);

            renderPassInfo.renderArea.offset = { 0, 0 };
            renderPassInfo.renderArea.extent = lveSwapChain.getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
            clearValues[1].depthStencil = { 1.0f, 0 };
            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            lvePipeline->bind(commandBuffers[i]);
            lveModel->bind(commandBuffers[i]);
            lveModel->draw(commandBuffers[i]);

            vkCmdEndRenderPass(commandBuffers[i]);
            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer!");
            }
        }
    }
    void FirstApp::drawFrame() {
        uint32_t imageIndex;
        auto result = lveSwapChain.acquireNextImage(&imageIndex);
        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        result = lveSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }
        

     
    }

    std::vector<LveModel::Vertex> FirstApp::makeSierpinskiTriangle(LveModel::Vertex A, LveModel::Vertex B, LveModel::Vertex C, int Iteration)
    {
        if (Iteration ==0)
        {
            std::vector<LveModel::Vertex> vectors;
            vectors.push_back(A);
            vectors.push_back(B);
            vectors.push_back(C);

            return vectors;
        }


        LveModel::Vertex tmpAB = {{0.0f, 0.0f}};
        tmpAB.position[0] = 0.5f * A.position[0] + 0.5f * B.position[0];
        tmpAB.position[1] = 0.5f * A.position[1] + 0.5f * B.position[1];
        LveModel::Vertex tmpBC = { {0.0f, 0.0f} };;
        tmpBC.position[0] = 0.5f * B.position[0] + 0.5f * C.position[0];
        tmpBC.position[1] = 0.5f * B.position[1] + 0.5f * C.position[1];
        LveModel::Vertex tmpAC = { {0.0f, 0.0f} };;
        tmpAC.position[0] = 0.5f * A.position[0] + 0.5f * C.position[0];
        tmpAC.position[1] = 0.5f * A.position[1] + 0.5f * C.position[1];

        std::vector<LveModel::Vertex> tmpVectorA = makeSierpinskiTriangle(A, tmpAB, tmpAC, Iteration-1);
        std::vector<LveModel::Vertex> tmpVectorB = makeSierpinskiTriangle(tmpAB, tmpBC, B, Iteration-1);
        std::vector<LveModel::Vertex> tmpVectorC = makeSierpinskiTriangle(tmpAC, C, tmpBC, Iteration-1);

        tmpVectorA.insert(tmpVectorA.end(), tmpVectorB.begin(), tmpVectorB.end());
        tmpVectorA.insert(tmpVectorA.end(), tmpVectorC.begin(), tmpVectorC.end());


        return tmpVectorA;
    }

   
    
}  // namespace lve