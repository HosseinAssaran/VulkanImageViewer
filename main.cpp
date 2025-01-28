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

#include <QGuiApplication>
#include <QApplication>
#include <QVulkanInstance>
#include <QLoggingCategory>
#include <QFileDialog>
#include "hellovulkantexture.h"

Q_LOGGING_CATEGORY(lcVk, "qt.vulkan")

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString fileName = QFileDialog::getOpenFileName(
        nullptr,
        "Open File",
        "",
        "Images (*.png *.jpg *.bmp);;All Files (*)"
        );

    if (!fileName.isEmpty()) {
        qDebug() << "Selected file:" << fileName;
    } else {
        qDebug() << "No file selected.";
    }

    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));

    QVulkanInstance inst;
    inst.setLayers({ "VK_LAYER_KHRONOS_validation" });

    if (!inst.create())
        qFatal("Failed to create Vulkan instance: %d", inst.errorCode());

    VulkanWindow w(fileName);
    w.setVulkanInstance(&inst);
    if (QCoreApplication::arguments().contains(QStringLiteral("--srgb")))
        w.setPreferredColorFormats(QList<VkFormat>() << VK_FORMAT_B8G8R8A8_SRGB);

    w.resize(1024, 768);
    w.show();

    return app.exec();
}
