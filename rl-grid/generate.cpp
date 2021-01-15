#include "global.hpp"

bool valid(int x, int y)
{
	if (x >= 0 && y >= 0 && x < SIZE && y < SIZE)
		return true;

	return false;
}

bool rdfs(int x, int y, spi &p, spi &visited)
{
	visited.insert(make_pair(x, y));
	if (x == rx && y == ry) {
		p.insert(make_pair(x, y));

		return true;
	}

	set <int> is;

	do {
		int i = rand() % 4;

		is.insert(i);

		int nx = x + dx[i];
		int ny = y + dy[i];

		spi tp;

		auto pr = make_pair(nx, ny);
		if (valid(nx, ny) && visited.find(pr) == visited.end()
				&& rdfs(nx, ny, tp, visited)) {
			p = tp;
			p.insert(make_pair(x, y));

			return true;
		}
	} while (is.size() != 4);

	return false;
}

// Valid vertices
bool dfs(int x, int y, pi exc, spi &visited)
{
	if (x == rx && y == ry)
		return true;

	bool stat = false;
	for (size_t i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		auto pr = make_pair(nx, ny);

		if (path.find(pr) != path.end()
				&& visited.find(pr) == visited.end()
				&& pr != exc) {
			visited.insert(pr);

			stat |= dfs(nx, ny, exc, visited);
		}
	}

	return stat;
}

void generate()
{
	srand(clock());

	grid = new char *[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		grid[i] = new char[SIZE];

		memset(grid[i], 0, SIZE * sizeof(char));
	}

	ix = rand() % SIZE;
	iy = rand() % SIZE;
	
	do {
		rx = rand() % SIZE;
		ry = rand() % SIZE;
	} while (rx == ix && ry == iy);

	spi vis;
	rdfs(ix, iy, path, vis);

	for (auto pr : path)
		grid[pr.first][pr.second] = 1;

	spi cpy = path;

	set <int> is;
	
	while (is.size() != cpy.size()) {
		int r = 0;
		
		do {
			r = rand() % cpy.size();
		} while (is.find(r) != is.end());

		is.insert(r);
		
		auto it = cpy.begin();

		advance(it, r);
	
		vis.clear();
		if (dfs(ix, iy, *it, vis)) {
			path.erase(*it);

			grid[it->first][it->second] = 0;
		}
	}
	
	grid[ix][iy] = 1;
	grid[rx][ry] = 1;
}

void print()
{
	for (size_t i = 0; i < SIZE; i++) {
		for (size_t j = 0; j < SIZE; j++) {
			if (i == ix && j == iy)
				cout << "x";
			else if (i == rx && j == ry)
				cout << "o";
			else if (grid[i][j] == 0)
				cout << "#";
			else if (grid[i][j] == 1)
				cout << " ";
		}

		cout << "\n";
	}
}
