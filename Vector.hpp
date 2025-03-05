#pragma once

#include <cstddef>
#include <initializer_list>
#include <iostream>

class Vector {
 private:
    size_t size_;
    size_t capacity_;
    int* vector_;

 public:
    Vector();
    explicit Vector(const size_t capacity);
    Vector(const Vector& other);
    Vector(std::initializer_list<int> list);
    Vector(Vector&& other) noexcept;

    ~Vector();

    size_t Size();

    bool Empty();
    void Clear();

    void PushBack(const int element);
    void Insert(const size_t position, const int element);
    void Insert(const size_t position, const Vector& vector, const size_t begin, const size_t end);

    void DeleteElement(const size_t elementNumber);
    void DeleteAll(const int element, const size_t begin, const size_t end);

    void DeleteLeft(const int element);
    void DeleteRight(const int element);

    size_t FindLeft(const int element);
    size_t FindRight(const int element);

    void Sort(const size_t begin, const size_t end);
    static Vector Sorted(const Vector& vector, const size_t begin, const size_t end);

    friend std::istream& operator>>(std::istream& is, Vector& vector);
    friend std::ostream& operator<<(std::ostream& os, const Vector& vector);

    friend Vector operator+(const Vector& vectorA, const Vector& vectorB);
    friend Vector operator+(const Vector& vector, const int number);

    Vector& operator=(const Vector& vector);
    Vector& operator=(Vector&& other) noexcept;

    Vector& operator+=(const Vector& vector);

    const int& operator[](const size_t elementNumber) const;
    int& operator[](const size_t elementNumber);

 private:
    void ResizeVector(Vector& vector);
};
