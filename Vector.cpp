#include "Vector.hpp"

#include <exception>
#include <limits>

namespace {
const size_t kDefaultSize{8};
const size_t kGrowFactor{2};
}  // namespace

namespace {
void QuickSort(Vector& vector, size_t left, size_t right) {
    if (left >= right || vector.Empty()) {
        return;
    }

    int pivot{vector[(left + right) / 2]};

    size_t i{left};
    size_t j{right};

    while (i <= j) {
        while (vector[i] < pivot) {
            ++i;
        }

        while (vector[j] > pivot) {
            if (j == 0) {
                break;
            }
            --j;
        }

        if (i <= j) {
            std::swap(vector[i], vector[j]);
            ++i;
            if (j > 0) {
                --j;
            }
        }
    }

    QuickSort(vector, left, j);
    QuickSort(vector, i, right);
}
}  // namespace

Vector::Vector() : size_(0), capacity_(kDefaultSize), vector_(new int[kDefaultSize]) {
}

Vector::Vector(const size_t capacity) : size_(0), capacity_(capacity), vector_(new int[capacity]) {
}

Vector::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_), vector_(nullptr) {
    if (other.vector_ == nullptr) {
        throw std::runtime_error("Invalid member for =constructor");
    }

    vector_ = new int[other.size_];
    std::copy(other.vector_, other.vector_ + other.size_, vector_);
}

Vector::Vector(std::initializer_list<int> list) : size_(list.size()), capacity_(list.size()), vector_(new int[capacity_]) {
    std::copy(list.begin(), list.begin() + list.size(), vector_);
}

Vector::Vector(Vector&& other) noexcept : size_(other.size_), capacity_(other.capacity_), vector_(other.vector_) {
    other.size_ = 0;
    other.capacity_ = 0;
    other.vector_ = nullptr;
}

Vector::~Vector() {
    delete[] vector_;
    vector_ = nullptr;
}

size_t Vector::Size() {
    return size_;
}

bool Vector::Empty() {
    return !size_;
}

void Vector::Clear() {
    if (vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for clearing");
    }

    if (size_ == 0) {
        return;
    }

    delete[] vector_;
    vector_ = new int[capacity_];

    size_ = 0;
}

void Vector::PushBack(const int element) {
    if (vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for pushback");
    }

    if (size_ >= capacity_) {
        ResizeVector(*this);
    }

    vector_[size_++] = element;
}

void Vector::Insert(const size_t position, const int element) {
    if (vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for inserting an element");
    }

    if (position > size_ || position == std::numeric_limits<size_t>::max()) {
        throw std::runtime_error("Invalid element number for insertion");
    }

    int* buff{new int[size_ + 1]};

    std::copy(vector_, vector_ + position, buff);
    buff[position] = element;
    std::copy(vector_ + position, vector_ + size_, buff + position + 1);

    delete[] vector_;
    vector_ = buff;
    ++size_;
}

void Vector::Insert(const size_t position, const Vector& vector, const size_t begin, const size_t end) {
    if (vector.vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for segment insertion");
    }

    if (position > size_) {
        throw std::runtime_error("Invalid position for insertion");
    }

    if (end == std::numeric_limits<size_t>::max() || end >= vector.size_ || begin >= end) {
        throw std::runtime_error("Invalid segment for insertion");
    }

    int* buff{new int[size_ + end - begin + 1]};

    std::copy(vector_, vector_ + position, buff);
    std::copy(vector.vector_ + begin, vector.vector_ + end + 1, buff + position);
    std::copy(vector_ + position, vector_ + size_, buff + position + end - begin + 1);

    delete[] vector_;
    vector_ = buff;
    size_ += end - begin + 1;
    capacity_ = size_;
}

void Vector::DeleteElement(const size_t elementNumber) {
    if (vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for deleting an element");
    }

    if (elementNumber >= size_) {
        throw std::runtime_error("Invalid element number for deletion");
    }

    int* buff{new int[size_ - 1]};

    std::copy(vector_, vector_ + elementNumber, buff);
    std::copy(vector_ + elementNumber + 1, vector_ + size_, buff + elementNumber);

    delete[] vector_;
    vector_ = buff;
    --size_;
}

void Vector::DeleteAll(const int element, const size_t begin, const size_t end) {
    if (vector_ == nullptr) {
        throw std::runtime_error("Invalid vector to delete segment");
    }

    if (end >= size_ || begin >= end) {
        throw std::runtime_error("Invalid segment to delete");
    }

    size_t newSize{};
    for (size_t i = begin; i < end; ++i) {
        if (vector_[i] != element) {
            vector_[newSize] = vector_[i];
            ++newSize;
        }
    }

    size_ = newSize;
}

void Vector::DeleteLeft(const int element) {
    if (vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for deleting an element on the left");
    }

    size_t elementNumber{this->FindLeft(element)};

    if (elementNumber == std::numeric_limits<size_t>::max()) {
        throw std::runtime_error("Element was not found to be deleted(left)");
    }

    this->DeleteElement(elementNumber);
}

void Vector::DeleteRight(const int element) {
    if (vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for deleting an element on the right");
    }

    size_t elementNumber{this->FindRight(element)};

    if (elementNumber == std::numeric_limits<size_t>::max()) {
        throw std::runtime_error("Element was not found to be deleted(right)");
    }

    this->DeleteElement(elementNumber);
}

size_t Vector::FindLeft(const int element) {
    if (vector_ == nullptr) {
        throw std::runtime_error("Invalid vector to search for on the left");
    }

    for (size_t i = 0; i < size_; ++i) {
        if (vector_[i] == element) {
            return i;
        }
    }

    return std::numeric_limits<size_t>::max();
}

size_t Vector::FindRight(const int element) {
    if (vector_ == nullptr) {
        throw std::runtime_error("Invalid vector to search for on the right");
    }

    for (size_t i = size_ - 1; i != std::numeric_limits<size_t>::max(); --i) {
        if (vector_[i] == element) {
            return i;
        }
    }

    return std::numeric_limits<size_t>::max();
}

void Vector::Sort(const size_t begin, const size_t end) {
    if (vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for sorting");
    }

    if (end >= size_ || begin > end) {
        throw std::runtime_error("In Sort method end < size");
    }

    QuickSort(*this, begin, end);
}

Vector Vector::Sorted(const Vector& vector, size_t begin, size_t end) {
    if (vector.vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for sorting");
    }

    if (end >= vector.size_ || begin > end) {
        throw std::runtime_error("In Sort function end < size and begin < end");
    }

    Vector newVector = vector;
    newVector.Sort(begin, end);

    return newVector;
}

std::istream& operator>>(std::istream& is, Vector& vector) {
    if (vector.vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for std::istream");
    }

    std::cout << "Введите длину вектора: ";
    is >> vector.size_;

    delete[] vector.vector_;
    vector.vector_ = new int[vector.size_];

    for (size_t i = 0; i < vector.size_; ++i) {
        is >> vector.vector_[i];
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {
    if (vector.vector_ == nullptr || vector.size_ == 0) {
        return os;
    }

    for (size_t i = 0; i < vector.size_ - 1; ++i) {
        os << vector.vector_[i] << ' ';
    }

    os << vector.vector_[vector.size_ - 1];

    return os;
}

Vector operator+(const Vector& vectorA, const Vector& vectorB) {
    if (vectorA.vector_ == nullptr || vectorB.vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for +");
    }

    Vector newVector(vectorA.size_ + vectorB.size_);

    std::copy(vectorA.vector_, vectorA.vector_ + vectorA.size_, newVector.vector_);
    std::copy(vectorB.vector_, vectorB.vector_ + vectorB.size_, newVector.vector_ + vectorA.size_);

    newVector.size_ = vectorA.size_ + vectorB.size_;

    return newVector;
}

Vector operator+(const Vector& vector, const int number) {
    if (vector.vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for +");
    }

    Vector newVector = vector;
    newVector.PushBack(number);

    return newVector;
}

Vector& Vector::operator=(const Vector& vector) {
    if (vector.vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for =");
    }

    if (this == &vector) {
        return *this;
    }

    if (vector_ != nullptr) {
        delete[] vector_;
    }

    vector_ = new int[vector.capacity_];
    std::copy(vector.vector_, vector.vector_ + vector.size_, vector_);

    size_ = vector.size_;
    capacity_ = vector.capacity_;

    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    if (vector_ != nullptr) {
        delete[] vector_;
    }

    size_ = other.size_;
    capacity_ = other.capacity_;
    vector_ = other.vector_;

    other.size_ = 0;
    other.capacity_ = 0;
    other.vector_ = nullptr;

    return *this;
}

Vector& Vector::operator+=(const Vector& vector) {
    if (vector_ == nullptr || vector.vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for +=");
    }

    if (vector.size_ == 0) {
        return *this;
    }

    *this = *this + vector;

    return *this;
}

const int& Vector::operator[](const size_t elementNumber) const {
    if (vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for operator []");
    }

    if (elementNumber >= size_) {
        throw std::runtime_error("Index out of range");
    }

    return vector_[elementNumber];
}

int& Vector::operator[](const size_t elementNumber) {
    if (vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for operator []");
    }

    if (elementNumber >= size_) {
        throw std::runtime_error("Index out of range");
    }

    return vector_[elementNumber];
}

void Vector::ResizeVector(Vector& vector) {
    if (vector.vector_ == nullptr) {
        throw std::runtime_error("Invalid vector for changing the size");
    }

    vector.capacity_ *= kGrowFactor;

    int* buff{new int[vector.capacity_]};

    std::copy(vector.vector_, vector.vector_ + vector.size_, buff);

    delete[] vector.vector_;
    vector.vector_ = buff;
}
