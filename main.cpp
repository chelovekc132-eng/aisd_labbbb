import std;
import Polyline;

int main() {
    using ComplexFloat = std::complex<float>;
    using ComplexDouble = std::complex<double>;

    std::cout << "=== Polyline demonstration ===" << std::endl << std::endl;

    std::cout << "1. Default constructor:" << std::endl;
    Polyline<int> empty;
    std::cout << "empty = " << empty << std::endl;
    std::cout << "size = " << empty.size() << std::endl << std::endl;

    std::cout << "2. Constructor from a point:" << std::endl;
    Point<int> origin{ 0, 0 };
    Polyline<int> single(origin);
    std::cout << "single = " << single << std::endl << std::endl;

    std::cout << "3. Constructor from a count:" << std::endl;
    Polyline<int> zeros(3);
    std::cout << "zeros = " << zeros << std::endl << std::endl;

    std::cout << "4. Random constructor (int):" << std::endl;
    Polyline<int> A(4, -10, 10);
    std::cout << "A = " << A << std::endl;
    std::cout << "size = " << A.size() << std::endl << std::endl;

    std::cout << "5. Random constructor (float):" << std::endl;
    Polyline<float> F(3, -5.0f, 5.0f);
    std::cout << "F = " << F << std::endl << std::endl;

    std::cout << "6. Random constructor (double):" << std::endl;
    Polyline<double> D(3, -5.0, 5.0);
    std::cout << "D = " << D << std::endl << std::endl;

    std::cout << "7. Random constructor (std::complex<float>):" << std::endl;
    Polyline<ComplexFloat> CF(3, ComplexFloat(-5.0f, -5.0f), ComplexFloat(5.0f, 5.0f));
    std::cout << "CF = " << CF << std::endl << std::endl;

    std::cout << "8. Random constructor (std::complex<double>):" << std::endl;
    Polyline<ComplexDouble> CD(3, ComplexDouble(-5.0, -5.0), ComplexDouble(5.0, 5.0));
    std::cout << "CD = " << CD << std::endl << std::endl;

    std::cout << "9. Operator []:" << std::endl;
    std::cout << "A[0] = " << A[0] << std::endl;
    A[0] = Point<int>{ 100, 100 };
    std::cout << "After A[0] = (100, 100): A = " << A << std::endl << std::endl;

    std::cout << "10. Concatenation of polylines:" << std::endl;
    Polyline<int> B(2, -10, 10);
    std::cout << "A = " << A << std::endl;
    std::cout << "B = " << B << std::endl;
    std::cout << "A + B = " << (A + B) << std::endl << std::endl;

    std::cout << "11. Adding a vertex to the end:" << std::endl;
    Point<int> vertex{ 7, 7 };
    std::cout << "A + (7, 7) = " << (A + vertex) << std::endl << std::endl;

    std::cout << "12. Adding a vertex to the beginning:" << std::endl;
    std::cout << "(7, 7) + A = " << (vertex + A) << std::endl << std::endl;

    std::cout << "13. Length:" << std::endl;
    std::cout << "length(A) = " << A.length() << std::endl;
    std::cout << "length(F) = " << F.length() << std::endl;
    std::cout << "length(D) = " << D.length() << std::endl;
    std::cout << "length(CF) = " << CF.length() << std::endl;
    std::cout << "length(CD) = " << CD.length() << std::endl << std::endl;

    std::cout << "14. Comparison:" << std::endl;
    Polyline<int> A_copy = A;
    std::cout << "A == A_copy? " << (A == A_copy ? "Yes" : "No") << std::endl;
    std::cout << "A == B? " << (A == B ? "Yes" : "No") << std::endl;
    std::cout << "A != B? " << (A != B ? "Yes" : "No") << std::endl << std::endl;

    std::cout << "15. Exception check:" << std::endl;
    try {
        std::cout << "Trying A[100]..." << std::endl;
        std::cout << A[100] << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    try {
        std::cout << "Trying Polyline<int>(-1)..." << std::endl;
        Polyline<int> bad(-1);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    try {
        std::cout << "Trying Polyline<int>(3, 10, -10)..." << std::endl;
        Polyline<int> bad(3, 10, -10);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "16. Task #1: isosceles triangle (outside class)" << std::endl;
    double x = 0.0;
    double y = 0.0;
    double angle = 0.0;
    double side = 0.0;
    std::cout << "Enter x y of the apex, apex angle in degrees, side length: ";
    std::cin >> x >> y >> angle >> side;
    try {
        Polyline<double> triangle = makeIsoscelesTriangle(Point<double>{ x, y }, angle, side);
        std::cout << "triangle = " << triangle << std::endl;
        std::cout << "perimeter = " << triangle.length() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
