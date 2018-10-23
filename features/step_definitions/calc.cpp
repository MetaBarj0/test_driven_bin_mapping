#include <gtest/gtest.h>
#include <cucumber-cpp/autodetect.hpp>

using cucumber::ScenarioScope;

#include <vector>
#include <numeric>

struct Calculator
{
  void push( double v ) { values.push_back( v ); }
  double add() const noexcept
  {
      return std::accumulate( std::cbegin( values ),
                              std::cend( values ), 0.0 );
  }

  std::vector< double > values;
};

struct CalcCtx {
    Calculator calc;
    double result;
};

GIVEN("^I have entered (\\d+) into the calculator$") {
    REGEX_PARAM(double, n);
    ScenarioScope<CalcCtx> context;

    context->calc.push(n);
}

WHEN("^I press add") {
    ScenarioScope<CalcCtx> context;

    context->result = context->calc.add();
}

THEN("^the result should be (.*) on the screen$") {
    REGEX_PARAM(double, expected);
    ScenarioScope<CalcCtx> context;

    EXPECT_EQ(expected, context->result);
}
