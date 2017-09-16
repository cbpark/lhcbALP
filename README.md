# lhcbALP

Codes to obtain the upper limits on the branching ratio of axion-like particles from the [LHCb](http://lhcb-public.web.cern.ch/lhcb-public/) experiment:

* [arXiv:1508.04094](https://arxiv.org/abs/1508.04094),
* [arXiv:1612.07818](https://arxiv.org/abs/1612.07818).

It has been used for analysis of [arXiv:1708.00021](https://arxiv.org/abs/1708.00021).

## Prerequisites

* C++ compiler supporting C++14 features,
* [ROOT](https://root.cern.ch): check whether `root-config` is in your `PATH`.

## Usage

Download [`LHCb-PAPER-2015-036-figures.zip`](https://cds.cern.ch/record/2045144/files/LHCb-PAPER-2015-036-figures.zip) and put `lhcb_2015_035.root` into [`data`](data) directory. Then, run `make` to get `bin/lhcb_bound_2015` and `bin/lhcb_bound_2016`.

* If building is too slow with GCC, it is recommended to use the [clang](https://clang.llvm.org) compiler.

```
CXX=clang++ make
```

The input must have three columns in units of `log10(m_a / MeV)`, `log10(f_a / GeV)`, and `log10(tau_a / ps)`, where `m_a` is the ALP mass, `f_a` is the decay constant, and `tau_a` is the lifetime. If the name of input file is `input.dat`, run

```
./bin/lhcb_bound_2015 input.dat output.dat
```

The `output.dat` will have four columns, where the first three are the same as the input and the last column corresponds to the upper limit extracted from `lhcb_2015_035.root`.

Similarly, `./bin/lhcb_bound_2016` will give you the upper limit extracted from Fig. 4 of [arXiv:1612.07818](https://arxiv.org/abs/1612.07818).
