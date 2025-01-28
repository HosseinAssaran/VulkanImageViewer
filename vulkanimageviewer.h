/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
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
    void setLocation(const float locX, const float locY);

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
    float m_locX = 0.0f;
    float m_locY = 0.0f;
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

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QString m_fileName;  // Store file name in the VulkanWindow class
    VulkanRenderer *m_renderer = nullptr; // Pointer to the renderer instance

    // Zoom variables
    bool m_ctrlPressed = false;   // Track if Ctrl is pressed
    float m_zoomFactor = 1.0f;    // Current zoom factor
    const float m_zoomStep = 0.1f; // Zoom increment step

    // For panning
    bool m_isPanning = false;
    QPoint m_lastMousePos;

    //For panning and scrolling
    float m_locX = 0.0f, m_locY = 0.0f;

    void updateProjectionMatrix(); // Update the projection matrix based on zoom
};

#endif // VULKANIMAGEVIEWER_H
