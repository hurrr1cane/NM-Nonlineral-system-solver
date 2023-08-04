#include <iostream>
#include <iomanip>

double y(double x) {
	return 1.5 - cos(x);
}

double x(double y) {
	return (1 + sin(y - 0.5)) / 2;
}

double func1(double x, double y) {
	return cos(x) + y - 1.5;
}

double func2(double x, double y) {
	return 2 * x - sin(y - 0.5) - 1;
}

double chast1x(double x) {
	return -sin(x);
}

double chast1y(double y) {
	return 1;
}

double chast2x(double x) {
	return 2;
}

double chast2y(double y) {
	return -cos(y - 0.5);
}

double getDelta(double first, double second) {
	//return sqrt(first * first + second * second);
	return abs(first) + abs(second);
}

double determinant(double matr[2][2]) {
	return matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0];
}


int main() {
	double eps = 0.001;
	double delta = 1;
	int countOfIterations = 0;

	double x1 = 0.6, x2, y1 = 0.7, y2;
	//x1 = 1; y1 = 1;
	std::cout << "System of equations:\ncos(x)+y=1,5\n2x-sin(y-0.5)=1\n\n";

	//if (std::max(abs(chast1x(x1)) + abs(chast1y(y1)), abs(chast2x(x1)) + abs(chast2y(y1))) < 1) std::cout << "The method is convergent\n\n";
	if (abs(chast1x(x1)) + abs(chast1y(y1)) < 1 && abs(chast2x(x1)) + abs(chast2y(y1)) < 1) std::cout << "The method is convergent\n\n";
	std::cout << std::setw(7) << std::setprecision(5) << "Iterational method:\nx\ty\tdelta\n" << x1 << "\t" << y1 << '\n';

	while (delta > eps) {
		x2 = x(y1);
		y2 = y(x1);
		delta = getDelta(x2 - x1, y2 - y1);
		std::cout << x2 << "\t" << y2 << "\t" << delta << '\n';
		countOfIterations++;
		y1 = y2;
		x1 = x2;
	}
	std::cout << "Count of iterations: " << countOfIterations << '\n';


	
	std::cout << "\n\nNewtone method:\n";
	x1 = 0.6; y1 = 0.7;
	//x1 = 1; y1 = 1;
	double det, detx, dety;
	std::cout << "\n" << abs(chast1x(x1)) + abs(chast1y(y1)) << " " << abs(chast2x(x1)) + abs(chast2y(y1)) << "\n";
	std::cout << "\n" << abs(chast1x(x1)) + abs(chast2x(x1)) << " " << abs(chast1y(y1)) + abs(chast2y(y1)) << "\n";
	

	double yakobi[2][2];
	std::cout << "delta X\t\tdelta Y\t\tx\ty\tdelta\n\t\t\t\t" << x1 << "\t" << y1 << '\n';
	delta = 1;
	countOfIterations = 0;
	while (delta > eps) {
		yakobi[0][0] = chast1x(x1);
		yakobi[0][1] = chast1y(y1);
		yakobi[1][0] = chast2x(x1);
		yakobi[1][1] = chast2y(y1);
		det = determinant(yakobi);

		yakobi[0][0] = func1(x1, y1);
		yakobi[1][0] = func2(x1, y1);
		detx = -determinant(yakobi) / det;

		yakobi[0][0] = chast1x(x1);
		yakobi[1][0] = chast1y(y1);
		yakobi[0][1] = func1(x1, y1);
		yakobi[1][1] = func2(x1, y1);
		dety = -determinant(yakobi) / det;

		x1 += detx;
		y1 += dety;
		delta = getDelta(detx, dety);
		std::cout << detx << "\t" << dety << "\t" << x1 << '\t' << y1 << '\t' << delta << '\n';
		countOfIterations++;
	}
	std::cout << "Count of iterations: " << countOfIterations << '\n';

}