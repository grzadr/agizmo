#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace AGizmo::Logging {

using steady_time_point = std::chrono::time_point<std::chrono::steady_clock>;
using steady_duration = std::chrono::duration<double>;
using sstream = std::stringstream;
using std::ostream;

inline std::string system_now() {
  sstream output;
  std::time_t time =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  output << "[" << std::put_time(std::localtime(&time), "%F %a %T") << "] ";
  return output.str();
}

class Timer {
public:
  static steady_time_point now() { return std::chrono::steady_clock::now(); }

  Timer() { reset(); }
  Timer(steady_time_point point) { reset(point); }

  void reset(steady_time_point point = Timer::now()) {
    this->end = steady_time_point{};
    this->elapsed = steady_duration{};
    this->start = point;
  }

  steady_duration mark(steady_time_point point = Timer::now()) {
    this->end = point;
    this->elapsed = end - start;
    return elapsed;
  }

  steady_time_point getStart() const { return this->start; }
  steady_time_point getEnd() const { return this->end; }
  steady_duration getElapsed() const { return this->elapsed; }

  auto getSeconds() const {
    return std::chrono::duration_cast<std::chrono::seconds>(this->elapsed)
        .count();
  }

  auto getMinutes() const {
    return std::chrono::duration_cast<std::chrono::minutes>(this->elapsed)
        .count();
  }

  auto getHours() const {
    return std::chrono::duration_cast<std::chrono::hours>(this->elapsed)
        .count();
  }

  auto getMili() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(this->elapsed)
        .count();
  }

  auto str() const {
    sstream output;

    auto hours = this->getHours();
    auto minutes = this->getMinutes() % 60;
    auto seconds = this->getSeconds() % 60;
    auto mili = this->getMili() % 1000;

    output << std::setw(2) << std::setfill('0') << hours << "h:" << std::setw(2)
           << std::setfill('0') << minutes << "m:" << std::setw(2)
           << std::setfill('0') << seconds << "s." << std::setw(3)
           << std::setfill('0') << mili;

    return output.str();
  }

  friend ostream &operator<<(ostream &stream, const Timer &item) {
    return stream << item.str();
  }

private:
  steady_time_point start{};
  steady_time_point end{};
  steady_duration elapsed{};
};

} // namespace AGizmo::Logging

