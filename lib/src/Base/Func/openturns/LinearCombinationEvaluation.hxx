//                                               -*- C++ -*-
/**
 *  @brief The evaluation part of linear combination of polynomials
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
#ifndef OPENTURNS_LINEARCOMBINATIONEVALUATION_HXX
#define OPENTURNS_LINEARCOMBINATIONEVALUATION_HXX

#include "openturns/EvaluationImplementation.hxx"
#include "openturns/Collection.hxx"
#include "openturns/PersistentCollection.hxx"
#include "openturns/Function.hxx"
#include "openturns/Evaluation.hxx"

BEGIN_NAMESPACE_OPENTURNS

/**
 * @class LinearCombinationEvaluation
 *
 * The evaluation part of linear combination of polynomials
 */

class OT_API LinearCombinationEvaluation
  : public EvaluationImplementation
{
  CLASSNAME
public:

  typedef Collection<Function>                              FunctionCollection;
  typedef PersistentCollection<Function>                    FunctionPersistentCollection;

  /** Default constructor */
  LinearCombinationEvaluation();

  /** Parameter constructor */
  LinearCombinationEvaluation(const FunctionCollection & functionsCollection,
                              const Point & coefficients);

  /** Virtual constructor */
  virtual LinearCombinationEvaluation * clone() const;

  /** String converter */
  String __repr__() const;
  String __str__(const String & offset = "") const;

  /** Evaluation operator */
  Point operator () (const Point & inP) const;
  Sample operator () (const Sample & inS) const;

  /** Coefficients accessor */
  Point getCoefficients() const;

  /** Functions accessor */
  FunctionCollection getFunctionsCollection() const;
  void setFunctionsCollectionAndCoefficients(const FunctionCollection & functionsCollection,
      const Point & coefficients);

  /** Input dimension accessor */
  UnsignedInteger getInputDimension() const;

  /** Output dimension accessor */
  UnsignedInteger getOutputDimension() const;

  /** Gradient according to the marginal parameters */
  Matrix parameterGradient(const Point & inP) const;

  /** Parameters value accessor */
  void setParameter(const Point & parameter);
  Point getParameter() const;

  /** Parameters description accessor */
  virtual Description getParameterDescription() const;

  /** Get the i-th marginal function */
  Evaluation getMarginal(const UnsignedInteger i) const;

  /** Get the function corresponding to indices components */
  Evaluation getMarginal(const Indices & indices) const;

  /** Linearity accessors */
  Bool isLinear() const;
  Bool isLinearlyDependent(const UnsignedInteger index) const;

  /** Method save() stores the object through the StorageManager */
  void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(Advocate & adv);


protected:

private:
  // Make the gradient and the hessian friend classes of the evaluation in order to share the functions and the coefficients
  friend class LinearCombinationGradient;
  friend class LinearCombinationHessian;
  friend struct LinearCombinationEvaluationPointFunctor;

  // The functions of the combination
  FunctionPersistentCollection functionsCollection_;

  // The coefficients of the combination
  Point coefficients_;

  // The flag telling if the combination reduces to zero
  Bool isZero_;

} ; /* class LinearCombinationEvaluation */


END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_LINEARCOMBINATIONEVALUATION_HXX */
