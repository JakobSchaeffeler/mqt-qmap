//
// This file is part of the MQT QMAP library released under the MIT license.
// See README.md or go to https://github.com/cda-tum/qmap for more information.
//

#pragma once

#include "QuantumComputation.hpp"
#include "cliffordsynthesis/Configuration.hpp"
#include "cliffordsynthesis/Results.hpp"
#include "cliffordsynthesis/Tableau.hpp"
#include "cliffordsynthesis/encoding/SATEncoder.hpp"

#include <cstddef>
#include <optional>
#include <sstream>

namespace cs {

class CliffordSynthesizer {
  using EncoderConfig = encoding::SATEncoder::Configuration;

public:
  CliffordSynthesizer() = default;
  CliffordSynthesizer(Tableau initial, Tableau target)
      : initialTableau(std::move(initial)), targetTableau(std::move(target)) {}
  explicit CliffordSynthesizer(Tableau target)
      : initialTableau(target.getQubitCount(), target.hasDestabilizers()),
        targetTableau(std::move(target)) {}
  CliffordSynthesizer(Tableau initial, qc::QuantumComputation& qc)
      : initialTableau(std::move(initial)),
        targetTableau(qc, 0, std::numeric_limits<std::size_t>::max(),
                      initialTableau.hasDestabilizers()),
        initialCircuit(std::make_shared<qc::QuantumComputation>(qc.clone())),
        results(qc, targetTableau) {}
  explicit CliffordSynthesizer(qc::QuantumComputation& qc,
                               const bool              useDestabilizers = false)
      : initialTableau(qc.getNqubits(), useDestabilizers),
        targetTableau(qc, 0, std::numeric_limits<std::size_t>::max(),
                      useDestabilizers),
        initialCircuit(std::make_shared<qc::QuantumComputation>(qc.clone())),
        results(qc, targetTableau) {}

  virtual ~CliffordSynthesizer() = default;

  void synthesize(const Configuration& config = {});

  [[nodiscard]] Results& getResults() { return results; };

  void initResultCircuitFromResults() {
    std::stringstream ss;
    ss << results.getResultCircuit();
    resultCircuit = std::make_unique<qc::QuantumComputation>();
    resultCircuit->import(ss, qc::Format::OpenQASM);
  }

  [[nodiscard]] qc::QuantumComputation& getResultCircuit() {
    initResultCircuitFromResults();
    return *resultCircuit;
  };
  [[nodiscard]] Tableau& getResultTableau() {
    std::stringstream ss;
    ss << results.getResultTableau();
    resultTableau.fromString(ss.str());
    return resultTableau;
  }

protected:
  Tableau                                 initialTableau{};
  Tableau                                 targetTableau{};
  std::shared_ptr<qc::QuantumComputation> initialCircuit{};

  Configuration configuration{};

  Results                                 results{};
  std::shared_ptr<qc::QuantumComputation> resultCircuit{};
  Tableau                                 resultTableau{};
  std::size_t                             solverCalls{};

  static bool requiresMultiGateEncoding(const TargetMetric metric) {
    return metric == TargetMetric::Depth;
  }

  void determineInitialTimestepLimit(EncoderConfig& config);
  std::pair<std::size_t, std::size_t> determineUpperBound(EncoderConfig config);
  void                                runMaxSAT(const EncoderConfig& config);
  Results                             callSolver(const EncoderConfig& config);

  void minimizeGatesFixedDepth(EncoderConfig config);

  void gateOptimalSynthesis(EncoderConfig config, std::size_t lower,
                            std::size_t upper);
  void depthOptimalSynthesis(EncoderConfig config, std::size_t lower,
                             std::size_t upper);
  void depthHeuristicSynthesis();
  void twoQubitGateOptimalSynthesis(EncoderConfig config, std::size_t lower,
                                    std::size_t upper);

  void minimizeTwoQubitGatesFixedGateCount(std::size_t   gateCount,
                                           EncoderConfig config);
  void minimizeGatesFixedTwoQubitGateCount(EncoderConfig config);

  template <typename T>
  void runBinarySearch(T& value, T lowerBound, T upperBound,
                       const EncoderConfig& config) {
    INFO() << "Running binary search in range [" << lowerBound << ", "
           << upperBound << ")";

    while (lowerBound != upperBound) {
      value = (lowerBound + upperBound) / 2;
      INFO() << "Trying value " << value << " in range [" << lowerBound << ", "
             << upperBound << ")";
      const auto r = callSolver(config);
      updateResults(configuration, r, results);
      if (r.sat()) {
        upperBound = value;
        INFO() << "Found solution. New upper bound is " << upperBound;
      } else {
        lowerBound = value + 1;
        INFO() << "No solution found. New lower bound is " << lowerBound;
      }
    }
    INFO() << "Found optimum: " << lowerBound;
  }

  template <typename T>
  void runLinearSearch(T& value, T lowerBound, T upperBound,
                       const EncoderConfig& config) {
    INFO() << "Running linear search in range [" << lowerBound << ", "
           << upperBound << ")";

    if (upperBound == 0U) {
      upperBound = std::numeric_limits<std::size_t>::max();
    }
    for (value = lowerBound; value < upperBound; ++value) {
      INFO() << "Trying value " << value << " in range [" << lowerBound << ", "
             << upperBound << ")";
      const auto r = callSolver(config);
      updateResults(configuration, r, results);
      if (r.sat()) {
        INFO() << "Found optimum " << value;
        return;
      }
      INFO() << "No solution found. Trying next value.";
    }
    INFO() << "No solution found in given interval.";
  }

  static std::shared_ptr<qc::QuantumComputation>
  synthesizeSubcircuit(const std::shared_ptr<qc::QuantumComputation>& qc,
                       std::size_t begin, std::size_t end,
                       const Configuration& config);
  static void updateResults(const Configuration& config,
                            const Results& newResults, Results& currentResults);
};

} // namespace cs
