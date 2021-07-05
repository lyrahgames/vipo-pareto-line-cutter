#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>
//
#include <lyrahgames/gnuplot/gnuplot.hpp>
#include <lyrahgames/pareto/pareto.hpp>

using namespace std;
using namespace lyrahgames;

using real = double;
struct point {
  real x, y;
};

int main(int argc, char *argv[]) {
  if ((argc < 5) || (argc > 6)) {
    cerr << "Error: Wrong number of command-line arguments!\n";
    cout << "Usage:\n"
         << argv[0]
         << " <input data file> <column objective 0> <column objective 1> "
            "<output file> [--plot]\n";
    return -1;
  }

  fstream input{argv[1], ios::in};
  if (!input) {
    cerr << "Error: Failed to open '" << argv[1] << "' for reading.\n";
    return -1;
  }

  size_t first, second;
  stringstream stream{argv[2]};
  stream >> first;
  stream = stringstream{argv[3]};
  stream >> second;

  fstream output{argv[4], ios::out};
  if (!output) {
    cerr << "Error: Failed to open '" << argv[2] << "' for writing.\n";
    return -1;
  }

  bool plot_enabled = false;
  if (argc == 6) {
    if (string(argv[5]) == "--plot")
      plot_enabled = true;
    else {
      cerr << "Error: Failed to parse last command-line argument.\n";
      return -1;
    }
  }

  vector<point> pareto_front{};

  string line;
  while (getline(input, line)) {
    if (line[0] == '#')
      continue;
    stringstream stream{line};
    point p;
    float tmp;
    size_t i = 0;
    for (; i < first; ++i)
      stream >> tmp;
    stream >> p.x;
    ++i;
    for (; i < second; ++i)
      stream >> tmp;
    stream >> p.y;
    pareto_front.push_back(p);
  }

  // cout << setw(30) << "size = " << pareto_front.size() << '\n';

  pareto::frontier<real> frontier{pareto_front.size(), 0, 2};
  for (size_t i = 0; i < frontier.sample_count(); ++i) {
    auto it = frontier.objectives_iterator(i);
    *it++ = pareto_front[i].x;
    *it = pareto_front[i].y;
  }

  const auto line_cut = pareto::line_cut(frontier);

  output << '#' << setw(19) << "ID" << setw(20) << "Objective X" << setw(20)
         << "Objective Y" << '\n';
  for (const auto &[first, last] : line_cut.lines()) {
    for (size_t i = first; i < last; ++i) {
      output << setw(20) << line_cut.permutation(i) << ' ';
      for (auto y : frontier.objectives(line_cut.permutation(i)))
        output << setw(20) << y << ' ';
      output << '\n';
    }
    output << '\n';
  }
  output << flush;

  if (plot_enabled) {
    gnuplot::pipe plot{};
    plot
        << "plot '" << argv[4]
        << "' u 2:3 w p pt 2 ps 0.5 lt rgb '#222222' title 'Point Estimation', "
           "'' u 2:3 w l lw 2 lt rgb '#ff3333' title 'Frontier Estimation'\n";
  }
}
