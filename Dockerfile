# Multi-stage Dockerfile for embedded C development

# Build stage
FROM gcc:latest as builder

WORKDIR /app

# Copy source files
COPY main.c main.h ./

# Install additional build tools
RUN apt-get update && apt-get install -y \
    gcc-arm-linux-gnueabihf \
    gcc-arm-none-eabi \
    make \
    cmake \
    && rm -rf /var/lib/apt/lists/*

# Compile for different targets
RUN gcc -o main_x86 main.c -Wall -Wextra -std=c99 && \
    arm-linux-gnueabihf-gcc -o main_arm main.c -static || true

# Runtime stage
FROM ubuntu:22.04

WORKDIR /embedded_app

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    qemu-user-static \
    && rm -rf /var/lib/apt/lists/*

# Copy compiled binaries from builder stage
COPY --from=builder /app/main_x86 ./main_x86

# Create a non-root user for security
RUN useradd -m -u 1000 embedded && \
    chown -R embedded:embedded /embedded_app

USER embedded

# Default command
CMD ["./main_x86"]

# Metadata
LABEL maintainer="Selbakai"
LABEL description="CI/CD Embedded C Project Container"
LABEL version="1.0.0"
