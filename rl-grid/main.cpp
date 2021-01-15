#include "global.hpp"

// Global variables
char **grid;

int ix = 0;
int iy = 0;

int rx = 0;
int ry = 0;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

spi path;

int act(int i)
{
	int nx = ix + dx[i];
	int ny = iy + dy[i];

	if (valid(nx, ny)) {
		ix = nx;
		iy = ny;
	} else {
		return -1;
	}

	if (grid[ix][iy] == 0)
		return -1;
	else if (rx == nx && ry == ny)
		return 1;

	return 0;
}

int main()
{
	generate();

	ml::NeuralNetwork <double> model (2, {
			ml::Layer <double> (4, new ml::ReLU <double> ()),
			ml::Layer <double> (4, new ml::Sigmoid <double> ()),
			ml::Layer <double> (4, new ml::Linear <double> ())
	});

	model.set_optimizer(new ml::Adam <double> (0.001));
	model.set_cost(new ml::MeanSquaredError <double> ());

	int oix = ix;
	int oiy = iy;

	Vector <double> Q_target;

	double epsilon = EPS;

	// Main loop
	
	size_t iter = 0;
	while (true) {
		printf("\x1b[d");

		Vector <double> In = {(double) ix, (double) iy};

		Vector <double> Q_values = model(In);

		cout << "model-out = " << model(In) << endl;
		cout << "epsilon = " << epsilon << endl;
		cout << "step #" << iter << endl;

		double r = rand()/((double) RAND_MAX);

		int imax;

		if (r > epsilon)
			imax = Q_values.imax();
		else
			imax = rand() % CHOICES;

		int ret = act(imax);
		
		Q_target = Q_values;
		if (ret == -1) {
			Q_target[imax] = P;

			model.fit(In, Q_target);

			ix = oix;
			iy = oiy;
		} else if (ret == 1) {
			Q_target = Q_values;

			Q_target[imax] = R;

			model.fit(In, Q_target);

			return 0;
		} else {
			Q_target = Q_values;

			Q_target[imax] = model({ix, iy})[imax];

			model.fit(In, Q_target);
		}

		print();
		
		printf("\x1b[2J");

		this_thread::sleep_for(10ms);

		if (++iter % 100 == 0)
			epsilon = max(epsilon - 0.0001, 0.001);
	}
}
