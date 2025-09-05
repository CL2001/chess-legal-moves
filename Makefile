.PHONY: all build clean run

# The name of the final executable (must match CMakeLists.txt)
EXECUTABLE = cmake_init

# The build directory
BUILD_DIR = build

# Default target
all: run

build:
	@mkdir -p $(BUILD_DIR)
	cmake -S . -B $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR)

run: build
	@./$(BUILD_DIR)/$(EXECUTABLE)

clean:
	@rm -rf $(BUILD_DIR)



# Create virtual environment and install dependencies
env:
	@echo "Setting up Poetry environment..."
	poetry install
	poetry env activate



# Run the project
python:
	poetry run python test_python.py