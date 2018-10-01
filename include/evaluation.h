#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "strings.h"

using namespace std::string_literals;
// using namespace HKL;
// using namespace ComTol;
// using namespace ComTol::StrTol;

using std::cout;
using std::endl;
using std::pair;

using std::tuple;
using std::vector;

using std::size_t;
using std::string;
using std::to_string;
using std::ostream;
using sstream = std::stringstream;

//using pair_int = pair<int, int>;
using pair_str = pair<string, string>;

namespace AGizmo {

using StringFormat::str_frame;

namespace Evaluation {

class Stats {
private:
  int total{0}, failed{0};

public:

  Stats() = default;

  Stats &operator++() {
    ++total;
    return *this;
  }

  void update(int t, int f){
    total += t;
    failed += f;
  }

  void update(const Stats &input) {
    this->update(input.total, input.failed);
  }

  void operator()(int t, int f) {
    this->update(t, f);
  }

  void operator()(const Stats &input) {
    this->update(input);
  }

  void reset() {
    total = 0;
    failed = 0;
  }

  int size() const { return this->total; }

  explicit operator int() const { return this->failed; }

  int getFailed() const { return this->failed; }
  bool hasFailed() const { return this->failed != 0; }
  void addFailure(int f = 1) { failed += f; }

  double getRatio() const { return failed / static_cast<double>(total); }

   friend std::ostream &operator<<(ostream &stream, const Stats &stats) {
     return stream << stats.total;
   }
};

inline const string passed_str{"[ PASSED ]"};
inline const string failed_str{"[~FAILED~]"};

inline string
gen_framed(const string &message, size_t width = 80, char frame = '#') {

  string result{string(width, frame) + "\n"};
  string frame_string = string(3, frame);

  result += str_frame(message, width, frame_string, frame_string);

  return result + "\n" + string(width, frame);
}

inline string gen_pretty(const string &message, size_t width = 80) {
  if (width % 2)
    ++width;

  string frame = string(width / 2, '<') + string(width / 2, '>');
  string result{frame};
  result += "\n" + str_frame(message, width, "<<<", ">>>");

  return result + "\n" + frame;
}

inline string gen_summary(const Stats &stats, string type = "Evaluation",
        bool framed = false) {
  sstream message;

  message << type;

  if (stats.getFailed())
    message << " failed in " << stats.getFailed() << "/" << stats.size() << " ("
            << std::setprecision(5) << 100 * stats.getRatio() << "%) cases!";
  else
    message << " succeeded in all " << stats.size() << " cases!";

  return framed ? gen_framed(message.str()) : message.str();

}

} // namespace Evaluation

} //namespace AGizmo
