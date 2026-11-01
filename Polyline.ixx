export module Polyline;

import std;

export template <typename T>
struct Point {
    T x;
    T y;
};

export template <typename T>
std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

export template <typename T>
class Polyline {
private:
    Point<T>* m_data;
    int m_size;

    static bool isClose(const T& first, const T& second);

public:
    static inline const double EPSILON = 1e-9;

    Polyline();
    explicit Polyline(const Point<T>& point);
    explicit Polyline(int count);
    Polyline(int count, T min, T max);
    ~Polyline();

    Polyline(const Polyline& other);
    Polyline& operator=(const Polyline& other);

    int size() const;
    double length() const;

    Point<T>& operator[](int index);
    const Point<T>& operator[](int index) const;

    Polyline operator+(const Polyline& other) const;
    Polyline operator+(const Point<T>& point) const;

    bool operator==(const Polyline& other) const;
    bool operator!=(const Polyline& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Polyline<T>& line) {
        os << "[ ";
        for (int i = 0; i < line.m_size; i++) {
            os << line.m_data[i];
            if (i < line.m_size - 1) os << ", ";
        }
        os << " ]";
        return os;
    }
};


template <typename T>
Polyline<T>::Polyline() : m_data(nullptr), m_size(0) {}

template <typename T>
Polyline<T>::Polyline(const Point<T>& point) : m_data(new Point<T>[1]), m_size(1) {
    m_data[0] = point;
}

template <typename T>
Polyline<T>::Polyline(int count) : m_data(nullptr), m_size(0) {
    if (count < 0) throw std::invalid_argument("Count cannot be negative");
    if (count > 0) {
        m_data = new Point<T>[static_cast<std::size_t>(count)]();
        m_size = count;
    }
}

template <typename T>
Polyline<T>::Polyline(int count, T min, T max) : Polyline(count) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    if constexpr (std::is_integral_v<T>) {
        if (min > max) throw std::invalid_argument("Min cannot be greater than max");
        std::uniform_int_distribution<T> dist(min, max);
        for (int i = 0; i < m_size; i++) {
            m_data[i].x = dist(gen);
            m_data[i].y = dist(gen);
        }
    }
    else if constexpr (std::is_floating_point_v<T>) {
        if (min > max) throw std::invalid_argument("Min cannot be greater than max");
        std::uniform_real_distribution<T> dist(min, max);
        for (int i = 0; i < m_size; i++) {
            m_data[i].x = dist(gen);
            m_data[i].y = dist(gen);
        }
    }
    else if constexpr (std::is_same_v<T, std::complex<float>> || std::is_same_v<T, std::complex<double>>) {
        using Real = typename T::value_type;
        if (min.real() > max.real() || min.imag() > max.imag()) {
            throw std::invalid_argument("Min cannot be greater than max");
        }
        std::uniform_real_distribution<Real> dist_re(min.real(), max.real());
        std::uniform_real_distribution<Real> dist_im(min.imag(), max.imag());
        for (int i = 0; i < m_size; i++) {
            m_data[i].x = T(dist_re(gen), dist_im(gen));
            m_data[i].y = T(dist_re(gen), dist_im(gen));
        }
    }
}

template <typename T>
Polyline<T>::~Polyline() {
    delete[] m_data;
}

template <typename T>
Polyline<T>::Polyline(const Polyline& other) : m_data(nullptr), m_size(0) {
    *this = other;
}

template <typename T>
Polyline<T>& Polyline<T>::operator=(const Polyline& other) {
    if (this == &other) return *this;
    delete[] m_data;
    m_size = other.m_size;
    if (m_size > 0) {
        m_data = new Point<T>[static_cast<std::size_t>(m_size)];
        for (int i = 0; i < m_size; i++) m_data[i] = other.m_data[i];
    }
    else {
        m_data = nullptr;
    }
    return *this;
}

template <typename T>
bool Polyline<T>::isClose(const T& first, const T& second) {
    return std::abs(first - second) < EPSILON;
}

template <typename T>
int Polyline<T>::size() const {
    return m_size;
}

template <typename T>
double Polyline<T>::length() const {
    double total = 0.0;
    for (int i = 1; i < m_size; i++) {
        double dx = std::abs(m_data[i].x - m_data[i - 1].x);
        double dy = std::abs(m_data[i].y - m_data[i - 1].y);
        total += std::sqrt(dx * dx + dy * dy);
    }
    return total;
}

template <typename T>
Point<T>& Polyline<T>::operator[](int index) {
    if (index < 0 || index >= m_size) throw std::out_of_range("Index out of range");
    return m_data[index];
}

template <typename T>
const Point<T>& Polyline<T>::operator[](int index) const {
    if (index < 0 || index >= m_size) throw std::out_of_range("Index out of range");
    return m_data[index];
}

template <typename T>
Polyline<T> Polyline<T>::operator+(const Polyline& other) const {
    Polyline<T> result(m_size + other.m_size);
    for (int i = 0; i < m_size; i++) result.m_data[i] = m_data[i];
    for (int i = 0; i < other.m_size; i++) result.m_data[m_size + i] = other.m_data[i];
    return result;
}

template <typename T>
Polyline<T> Polyline<T>::operator+(const Point<T>& point) const {
    return *this + Polyline<T>(point);
}

template <typename T>
bool Polyline<T>::operator==(const Polyline& other) const {
    if (m_size != other.m_size) return false;
    for (int i = 0; i < m_size; i++) {
        if (!isClose(m_data[i].x, other.m_data[i].x)) return false;
        if (!isClose(m_data[i].y, other.m_data[i].y)) return false;
    }
    return true;
}

template <typename T>
bool Polyline<T>::operator!=(const Polyline& other) const {
    return !(*this == other);
}

export template <typename T>
Polyline<T> operator+(const Point<T>& point, const Polyline<T>& line) {
    return Polyline<T>(point) + line;
}

export Polyline<double> makeIsoscelesTriangle(const Point<double>& apex, double apex_angle, double side) {
    if (side <= 0.0) throw std::invalid_argument("Side must be positive");
    if (apex_angle <= 0.0 || apex_angle >= 180.0) {
        throw std::invalid_argument("Angle must be between 0 and 180 degrees");
    }
    double angle = apex_angle * std::numbers::pi / 180.0;
    Point<double> second{ apex.x + side, apex.y };
    Point<double> third{ apex.x + side * std::cos(angle), apex.y + side * std::sin(angle) };
    return Polyline<double>(apex) + second + third + apex;
}
