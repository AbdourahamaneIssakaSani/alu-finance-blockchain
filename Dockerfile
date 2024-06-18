# Use an official Ubuntu 20.04 as a parent image
FROM ubuntu:20.04

# Set environment variables to non-interactive for the installation
ENV DEBIAN_FRONTEND=noninteractive

# Update and install necessary packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    wget \
    man-db \
    && rm -rf /var/lib/apt/lists/*

# Copy the OpenSSL source to the container and install it
COPY openssl-1.1.1w /usr/local/src/openssl-1.1.1w

# Install OpenSSL
RUN cd /usr/local/src/openssl-1.1.1w && \
    ./config && \
    make && \
    make test && \
    make install

# Copy the llist installation script and library files to the container
COPY llist/install.bash /usr/local/src/llist_install.sh
COPY llist/ /usr/local/src/llist/

# Make the llist installation script executable and run it
RUN chmod +x /usr/local/src/llist_install.sh && /usr/local/src/llist_install.sh

# Copy the CMakeLists.txt and source files to the container
COPY CMakeLists.txt /usr/local/src/myapp/
COPY blockchain/ /usr/local/src/myapp/blockchain/
COPY cli/ /usr/local/src/myapp/cli/
COPY crypto/ /usr/local/src/myapp/crypto/
COPY utils/ /usr/local/src/myapp/utils/

# Set the working directory
WORKDIR /usr/local/src/myapp

# Build the application
RUN cmake . && make

# Command to run your application
CMD ["./BlockChainSummative"]
