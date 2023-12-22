"""Test the compilation of circuits."""

from __future__ import annotations

from pathlib import Path

import pytest
from qiskit import QuantumCircuit

from mqt import qmap
from mqt.qcec import verify


@pytest.fixture()
def example_circuit() -> QuantumCircuit:
    """Return a simple example circuit."""
    qc = QuantumCircuit(3)
    qc.h(0)
    qc.cx(0, 1)
    qc.cx(1, 2)
    qc.measure_all()
    return qc


def test_either_arch_or_calibration(example_circuit: QuantumCircuit) -> None:
    """Test that either arch or calibration must be provided."""
    with pytest.raises(ValueError, match="Either arch or calibration must be specified"):
        qmap.compile(example_circuit, arch=None, calibration=None)


@pytest.mark.parametrize(
    "arch",
    [
        "IBM_QX4",
        "IBM_QX5",
        "IBMQ_Yorktown",
        "IBMQ_London",
        "IBMQ_Bogota",
        "IBMQ_Tokyo",
        "Rigetti_Agave",
        "Rigetti_Aspen",
    ],
)
def test_available_architectures_str(example_circuit: QuantumCircuit, arch: str) -> None:
    """Test that the available architectures can be properly used."""
    example_circuit_mapped, results = qmap.compile(example_circuit, arch=arch)
    assert results.timeout is False
    assert results.mapped_circuit

    result = verify(example_circuit, example_circuit_mapped)
    assert result.considered_equivalent() is True


# test that all available architecture enumerations can be properly used
@pytest.mark.parametrize(
    "arch",
    [
        qmap.Arch.IBM_QX4,
        qmap.Arch.IBM_QX5,
        qmap.Arch.IBMQ_Yorktown,
        qmap.Arch.IBMQ_London,
        qmap.Arch.IBMQ_Bogota,
        qmap.Arch.IBMQ_Tokyo,
        qmap.Arch.Rigetti_Agave,
        qmap.Arch.Rigetti_Aspen,
    ],
)
def test_available_architectures_enum(example_circuit: QuantumCircuit, arch: qmap.Arch) -> None:
    """Test that the available architecture enums can be properly used."""
    example_circuit_mapped, results = qmap.compile(example_circuit, arch=arch)
    assert results.timeout is False
    assert results.mapped_circuit

    result = verify(example_circuit, example_circuit_mapped)
    assert result.considered_equivalent() is True


def test_architecture_from_file(example_circuit: QuantumCircuit) -> None:
    """Test that architectures from files can be properly used."""
    with Path("test_architecture.arch").open("w+") as f:
        f.write("3\n0 1\n0 2\n1 2\n")

    example_circuit_mapped, results = qmap.compile(example_circuit, arch="test_architecture.arch")
    assert results.timeout is False
    assert results.mapped_circuit

    result = verify(example_circuit, example_circuit_mapped)
    assert result.considered_equivalent() is True


def test_architecture_from_python(example_circuit: QuantumCircuit) -> None:
    """Test that architectures from python can be properly used."""
    arch = qmap.Architecture(3, {(0, 1), (0, 2), (1, 2)})
    example_circuit_mapped, results = qmap.compile(example_circuit, arch=arch)
    assert results.timeout is False
    assert results.mapped_circuit

    result = verify(example_circuit, example_circuit_mapped)
    assert result.considered_equivalent() is True


def test_calibration_from_file(example_circuit: QuantumCircuit) -> None:
    """Test that calibrations from files can be properly used."""
    with Path("test_calibration.cal").open("w+") as f:
        f.write("Header\n")
        f.write('Q0,0,0,0,1e-2,1e-4,"0_1: 1e-2, 0_2: 1e-2"\n')
        f.write('Q1,0,0,0,1e-2,1e-4,"1_2: 1e-2"\n')
        f.write("Q2,0,0,0,1e-2,1e-4, \n")

    example_circuit_mapped, results = qmap.compile(example_circuit, arch=None, calibration="test_calibration.cal")
    assert results.timeout is False
    assert results.mapped_circuit

    result = verify(example_circuit, example_circuit_mapped)
    assert result.considered_equivalent() is True


def test_parameters(example_circuit: QuantumCircuit) -> None:
    """Test that parameters to compile are properly parsed and passed to the backend."""
    properties = qmap.Architecture.Properties()
    properties.set_single_qubit_error(0, "x", 0.01)
    properties.set_single_qubit_error(1, "x", 0.01)
    properties.set_single_qubit_error(2, "x", 0.01)
    properties.set_two_qubit_error(0, 1, 0.02, "cx")
    properties.set_two_qubit_error(1, 0, 0.02, "cx")
    properties.set_two_qubit_error(1, 2, 0.02, "cx")
    properties.set_two_qubit_error(2, 1, 0.02, "cx")
    arch = qmap.Architecture(3, {(0, 1), (1, 0), (1, 2), (2, 1)}, properties)
    _, results = qmap.compile(
        example_circuit,
        arch=arch,
        method="exact",
        encoding="commander",
        commander_grouping="fixed3",
        use_bdd=False,
        swap_reduction="coupling_limit",
        include_WCNF=False,
        use_subsets=True,
        subgraph=None,
        add_measurements_to_mapped_circuit=True,
    )
    assert results.configuration.method == qmap.Method.exact
    assert results.configuration.encoding == qmap.Encoding.commander
    assert results.configuration.commander_grouping == qmap.CommanderGrouping.fixed3
    assert results.configuration.use_bdd is False
    assert results.configuration.swap_reduction == qmap.SwapReduction.coupling_limit
    assert results.configuration.include_WCNF is False
    assert results.configuration.use_subsets is True
    assert results.configuration.subgraph == set()
    assert results.configuration.add_measurements_to_mapped_circuit is True

    with qmap.visualization.SearchVisualizer() as visualizer:
        _, results = qmap.compile(
            example_circuit,
            arch=arch,
            method="heuristic",
            consider_fidelity=False,
            initial_layout="dynamic",
            iterative_bidirectional_routing_passes=1,
            layering="individual_gates",
            automatic_layer_splits_node_limit=5000,
            lookaheads=15,
            lookahead_factor=0.5,
            use_teleportation=True,
            teleportation_fake=False,
            teleportation_seed=0,
            pre_mapping_optimizations=True,
            post_mapping_optimizations=True,
            verbose=True,
            debug=True,
            visualizer=visualizer,
        )
        assert results.configuration.method == qmap.Method.heuristic
        assert results.configuration.consider_fidelity is False
        assert results.configuration.initial_layout == qmap.InitialLayout.dynamic
        assert results.configuration.iterative_bidirectional_routing is True
        assert results.configuration.iterative_bidirectional_routing_passes == 1
        assert results.configuration.layering == qmap.Layering.individual_gates
        assert results.configuration.automatic_layer_splits is True
        assert results.configuration.automatic_layer_splits_node_limit == 5000
        assert results.configuration.lookaheads == 15
        assert results.configuration.lookahead is True
        assert results.configuration.lookahead_factor == 0.5
        assert results.configuration.use_teleportation is True
        assert results.configuration.teleportation_fake is False
        assert results.configuration.teleportation_seed == 0
        assert results.configuration.pre_mapping_optimizations is True
        assert results.configuration.post_mapping_optimizations is True
        assert results.configuration.verbose is True
        assert results.configuration.debug is True
        assert results.configuration.data_logging_path == visualizer.data_logging_path

    _, results = qmap.compile(
        example_circuit,
        arch=arch,
        method="heuristic",
        consider_fidelity=True,
        initial_layout="identity",
        iterative_bidirectional_routing_passes=None,
        layering="disjoint_qubits",
        automatic_layer_splits_node_limit=None,
        lookaheads=None,
        use_teleportation=False,
        pre_mapping_optimizations=False,
        post_mapping_optimizations=False,
        verbose=False,
        debug=False,
    )
    assert results.configuration.method == qmap.Method.heuristic
    assert results.configuration.consider_fidelity is True
    assert results.configuration.initial_layout == qmap.InitialLayout.identity
    assert results.configuration.iterative_bidirectional_routing is False
    assert results.configuration.layering == qmap.Layering.disjoint_qubits
    assert results.configuration.automatic_layer_splits is False
    assert results.configuration.lookaheads == 0
    assert results.configuration.lookahead is False
    assert results.configuration.use_teleportation is False
    assert results.configuration.pre_mapping_optimizations is False
    assert results.configuration.post_mapping_optimizations is False
    assert results.configuration.verbose is False
    assert results.configuration.debug is False
    assert not results.configuration.data_logging_path
