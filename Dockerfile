FROM ubuntu:24.04

# Install dependencies
RUN apt update && apt install -y \
    libqt6widgets6 \
    libvulkan1 \
    vulkan-tools \
    mesa-vulkan-drivers \
    && rm -rf /var/lib/apt/lists/*

# Copy the built application
COPY vulkanimageviewer /app/vulkanimageviewer
COPY 1024-768.jpg /app/1.png

# Set executable permission
RUN chmod +x /app/vulkanimageviewer

# Run the application
CMD ["/app/vulkanimageviewer"]
