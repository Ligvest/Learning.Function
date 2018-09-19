#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct Image {
	double quality;
	double freshness;
	double rating;
};

struct Params {
	double a;
	double b;
	double c;
};

struct Part {
	char sign;
	double value;
};

class Function {
public:
	void AddPart(char sign, double value) {
		parts.push_back({ sign, value });
	}

	double Apply(double dResult) {
		for (auto part : parts) {
			if (part.sign == '+') {
				dResult += part.value;
			}
			else if (part.sign == '-') {
				dResult -= part.value;
			}
			else if (part.sign == '*') {
				dResult *= part.value;
			}
			else if (part.sign == '/') {
				dResult /= part.value;
			}
		}
		return dResult;
	}

	void Invert() {
		for (auto &part : parts) {
			if (part.sign == '+') {
				part.sign = '-';
			}
			else if (part.sign == '-') {
				part.sign = '+';
			}
			else if (part.sign == '*') {
				part.sign = '/';
			}
			else if (part.sign == '/') {
				part.sign = '*';
			}
		}
		std::reverse(std::begin(parts), std::end(parts));
	}



	vector<Part> parts;
};



Function MakeWeightFunction(const Params& params,
	const Image& image) {
	Function function;
	function.AddPart('*', params.a);
	function.AddPart('-', image.freshness * params.b);
	function.AddPart('+', image.rating * params.c);
	return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
	Function function = MakeWeightFunction(params, image);
	return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
	const Image& image,
	double weight) {
	Function function = MakeWeightFunction(params, image);
	function.Invert();
	return function.Apply(weight);
}

int main() {
	double qual = 10;
	Image image = { qual, 2, 6 };
	Params params = { 4, 2, 6 };
	double weight = ComputeImageWeight(params, image);
	cout << "Quality = " << qual << std::endl;
	cout << "Weight = " << weight << endl; //36
	cout << "Compute quality by weight = " << ComputeQualityByWeight(params, image, weight) << endl; //20
	system("pause");
	return 0;
}