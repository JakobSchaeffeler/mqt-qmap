#include "Architecture.hpp"

#include "gtest/gtest.h"

class TestArchitecture: public testing::TestWithParam<std::string> {
protected:
    std::string test_architecture_dir = "./architectures/";
    std::string test_calibration_dir  = "./calibration/";

    void SetUp() override {
        using namespace dd::literals;
    }
};

INSTANTIATE_TEST_SUITE_P(
        Architecture, TestArchitecture,
        testing::Values(
                "ibm_qx4.arch",
                "ibmq_casablanca.arch",
                "ibmq_london.arch",
                "ibmq_london.csv"));

TEST_P(TestArchitecture, QubitMap) {
    auto&             arch_name = GetParam();
    Architecture      arch{};
    std::stringstream ss{};
    if (arch_name.find(".arch") != std::string::npos) {
        ss << test_architecture_dir << arch_name;
        arch.loadCouplingMap(ss.str());
    } else {
        ss << test_calibration_dir << arch_name;
        arch.loadCalibrationData(ss.str());
    }

    EXPECT_EQ(Architecture::getQubitList(arch.getCouplingMap()).size(), arch.getNqubits());
}
TEST_P(TestArchitecture, GetAllConnectedSubsets) {
    auto&             arch_name = GetParam();
    Architecture      arch{};
    std::stringstream ss{};
    if (arch_name.find(".arch") != std::string::npos) {
        ss << test_architecture_dir << arch_name;
        arch.loadCouplingMap(ss.str());
    } else {
        ss << test_calibration_dir << arch_name;
        arch.loadCalibrationData(ss.str());
    }

    EXPECT_EQ(arch.getAllConnectedSubsets(arch.getNqubits()).size(), 1);
    EXPECT_EQ(arch.getAllConnectedSubsets(1).size(), arch.getNqubits());
}
TEST_P(TestArchitecture, GetHighestFidelity) {
    auto&             arch_name = GetParam();
    Architecture      arch{};
    std::stringstream ss{};
    if (arch_name.find(".arch") != std::string::npos) {
        ss << test_architecture_dir << arch_name;
        arch.loadCouplingMap(ss.str());
    } else {
        ss << test_calibration_dir << arch_name;
        arch.loadCalibrationData(ss.str());
    }
    CouplingMap cm{};

    arch.getHighestFidelityCouplingMap(arch.getNqubits(), cm);

    EXPECT_EQ(cm, arch.getCouplingMap());

    arch.getHighestFidelityCouplingMap(1, cm);

    CouplingMap expected{};

    if (arch_name.find(".csv") == std::string::npos) {
        EXPECT_EQ(cm, arch.getCouplingMap());
    } else {
        EXPECT_NE(cm, arch.getCouplingMap());
    }
}
TEST_P(TestArchitecture, ReducedMaps) {
    auto&             arch_name = GetParam();
    Architecture      arch{};
    std::stringstream ss{};
    if (arch_name.find(".arch") != std::string::npos) {
        ss << test_architecture_dir << arch_name;
        arch.loadCouplingMap(ss.str());
    } else {
        ss << test_calibration_dir << arch_name;
        arch.loadCalibrationData(ss.str());
    }

    std::vector<CouplingMap> cms;

    arch.getReducedCouplingMaps(1, cms);

    EXPECT_EQ(cms.size(), arch.getNqubits());
}

TEST(TestArchitecture, ConnectedTest) {
    Architecture architecture{};
    CouplingMap  cm{};

    cm.emplace(std::make_pair(0, 1));
    cm.emplace(std::make_pair(1, 2));
    cm.emplace(std::make_pair(2, 3));
    cm.emplace(std::make_pair(3, 4));
    cm.emplace(std::make_pair(4, 0));

    architecture.loadCouplingMap(5, cm);

    std::vector<CouplingMap> cms;

    architecture.getReducedCouplingMaps(2, cms);

    EXPECT_EQ(cms.size(), 5);

    architecture.getReducedCouplingMaps(4, cms);

    EXPECT_EQ(cms.size(), 5);
}

TEST(TestArchitecture, FidelityTest) {
    Architecture                               architecture{};
    CouplingMap                                cm{};
    std::vector<Architecture::CalibrationData> calibrationData{};

    Architecture::CalibrationData data{};
    data.qubit                = 0;
    data.singleQubitErrorRate = 0.9;
    data.cnotErrors.emplace(std::make_pair(0, 1), 0.8);
    calibrationData.push_back(data);
    data.qubit                = 1;
    data.singleQubitErrorRate = 0.9;
    data.cnotErrors.emplace(std::make_pair(1, 0), 0.8);
    data.cnotErrors.emplace(std::make_pair(1, 2), 0.7);
    calibrationData.push_back(data);
    data.qubit                = 2;
    data.singleQubitErrorRate = 0.9;
    data.cnotErrors.emplace(std::make_pair(2, 1), 0.7);
    data.cnotErrors.emplace(std::make_pair(2, 3), 0.6);
    calibrationData.push_back(data);
    data.qubit                = 3;
    data.singleQubitErrorRate = 0.9;
    data.cnotErrors.emplace(std::make_pair(3, 2), 0.6);
    calibrationData.push_back(data);

    architecture.loadCalibrationData(calibrationData);

    architecture.getHighestFidelityCouplingMap(2, cm);

    std::vector<unsigned short> highestFidelity{};
    highestFidelity.push_back(2);
    highestFidelity.push_back(3);

    auto qubitList = Architecture::getQubitList(cm);

    ASSERT_TRUE((qubitList.size() == highestFidelity.size() &&
                 std::equal(qubitList.begin(), qubitList.end(), highestFidelity.begin())));
}

TEST(TestArchitecture, FullyConnectedTest) {
    CouplingMap cm = getFullyConnectedMap(3);

    ASSERT_TRUE(cm.size() == 3 * 2);
}