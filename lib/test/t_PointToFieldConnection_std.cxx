//                                               -*- C++ -*-
/**
 *  @brief The test file of class PointToFieldConnection for standard methods
 *
 *  Copyright 2005-2020 Airbus-EDF-IMACS-ONERA-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "openturns/OT.hxx"
#include "openturns/OTtestcode.hxx"

using namespace OT;
using namespace OT::Test;

int main(int, char *[])
{
  TESTPREAMBLE;
  OStream fullprint(std::cout);

  try
  {
    // Create a KarhunenLoeveResult
    Mesh mesh(IntervalMesher(Indices(1, 9)).build(Interval(-1.0, 1.0)));
    AbsoluteExponential cov1D(Point(1, 1.0));
    KarhunenLoeveP1Algorithm algo(mesh, cov1D, 0.0);
    algo.run();
    KarhunenLoeveResult result(algo.getResult());
    KarhunenLoeveLifting lifting(result);
    // Construction based on a Function followed by a PointToFieldFunction
    {
      UnsignedInteger dimension = lifting.getInputDimension();
      SymbolicFunction function(Description::BuildDefault(dimension, "x"), Description::BuildDefault(dimension, "x"));
      /* Create an instance */
      PointToFieldConnection myFunc(lifting, function);

      fullprint << "myFunc=" << myFunc << std::endl;
      /* Get the input and output description */
      fullprint << "myFunc input description=" << myFunc.getInputDescription() << std::endl;
      fullprint << "myFunc output description=" << myFunc.getOutputDescription() << std::endl;
      /* Get the input and output dimension */
      fullprint << "myFunc input dimension=" << myFunc.getInputDimension() << std::endl;
      fullprint << "myFunc output dimension=" << myFunc.getOutputDimension() << std::endl;
      /* Connection on a point */
      Point point(myFunc.getInputDimension(), 1.0);
      fullprint << "point=" << point << std::endl;
      fullprint << "myFunc(point)=" << myFunc(point) << std::endl;
      /* Get the number of calls */
      fullprint << "called " << myFunc.getCallsNumber() << " times" << std::endl;
    }
    // Construction based on a PointToFieldFunction followed by a FieldToPointFunction
    {
      ValueFunction fieldFunction(SymbolicFunction("x", "x"), mesh);
      /* Create an instance */
      PointToFieldConnection myFunc(fieldFunction, lifting);

      fullprint << "myFunc=" << myFunc << std::endl;
      /* Get the input and output description */
      fullprint << "myFunc input description=" << myFunc.getInputDescription() << std::endl;
      fullprint << "myFunc output description=" << myFunc.getOutputDescription() << std::endl;
      /* Get the input and output dimension */
      fullprint << "myFunc input dimension=" << myFunc.getInputDimension() << std::endl;
      fullprint << "myFunc output dimension=" << myFunc.getOutputDimension() << std::endl;
      /* Connection on a point */
      Point point(myFunc.getInputDimension(), 1.0);
      fullprint << "point=" << point << std::endl;
      fullprint << "myFunc(point)=" << myFunc(point) << std::endl;
      /* Get the number of calls */
      fullprint << "called " << myFunc.getCallsNumber() << " times" << std::endl;
    }
  } // try
  catch (TestFailed & ex)
  {
    std::cerr << ex << std::endl;
    return ExitCode::Error;
  }


  return ExitCode::Success;
}
