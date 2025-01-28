/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Copyright (C) 2025 Hossein Assaran
**
** This file is part of VulkanImageViewer.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU Affero General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Affero General Public License for more details.
**
** You should have received a copy of the GNU Affero General Public License
** along with this program.  If not, see <https://www.gnu.org/licenses/>.
**
** This file was modified from an example of the Qt Toolkit.
** Original copyright notice and BSD license terms are preserved above.
**
****************************************************************************/

#ifndef VULKANIMAGEVIEWER_H
#define VULKANIMAGEVIEWER_H

#include <QVulkanWindow>
#include <QImage>

class VulkanRenderer : public QVulkanWindowRenderer
{
public:
    VulkanRenderer(QVulkanWindow *w, const QString &fileName);

    void initResources() override;
    void initSwapChainResources() override;
    void releaseSwapChainResources() override;
    void releaseResources() override;

    void startNextFrame() override;

    void setScale(const float scale); // Add this setter

private:
    QString m_fileName;  // Store file name
private:
    VkShaderModule createShader(const QString &name);
    bool createTexture(const QString &name);
    bool createTextureImage(const QSize &size, VkImage *image, VkDeviceMemory *mem,
                            VkImageTiling tiling, VkImageUsageFlags usage, uint32_t memIndex);
    bool writeLinearImage(const QImage &img, VkImage image, VkDeviceMemory memory);
    void ensureTexture();

    QVulkanWindow *m_window;
    QVulkanDeviceFunctions *m_devFuncs;

    VkDeviceMemory m_bufMem = VK_NULL_HANDLE;
    VkBuffer m_buf = VK_NULL_HANDLE;
    VkDescriptorBufferInfo m_uniformBufInfo[QVulkanWindow::MAX_CONCURRENT_FRAME_COUNT];

    VkDescriptorPool m_descPool = VK_NULL_HANDLE;
    VkDescriptorSetLayout m_descSetLayout = VK_NULL_HANDLE;
    VkDescriptorSet m_descSet[QVulkanWindow::MAX_CONCURRENT_FRAME_COUNT];

    VkPipelineCache m_pipelineCache = VK_NULL_HANDLE;
    VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
    VkPipeline m_pipeline = VK_NULL_HANDLE;

    VkSampler m_sampler = VK_NULL_HANDLE;
    VkImage m_texImage = VK_NULL_HANDLE;
    VkDeviceMemory m_texMem = VK_NULL_HANDLE;
    bool m_texLayoutPending = false;
    VkImageView m_texView = VK_NULL_HANDLE;
    VkImage m_texStaging = VK_NULL_HANDLE;
    VkDeviceMemory m_texStagingMem = VK_NULL_HANDLE;
    bool m_texStagingPending = false;
    QSize m_texSize;
    VkFormat m_texFormat;

    QMatrix4x4 m_proj;
    float m_rotation = 0.0f;
    float m_scale = 1.0f;
};

class VulkanWindow : public QVulkanWindow
{
public:
    VulkanWindow(const QString &fileName);  // Constructor to accept fileName
    QVulkanWindowRenderer *createRenderer() override;

protected:
    // Input event handlers for zoom functionality
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QString m_fileName;  // Store file name in the VulkanWindow class
    VulkanRenderer *m_renderer = nullptr; // Pointer to the renderer instance

    // Zoom variables
    bool m_ctrlPressed = false;   // Track if Ctrl is pressed
    float m_zoomFactor = 1.0f;    // Current zoom factor
    const float m_zoomStep = 0.1f; // Zoom increment step

    void updateProjectionMatrix(); // Update the projection matrix based on zoom
};

#endif // VULKANIMAGEVIEWER_H
