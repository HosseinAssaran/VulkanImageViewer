# Qt6 Vulkan Image Viewer

## Overview
This project is an image viewer built using Qt6, C++, and Vulkan. It supports BMP, PNG, and JPG images and provides essential viewing features such as pan, zoom, and scrolling. The application utilizes Vulkan for rendering and implements custom shaders for efficient image processing.

## Features
- **Supported Image Formats**: BMP, PNG, JPG.
- **Pan & Scrolling**:
  - Panning occurs while holding the left mouse button and dragging.
  - Scrolling is handled using the mouse's horizontal and vertical scrolls.
- **Zooming**:
  - Supports zoom levels from **10% to 1600%**.
  - **Linear Resampling** for zoom levels below 100%.
  - **Pixelation** for zoom levels above 100%, displaying each pixel as an **n×n** block up to 1600%.
  - **Integral Zoom Levels** above 100% (**200%, 300%, ..., 1600%**).
  - **Zoom to Pixel**: Ensures that the mouse pointer remains focused on the exact pixel it was pointing to before zooming.
  - **Zooming is activated by holding the Control button and using the mouse scroll**.
- **Vulkan Integration**:
  - Custom Vulkan swapchain.
  - Vertex and fragment shaders for optimized rendering.
- **File Open Dialog**: Allows users to select and load images.

## Dependencies
Ensure the following dependencies are installed before building:
- **Qt6** (with Vulkan support)
- **Vulkan SDK**
- **CMake**
- **C++14 or later**

## Build Instructions
1. **Install Dependencies**:
   - Download and install the [Vulkan SDK](https://vulkan.lunarg.com/sdk/home).
   - Install Qt6 with Vulkan support.
2. **Clone the Repository**:
   ```sh
   git clone https://github.com/HosseinAssaran/VulkanImageViewer.git
   cd VulkanImageViewer
   ```
3. **Set Up Environment Variables**:
   ```sh
   export CMAKE_PREFIX_PATH=~/Qt/6.8.1/gcc_64/lib/cmake/Qt6/
   ```
4. **Configure the Project**:
   ```sh
   mkdir build && cd build
   cmake ..
   ```
5. **Build the Project**:
   ```sh
   cmake --build .
   ```
6. **Run the Application**:
   ```sh
   ./vulkanimageviewer
   ```

## Usage
- **Open Image**: Use the file dialog to load an image.
- **Zooming**:
  - Hold `Ctrl` and use the mouse scroll to zoom in/out.
  - The zooming maintains focus on the exact pixel under the pointer.
- **Panning**:
  - Click and drag with the left mouse button.
  - Use arrow keys for navigation.
- **Scrolling**:
  - Use the mouse's vertical and horizontal scroll.

## Technical Details
- **Rendering Pipeline**:
  - Uses Vulkan swapchain for efficient image rendering.
  - Implements **vertex and fragment shaders**.
  - Supports different resampling methods (**linear resampling** for zoom < 100%, **pixelation** for zoom ≥ 100%).
- **Memory Management**:
  - Uses Vulkan buffers for optimized image loading and rendering.

## Platform Support
- The project has been built and tested on **Ubuntu** and can be compiled on any Linux-based system.

## License
This project is licensed under the GNU Affero General Public License v3.0 (AGPL-3.0). 

## Contribution
Feel free to fork and submit pull requests to improve the project.

---
For more details, visit the [GitHub Repository](https://github.com/HosseinAssaran/VulkanImageViewer).
