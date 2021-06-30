#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

using real = float;
struct point {
  real x, y;
  size_t id;
};

int main(int argc, char* argv[]) {
  if (3 != argc) {
    cerr << "Error: Wrong number of command-line arguments!\n";
    cout << "Usage:\n" << argv[0] << " <input data file> <output file>\n";
    return -1;
  }

  fstream input{argv[1], ios::in};
  if (!input) {
    cerr << "Error: Failed to open '" << argv[1] << "' for reading.\n";
    return -1;
  }

  fstream output{argv[2], ios::out};
  if (!output) {
    cerr << "Error: Failed to open '" << argv[2] << "' for writing.\n";
    return -1;
  }

  vector<point> pareto_front{};

  string line;
  while (getline(input, line)) {
    if (line[0] == '#')
      continue;
    stringstream stream{line};
    point p;
    stream >> p.x >> p.y;
    p.id = pareto_front.size();
    pareto_front.push_back(p);
  }

  cout << setw(30) << "size = " << pareto_front.size() << '\n';

  // Sort Pareto frontier in x direction.
  ranges::sort(pareto_front,
               [](const auto& p, const auto& q) { return p.x < q.x; });

  // Compute mean value.
  real mean_distance = 0;
  for (size_t i = 0; i < pareto_front.size() - 1; ++i) {
    const auto [x1, y1, id1] = pareto_front[i];
    const auto [x2, y2, id2] = pareto_front[i + 1];
    mean_distance += sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
  }
  mean_distance /= pareto_front.size() - 1;

  cout << setw(30) << "mean distance = " << mean_distance << '\n';

  // Compute the variance and standard deviation.
  real var_distance = 0;
  for (size_t i = 0; i < pareto_front.size() - 1; ++i) {
    const auto [x1, y1, id1] = pareto_front[i];
    const auto [x2, y2, id2] = pareto_front[i + 1];
    const auto distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    var_distance += (distance - mean_distance) * (distance - mean_distance);
  }
  var_distance /= pareto_front.size() - 2;
  auto stddev_distance = sqrt(var_distance);

  cout << setw(30) << "distance variance = " << var_distance << '\n'
       << setw(30) << "distance stddev = " << stddev_distance << '\n';

  output << '#' << setw(19) << "ID" << setw(20) << "Objective X" << setw(20)
         << "Objective Y" << '\n';
  for (size_t i = 0; i < pareto_front.size() - 1; ++i) {
    const auto [x1, y1, id] = pareto_front[i];
    const auto [x2, y2, _] = pareto_front[i + 1];
    const auto distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    output << setw(20) << id << setw(20) << x1 << setw(20) << y1 << '\n';
    if (distance > mean_distance + 2 * stddev_distance) {
      cout << "Cut connection (" << i << ", " << i + 1 << ").\n";
      output << '\n';
    }
  }
  output << setw(20) << pareto_front.back().id << setw(20)
         << pareto_front.back().x << setw(20) << pareto_front.back().y << '\n'
         << flush;
}
