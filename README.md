### README.md

```markdown
# ALU Finance System - aka BlockChainSummative

This project is a blockchain application written in C. To compile and run the project, you will need to install the following dependencies:

- OpenSSL version 1.1.1w
- Perl 5
- Custom `llist` library

## Prerequisites

### 1. Install Perl 5

You need to have Perl 5 installed on your system before installing OpenSSL. Follow the instructions in the `perl-5.40.0/INSTALL` file to install Perl 5.

```sh
# Navigate to the Perl source directory
cd perl-5.40.0

# Follow the installation instructions in the INSTALL file
less INSTALL
```

### 2. Install OpenSSL

After installing Perl 5, you can install OpenSSL version 1.1.1w. Follow the instructions in the `openssl-1.1.1w/INSTALL` file.

```sh
# Navigate to the OpenSSL source directory
cd openssl-1.1.1w

# Follow the installation instructions in the INSTALL file
less INSTALL
```

### 3. Install Custom `llist` Library

The project uses a custom `llist` library. Use the provided `install.bash` script to install it.

```sh
# Navigate to the llist directory
cd llist

# Run the installation script
sudo ./install.bash
```

## Building the Project

Once you have installed the dependencies, you can compile the project using CMake.

```sh
# Navigate to the project root directory
cd /path/to/BlockChainSummative

# Create a build directory
mkdir build
cd build

# Run CMake to configure the project
cmake ..

# Compile the project
make
```

## Running the Project

After successfully building the project, you can run the executable.

```sh
# Run the compiled executable
./BlockChainSummative
```

Type `help` to see the list of available commands in the command-line interface.

## Project Structure

- `blockchain/` - Contains the blockchain-related source files.
- `cli/` - Contains the command-line interface source files.
- `crypto/` - Contains the cryptographic functions source files.
- `llist/` - Contains the custom linked list library and installation script.
- `utils/` - Contains utility functions and headers.
- `openssl-1.1.1w/` - Contains the OpenSSL source files.
- `perl-5.40.0/` - Contains the Perl source files.
- `CMakeLists.txt` - CMake configuration file.
- `cli/main.c` - The main entry point for the application.

## Additional Notes

- Ensure that all dependencies are correctly installed before attempting to build the project.
- If you encounter any issues, refer to the respective `INSTALL` files in the `openssl-1.1.1w` and `perl-5.40.0` directories for troubleshooting.

## License

This project is licensed under the MIT License .
```

This README provides users with clear instructions on installing the necessary dependencies, building, and running your project. It also includes additional notes and a project structure overview to help users navigate the project.