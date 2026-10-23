#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <vector>

class Array {
private:
    int* data;
    int shape[3];
    int totalSize;
    bool owner;

public:
    Array() : data(nullptr), totalSize(0), owner(false) {
        shape[0] = shape[1] = shape[2] = 0;
    }

    Array(int dim1, int dim2) : data(nullptr), totalSize(0), owner(true) {
        if (dim1 <= 0 || dim2 <= 0) throw std::invalid_argument("Array dimensions must be positive!");
        shape[0] = dim1;
        shape[1] = dim2;
        shape[2] = 1;
        totalSize = dim1 * dim2;
        data = new int[totalSize];
        std::memset(data, 0, totalSize * sizeof(int));
    }

    Array(int dim1, int dim2, int dim3) : data(nullptr), totalSize(0), owner(true) {
        if (dim1 <= 0 || dim2 <= 0 || dim3 <= 0)
            throw std::invalid_argument("Array dimensions must be positive!");
        shape[0] = dim1;
        shape[1] = dim2;
        shape[2] = dim3;
        totalSize = dim1 * dim2 * dim3;
        data = new int[totalSize];
        std::memset(data, 0, totalSize * sizeof(int));
    }

    Array(const std::vector<int>& vec) : data(nullptr), totalSize(0), owner(true) {
        if (vec.empty()) throw std::invalid_argument("Vector cannot be empty!");
        shape[0] = vec.size();
        shape[1] = 1;
        shape[2] = 1;
        totalSize = vec.size();
        data = new int[totalSize];
        std::copy(vec.begin(), vec.end(), data);
    }

    Array(const Array& other) : data(nullptr), totalSize(0), owner(true) {
        shape[0] = other.shape[0];
        shape[1] = other.shape[1];
        shape[2] = other.shape[2];
        totalSize = other.totalSize;

        if (totalSize > 0) {
            data = new int[totalSize];
            std::memcpy(data, other.data, totalSize * sizeof(int));
        }
        else {
            data = nullptr;
        }
    }

    Array(Array&& other) noexcept
        : data(other.data), totalSize(other.totalSize), owner(other.owner) {
        shape[0] = other.shape[0];
        shape[1] = other.shape[1];
        shape[2] = other.shape[2];

        other.data = nullptr;
        other.totalSize = 0;
        other.owner = false;
        other.shape[0] = other.shape[1] = other.shape[2] = 0;
    }

    ~Array() {
        if (owner && data != nullptr) {
            delete[] data;
            data = nullptr;
        }
    }

    Array& operator=(const Array& other) {
        if (this == &other) return *this;

        if (owner && data != nullptr) {
            delete[] data;
            data = nullptr;
        }

        shape[0] = other.shape[0];
        shape[1] = other.shape[1];
        shape[2] = other.shape[2];
        totalSize = other.totalSize;
        owner = true;

        if (totalSize > 0) {
            data = new int[totalSize];
            std::memcpy(data, other.data, totalSize * sizeof(int));
        }
        else {
            data = nullptr;
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            if (owner && data != nullptr) {
                delete[] data;
            }
            data = other.data;
            totalSize = other.totalSize;
            owner = other.owner;
            shape[0] = other.shape[0];
            shape[1] = other.shape[1];
            shape[2] = other.shape[2];

            other.data = nullptr;
            other.totalSize = 0;
            other.owner = false;
            other.shape[0] = other.shape[1] = other.shape[2] = 0;
        }
        return *this;
    }

    inline int& at(int x, int y, int z) {
        if (x < 0 || x >= shape[0]) throw std::out_of_range("x index out of bounds");
        if (y < 0 || y >= shape[1]) throw std::out_of_range("y index out of bounds");
        if (z < 0 || z >= shape[2]) throw std::out_of_range("z index out of bounds");

        int index = z + shape[2] * (y + shape[1] * x);
        return data[index];
    }

    inline const int& at(int x, int y, int z) const {
        if (x < 0 || x >= shape[0]) throw std::out_of_range("x index out of bounds");
        if (y < 0 || y >= shape[1]) throw std::out_of_range("y index out of bounds");
        if (z < 0 || z >= shape[2]) throw std::out_of_range("z index out of bounds");

        int index = z + shape[2] * (y + shape[1] * x);
        return data[index];
    }

    inline int& at2D(int x, int y) {
        return at(x, y, 0);
    }

    inline const int& at2D(int x, int y) const {
        return at(x, y, 0);
    }

    inline int& operator[](int index) {
        if (index < 0 || index >= totalSize) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    inline const int& operator[](int index) const {
        if (index < 0 || index >= totalSize) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    void reshape(int newDim1, int newDim2, int newDim3) {
        long long newTotal = 1LL * newDim1 * newDim2 * newDim3;
        if (newTotal != totalSize) {
            throw std::invalid_argument("Total number of elements must remain the same after reshape!");
        }
        shape[0] = newDim1;
        shape[1] = newDim2;
        shape[2] = newDim3;
    }

    Array operator+(int scalar) const {
        Array result = *this;
        for (int i = 0; i < totalSize; ++i) result.data[i] = data[i] + scalar;
        return result;
    }
    Array operator-(int scalar) const {
        Array result = *this;
        for (int i = 0; i < totalSize; ++i) result.data[i] = data[i] - scalar;
        return result;
    }
    Array operator*(int scalar) const {
        Array result = *this;
        for (int i = 0; i < totalSize; ++i) result.data[i] = data[i] * scalar;
        return result;
    }
    Array operator/(int scalar) const {
        if (scalar == 0) throw std::runtime_error("Division by zero!");
        Array result = *this;
        for (int i = 0; i < totalSize; ++i) result.data[i] = data[i] / scalar;
        return result;
    }

    Array operator+(const Array& other) const {
        if (shape[0] != other.shape[0] || shape[1] != other.shape[1] || shape[2] != other.shape[2])
            throw std::invalid_argument("Arrays must have the same shape!");
        Array result = *this;
        for (int i = 0; i < totalSize; ++i) result.data[i] = data[i] + other.data[i];
        return result;
    }
    Array operator-(const Array& other) const {
        if (shape[0] != other.shape[0] || shape[1] != other.shape[1] || shape[2] != other.shape[2])
            throw std::invalid_argument("Arrays must have the same shape!");
        Array result = *this;
        for (int i = 0; i < totalSize; ++i) result.data[i] = data[i] - other.data[i];
        return result;
    }
    Array operator*(const Array& other) const {
        if (shape[0] != other.shape[0] || shape[1] != other.shape[1] || shape[2] != other.shape[2])
            throw std::invalid_argument("Arrays must have the same shape!");
        Array result = *this;
        for (int i = 0; i < totalSize; ++i) result.data[i] = data[i] * other.data[i];
        return result;
    }
    Array operator/(const Array& other) const {
        if (shape[0] != other.shape[0] || shape[1] != other.shape[1] || shape[2] != other.shape[2])
            throw std::invalid_argument("Arrays must have the same shape!");
        Array result = *this;
        for (int i = 0; i < totalSize; ++i) {
            if (other.data[i] == 0) throw std::runtime_error("Division by zero!");
            result.data[i] = data[i] / other.data[i];
        }
        return result;
    }

    inline int* get_content() { return data; }
    inline const int* get_content() const { return data; }
    inline int get_total_size() const { return totalSize; }
    inline int get_dim(int dim) const {
        if (dim < 0 || dim > 2) throw std::out_of_range("Dimension index must be 0, 1, or 2");
        return shape[dim];
    }

    inline int get_width() const { return shape[0]; }
    inline int get_height() const { return shape[1]; }
    inline int get_depth() const { return shape[2]; }

    Array toGrayScale() const {
        if (get_depth() < 3) {
            throw std::runtime_error("Array must have at least 3 channels for RGB to grayscale conversion");
        }

        Array gray(get_width(), get_height(), 1);
        for (int y = 0; y < get_height(); ++y) {
            for (int x = 0; x < get_width(); ++x) {
                int r = at(x, y, 0);
                int g = at(x, y, 1);
                int b = at(x, y, 2);
                int grayValue = (r * 299 + g * 587 + b * 114 + 500) / 1000;
                gray.at2D(x, y) = grayValue;
            }
        }
        return gray;
    }

    Array getSubArray(int x, int y, int w, int h) const {
        if (x < 0 || y < 0 || x + w > get_width() || y + h > get_height()) {
            throw std::out_of_range("Subarray indices out of bounds");
        }

        Array sub(w, h, get_depth());
        for (int dy = 0; dy < h; ++dy) {
            for (int dx = 0; dx < w; ++dx) {
                for (int c = 0; c < get_depth(); ++c) {
                    sub.at(dx, dy, c) = at(x + dx, y + dy, c);
                }
            }
        }
        return sub;
    }
};
#endif