//                      ┌─────────┐┌─────────┐┌──────────┐
// q_0: ────────────────┤         ├┤ Rz(π/4) ├┤          ├──────
//                      |         |├─────────┤|          |
// q_1: ──■──■──────────┤         ├┤ Rz(π/4) ├┤          ├─■────
//        │  │          |         |├─────────┤|          | │
// q_2: ──■──┼──■───────┤         ├┤ Rz(π/4) ├┤          ├─■────
//           │  │       |         |└─────────┘|          |
// q_3: ──■──┼──┼───────┤ Ry(π/2) ├───────────┤ Ry(-π/2) ├─■────
//        │  │  │       |         |           |          | │
// q_4: ──■──┼──┼──■────┤         ├───────────┤          ├─┼──■─
//           │  │  │    |         |           |          | │  │
// q_5: ─────┼──┼──┼──■─┤         ├───────────┤          ├─■──■─
//           │  │  │  │ |         |           |          |
// q_6: ──■──■──┼──┼──┼─┤         ├───────────┤          ├──────
//        │     │  │  │ |         |           |          |
// q_7: ──■─────■──■──■─┤         ├───────────┤          ├──────
//                      └─────────┘           └──────────┘
OPENQASM 2.0;
include "qelib1.inc";
qreg q[8];
cz q[1], q[2];
cz q[1], q[6];
cz q[2], q[7];
cz q[3], q[4];
cz q[4], q[7];
cz q[5], q[7];
cz q[6], q[7];
ry(1.5707963267949) q;
rz(0.785398163397448) q[0];
rz(0.785398163397448) q[1];
rz(0.785398163397448) q[2];
ry(-1.5707963267949) q;
cz q[3], q[5];
cz q[4], q[5];
cz q[1], q[2];
